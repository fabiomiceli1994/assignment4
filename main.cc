#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>

#include "models.hh"
#include "schemes.hh"

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

int main(int argc, char** argv)
{
  // read parameters as command line arguments
  int N = atoi(argv[1]);
  double kappa = atof(argv[2]);
  int schemeNumber = atof(argv[3]);

  HeatEquation model(N, kappa);

  std::vector<DIRK *> schemes; // Vector of schemes
  schemes.push_back(new FE());
  schemes.push_back(new BE());
  schemes.push_back(new Heun3());

  double tau = 1e-6;

  // example invocation of solver
  solve(model,*schemes[schemeNumber],tau).toFile("HE_kappa_" + std::to_string(kappa) + "_N_" + std::to_string(N) + "_scheme_" + std::to_string(schemeNumber) + ".dat");

  return 0;
}
