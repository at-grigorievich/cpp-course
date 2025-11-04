#include "complex.h"
#include <iostream>

namespace friendly_complex {
	double complex::getReal() const { return real; }
	double complex::getImaginary() const { return img; }

	void complex::setReal(double r) { real = r; }
	void complex::setImaginary(double i) { img = i; }

	complex complex::operator+(const complex& other) const {
		return complex(real + other.real, img + other.img);
	}

	complex complex::operator-(const complex& other) const {
		return complex(real - other.real, img - other.img);
	}

	complex complex::operator*(const complex& other) const {
		return complex(
			real * other.real - img * other.img,
			real * other.img + img * other.real
		);
	}

	bool complex::operator==(const complex& other) const {
		return real == other.real && img == other.img;
	}

	std::ostream& operator<<(std::ostream& os, const complex& c) {
		os << c.real << " + " << c.img << "i";
		return os;
	}

	std::istream& operator>>(std::istream& is, complex& c) {
		std::cout << "¬ведите действительную часть: ";
		is >> c.real;
		std::cout << "¬ведите мнимую часть: ";
		is >> c.img;
		return is;
	}

	void complex::display() const {
		std::cout << real << " + " << img << "i" << std::endl;
	}
}