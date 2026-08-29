#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <vector>
#include <algorithm>
#include <functional>

template <typename T>
class DataManager {
private:
    std::vector<T> items;

public:
    // Thêm phần tử
    void add(const T& item) {
        items.push_back(item);
    }

    // Xóa phần tử theo index
    bool remove(int index) {
        if (index < 0 || index >= static_cast<int>(items.size())) {
            return false;
        }

        items.erase(items.begin() + index);
        return true;
    }

    // Lấy toàn bộ dữ liệu
    const std::vector<T>& getAll() const {
        return items;
    }

    // Đếm số lượng phần tử
    size_t count() const {
        return items.size();
    }

    // Truy cập phần tử
    T& operator[](int index) {
        return items[index];
    }

    const T& operator[](int index) const {
        return items[index];
    }

    // Lọc dữ liệu bằng Lambda
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

    // Sắp xếp dữ liệu bằng Lambda
    template <typename Func>
    void sort(Func comparator) {
        std::sort(items.begin(), items.end(), comparator);
    }

    // Tìm phần tử đầu tiên thỏa điều kiện
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

#endif
