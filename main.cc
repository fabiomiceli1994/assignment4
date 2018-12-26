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
    y = scheme.evolve(y,t,tau,model);
    t += tau;
  }
  std::cout << "Finished time integration at t=" << t << std::endl;
  return y;
}

int main(int argc, char** argv)
{
  if ( argc<4 || atoi(argv[1])<2 || atof(argv[2])<0 || ( atoi(argv[3])!=0 && atoi(argv[3])!=1 && atoi(argv[3])!=2 ) )
  {
    std::cerr << "Usage: " << std::endl
			  << "  " << argv[0] << " <Nx> <kappa> <scheme>" << std::endl << std::endl
			  << "where" << std::endl
			  << "  <Nx>       spatial resolution (int) -- required to be >2 " << std::endl
			  << "  <kappa>    diffusivity (double) -- only takes positive values" << std::endl
			  << "  <scheme>   scheme index (int) -- only takes values in {0, 1, 2}" << std::endl;
    return 1;
  }
  // read parameters as command line arguments
  int N = atoi(argv[1]); //if a float is inserted the program takes its integerpart as an input
  double kappa = atof(argv[2]);
  int schemeNumber = atoi(argv[3]);

  HeatEquation model(N, kappa);

  std::vector<DIRK *> schemes; // Vector of schemes
  schemes.push_back(new FE());
  schemes.push_back(new BE());
  schemes.push_back(new Heun3());

  double tau = 1e-3; //temporal integration step

  // example invocation of solver
  Vector y=solve(model,*schemes[schemeNumber],tau);
  y.push_back(0);
  y.insert(y.begin(), 0);
  y.toFile("HE_kappa_" + std::to_string(kappa) + "_N_" + std::to_string(N) + "_scheme_" + std::to_string(schemeNumber) + ".dat");

  for (const auto& r : (schemes)) //freeing memory
  {
    delete r;
  }

  return 0;
}
