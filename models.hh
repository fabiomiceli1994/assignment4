#ifndef MODELS_HH
#define MODELS_HH

#include "sparse.hh"

class HeatEquation
{
public:

  HeatEquation(int N_, double kappa_)
    : N(N_), kappa(kappa_), A(SparseMatrix(N)) {}

  Vector f(double t,const Vector &y) const
  {
    SparseMatrix A = SparseMatrix(N);
    double h = 1/(N + 1);
    double UD = kappa/(h*h);
    double D = -2*kappa/(h*h);
    double LD = kappa/(h*h);
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
    return A*y;
  }

  const SparseMatrix& df(double t,const Vector &y) const
  {
    // SparseMatrix A = SparseMatrix(N);
    // double h = 1/(N + 1);
    // double UD = kappa/(h*h);
    // double D = -2*kappa/(h*h);
    // double LD = kappa/(h*h);
    // for (int i = 0; i < N; ++i)
    // {
    //   for (int j = 0; j < N; ++j)
    //   {
    //     if(j == i + 1) // Upper-diagonal entries
    //     {
    //       A.addEntry(i, j, UD);
    //     }
    //     else if(j == i) // Diagonal entries
    //     {
    //       A.addEntry(i, j, D);
    //     }
    //     else if (j == i - 1) // Lower-diagonal entries
    //     {
    //       A.addEntry(i, j, LD);
    //     }
    //   }
    // }
    return A;
  }

  double T() const
  {
    return 0.1;
  }

  Vector y0() const
  {
    double h = 1/((*this).N + 1);
    Vector v((*this).N,1);
    for (int i = 0; i < (*this).N; ++i)
    {
      if (i*h >= 0.25 && i*h < 0.75)
      {
        v[i] = 1;
      }
    }
    return v;
  }

  int N;
  double kappa;
  SparseMatrix A;

private:
  // persistent data

};

#endif // MODELS_HH
