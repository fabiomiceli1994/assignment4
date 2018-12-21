#ifndef MODELS_HH
#define MODELS_HH

#include "sparse.hh"

class HeatEquation
{
public:

  HeatEquation(int N, double kappa);
  
  Vector f(double t,const Vector &y) const;
  
  const SparseMatrix& df(double t,const Vector &y) const;
  
  double T() const;
  
  Vector y0() const;
  
  int N;

private:

  // persistent data
};

#endif // MODELS_HH
