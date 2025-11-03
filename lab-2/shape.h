#pragma once

#include <string>
#include <iostream>

namespace shapes {
	class shape {
	protected:
		std::string color;
		std::string name;
	public:
		shape(std::string _name, std::string _color) :
			name(_name), color(_color) {}
		virtual ~shape() = default;

		virtual double calculateArea() const = 0;
		virtual double calculatePerimeter() const = 0;
		virtual void draw() const = 0;

		virtual void displayInfo() const {
			std::cout << "Фигура: " << name << ", Цвет: " << color << std::endl;
		}
	};

	class circle : public shape{
	private:
		double radius;
	public:
		circle(std::string _color, double _radius) :
			shape("Кружочечек", _color), radius(_radius) {}

		double calculateArea() const override;
		double calculatePerimeter() const override;
		void draw() const override;
		void displayInfo() const override;
	};

	class rectangle : public shape {
	private:
		double width;
		double height;
	public:
		rectangle(std::string _color, double w, double h) :
			shape("Прямоугольничек", _color), width(w), height(h) {}

		double calculateArea() const override;
		double calculatePerimeter() const override;
		void draw() const override;
		void displayInfo() const override;
	};

	class triangle : public shape {
	private:
		double sideA;
		double sideB;
		double sideC;
		double calculateHeronArea() const;

	public:
		triangle(std::string _color, double _sideA, double _sideB, double _sideC) :
			shape("Треугольничек", _color), sideA(_sideA), sideB(_sideB), sideC(_sideC) {}

		double calculateArea() const override;

		double calculatePerimeter() const override;
		void draw() const override;
		void displayInfo() const override;
	};
}