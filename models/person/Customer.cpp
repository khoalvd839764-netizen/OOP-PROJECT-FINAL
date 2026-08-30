#include "Customer.h"

Customer::Customer()
    : Person("", "", ""), customerId(""), address(""), username(""), password(""), loyaltyPoints(0) {}

// [FIX - 30/08/2026]: Bo sung tai khoan thanh vien, diem thuong va phan hang VIP
Customer::Customer(const std::string& id, const std::string& name, const std::string& phone,
                   const std::string& email, const std::string& address,
                   const std::string& username, const std::string& password,
                   int loyaltyPoints)
    : Person(name, phone, email), customerId(id), address(address),
      username(username), password(password), loyaltyPoints(loyaltyPoints) {}

std::string Customer::getCustomerId() const {
    return customerId;
}

std::string Customer::getAddress() const {
    return address;
}

void Customer::setAddress(const std::string& address) {
    this->address = address;
}

std::string Customer::getUsername() const {
    return username;
}

void Customer::setUsername(const std::string& username) {
    this->username = username;
}

std::string Customer::getPassword() const {
    return password;
}

void Customer::setPassword(const std::string& password) {
    this->password = password;
}

int Customer::getLoyaltyPoints() const {
    return loyaltyPoints;
}

void Customer::setLoyaltyPoints(int points) {
    this->loyaltyPoints = points;
}

void Customer::addLoyaltyPoints(int points) {
    this->loyaltyPoints += points;
}

bool Customer::usePointsForFreeship() {
    if (loyaltyPoints >= 20000) {
        loyaltyPoints -= 20000;
        return true;
    }
    return false;
}

std::string Customer::getMembershipTier() const {
    if (loyaltyPoints >= 1000000) {
        return "Thanh vien VANG (Giam 15%)";
    } else if (loyaltyPoints >= 500000) {
        return "Thanh vien BAC (Giam 5%)";
    } else if (loyaltyPoints >= 200000) {
        return "Thanh vien DONG (Giam 3%)";
    }
    return "Thanh vien Tieu Chuan (0%)";
}

double Customer::getTierDiscountRate() const {
    if (loyaltyPoints >= 1000000) {
        return 0.15; // Giam 15%
    } else if (loyaltyPoints >= 500000) {
        return 0.05; // Giam 5%
    } else if (loyaltyPoints >= 200000) {
        return 0.03; // Giam 3%
    }
    return 0.0;
}

void Customer::addOrderHistory(const std::string& orderId) {
    orderHistory.push_back(orderId);
}

const std::vector<std::string>& Customer::getOrderHistory() const {
    return orderHistory;
}

int Customer::getOrderCount() const {
    return static_cast<int>(orderHistory.size());
}

void Customer::displayInfo() const {
    std::cout << "[KHACH HANG] Ma: " << customerId
              << " | Ten: " << name
              << " | SDT: " << phone
              << " | Email: " << email
              << " | Dia chi: " << address
              << " | Hang: " << getMembershipTier()
              << " | Diem: " << loyaltyPoints << " pts\n";
}
