#ifndef MODELS_HH
#define MODELS_HH

#include "sparse.hh"
#include "vector.hh"

class HeatEquation
{
public:

  int N;
  double kappa;
  SparseMatrix A;

  HeatEquation(int N, double kappa, SparseMatrix A)
  {

    A = SparseMatrix(N, N);
    double h = 1/(N+1);
    double OD = (kappa)/(h*h); //off diagonal terminal
    double D = -2*(kappa)/(h*h); //diagonal
    for(i=0; i<N; ++i)
    {
      for(j=0; j<N, ++j)
      {
        if( (i-1) == j ) //lower diagonal
        {
          A.addEntry( i, j, OD);
        }else if( i == j ) //diagonal
        {
          A.addEntry( i, j, D);
        }else if( (i+1) == j ) //upper diagonal
        {
          A.addEntry( i, j, OD);
        }else
        {
          continue;
        }
      }
    }

  }

  Vector f(double t,const Vector &y) const
  {
    return A*y;
  }

  const SparseMatrix& df(double t,const Vector &y) const
  {
    return A;
  }

  double T() const
  {
    return 0.1;
  }

  Vector y0() const
  {
    double h = 1/((*this).N + 1);
    Vector v((*this).N);
    for(i=0;i<N;++i)
    {
      if(i*h>=0.25 && i*h<0.75)
      {
        v[i]=1.;
      }
    }
    return v;
  }



private:

  // persistent data
};

#endif // MODELS_HH
