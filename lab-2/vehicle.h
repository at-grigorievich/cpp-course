#pragma once
#include <string>
#include <iostream>

namespace vehicles {
	class vehicle {
	protected:
		std::string brand;
		std::string model;
		int year;
		double fuelLevel;
	public:
		vehicle(std::string _brand, std::string _model, int _year) :
			brand(_brand), model(_model), year(_year), fuelLevel(60){}
		virtual ~vehicle() = default;

		virtual void startEngine() = 0;
		virtual void stopEngine() = 0;
		virtual void refuel(double amount) = 0;

		virtual void displayInfo() const {
			std::cout << brand << " " << model << " (" << year << ")" << std::endl;
			std::cout << "Уровень топлива: " << fuelLevel << "%" << std::endl;
		}

		double getFuelLevel() const;
		void setFuelLevel(double level);
	};

	class car : public vehicle {
	private:
		int doors;
		std::string transmission;
	public:
		car(std::string _brand, std::string _model, int _year, int _doors, std::string _transmsn) :
			vehicle(_brand, _model, _year), doors(_doors), transmission(_transmsn) {}

		void startEngine() override;
		void stopEngine() override;
		void refuel(double amount) override;

		void displayInfo() const override;
	};

	class motorcycle : public vehicle {
	private:
		bool hasFairing;

	public:
		motorcycle(std::string _brand, std::string _model, int _year, bool fairing) :
			vehicle(_brand, _model, _year), hasFairing(fairing) {}

		void startEngine() override;
		void stopEngine() override;
		void refuel(double amount) override;

		void displayInfo() const override;

		void wheelie() const;
	};
}
