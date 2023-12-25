#pragma once
#include <iostream>
#include <map>
#include <math.h>

class Poly {
  private:
	std::map<int, double> polynomialCoefficients;

  public:
	Poly() = default;
	Poly(double constant);

	double& operator[](int power);
	double operator[](int power) const;
	Poly operator+(const Poly& other) const;
	Poly operator+(double constant) const;
	Poly operator-(const Poly& other) const;
	Poly operator-(double constant) const;
	Poly operator*(const Poly& other) const;
	Poly operator*(double constant) const;
	Poly operator-() const;

	double operator()(double x) const;

	friend Poly operator+(double constant, const Poly& poly);
	friend Poly operator-(double constant, const Poly& poly);
	friend Poly operator*(double constant, const Poly& poly);
	friend std::ostream& operator<<(std::ostream& os, const Poly& poly);
};
