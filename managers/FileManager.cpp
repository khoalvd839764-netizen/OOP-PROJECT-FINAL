#include "FileManager.h"

#include "../models/products/ClothingProduct.h"
#include "../models/products/ElectronicsProduct.h"
#include "../models/products/FoodProduct.h"

#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static std::string getDataPrefix() {
    static std::string basePrefix = "";
    static bool resolved = false;
    if (resolved) return basePrefix;

    const std::vector<std::string> candidates = {
        "",
        "Source code/",
        "../",
        "../../",
        "../../../",
        "../Source code/",
        "../../Source code/"
    };

    for (const auto& c : candidates) {
        std::ifstream f(c + "data/products.txt");
        if (f.is_open()) {
            basePrefix = c;
            resolved = true;
            return basePrefix;
        }
    }
    resolved = true;
    return "";
}

static std::string resolvePath(const std::string& filename) {
    std::ifstream f(filename);
    if (f.is_open()) return filename;
    return getDataPrefix() + filename;
}

std::vector<std::shared_ptr<Product>> FileManager::loadProducts(
    const std::string& filename) {
    std::string resolvedFile = resolvePath(filename);
    std::vector<std::shared_ptr<Product>> products;
    std::ifstream inputFile(resolvedFile);

    if (!inputFile.is_open()) {
        std::cerr << "Khong the mo file san pham: " << resolvedFile << '\n';
        return products;
    }

    std::string line;
    std::getline(inputFile, line);

    int lineNumber = 1;
    while (std::getline(inputFile, line)) {
        ++lineNumber;

        if (line.empty() || line == "\r") {
            continue;
        }

        std::stringstream ss(line);
        std::vector<std::string> fields;
        std::string token;

        while (std::getline(ss, token, '|')) {
            if (!token.empty() && token.back() == '\r') {
                token.pop_back();
            }
            fields.push_back(token);
        }

        if (fields.size() != 7) {
            std::cerr << "Bo qua dong " << lineNumber
                      << " vi khong du 7 cot du lieu.\n";
            continue;
        }

        const std::string& type = fields[0];
        const std::string& id = fields[1];
        const std::string& name = fields[2];

        try {
            const double price = std::stod(fields[3]);
            const int stock = std::stoi(fields[4]);

            if (type == "FOOD") {
                const bool isOrganic = (fields[6] == "true" || fields[6] == "1");
                products.push_back(std::make_shared<FoodProduct>(
                    id, name, price, stock, fields[5], isOrganic));
            } else if (type == "ELECTRONICS") {
                const int warrantyMonths = std::stoi(fields[5]);
                products.push_back(std::make_shared<ElectronicsProduct>(
                    id, name, price, stock, warrantyMonths, fields[6]));
            } else if (type == "CLOTHING") {
                products.push_back(std::make_shared<ClothingProduct>(
                    id, name, price, stock, fields[5], fields[6]));
            } else {
                std::cerr << "Bo qua dong " << lineNumber
                          << " vi loai san pham khong hop le: " << type << '\n';
            }
        } catch (const std::exception&) {
            std::cerr << "Bo qua dong " << lineNumber
                      << " vi du lieu so khong hop le.\n";
        }
    }

    inputFile.close();
    return products;
}

