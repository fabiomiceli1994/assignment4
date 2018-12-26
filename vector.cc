#include <cassert>
#include <cmath>
#include <fstream>

#include "vector.hh"
#include "sparse.hh"
#include "models.hh"

std::ostream& operator<<(std::ostream& s, const Vector& v) {
  for (double l : v ) {
	s << l << std::endl;
  }
  return s;
}

Vector operator*(double a, const Vector& v) {
  Vector ret(v.size());
  for ( int i=0; i<v.size(); ++i ) {
	ret[i] = a*v[i];
  }
  return ret;
}


double Vector::norm() const {
  double ret = 0.0;
  for ( int i=0; i<size(); ++i ) {
	ret += (*this)[i] * (*this)[i];
  }
  return std::sqrt(ret);
}

double Vector::maxNorm() const {
  double ret = 0.0;
  for ( int i=0; i<size(); ++i ) {
	const double v = std::abs((*this)[i]);
	if (v > ret) ret = v;
  }
  return ret;
}

Vector Vector::operator+(const Vector& other) const {
  Vector ret(size());
  for ( int i=0; i<size(); ++i ) {
	ret[i] = (*this)[i] + other[i];
  }
  return ret;
}


Vector& Vector::operator+=(const Vector& other) {
  for ( int i=0; i<size(); ++i ) {
	(*this)[i] += other[i];
  }
  return *this;
}

Vector Vector::operator-(const Vector& other) const {
  Vector ret(size());
  for ( int i=0; i<size(); ++i ) {
	ret[i] = (*this)[i] - other[i];
  }
  return ret;
}

double Vector::operator*(const Vector& other) const {
  double ret = 0.0;
  for ( int i=0; i<size(); ++i ) {
	ret += (*this)[i]*other[i];
  }
  return ret;
}

Vector Vector::operator*(double v) const {
  Vector ret(*this);
  for ( int i=0; i<size(); ++i ) {
	ret[i] = (*this)[i]*v;
  }
  return ret;
}

void Vector::toFile(const std::string& filename, double L) {
  std::ofstream file;
  file.open(filename);
  for ( int i = 0; i<size(); ++i ) {
  file.width(20);
	file << std::left << ((double) i)/(size()-1)*L << " " << (*this)[i] << std::endl; // -1 is added to the provided code to make it print correctly
  }
  file.close();
}
