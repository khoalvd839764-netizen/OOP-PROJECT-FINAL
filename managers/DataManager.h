#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <vector>
#include <algorithm>
#include <functional>

// Lop Template dung chung DataManager<T> de quan ly danh sach va ho tro filter/sort bang Lambda
template <typename T>
class DataManager {
private:
    std::vector<T> items;

public:
    void add(const T& item) {
        items.push_back(item);
    }

    bool remove(int index) {
        if (index < 0 || index >= static_cast<int>(items.size())) {
            return false;
        }
        items.erase(items.begin() + index);
        return true;
    }

    const std::vector<T>& getAll() const {
        return items;
    }

    size_t count() const {
        return items.size();
    }

    T& operator[](int index) {
        return items[index];
    }

    const T& operator[](int index) const {
        return items[index];
    }

    // Loc du lieu bang bieu thuc Lambda
    template <typename Func>
    std::vector<T> filter(Func condition) const {
        std::vector<T> result;
        for (const T& item : items) {
            if (condition(item)) {
                result.push_back(item);
            }
        }
        return result;
    }

    // Sap xep du lieu bang Lambda
    template <typename Func>
    void sort(Func comparator) {
        std::sort(items.begin(), items.end(), comparator);
    }

    // Tim phan tu dau tien thoa man dieu kien Lambda
    template <typename Func>
    T* find(Func condition) {
        for (T& item : items) {
            if (condition(item)) {
                return &item;
            }
        }
        return nullptr;
    }
};

#endif // DATA_MANAGER_H
