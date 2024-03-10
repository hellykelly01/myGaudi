#ifndef FOURMOMENTUM_H
#define FOURMOMENTUM_H

// includes
#include "GaudiKernel/DataObject.h"
#include <cmath>
#include <stdexcept>

// сlass definition

/* Simple 4momentum class, only setters and getters provided */
class FourMomentum : public DataObject{
public:
  FourMomentum();
  double GetM() const;
  double GetMomentum() const;
  double GetE() const;
  double GetPx() const;
  double GetPy() const;
  double GetPz() const; 
  void SetEPxPyPz(double E, double px, double py, double pz);
  void SetMPThetaPhi(double m, double p, double theta, double phi);
private:
  double E_ {0};
  double px_ {0};
  double py_ {0};
  double pz_ {0};
  void CheckConsistency(double E, double px, double py, double pz);
};

#endif // FOURMOMENTUM_H
