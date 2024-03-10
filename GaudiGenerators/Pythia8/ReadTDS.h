#ifndef READTDSALG_H
#define READTDSALG_H

// includes
#include "GaudiKernel/Algorithm.h"

/* Simple Algorithm for retreiving Pythia output from TDS */
class ReadTDSAlg : public Algorithm{
public:
  ReadTDSAlg(const std::string& name, ISvcLocator* pSvcLocator);
  StatusCode initialize() override;
  StatusCode execute() override;
  StatusCode finalize() override;
private:
};


#endif // READTDSALG_H