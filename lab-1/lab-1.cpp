// lab-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <locale>
#include <windows.h>

struct Complex {
    double real;
    double imag;
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

int main()
{
    setlocale(LC_ALL, "Russian");
    //temperatureExample();
    //manipulateString();
    //complexCalculate();
    swapIntegers();
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