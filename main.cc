#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>
#include <time.h>

#include "models.hh"
#include "schemes.hh"

template <class Model>
Vector solve(const Model &model, const DIRK &scheme, double tau, int schemeNumber, unsigned int &count)
{
  int n=1; // needed for the printing
  double timeStart = clock(); //this is for initialising the target wallclock
  Vector y=model.y0();
  double t=0;
  while ( model.T()-t >= tau )
  {
    y =  scheme.evolve(y,t,tau,model,count);
    t += tau;
    if (y.maxNorm()>1 || (clock() - timeStart) / CLOCKS_PER_SEC >= 10) // time in seconds. Tarhget wallclock fixed as required
    {
      for(unsigned int m=0; m<6; ++m)
      {
        Vector dummy(model.N+2, 0.9);
        dummy.toFile("HE_k_" + std::to_string(model.kappa) + "_N_" + std::to_string(model.N) + "_tau_" + std::to_string(tau) + "_scheme_" + std::to_string(schemeNumber) + "_t_" + std::to_string(m) + ".dat");
      }
      std::cout << "Scheme " + std::to_string(schemeNumber) + " is unstable for N=" + std::to_string(model.N) + ", kappa=" + std::to_string(model.kappa) + ", tau=" + std::to_string(tau) << std::endl;
      break;
    }
    else
    {
      if (t == tau)
      {
        y.push_back(0);
        y.insert(y.begin(),0);
        y.toFile("HE_k_" + std::to_string(model.kappa) + "_N_" + std::to_string(model.N) + "_tau_" + std::to_string(tau) + "_scheme_" + std::to_string(schemeNumber) + "_t_0.dat");
        y.erase(y.begin()+model.N+1);
        y.erase(y.begin());
      }
      else if(std::abs(t - n*model.T()/5) <= tau)
      {
        y.push_back(0);
        y.insert(y.begin(),0);
        y.toFile("HE_k_" + std::to_string(model.kappa) + "_N_" + std::to_string(model.N) + "_tau_" + std::to_string(tau) + "_scheme_" + std::to_string(schemeNumber) + "_t_" + std::to_string(n) + ".dat");
        y.erase(y.begin()+model.N+1);
        y.erase(y.begin());
        n++;
      }
    }
  }
  std::cout << "Finished time integration at t=" << t << std::endl;
  return y;
}

int main(int argc, char** argv)
{
  if ( argc<5 || atoi(argv[1])<1 || atof(argv[2])<0 || ( atoi(argv[3])!=0 && atoi(argv[3])!=1 && atoi(argv[3])!=2 ) || atof(argv[4])<=0 )
  {
    std::cerr << "Usage: " << std::endl
			  << "  " << argv[0] << " <Nx> <kappa> <scheme> <tau>" << std::endl << std::endl
			  << "where" << std::endl
			  << "  <Nx>       spatial resolution (int) -- required to be >2 " << std::endl
			  << "  <kappa>    diffusivity (double) -- only takes positive values" << std::endl
			  << "  <scheme>   scheme index (int) -- FE=0, BE=1, Heun3=2" << std::endl
        << "  <tau>      temporal time step (double) -- only takes positive values" << std::endl;
    return 1;
  }
  // read parameters as command line arguments
  int N = atoi(argv[1]); //if a float is inserted the program takes its integer part as an input
  double kappa = atof(argv[2]);
  int schemeNumber = atoi(argv[3]);
  double tau = atof(argv[4]);

  HeatEquation model(N, kappa);

  std::vector<DIRK *> schemes; // Vector of schemes
  schemes.push_back(new FE());
  schemes.push_back(new BE());
  schemes.push_back(new Heun3());

  unsigned int count = 0; // counts the number of calls to f and df and gives an evaluation of perfomances

  // example invocation of solver
  Vector y=solve(model,*schemes[schemeNumber],tau,schemeNumber, count);

  //efficiency analysis through count of evaluations of calls to f and df
  std::cout << "Number of calls to f and df in scheme " << schemeNumber << " is " << count << std::endl;

  for (const auto& r : (schemes)) //freeing memory
  {
    delete r;
  }

  return 0;
}
