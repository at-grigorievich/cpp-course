// lab-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <locale>
#include <windows.h>
#include <string>

struct Complex {
    double real;
    double imag;
};

struct Book {
    std::string title; 
    std::string author;
    int year;          
    double price;       
};

struct Date {
    int day;
    int month;
    int year;
};

struct Student {
    std::string fullname;
    Date birthDate;
    int grades[5];
};

void temperatureExample();
void manipulateString();

Complex complexAdd(Complex a, Complex b);
Complex complexSubstract(Complex from, Complex to);
Complex complexMultiply(Complex a, Complex b);
void complexPrint(Complex printed);
void complexCalculate();

void swapValuesForward(int a, int b);
void swapValues(int& a, int& b);
void swapValues(int* a, int* b);
void swapIntegers();

void printBooks(Book* books, int size);
void printExpensiveBook(Book* books, int size);
void dynamicBookArray();

void Fibonacci();

void printStudent(const Student& student);
double getAverageRating(const Student& student);
void studentsRating();

void arrayInfo(int* arr, int size);
void utilityArray();

int main()
{
    setlocale(LC_ALL, "Russian");
    //temperatureExample();
    //manipulateString();
    //complexCalculate();
    //swapIntegers();
    //dynamicBookArray();
    //Fibonacci();
    //studentsRating();
    utilityArray();
}

void temperatureExample() {
    int n;
    double average = 0.0;
    double minTemp = 0.0;
    double maxTemp = 0.0;
    int lowerAverageDays = 0;

    std::cout << "Введите количество дней для анализа: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Некорректное количество дней." << std::endl;
        return;
    }

    double* temp = new double[n];

    for (int i = 0; i < n; i++) {
        std::cout << "Введите температуру для дня номер " << i + 1 << ": ";
        std::cin >> temp[i];

        average += temp[i];

        if (i == 0)
        {
            minTemp = maxTemp = temp[i];
            continue;
        }

        if (temp[i] < minTemp) minTemp = temp[i];
        if (temp[i] > maxTemp) maxTemp = temp[i];
    }

    average /= n;

    for (int i = 0; i < n; i++) {
        if (temp[i] >= average) continue;
        lowerAverageDays++;
    }

    delete[] temp;

    std::cout << "Средняя температура: " << average << std::endl;
    std::cout << "Минимальная температура: " << minTemp << std::endl;
    std::cout << "Максимальная температура: " << maxTemp << std::endl;
    std::cout << "Количество дней с температурой ниже средней: " << lowerAverageDays << std::endl;
}
void manipulateString() {
    char output[256];
    char findedSymbol = '\0';
    char endSym = '\0';
    int length = 0;
    int findedSymbolCount = 0;

    std::cout << "Введите строку: ";
    std::cin.getline(output, 256);

    std::cout << "Введите символ для поиска: ";
    std::cin >> findedSymbol;

    while (output[length] != '\0') {
        length++;
    }

    std::cout << "Длина строки: " << length << std::endl;

    for (int i = 0; i < length / 2; i++) {
        char buf = output[i];
        output[i] = output[length - i - 1];
        output[length - i - 1] = buf;
    }
    std::cout << "Перевернутая строка: " << output << std::endl;

    for (int i = 0; i < length; i++) {
        if (output[i] == findedSymbol)
            findedSymbolCount++;
    }

    std::cout << "Количество вхождений символа " << findedSymbol << " : " << findedSymbolCount << std::endl;
}

Complex complexAdd(Complex a, Complex b) {
    Complex result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    return result;
}
Complex complexSubstract(Complex from, Complex to) {
    Complex result;
    result.real = from.real - to.real;
    result.imag = from.imag - to.imag;
    return result;
}
Complex complexMultiply(Complex a, Complex b) {
    Complex result;
    result.real = a.real * b.real - a.imag * b.imag;
    result.imag = a.real * b.imag + a.imag * b.real;
    return result;
}
void complexPrint(Complex printed) {
    std::cout << "(" << printed.real;
    if (printed.imag >= 0) std::cout << " + " << printed.imag << "i)";
    else std::cout << " - " << -printed.imag << "i)";
}
void complexCalculate() {
    Complex c1, c2;
    c1.real = 1.0;
    c1.imag = 1.0;

    c2.real = 5.0;
    c2.imag = -10.0;

    Complex sum = complexAdd(c1, c2);
    Complex diff = complexSubstract(c1, c2);
    Complex multiply = complexMultiply(c1, c2);

    std::cout << "\nСумма: ";
    complexPrint(sum);
    std::cout << "\nРазность: ";
    complexPrint(diff);
    std::cout << "\nПроизведение: ";
    complexPrint(multiply);
    std::cout << std::endl;
}

void swapValuesForward(int a, int b) {
    int buf = a;
    a = b;
    b = buf;
}
void swapValues(int& a, int& b) {
    int buf = a;
    a = b;
    b = buf;
}
void swapValues(int* a, int* b) {
    int buf = *a;
    *a = *b;
    *b = buf;
}
void swapIntegers() {
    int a = 1;
    int b = 2;

    swapValuesForward(a, b);
    std::cout << "После swapValues(a, b) (по значению): a = " << a << ", b = " << b << "\n";

    swapValues(a, b);
    std::cout << "После swapValues(a, b) (по ссылке): a = " << a << ", b = " << b << "\n";

    swapValues(&a, &b);
    std::cout << "После swapValues(a, b) (по указателю): a = " << a << ", b = " << b << "\n";
}

