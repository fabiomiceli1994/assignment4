#ifndef MODELS_HH
#define MODELS_HH

#include "sparse.hh"

class HeatEquation
{
public:

  HeatEquation(int N_, double kappa_) // Default Constructor
    : N(N_), kappa(kappa_), A(SparseMatrix(N))
    {
      double h = 1./(double)(N + 1);  // Spatial stepsize h
      double UD = kappa/(h*h); // Upper diagonal terms of A
      double D = -2*kappa/(h*h);  // Diagonal terms of A
      double LD = kappa/(h*h); // Lower diagonal terms of A
      for (int i = 0; i < N; ++i)
      {
        for (int j = 0; j < N; ++j)
        {
          if(j == i + 1) // Upper-diagonal entries
          {
            A.addEntry(i, j, UD);
          }
          else if(j == i) // Diagonal entries
          {
            A.addEntry(i, j, D);
          }
          else if (j == i - 1) // Lower-diagonal entries
          {
            A.addEntry(i, j, LD);
          }
        }
      }
    }

  // returns f(t,y) in the IVP obtained for method of lines
  Vector f(double t,const Vector &y) const
  {
    return A*y;
  }

  // returns the gradient of f, which is the Jacobian matrix. Here is just A
  const SparseMatrix& df(double t,const Vector &y) const
  {
    return A;
  }

  // returns the interval length in time
  double T() const
  {
    return 0.1;
  }

  // y0 is the initial function at time t = 0
  Vector y0() const
  {
    double h = 1./(N + 1);
    Vector v(N);
    for (int i = 0; i < N; ++i)
    {
      if (i*h > 0.25 && i*h <= 0.75)
      {
        v[i] = 1;
      }
    }
    return v;
  }

  int N; // N denotes the number of spatial discretisation points
  double kappa; // kappa is the thermal diffusivity parameter
  SparseMatrix A; // A is the matrix in the matrix IVP equation obtained after the spatial discretisation

private:
  // persistent data

};

#endif // MODELS_HH
