#include "FourMomentum.h"
#include <cmath>

FourMomentum::FourMomentum() : DataObject(){}

double FourMomentum::GetM() const{
  return std::sqrt(E_ * E_ - px_ * px_ - py_ * py_ - pz_ * pz_);
}

double FourMomentum::GetMomentum() const{
  return std::sqrt(px_ * px_ + py_ * py_ + pz_ * pz_);
}

double FourMomentum::GetE() const{
  return E_;
}

double FourMomentum::GetPx() const{
  return px_;
}

double FourMomentum::GetPy() const{
  return py_;
}

double FourMomentum::GetPz() const{
  return pz_;
}

void FourMomentum::CheckConsistency(double E, double px, double py, double pz){
  if (E * E < (px * px + py * py + pz * pz)){
    throw std::runtime_error("invalid FourMomentum arguments");
  }
}

void FourMomentum::SetEPxPyPz(double E, double px, double py, double pz){
  CheckConsistency(E, px, py, pz);
  E_ = E;
  px_ = px;
  py_ = py;
  pz_ = pz;
}

void FourMomentum::SetMPThetaPhi(double m, double p, double theta, double phi){
  E_ = sqrt(m * m + p * p);
  px_ = p * sin(theta) * cos(phi);
  py_ = p * sin(theta) * sin(phi);
  pz_ = p * cos(theta);
}

