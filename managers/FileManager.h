#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "../models/products/Product.h"
#include "../models/order/Order.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>

class FileManager {
public:
    // [FIX - 29/08/2026]: Khai bao 2 phuong thuc static loadProducts va saveOrder vao header de link thanh cong voi FileManager.cpp
    static std::vector<std::shared_ptr<Product>> loadProducts(const std::string& filename);
    static void saveOrder(const Order& order, const std::string& filename);
    // [FIX - 30/08/2026]: Phuong thuc ghi de toan bo danh sach don hang khi co cap nhat trang thai huy
    static void rewriteAllOrders(const std::vector<Order>& orders, const std::string& filename);
    // [FIX - 30/08/2026]: Doc va ghi danh sach tai khoan nguoi dung (users.txt)
    static std::vector<Customer> loadUsers(const std::string& filename);
    static void saveUsers(const std::vector<Customer>& users, const std::string& filename);
};

#endif // FILE_MANAGER_H
