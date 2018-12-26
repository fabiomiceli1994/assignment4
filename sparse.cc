#include <cassert>

#include "vector.hh"
#include "sparse.hh"
#include "models.hh"

int SparseMatrix::findEntry(int i, int j) const {
  for ( int k = 0; k<index_[i].size(); ++k ) {
	if ( index_[i][k] == j ) {
	  return k;
	}
  }
  return -1;
}

double SparseMatrix::getEntry(int i, int j) const {
  int idx = findEntry(i,j);
  if (idx  == -1 ) {
	return 0.0;
  } else {
	return data_[i][idx];
  }
}

void SparseMatrix::addEntry(int i, int j, double v) {
  int idx = findEntry(i,j);
  if (idx  == -1 ) {
	index_[i].push_back(j);
	data_[i].push_back(v);
  } else {
	data_[i][idx] = v;
  }
}

Vector SparseMatrix::multiply(const Vector& other) const {
  Vector x(N);
  for ( int i = 0; i<N; ++i ) {
	x[i] = multiplyLine(other, i);
  }
  return x;
}

const SparseMatrix& SparseMatrix::Id() {
  clear();
  for ( int i=0; i<N; ++i ) {
	addEntry(i,i,1.0);
  }
  return *this;
}

double SparseMatrix::multiplyLine(const Vector& x, int i) const
{
  double ret = 0.0;
  for ( int k = 0; k<index_[i].size(); ++k ) {
	ret += data_[i][k]*x[index_[i][k]];
  }
  return ret;
}

Vector SparseMatrix::GaussSeidel(const Vector& b, const Vector& x0, double tolerance, int maxIter) const {
  const SparseMatrix& A = (*this);
  assert(b.size() == N);
  Vector x = x0;
  for ( int iter=0; iter < maxIter; ++iter ) {
	for ( int i = 0; i<N; ++i ) {
	  const double a_ii = getEntry(i,i);
	  x[i] += (b[i] - multiplyLine(x, i))/a_ii;
	}
	if ( (iter % 100) == 0 ) {
	  const double resi = (b - A*x).maxNorm();
	  // std::cout << "Iteration " << iter << ": residual=" << resi << std::endl;
	  if ( resi < tolerance ) {
		return x;
	  }
	}
  }
  std::cerr << "Tolerance not reached after " << maxIter << " iterations. Aborting!" << std::endl;
  return x;
}

Vector SparseMatrix::SteepestDescent(const Vector& b, const Vector& x0, double tolerance, int maxIter) const {
  const SparseMatrix& A = (*this);
  assert(b.size() == N);
  Vector x = x0;
  for ( int iter=0; iter < maxIter; ++iter ) {
	Vector r = b - A*x;
	if ( (iter % 100) == 0 ) {
	  const double resi = r.maxNorm();
	  std::cout << "GaussSeidel: Iteration " << iter << ": residual=" << resi << std::endl;
	  if ( resi < tolerance ) {
		return x;
	  }
	}
	double alpha = (r*r)/(A*r*r);
	x = x + r*alpha;
  }
  std::cerr << "GaussSeidel: Tolerance not reached after " << maxIter << " iterations. Aborting!" << std::endl;
  return x;
}

Vector SparseMatrix::ConjugateGradient(const Vector& b, const Vector& x0, double tolerance, int maxIter) const {
  const SparseMatrix& A = (*this);
  assert(b.size() == N);
  Vector x = x0;
  Vector r = b - A*x;
  Vector p = r;

  for ( int iter=0; iter < maxIter; ++iter ) {
	const double App = A*p*p;
	double alpha = (p*r)/App;
	x = x + p*alpha;

	r = b - A*x;

	const double beta = -(A*p*r)/App;
	p = r + p*beta;
	if ( (iter % 10) == 0 ) {
	  const double resi = r.maxNorm();
	  //std::cout << "ConjugateGradient: Iteration " << iter << ": residual=" << resi << std::endl;
	  if ( resi < tolerance ) {
		return x;
	  }
	}
  }
  std::cerr << "ConjugateGradient: Tolerance not reached after " << maxIter << " iterations. Aborting!" << std::endl;
  return x;
}

SparseMatrix SparseMatrix::operator-(const SparseMatrix& other) const
{
  assert(N == other.N);
  SparseMatrix ret(*this);
  for (int i=0; i<N; ++i ) {
	for ( int k = 0; k<other.index_[i].size(); ++k ) {
	  const int j = other.index_[i][k];
	  const double v = other.data_[i][k];
	  int idx = ret.findEntry(i,j);
	  if (idx  == -1 ) {
		ret.index_[i].push_back(j);
		ret.data_[i].push_back(-v);
	  } else {
		ret.data_[i][idx] -= v;
	  }
	}
  }
  return ret;
}

SparseMatrix SparseMatrix::operator*(double v) const
{
  SparseMatrix ret(*this);
  for (int i=0; i<N; ++i ) {
	for ( int k = 0; k<data_[i].size(); ++k ) {
	  ret.data_[i][k] *= v;
	}
  }
  return ret;
}
