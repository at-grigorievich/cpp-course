// lab-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <locale>
#include <windows.h>

void temperatureExample();

int main()
{
    setlocale(LC_ALL, "Russian");
    temperatureExample();
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

    std::cout << "Средняя температура: " << average << std::endl;
    std::cout << "Минимальная температура: " << minTemp << std::endl;
    std::cout << "Максимальная температура: " << maxTemp << std::endl;
    std::cout << "Количество дней с температурой ниже средней: " << lowerAverageDays << std::endl;
}
