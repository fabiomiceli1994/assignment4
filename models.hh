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
      double UD = kappa/(h*h); // Upper diagonal terms of matrix A
      double D = -2*kappa/(h*h);  // Diagonal terms of matrix A
      double LD = kappa/(h*h); // Lower diagonal terms of matrix A
      for (int i = 0; i < N; ++i)
      {
        for (int j = 0; j < N; ++j)
        {
          if(i==0 && j == N-1) // PBC (up-right entry)
          {
            A.addEntry(i, j, 1.);
          }
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
          else if (i==N-1 && j == 0) // PBC (lower left entry)
          {
            A.addEntry(i, j, 1.);
          }

        }
      }
    }

  // f : returns the function f(t,y) in the IVP obtained after implementing method of lines
  Vector f(double t,const Vector &y) const
  {
    return A*y;
  }

  // df : returns the gradient of f, and since f is vector values, grad f is the Jacobian matrix, which in this case is A
  const SparseMatrix& df(double t,const Vector &y) const
  {
    return A;
  }

  // T : returns the interval length in time
  double T() const
  {
    return 0.1;
  }

  // y0 : initial function at time t = 0
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
  double kappa; // kappa is the thermal diffusivity parameter in the heat equation
  SparseMatrix A; // A is the matrix in the matrix IVP equation obtained after implementing method of lines to the heat equation

private:
  // persistent data

};

#endif // MODELS_HH
