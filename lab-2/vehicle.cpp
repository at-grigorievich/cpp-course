#include "vehicle.h"

namespace vehicles {
	//VEHICLE IMPLEMENT
	double vehicle::getFuelLevel() const {
		return fuelLevel;
	}

	void vehicle::setFuelLevel(double level) {
		if (level >= 0 && level <= 100) fuelLevel = level;
	}

	//CAR IMPLEMENT
	void car::startEngine() {
		std::cout << brand << " " << model << " заводитс€ (двигатель запущен)" << std::endl;
	}

	void car::stopEngine() {
		std::cout << brand << " " << model << " останавливаетс€ (двигатель заглушен)" << std::endl;
	}

	void car::refuel(double amount) {
		setFuelLevel(fuelLevel + amount);
		std::cout << brand << " " << model << " заправлен на " << amount << "%, текущий уровень: " << fuelLevel << "%" << std::endl;
	}

	void car::displayInfo() const {
		vehicle::displayInfo();
		std::cout << " оличество дверей: " << doors << ",  оробка передач: " << transmission << std::endl;
	}

	//MOTORCYCLE IMPLEMENT
	void motorcycle::startEngine() {
		std::cout << brand << " " << model << " заводитс€ (двигатель запущен)" << std::endl;
	}

	void motorcycle::stopEngine() {
		std::cout << brand << " " << model << " останавливаетс€ (двигатель заглушен)" << std::endl;
	}

	void motorcycle::refuel(double amount) {
		setFuelLevel(fuelLevel + amount);
		std::cout << brand << " " << model << " заправлен на " << amount << "%, текущий уровень: " << fuelLevel << "%" << std::endl;
	}

	void motorcycle::displayInfo() const {
		vehicle::displayInfo();
		std::cout << "— обтекателем: " << (hasFairing ? "ƒа" : "Ќет") << std::endl;
	}

	void motorcycle::wheelie() const {
		std::cout << brand << " " << model << " делает вилли!" << std::endl;
	}
}