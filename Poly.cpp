#include "Poly.h"

Poly::Poly(double constant)
{
	if (constant != 0) {
		polynomialCoefficients[0] = constant;
	}
}

double& Poly::operator[](int exponent)
{
	if (exponent < 0) {
		std::cout << "Exponent is invalid (negative)" << std::endl;
		exit(EXIT_FAILURE);
	}

	return polynomialCoefficients[exponent];
}

double Poly::operator[](int exponent) const
{
	auto it = polynomialCoefficients.find(exponent);
	if (it != polynomialCoefficients.end()) {
		return it->second;
	}
	return 0.0;
}

Poly Poly::operator+(const Poly& other) const
{
	Poly result;
	for (const auto& term : polynomialCoefficients) {
		result[term.first] += term.second;
	}
	for (const auto& term : other.polynomialCoefficients) {
		result[term.first] += term.second;
	}
	return result;
}

Poly Poly::operator+(double constant) const
{
	Poly result = *this;
	result[0] += constant;
	return result;
}

Poly operator+(double constant, const Poly& poly)
{
	return poly + constant;
}

Poly Poly::operator-(const Poly& other) const
{
	Poly result;
	for (const auto& term : polynomialCoefficients) {
		result[term.first] += term.second;
	}
	for (const auto& term : other.polynomialCoefficients) {
		result[term.first] -= term.second;
	}
	return result;
}

Poly Poly::operator-(double constant) const
{
	return *this + -constant;
}

Poly operator-(double constant, const Poly& poly)
{
	return Poly(constant) - poly;
}

Poly Poly::operator*(const Poly& other) const
{
	Poly result;
	for (const auto& term1 : polynomialCoefficients) {
		for (const auto& term2 : other.polynomialCoefficients) {
			result[term1.first + term2.first] += term1.second * term2.second;
		}
	}
	return result;
}

Poly Poly::operator*(double constant) const
{
	Poly result;
	for (const auto& term : polynomialCoefficients) {
		result[term.first] = term.second * constant;
	}
	return result;
}

Poly operator*(double constant, const Poly& poly)
{
	return poly * constant;
}

Poly Poly::operator-() const
{
	Poly result = *this;
	for (auto& term : result.polynomialCoefficients) {
		term.second = -term.second;
	}
	return result;
}

double Poly::operator()(double x) const
{
	double result = 0.0;
	for (const auto& term : polynomialCoefficients) {
		result += term.second * std::pow(x, static_cast<double>(term.first));
	}
	return result;
}

std::ostream& operator<<(std::ostream& os, const Poly& poly)
{
	bool firstTerm = true;
	for (auto it = poly.polynomialCoefficients.rbegin();
		 it != poly.polynomialCoefficients.rend(); ++it) {
		int exponent = it->first;
		double coefficient = it->second;

		if (coefficient != 0) {
			if (!firstTerm) {
				os << " ";
				if (coefficient > 0) {
					os << "+ ";
				}
				else {
					os << "- ";
				}
			}
			else {
				if (coefficient < 0) {
					os << "-";
				}
			}

			if (exponent == 0 || abs(coefficient) != 1) {
				os << abs(coefficient);
			}

			if (exponent > 0) {
				os << "x";
				if (exponent > 1) {
					os << "^" << exponent;
				}
			}

			firstTerm = false;
		}
	}

	if (firstTerm) {
		os << "0";
	}

	return os;
}
