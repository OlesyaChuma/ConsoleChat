#pragma once

#include <vector>
#include <string>

using namespace std;

// Универсальный шаблонный класс для хранения элементов
template <typename T>
class Storage {
private:
    vector<T> items; // внутреннее хранилище объектов

public:
    // Добавить элемент
    void add(const T& item) {
        items.push_back(item);
    }

    // Получить все элементы
    const vector<T>& getAll() const {
        return items;
    }

    // Найти элемент по индексу (если нужно прямое обращение)
    T* get(size_t index) {
        if (index < items.size())
            return &items[index];
        return nullptr;
    }

    // Очистить хранилище
    void clear() {
        items.clear();
    }

    // Количество элементов
    size_t size() const {
        return items.size();
    }
};