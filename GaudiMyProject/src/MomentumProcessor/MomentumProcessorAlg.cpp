
#include "MomentumProcessorAlg.h"
#include "FourMomentum.h"
#include "GaudiKernel/SmartDataPtr.h"

DECLARE_COMPONENT(MomentumProcessorAlg)

// constructor
MomentumProcessorAlg::MomentumProcessorAlg(const std::string& name, ISvcLocator* ploc) : Algorithm(name, ploc){}

// initialize
StatusCode MomentumProcessorAlg::initialize() {
  StatusCode status;
  m_ntuple = ntupleSvc()->book("/NTUPLES/FILE1/100", CLID_RowWiseTuple, "p_ntuple");
  if (m_ntuple) {
    status = m_ntuple->addItem("px", m_px);
    status = m_ntuple->addItem("py", m_py);
    status = m_ntuple->addItem("pz", m_pz);
  } else{
    return StatusCode::FAILURE;
  }
  return status;
}

// execute
StatusCode MomentumProcessorAlg::execute() {
  StatusCode status;
  // we don't get raw pointer, so we don't care about it's deletion
  SmartDataPtr<FourMomentum> fm(eventSvc(), "/Event/1");
  if(!fm){
    StatusCode::FAILURE;
  }
  //info() << fm->GetM() << endmsg;
  m_px = fm->GetPx();
  m_py = fm->GetPy();
  m_pz = fm->GetPz();
  status = m_ntuple->write();
  if (!status.isSuccess()) {
    error() << "Cannot fill NTuple" << endmsg;
    return status;
  }
  return StatusCode::SUCCESS;
}

// finalize
StatusCode MomentumProcessorAlg::finalize() {
  return StatusCode::SUCCESS;
}