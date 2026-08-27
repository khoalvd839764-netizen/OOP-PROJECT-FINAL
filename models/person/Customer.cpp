#include "Customer.h"

Customer::Customer()
    : Person("", "", ""), customerId(""), address("") {}

Customer::Customer(const std::string& id, const std::string& name, const std::string& phone,
                   const std::string& email, const std::string& address)
    : Person(name, phone, email), customerId(id), address(address) {}

std::string Customer::getCustomerId() const {
    return customerId;
}

std::string Customer::getAddress() const {
    return address;
}

void Customer::setAddress(const std::string& address) {
    this->address = address;
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
              << " | Dia chi: " << address << '\n';
}