void printBooks(Book* books, int size) {
    std::cout << "Список книг:" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << i + 1 << ". \"" << books[i].title 
            << "\", автор: " << books[i].author 
            << ", год: " << books[i].year
            << ", цена: " << books[i].price << std::endl;
    }
}
void printExpensiveBook(Book* books, int size) {
    int maxIndex = 0;

    for (int i = 1; i < size; ++i) {
        if (books[i].price > books[maxIndex].price) {
            maxIndex = i;
        }
    }

    std::cout << "\nСамая дорогая книга:" << books[maxIndex].title << std::endl;
}
void dynamicBookArray() {
    int n = 0;
    std::cout << "Введите количество книг в библиотеке: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Некорректное количество книг." << std::endl;
        return;
    }

    Book* books = new Book[n];

    for (int i = 0; i < n; i++) {
        std::cout << "Книга " << i + 1 << ":" << std::endl;
        std::cout << "Название: ";
        std::cin >> books[i].title;
        std::cout << "Автор: ";
        std::cin >> books[i].author;
        std::cout << "Год издания: ";
        std::cin >> books[i].year;
        std::cout << "Цена: ";
        std::cin >> books[i].price;
    }

    printBooks(books, n);
    printExpensiveBook(books, n);

    delete[] books;
}

void Fibonacci() {
    int arr1[10];
    int arr2[10];
    int sum = 0, min = 0, max = 0;

    int* p = arr1;

    *p = 0;
    *(p + 1) = 1;

    for (int i = 2; i < 10; i++) {
        *(p + i) = *(p + i - 1) + *(p + i - 2);
    }

    std::cout << "Массив Фибоначчи: ";
    for (int* ptr = p; ptr < p + 10; ptr++)
        std::cout << *ptr << " ";
    std::cout << std::endl;

    min = *p;
    max = *p;

    for (int* ptr = p; ptr < p + 10; ptr++) {
        sum += *ptr;

        if (*ptr < min){
            min = *ptr;
        }
        if(*ptr > max) {
            max = *ptr;
        }
    }

    std::cout << "Сумма элементов: " << sum << std::endl;
    std::cout << "Минимальный элемент: " << min << std::endl;
    std::cout << "Максимальный элемент: " << max << std::endl;

    int* src = p + 9;
    int* tgt = arr2;
    while (src >= p) {
        *tgt = *src;
        tgt++;
        src--;
    }

    std::cout << "Зеркальный массив : ";
    for (int* ptr = arr2; ptr < arr2 + 10; ++ptr)
        std::cout << *ptr << " ";
    std::cout << std::endl;
}

void printStudent(const Student& student) {
    std::cout << "ФИО: " << student.fullname << std::endl;
    std::cout << "Дата рождения: "
        << student.birthDate.day << "."
        << student.birthDate.month << "."
        << student.birthDate.year << std::endl;

    std::cout << "Оценки: ";
    for (int i = 0; i < 5; i++) {
        std::cout << student.grades[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Средний балл: " << getAverageRating(student) << std::endl;
    std::cout << "-*************************-" << std::endl;
}
double getAverageRating(const Student& student) {
    int sum = 0;
    for (int i = 0; i < 5; i++)
        sum += student.grades[i];
    return sum / 5.0;
}
void studentsRating() {
    Student students[3] = {
        {"Иванов Иван", {1, 1, 2025}, {5, 4, 5, 5, 4}},
        {"Петров Петр", {30, 2, 1928}, {3, 4, 4, 3, 4}},
        {"Герман Стерлингов", {9, 9, 1950}, {4, 4, 4, 4, 5}}
    };

    for (int i = 0; i < 3; i++) {
        printStudent(students[i]);
    }

    std::cout << "[*************************]" << std::endl;

    std::cout << "Студенты со средним баллом выше 4.0:" << std::endl;
    for (int i = 0; i < 3; i++) {
        if (getAverageRating(students[i]) > 4.0) {
            printStudent(students[i]);
        }
    }
}

void arrayInfo(int* arr, int size) {
    if (size <= 0) {
        std::cout << "Массив пустой или имеет некорректный размер." << std::endl;
        return;
    }

    int sum = 0;

    for (int i = 0; i < size; i++) {
        sum += *(arr + i);
    }

    std::cout << "Размер массива: " << size << std::endl;
    std::cout << "Сумма элементов: " << sum << std::endl;
    std::cout << "Первый элемент: " << *arr << std::endl;
    std::cout << "Последний элемент: " << *(arr + size - 1) << std::endl;
}

void utilityArray() {
    int arr1[] = { 1, 2, 3, 4, 5 };
    int arr2[] = { 10, 20, 30, 40, 50, 60, 80, 100, 200, 400 };


    std::cout << "первый массив:" << std::endl;
    arrayInfo(arr1, 5);

    std::cout << "второй массив:" << std::endl;
    arrayInfo(arr2, 10);
}