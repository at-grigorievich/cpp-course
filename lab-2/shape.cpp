#include "shape.h"
#include <iostream>
#include <cmath>

namespace shapes {
	const double M_PI = 3.141592653589793;

	//CIRCLE IMPLEMENT
	double circle::calculateArea() const {
		return M_PI * radius * radius;
	}

	double circle::calculatePerimeter() const {
		return 2 * M_PI * radius;
	}

	void circle::draw() const {
		std::cout << "Рисуется круг радиуса " << radius << std::endl;
	}

	void circle::displayInfo() const {
		shape::displayInfo();
		std::cout << "Радиус: " << radius
			<< ", Площадь: " << calculateArea()
			<< ", Периметр: " << calculatePerimeter() << std::endl;
	}

	//RECTANGLE IMPLEMENT
	double rectangle::calculateArea() const {
		return width * height;
	}

	double rectangle::calculatePerimeter() const {
		return 2 * (width + height);
	}

	void rectangle::draw() const {
		std::cout << "Рисуется прямоугольник " << width << "x" << height << std::endl;
	}

	void rectangle::displayInfo() const {
		shape::displayInfo();
		std::cout << "Ширина: " << width
			<< ", Высота: " << height
			<< ", Площадь: " << calculateArea()
			<< ", Периметр: " << calculatePerimeter() << std::endl;
	}

	//TRIANGLE IMPLEMENT
	double triangle::calculateArea() const {
		return calculateHeronArea();
	}

	double triangle::calculateHeronArea() const {
		double p = (sideA + sideB + sideC) / 2.0;
		return sqrt(p * (p - sideA) * (p - sideB) * (p - sideC));
	}

	double triangle::calculatePerimeter() const {
		return sideA + sideB + sideC;
	}

	void triangle::draw() const {
		std::cout << "Рисуется треугольник со сторонами "
			<< sideA << ", " << sideB << ", " << sideC << std::endl;
	}

	void triangle::displayInfo() const {
		shape::displayInfo();
		std::cout << "Стороны: " << sideA << ", " << sideB << ", " << sideC
			<< ", Площадь: " << calculateArea()
			<< ", Периметр: " << calculatePerimeter() << std::endl;
	}
}