void FileManager::saveOrder(const Order& order, const std::string& filename) {
    std::string resolvedFile = resolvePath(filename);
    std::ofstream outputFile(resolvedFile, std::ios::app);

    if (!outputFile.is_open()) {
        std::cerr << "Khong the mo file de luu don hang: " << resolvedFile << '\n';
        return;
    }

    const Customer customer = order.getCustomer();
    outputFile << "MA DON HANG      : " << order.getOrderId() << '\n';
    outputFile << "NGAY DAT         : " << order.getOrderDate() << '\n';
    outputFile << "NGAY GIAO DU KIEN: " << order.getExpectedDelivery() << '\n';
    outputFile << "TRANG THAI       : " << order.getStatus() << '\n';
    // [FIX - 30/08/2026]: Ghi thong tin phuong thuc thanh toan vao file orders.txt
    auto pm = order.getPaymentMethod();
    outputFile << "PHUONG THUC TT   : " << (pm ? pm->getMethodName() : "Tien mat (COD)") << '\n';
    if (pm) {
        outputFile << "CHI TIET TT      : " << pm->getPaymentDetails(order.getOrderId()) << '\n';
    }
    outputFile << "TEN KHACH HANG   : " << customer.getName() << '\n';
    outputFile << "SO DIEN THOAI    : " << customer.getPhone() << '\n';
    outputFile << "EMAIL            : " << customer.getEmail() << '\n';
    outputFile << "DIA CHI          : " << customer.getAddress() << '\n';
    outputFile << "DANH SACH SAN PHAM:\n";

    for (const CartItem& item : order.getItems()) {
        const std::shared_ptr<Product> product = item.getProduct();
        if (product == nullptr) {
            continue;
        }

        outputFile << "  - " << product->getId()
                   << " | " << product->getName()
                   << " | So luong: " << item.getQuantity()
                   << " | Don gia: " << std::fixed << std::setprecision(0)
                   << product->calculateFinalPrice() << " VND"
                   << " | Thanh tien: " << item.getSubtotal() << " VND\n";
    }

    outputFile << std::fixed << std::setprecision(0);
    outputFile << "PHI GIAO HANG    : " << order.getShippingFee() << " VND\n";
    outputFile << "TONG THANH TOAN  : " << order.getTotalAmount() << " VND\n";
    outputFile << "=========================================================\n\n";

    outputFile.close();
}

// [FIX - 30/08/2026]: Ghi de toan bo danh sach don hang khi co cap nhat trang thai huy
void FileManager::rewriteAllOrders(const std::vector<Order>& orders, const std::string& filename) {
    std::string resolvedFile = resolvePath(filename);
    std::ofstream outputFile(resolvedFile, std::ios::trunc);

    if (!outputFile.is_open()) {
        std::cerr << "Khong the mo file de cap nhat don hang: " << resolvedFile << '\n';
        return;
    }

    for (const Order& order : orders) {
        const Customer customer = order.getCustomer();
        outputFile << "MA DON HANG      : " << order.getOrderId() << '\n';
        outputFile << "NGAY DAT         : " << order.getOrderDate() << '\n';
        outputFile << "NGAY GIAO DU KIEN: " << order.getExpectedDelivery() << '\n';
        outputFile << "TRANG THAI       : " << order.getStatus() << '\n';
        auto pm = order.getPaymentMethod();
        outputFile << "PHUONG THUC TT   : " << (pm ? pm->getMethodName() : "Tien mat (COD)") << '\n';
        if (pm) {
            outputFile << "CHI TIET TT      : " << pm->getPaymentDetails(order.getOrderId()) << '\n';
        }
        outputFile << "TEN KHACH HANG   : " << customer.getName() << '\n';
        outputFile << "SO DIEN THOAI    : " << customer.getPhone() << '\n';
        outputFile << "EMAIL            : " << customer.getEmail() << '\n';
        outputFile << "DIA CHI          : " << customer.getAddress() << '\n';
        outputFile << "DANH SACH SAN PHAM:\n";

        for (const CartItem& item : order.getItems()) {
            const std::shared_ptr<Product> product = item.getProduct();
            if (product == nullptr) {
                continue;
            }

            outputFile << "  - " << product->getId()
                       << " | " << product->getName()
                       << " | So luong: " << item.getQuantity()
                       << " | Don gia: " << std::fixed << std::setprecision(0)
                       << product->calculateFinalPrice() << " VND"
                       << " | Thanh tien: " << item.getSubtotal() << " VND\n";
        }

        outputFile << std::fixed << std::setprecision(0);
        outputFile << "PHI GIAO HANG    : " << order.getShippingFee() << " VND\n";
        outputFile << "TONG THANH TOAN  : " << order.getTotalAmount() << " VND\n";
        outputFile << "=========================================================\n\n";
    }

    outputFile.close();
}

