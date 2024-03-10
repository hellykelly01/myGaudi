
#include "MomentumGenerotorAlg.h"
#include "FourMomentum.h"

DECLARE_COMPONENT(MomentumGeneratorAlg)

// constructor
MomentumGeneratorAlg::MomentumGeneratorAlg(const std::string& name, ISvcLocator* ploc) : Algorithm(name, ploc){}

// put
StatusCode MomentumGeneratorAlg::put(IDataProviderSvc* s, const std::string& path, DataObject* pObj) {
  StatusCode sc = s->registerObject( path, pObj );
  if (sc.isFailure()) { 
    error() << "Unable to register object " << path << endmsg; 
  }
  return sc;
}

// generate_p (gauss)

double MomentumGeneratorAlg::generate_p(){
  Rndm::Numbers gen(randSvc(), Rndm::Gauss(mean_p.value(), sigma_p.value()));
  double p = gen();
  if (p < 0){
    error() << "Generated p < 0" << endmsg;
  }
  return p;
}

// generate_theta (isotropic by cos(theta))

double MomentumGeneratorAlg::generate_theta(){
  Rndm::Numbers gen(randSvc(), Rndm::Flat(0.0, 1.0));
  return acos(1 - 2 * gen());
}

// generate_phi (isotropic)

double MomentumGeneratorAlg::generate_phi(){
  Rndm::Numbers gen(randSvc(), Rndm::Flat(0.0, 1.0));
  return gen() * 2 * M_PI;
}

// initialize
StatusCode MomentumGeneratorAlg::initialize() {
  info() << "MEAN P = " << mean_p.value() << endmsg;
  info() << "SIGMA P = " << sigma_p.value() << endmsg;
  info() << "MASS = " << mass.value() << endmsg;
  return StatusCode::SUCCESS;
}

// execute
StatusCode MomentumGeneratorAlg::execute() {
  // we don't have to delete fm in the end as we pass it to TES and TES will take care of it
  FourMomentum* fm = new FourMomentum();
  double p = generate_p();
  double theta = generate_theta();
  double phi = generate_phi();
  fm->SetMPThetaPhi(mass, p, theta, phi);
  // for some reason line below is not recommended
  // fm->SetMPThetaPhi(mass, generate_p(), generate_theta(), generate_phi());
  StatusCode sc = put(eventSvc(), "/Event/1", fm);
  if (sc.isFailure()){
    return sc;
  } 
  return StatusCode::SUCCESS;
}

// finalize
StatusCode MomentumGeneratorAlg::finalize() {
  return StatusCode::SUCCESS;
}