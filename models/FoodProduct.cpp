#include "FoodProduct.h"

FoodProduct::FoodProduct()
    : Product("", "", "Food", 0, 0), expiryDate(""), isOrganic(false) {}

FoodProduct::FoodProduct(const std::string& id, const std::string& name,
                         double price, int stock,
                         const std::string& expiryDate, bool isOrganic)
    : Product(id, name, "Food", price, stock),
      expiryDate(expiryDate),
      isOrganic(isOrganic) {}

std::string FoodProduct::getExpiryDate() const {
    return expiryDate;
}

bool FoodProduct::getIsOrganic() const {
    return isOrganic;
}

void FoodProduct::displayInfo() const {
    std::cout << "[FOOD] " << name
              << " | " << price << " VND"
              << " | HSD: " << expiryDate
              << " | Hữu cơ: " << (isOrganic ? "Có" : "Không")
              << '\n';
}

double FoodProduct::calculateFinalPrice() const {
    return isOrganic ? price * 1.05 : price;
}

std::string FoodProduct::getType() const {
    return "FOOD";
}

Product* FoodProduct::clone() const {
    return new FoodProduct(*this);
}
