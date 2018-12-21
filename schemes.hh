#ifndef SCHEMES_HH
#define SCHEMES_HH

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

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
  Vector evolve(const Vector &y, double t, double h, const Model &model) const
  {
    Vector ret = y;
    std::vector<Vector> k(stages_, Vector(model.N));
	
	for (int s=0; s<stages_; ++s ) {
	  // compute k_s and store inside k[s]
	  
	  if (a(s,s) == 0) {
		// explicit case
	  } else {
		// implicit case
		// solve via Newton method
	  }
	  
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
