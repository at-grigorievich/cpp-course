#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>

namespace generic_structures {

    template<typename T>
    class stack {
    private:
        std::vector<T> elements;
        int capacity;

    public:
        stack(int size = 10) : capacity(size) {}

        void push(const T& element) {
            if (isFull())
                throw std::overflow_error("Стек переполнен");
            elements.push_back(element);
        }

        T pop() {
            if (isEmpty())
                throw std::underflow_error("Стек пуст");
            T topElement = elements.back();
            elements.pop_back();
            return topElement;
        }

        T top() const {
            if (isEmpty())
                throw std::underflow_error("Стек пуст");
            return elements.back();
        }

        bool isEmpty() const { return elements.empty(); }
        bool isFull() const { return size() >= capacity; }
        int size() const { return static_cast<int>(elements.size()); }

        void display() const {
            std::cout << "Стек: ";
            for (const auto& elem : elements)
                std::cout << elem << " ";
            std::cout << std::endl;
        }
    };

    template<typename T>
    class queue {
    private:
        std::vector<T> elements;
        int capacity;

    public:
        queue(int size = 10) : capacity(size) {}

        void enqueue(const T& element) {
            if (isFull())
                throw std::overflow_error("Очередь переполнена");
            elements.push_back(element);
        }

        T dequeue() {
            if (isEmpty())
                throw std::underflow_error("Очередь пуста");
            T frontElement = elements.front();
            elements.erase(elements.begin());
            return frontElement;
        }

        T front() const {
            if (isEmpty())
                throw std::underflow_error("Очередь пуста");
            return elements.front();
        }

        bool isEmpty() const { return elements.empty(); }
        bool isFull() const { return size() >= capacity; }
        int size() const { return static_cast<int>(elements.size()); }

        void display() const {
            std::cout << "Очередь: ";
            for (const auto& elem : elements)
                std::cout << elem << " ";
            std::cout << std::endl;
        }
    };

}
