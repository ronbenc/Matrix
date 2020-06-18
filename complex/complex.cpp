#include "complex.h"

Complex::Complex(double re, double im) : re(re), im(im) {};

Complex& Complex::operator+=(const Complex& c)
{
	re += c.re;
	im += c.im;
	return *this;
}

Complex& Complex::operator-=(const Complex& c)
{
	return *this += -c;
}

Complex Complex::operator-() const 
{
	return Complex(-re, -im);
}

Complex operator+(const Complex& a, const Complex& b)
{
	return Complex(a) += b;
}

Complex operator-(const Complex& a, const Complex& b)
{
	return Complex(a) -= b;
}


ostream& operator<<(ostream& os, const Complex& c)
{
    if(c.im < 0)
        return os << c.re << "-" << -c.im << "i";

    return os << c.re << "+" << c.im << "i";
}


istream& operator>>(istream& is, Complex& c)
{
	return is >> c.re >> c.im;
}

bool operator==(const Complex& a, const Complex& b)
{
	return a.re == b.re && a.im == b.im;
}


Complex& Complex::operator*=(const Complex& c)
{
    double a = re;
    double b = im;

	re = a*c.re - b*c.im;
    im = a*c.im + b*c.re;
    

	return *this;
}

Complex operator*(const Complex& a, const Complex& b)
{
    return Complex(a) *= b; 
}

Complex::operator double() const
{
	return re;
}
