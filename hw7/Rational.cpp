// Alex Htut
// CSE 374 | HW7
// 06/05/2018
// Rational.cpp - Implemenation of the header file Rational.h
#include <cstdlib>

#include "Rational.h"

int gcd(int a, int b);

namespace rational374 {
  Rational::Rational(int n, int d) {
    numer_ = n;
    denom_ = d;
  }

  Rational::Rational() {
    Rational(0, 1);
  }

  Rational::Rational(int n) {
    Rational(n, 1);
  }

  int Rational::n() const {
    return numer_;
  }

  int Rational::d() const {
    return denom_;
  }

  Rational Rational::plus(Rational other) const {
    // common denominator
    int den = denom_ * other.d();
    int num = (numer_ * other.d()) + (other.n() * denom_);
    int gcd_num = gcd(abs(num), abs(den));

    num = num / gcd_num;
    den = den / gcd_num;

    if (den < 0) {
      num = -1 * num;
    }

    return(Rational(num, abs(den)));
  }

  Rational Rational::minus(Rational other) const {
    return(plus(Rational(-1 * other.n(), other.d())));
  }

  Rational Rational::times(Rational other) const {
    int num = numer_ * other.n();
    int den = denom_ * other.d();
    int gcd_num = gcd(abs(num), abs(den));

    num = num / gcd_num;
    den = den / gcd_num;

    if (den < 0) {
      num = -1 * num;
    }

    return(Rational(num, abs(den)));
  }

  Rational Rational::div(Rational other) const {
    return(times(Rational(other.d(), other.n())));
  }
}

int gcd(int a, int b) {
  if (a == 0) {
    return b;
  } else if (b == 0) {
    return a;
  }
  while (a != b) {
    if (a > b) {
      a = a - b;
    } else {
      b = b - a;
    }
  }
  return a;
}
