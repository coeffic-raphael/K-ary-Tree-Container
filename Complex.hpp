// racoeffic@gmail.com

#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>

class Complex {
private:
    double real;
    double imaginary;

public:
    Complex(double r, double i);

    double getReal() const;
    double getImaginary() const;

    // compute the lenght for the boolean functions
    double vec() const;

    // Operators
    Complex operator+(const Complex &c) const;
    Complex& operator+=(const Complex &c);
    Complex operator-(const Complex &c) const;
    Complex& operator-=(const Complex &c);
    Complex operator*(const Complex &c) const;
    Complex& operator*=(const Complex &c);
    Complex operator/(const Complex &c) const;
    Complex& operator/=(const Complex &c);

    Complex operator-() const;// unary -

    friend std::ostream &operator<<(std::ostream &os, const Complex &c);
    friend std::istream &operator>>(std::istream &is, Complex &c);

    bool operator==(const Complex &c) const;
    bool operator!=(const Complex &c) const;

    

    bool operator<(const Complex &c) const;
    bool operator<=(const Complex &c) const;
    bool operator>(const Complex &c) const;
    bool operator>=(const Complex &c) const;
};

#endif // COMPLEX_HPP
