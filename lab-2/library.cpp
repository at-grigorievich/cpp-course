#include "library.h"
#include <iostream>

namespace librarybooks {
	//BOOK IMPLEMENT
	std::string book::getTitle() const { return title; }
	std::string book::getAuthor() const { return author; }
	std::string book::getISBN() const { return isbn; }
	int book::getYear() const { return year; }
	bool book::getAvailable() const { return isAvailable; }

	void book::setTitle(const std::string& t) { title = t; }
	void book::setAuthor(const std::string& a) { author = a; }
	void book::setYear(int y) { year = y; }

	bool book::borrow() {
		if (isAvailable) {
			isAvailable = false;
			return true;
		}
		return false;
	}

	void book::returnBook() {
		isAvailable = true;
	}

	void book::displayInfo() const {
		std::cout << title << " | " << author << " | " << isbn << " | " << year
			<< " | " << (isAvailable ? "Доступна" : "Не доступна") << std::endl;
	}

	//LIBRARY IMPLEMENT
	void library::addBook(const book& book) {
		books.push_back(book);
	}

	void library::removeBook(const std::string& isbn) {
		for (size_t i = 0; i < books.size(); i++) {
			if (books[i].getISBN() == isbn) {
				books.erase(books.begin() + i);
				break;
			}
		}
	}

	book* library::findBook(const std::string& title) {
		for (size_t i = 0; i < books.size(); i++) {
			if (books[i].getTitle() == title) {
				return &books[i];
			}
		}
		return nullptr;
	}

	bool library::borrowBook(const std::string& isbn) {
		for (size_t i = 0; i < books.size(); i++) {
			if (books[i].getISBN() == isbn) {
				return books[i].borrow();
			}
		}
		return false;
	}

	void library::returnBook(const std::string& isbn) {
		for (size_t i = 0; i < books.size(); i++) {
			if (books[i].getISBN() == isbn) {
				books[i].returnBook();
				break;
			}
		}
	}

	void library::displayAllBooks() const {
		std::cout << "Все книги в библиотеке " << name << ":" << std::endl;
		
		for (size_t i = 0; i < books.size(); i++) {
			books[i].displayInfo();
		}
	}

	void library::displayAvailableBooks() const {
		std::cout << "Доступные книги в библиотеке " << name << ":" << std::endl;

		for (size_t i = 0; i < books.size(); i++) {
			if (books[i].getAvailable() == true) {
				books[i].displayInfo();
			}
		}
	}
}