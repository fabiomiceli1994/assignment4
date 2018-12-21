#ifndef SPARSE_H
#define SPARSE_H

#include "vector.hh"

class SparseMatrix {
public:

  SparseMatrix(int N_)
	: N(N_), index_(N), data_(N) {}

  SparseMatrix(const SparseMatrix& other)
	: N(other.N), index_(other.index_), data_(other.data_) {}

  double operator()(int i, int j) const { return getEntry(i,j); }
  Vector operator*(const Vector& other) const { return multiply(other); };
  SparseMatrix operator*(double v) const;
  SparseMatrix operator-(const SparseMatrix& other) const;

  const SparseMatrix& Id();

  void addEntry(int i, int j, double val);
  void clear() { data_ = std::vector<std::vector<double> >(N); index_ = std::vector<std::vector<int> >(N); }

  Vector GaussSeidel(const Vector& b, const Vector& x0, double tolerance = 1e-6, int maxIter = 100000) const;
  Vector SteepestDescent(const Vector& b, const Vector& x0, double tolerance = 1e-6, int maxIter = 100000) const;
  Vector ConjugateGradient(const Vector& b, const Vector& x0, double tolerance = 1e-6, int maxIter = 100000) const;

  int N;

private:

  double multiplyLine(const Vector& x, int i) const;
  Vector multiply(const Vector& other) const;
  double getEntry(int i, int j) const;
  int findEntry(int i, int j) const;

  std::vector<std::vector<double> > data_;
  std::vector<std::vector<int> > index_;
};

#endif
