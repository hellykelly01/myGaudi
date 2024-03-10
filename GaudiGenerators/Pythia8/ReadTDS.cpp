#include "ReadTDS.h"
#include "Pythia8_i.h"
#include "GaudiKernel/SmartDataPtr.h"

DECLARE_COMPONENT(ReadTDSAlg)

// constructor
ReadTDSAlg::ReadTDSAlg(const std::string& name, ISvcLocator* ploc) : Algorithm(name, ploc){}

// initialize
StatusCode ReadTDSAlg::initialize() {
  return StatusCode::SUCCESS;
}

// execute
StatusCode ReadTDSAlg::execute() {
  StatusCode status;
  // we don't get raw pointer, so we don't care about it's deletion
  SmartDataPtr<Pythia8Event> ev(eventSvc(), "/Event/1");
  if(!ev){
    return StatusCode::FAILURE;
  }
  info() << ev->GetEvent().size() << endmsg;
  return StatusCode::SUCCESS;
}

// finalize
StatusCode ReadTDSAlg::finalize() {
  return StatusCode::SUCCESS;
}