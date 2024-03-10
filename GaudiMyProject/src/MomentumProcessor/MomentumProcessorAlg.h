#ifndef MOMENTUMPROCESSORALG_H
#define MOMENTUMPROCESSORALG_H

// includes
#include "GaudiKernel/Algorithm.h"
#include "FourMomentum.h"
#include "GaudiKernel/NTuple.h"

/* Simple Algorithm for retreiving 4momentums from TES and generating some root output*/
class MomentumProcessorAlg : public Algorithm{
public:
  MomentumProcessorAlg(const std::string& name, ISvcLocator* pSvcLocator);
  template<typename T> 
  StatusCode get(IDataProviderSvc* s, const std::string& path, T*& pObj);
  StatusCode initialize() override;
  StatusCode execute() override;
  StatusCode finalize() override;
private:
  NTuple::Tuple* m_ntuple{nullptr};
  NTuple::Item<double> m_px;
  NTuple::Item<double> m_py;
  NTuple::Item<double> m_pz;
};


// We have to cast DataObject to 4momentum (but there is another way to do it via SmartDataPtr)
template <typename T>
StatusCode MomentumProcessorAlg::get(IDataProviderSvc* s, const std::string& path, T*& pObj){
  DataObject* tmp;
  StatusCode sc = s->retrieveObject(path, tmp);
  if (sc.isFailure()) { 
    error() << "Unable to retreive object " << path << endmsg; 
    return sc;
  }

  try {
      pObj = dynamic_cast<T*> (tmp);
  } catch(...) {
    error() << "Unable to convert object " << path << endmsg;
    sc = StatusCode::FAILURE;
  }
  return sc;
}

#endif // MOMENTUMGENERATORALG_H