#ifndef SCHEMES_HH
#define SCHEMES_HH

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "vector.hh"
#include "sparse.hh"
#include "models.hh"

class DIRK
{
public:

  DIRK(int stages)
  : stages_(stages),
    a_(stages*stages), b_(stages), c_(stages)
  {
    for (int i=0;i<stages_;++i)
      for (int j=0;j<stages_;++j)
        a_[i*stages_+j] = 0.;
     // putting in forward Euler here (although we are not using them at the moment)
     b_[0] = 1.;
     c_[0] = 0.;
  }

  // evolve the solution y(t) to y(t+h)
  // take y,t,h, and the model and return the approximation at the next
  // time level
  // The Model is given by a template argument, which has to provide the
  // following methods:
  // - model.f(t,y)
  // - model.df(t,y)
  // - model.N
  template <class Model>
  Vector evolve(const Vector &y, double t, double h, const Model &model) const //h stands for tau
  {
    Vector ret = y;
    std::vector<Vector> k(stages_, Vector(model.N)); //taking number of stages and number of points in the interior of the interval


	  for (int s=0; s<stages_; ++s ) {
	  // compute k_s and store inside k[s]

      Vector temp_sum = y;
      for(int j=0; j<s; ++j)
      {
        temp_sum += h*a(s,j)*k[j];
      }
	    if (a(s,s) != 0)
      {
		  // implicit case
        int iter = 0; // iter is the counter which allows to stop the while after a certain number of iterations

        double error = maxNorm( model.f(t+ h*c[s], temp_sum + h*a(s,s)*k[s]) - k[s] );
        SparseMatrix Jac = model.df(t+h*c[s], temp_sum+h*a(s,s)*k[s]);
        while( iter<1e6 && std::abs(error)>1e-6 )
        {
            k[s] = Jac.GaussSeidel(-model.f(t+h*c[s], temp_sum+h*a(s,s)*k[s]), k[s], 1e-6, 1e6) + k[s];
            double error = maxNorm( model.f(t+ h*c[s], temp_sum + h*a(s,s)*k[s]) - k[s] );
            iter ++;
        }
        tmp_sum += h*a(s,s)*k[s];
	    }

      k[s]=model.f(t + c[s]*h, temp_sum);

	    // Increment the return value by the current k[s]
	    ret += h*b_[s]*k[s];

    } //end of for loop

     return ret;
  }

protected:

  const double a(int i, int j) const { return a_[i*stages_+j]; }
  double& a(int i, int j) { return a_[i*stages_+j]; }

  int stages_;

  std::vector<double> a_,b_,c_;
};


class FE: public DIRK
{
public:

  FE() : DIRK(1)
  {
	a(0,0) = 0.;
	b_[0] = 1.;
	c_[0] = 0.;
  }
};

#endif
