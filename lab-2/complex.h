#pragma once
#include <ostream>
#include <istream>

namespace friendly_complex {
	class complex {
	private:
		double real;
		double img;
	public:
		complex(double r = 0, double i = 0) :
			real(r), img(i) {}

		double getReal() const;
		double getImaginary() const;

		void setReal(double r);
		void setImaginary(double i);

		complex operator+(const complex& other) const;
		complex operator-(const complex& other) const;
		complex operator*(const complex& other) const;
		bool operator==(const complex& other) const;

		friend std::ostream& operator<<(std::ostream& os, const complex& c);
		friend std::istream& operator>>(std::istream& is, complex& c);

		void display() const;
	};
}