// [FIX - 30/08/2026]: Doc danh sach tai khoan nguoi dung tu file users.txt
std::vector<Customer> FileManager::loadUsers(const std::string& filename) {
    std::string resolvedFile = resolvePath(filename);
    std::vector<Customer> users;
    std::ifstream inputFile(resolvedFile);

    if (!inputFile.is_open()) {
        std::cerr << "Khong the mo file nguoi dung: " << resolvedFile << '\n';
        return users;
    }

    std::string line;
    int index = 1;
    while (std::getline(inputFile, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string username, password, name, phone, email, address, ptsStr;

        if (std::getline(ss, username, '|') &&
            std::getline(ss, password, '|') &&
            std::getline(ss, name, '|') &&
            std::getline(ss, phone, '|') &&
            std::getline(ss, email, '|') &&
            std::getline(ss, address, '|') &&
            std::getline(ss, ptsStr)) {

            int points = 0;
            try {
                points = std::stoi(ptsStr);
            } catch (...) {
                points = 0;
            }

            std::string custId = "USER-" + std::to_string(index++);
            users.emplace_back(custId, name, phone, email, address, username, password, points);
        }
    }

    inputFile.close();
    return users;
}

// [FIX - 30/08/2026]: Ghi danh sach tai khoan nguoi dung vao file users.txt
void FileManager::saveUsers(const std::vector<Customer>& users, const std::string& filename) {
    std::string resolvedFile = resolvePath(filename);
    std::ofstream outputFile(resolvedFile, std::ios::trunc);

    if (!outputFile.is_open()) {
        std::cerr << "Khong the mo file de luu nguoi dung: " << resolvedFile << '\n';
        return;
    }

    for (const auto& user : users) {
        if (user.getUsername().empty()) continue; // Khong luu khach vang lai
        outputFile << user.getUsername() << '|'
                   << user.getPassword() << '|'
                   << user.getName() << '|'
                   << user.getPhone() << '|'
                   << user.getEmail() << '|'
                   << user.getAddress() << '|'
                   << user.getLoyaltyPoints() << '\n';
    }

    outputFile.close();
}

// [FIX - 31/08/2026]: Ghi de toan bo danh sach san pham vao data/products.txt khi Admin them/sua/xoa san pham
void FileManager::saveProducts(const std::vector<std::shared_ptr<Product>>& products, const std::string& filename) {
    std::string resolvedFile = resolvePath(filename);
    std::ofstream outputFile(resolvedFile, std::ios::trunc);

    if (!outputFile.is_open()) {
        std::cerr << "Khong the mo file de luu danh muc san pham: " << resolvedFile << '\n';
        return;
    }

    // Dong tieu de
    outputFile << "TYPE|ID|NAME|PRICE|STOCK|EXTRA1|EXTRA2\n";

    for (const auto& prod : products) {
        if (!prod) continue;
        outputFile << std::fixed << std::setprecision(0);

        if (auto food = std::dynamic_pointer_cast<FoodProduct>(prod)) {
            outputFile << "FOOD|" << food->getId() << '|'
                       << food->getName() << '|'
                       << food->getPrice() << '|'
                       << food->getStockQuantity() << '|'
                       << food->getExpiryDate() << '|'
                       << (food->getIsOrganic() ? "true" : "false") << '\n';
        } else if (auto elec = std::dynamic_pointer_cast<ElectronicsProduct>(prod)) {
            outputFile << "ELECTRONICS|" << elec->getId() << '|'
                       << elec->getName() << '|'
                       << elec->getPrice() << '|'
                       << elec->getStockQuantity() << '|'
                       << elec->getWarrantyMonths() << '|'
                       << elec->getBrand() << '\n';
        } else if (auto cloth = std::dynamic_pointer_cast<ClothingProduct>(prod)) {
            outputFile << "CLOTHING|" << cloth->getId() << '|'
                       << cloth->getName() << '|'
                       << cloth->getPrice() << '|'
                       << cloth->getStockQuantity() << '|'
                       << cloth->getSize() << '|'
                       << cloth->getMaterial() << '\n';
        }
    }

    outputFile.close();
}
