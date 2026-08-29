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

std::vector<std::shared_ptr<Product>> FileManager::loadProducts(
    const std::string& filename) {
    std::vector<std::shared_ptr<Product>> products;
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Khong the mo file san pham: " << filename << '\n';
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
    std::ofstream outputFile(filename, std::ios::app);

    if (!outputFile.is_open()) {
        std::cerr << "Khong the mo file de luu don hang: " << filename << '\n';
        return;
    }

    const Customer customer = order.getCustomer();
    outputFile << "MA DON HANG      : " << order.getOrderId() << '\n';
    outputFile << "NGAY DAT         : " << order.getOrderDate() << '\n';
    outputFile << "NGAY GIAO DU KIEN: " << order.getExpectedDelivery() << '\n';
    outputFile << "TRANG THAI       : " << order.getStatus() << '\n';
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

    outputFile.close();
}
