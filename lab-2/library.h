#pragma once
#include <string>
#include <vector>

namespace librarybooks {
	class book {
	private:
		std::string title;
		std::string author;
		std::string isbn;
		int year;
		bool isAvailable;
	public:
		book(std::string _title, std::string _author, std::string _isbn, int _year) :
			title(_title), author(_author), isbn(_isbn), year(_year), isAvailable(true) {}

		std::string getTitle() const;
		std::string getAuthor() const;
		std::string getISBN() const;
		int getYear() const;
		bool getAvailable() const;

		void setTitle(const std::string& t);
		void setAuthor(const std::string& a);
		void setYear(int y);

		bool borrow();
		void returnBook();
		void displayInfo() const;
	};

	class library {
	private:
		std::string name;
		std::string address;
		std::vector<book> books;
	public:
		library(std::string _name, std::string _addr) :
			name(_name), address(_addr) {}

		void addBook(const book& book);
		void removeBook(const std::string& isbn);
		book* findBook(const std::string& title);
		bool borrowBook(const std::string& isbn);
		void returnBook(const std::string& isbn);
		void displayAllBooks() const;
		void displayAvailableBooks() const;
	};
}
