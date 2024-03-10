#ifndef MOMENTUMGENERATORALG_H
#define MOMENTUMGENERATORALG_H


// includes
#include <cmath>
#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/RndmGenerators.h"
#include "Gaudi/Property.h"
#include "Pythia8/Pythia.h"

/* Simple Algorithm for 4momentum generation. P magnitude is gauss distributed, direction is isotropic */

class MomentumGeneratorAlg : public Algorithm{
public:
  MomentumGeneratorAlg(const std::string& name, ISvcLocator* pSvcLocator);
  // simplified way to put something somewhere
  StatusCode put(IDataProviderSvc* s, const std::string& path, DataObject* pObj);
  StatusCode initialize() override;
  StatusCode execute() override;
  StatusCode finalize() override;
private:
  // distribution properties
  Gaudi::Property<double> mean_p{this, "min_p", 100.0};
  Gaudi::Property<double> sigma_p{this, "max_p", 1.0};
  Gaudi::Property<double> mass{this, "mass", 939};
  double generate_p();
  double generate_theta();
  double generate_phi();
  Pythia8::Pythia pythia;
};

#endif // MOMENTUMGENERATORALG_H