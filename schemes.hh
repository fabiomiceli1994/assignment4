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
  Vector evolve(const Vector &y, double t, double h, const Model &model, unsigned int &count ) const // h  = tau
  {
    Vector ret = y;
    std::vector<Vector> k(stages_, Vector(model.N));
	   for (int s=0; s<stages_; ++s )
     {
	      // compute k_s and store inside k[s]
        Vector temp_sum = y; //I use this sum for updating the k[i] values.
        for (int j = 0; j < s; ++j)
        {
          temp_sum += h*a(s,j)*k[j];
        }
	      if (a(s,s) != 0)
        {
          int iter = 0; // iter is the counter to stop the while loop after a certain number of iterations
          Vector error = (model.f(t + h*c_[s], temp_sum + h*a(s,s)*k[s]) - k[s]);
          count ++; //efficiecy count
          SparseMatrix Jac = model.df(t + h*c_[s], temp_sum + h*a(s,s)*k[s]); //jacobian (see models.hh)
          count ++; //efficiency count
          while (iter < 1e6 && error.maxNorm() > 1e-6)
          {
            k[s] = Jac.ConjugateGradient((-1)*model.f(t + h*c_[s], temp_sum + h*a(s,s)*k[s]) + k[s], k[s], 1e-6, 1e6) + k[s];
            count ++; //efficiency count
            error = (model.f(t + h*c_[s], temp_sum + h*a(s,s)*k[s]) - k[s]);
            count ++; //efficiency count
            iter++;
          }
          temp_sum += h*a(s,s)*k[s];
	      }
        k[s] = model.f(t + c_[s]*h, temp_sum);
        count ++;
	      // Increment the return value by the current k[s]
	      ret += h*b_[s]*k[s];
	    }
    return ret;
  }

protected:

  const double a(int i, int j) const { return a_[i*stages_+j]; }
  double& a(int i, int j) { return a_[i*stages_+j]; }

  int stages_;

  std::vector<double> a_,b_,c_;
};

// forward Euler method
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

// backward Euler method
class BE: public DIRK
{
public:

  BE() : DIRK(1)
  {
	a(0,0) = 1.;
	b_[0] = 1.;
	c_[0] = 1.;
  }

};

// Heun3 method
class Heun3: public DIRK
{
public:

  Heun3() : DIRK(3)
  {
	a(1,0) = 1./3;
  a(2,1) = 2./3;
	b_[0] = 0.25;
  b_[1] = 0.;
  b_[2] = 0.75;
	c_[0] = 0;
  c_[1] = 1./3;
  c_[2] = 2./3;
  }

};


#endif
