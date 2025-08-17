// racoeffic@gmail.com

#include "Complex.hpp"
#include <cmath>

using namespace std;
Complex::Complex(double r, double i) : real(r), imaginary(i) {}

double Complex::getReal() const { return real; }
double Complex::getImaginary() const { return imaginary; }
double Complex::vec() const { return sqrt(real * real + imaginary * imaginary); }

Complex Complex::operator+(const Complex &c) const {
    return Complex(real + c.real, imaginary + c.imaginary);
}
Complex& Complex::operator+=(const Complex &c) {
    real += c.real;
    imaginary += c.imaginary;
    return *this;
}
Complex Complex::operator-(const Complex &c) const {
    return Complex(real - c.real, imaginary - c.imaginary);
}
Complex& Complex::operator-=(const Complex &c) {
    real -= c.real;
    imaginary -= c.imaginary;
    return *this;
}

Complex Complex::operator*(const Complex &c) const {
    return Complex(real * c.real - imaginary * c.imaginary, real * c.imaginary + imaginary * c.real);
}
Complex& Complex::operator*=(const Complex &c) {
    double temp = real;
    real = real * c.real - imaginary * c.imaginary;
    imaginary = temp * c.imaginary + imaginary * c.real;
    return *this;
}
Complex Complex::operator/(const Complex &c) const {
    double denominator = c.real * c.real + c.imaginary * c.imaginary;
    if (denominator == 0) {throw std::invalid_argument("Can't divide by 0.");}
    return Complex((real * c.real + imaginary * c.imaginary) / denominator, (imaginary * c.real - real * c.imaginary) / denominator);
}
Complex& Complex::operator/=(const Complex &c) {
    double denominator = c.real * c.real + c.imaginary * c.imaginary;
    if (denominator == 0) {throw std::invalid_argument("Can't divide by 0.");}

    double temp = real;
    real = (real * c.real + imaginary * c.imaginary) / denominator;
    imaginary = (imaginary * c.real - temp * c.imaginary) / denominator;
    return *this;
}


Complex Complex::operator-() const {
    return Complex(-real, -imaginary);
}


ostream &operator<<(ostream &os, const Complex &c) {
    os << c.real << "+" << c.imaginary << "i";
    return os;
}

istream &operator>>(istream &is, Complex &c) {
    is >> c.real >> c.imaginary;
    return is;
}

bool Complex::operator==(const Complex &c) const {
    return real == c.real && imaginary == c.imaginary;
}

bool Complex::operator!=(const Complex &c) const {
    return !(*this == c);
}


bool Complex::operator<(const Complex &c) const {
    return vec() < c.vec();
}

bool Complex::operator<=(const Complex &c) const {
    return vec() <= c.vec();
}

bool Complex::operator>(const Complex &c) const {
    return vec() > c.vec();
}

bool Complex::operator>=(const Complex &c) const {
    return vec() >= c.vec();
}
