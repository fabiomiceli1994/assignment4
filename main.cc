#include <iostream>
#include <fstream>
#include <sstream>

#include "models.hh"
#include "schemes.hh"
#include "vector.hh"
#include "sparse.hh"

template <class Model>
Vector solve(const Model &model, const DIRK &scheme, double tau)
{
  Vector y=model.y0();
  double t=0;
  while ( std::abs(model.T()-t)>tau )
  {
    y =  scheme.evolve(y,t,tau,model);
    t += tau;
  }
  std::cout << "Finished time integration at t=" << t << std::endl;
  return y;
}

int main(int argc, char* argv[])
{
  // read parameters as command line arguments

  unsigned N = arg[0];
  unsigned kappa = 1.; 

  HeatEquation model(N, kappa);
  FE scheme;

  // example invocation of solver
  solve(model,*scheme,tau).toFile("out.dat");

  return 0;
}
