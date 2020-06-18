#ifndef COMPLEX_H_
#define COMPLEX_H_

#include <iostream>

using namespace std;

class Complex
{
	double re, im;

public:
	Complex(double re = 0.0, double im = 0.0);
	Complex(const Complex&) = default;
	Complex& operator=(const Complex&) = default;
	Complex& operator+=(const Complex& c);
	Complex& operator-=(const Complex& c);
	Complex operator-() const;
	friend bool operator==(const Complex& a, const Complex& b);
	friend ostream& operator<<(ostream& os, const Complex& c);
	friend istream& operator>>(istream& is, Complex& c);

    Complex& operator*=(const Complex& c);
	explicit operator double() const;
};

Complex operator+(const Complex& a, const Complex& b);
Complex operator-(const Complex& a, const Complex& b);

Complex operator*(const Complex& a, const Complex& b);

#endif
