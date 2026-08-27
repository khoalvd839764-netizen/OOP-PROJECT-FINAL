#include "Order.h"
#include <iomanip>
#include <sstream>

Order::Order()
    : orderId(""), customer(), items(), orderDate(""),
      expectedDeliveryDate(""), shippingFee(0.0), totalAmount(0.0), status("Pending") {}

Order::Order(const Customer& customer, const std::vector<CartItem>& items)
    : customer(customer), items(items), status("Confirmed") {
    this->orderId = generateOrderId();
    this->orderDate = getSystemDate();
    this->expectedDeliveryDate = calcExpectedDelivery();
    this->shippingFee = calculateShipping();
    this->totalAmount = calculateTotal();
}

std::string Order::generateOrderId() {
    static int counter = 1000;
    std::stringstream ss;
    ss << "ORD-" << (++counter);
    return ss.str();
}

std::string Order::getSystemDate() {
    std::time_t now = std::time(nullptr);
    std::tm* ltm = std::localtime(&now);
    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%d/%m/%Y", ltm);
    return std::string(buffer);
}

std::string Order::calcExpectedDelivery() {
    std::time_t now = std::time(nullptr);
    std::tm* ltm = std::localtime(&now);
    ltm->tm_mday += 5; // Du kien giao sau 5 ngay
    std::mktime(ltm);  // Tu dong xu ly nhay thang/nam
    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%d/%m/%Y", ltm);
    return std::string(buffer);
}

double Order::calculateShipping() const {
    double subtotalSum = 0.0;
    for (const auto& item : items) {
        subtotalSum += item.getSubtotal();
    }
    // Don hang tren 500,000 VND duoc Mien phi ship, nguoc lai phi ship 30,000 VND
    if (subtotalSum >= 500000.0 || items.empty()) {
        return 0.0;
    }
    return 30000.0;
}

double Order::calculateTotal() const {
    double sum = 0.0;
    for (const auto& item : items) {
        sum += item.getSubtotal();
    }
    return sum + shippingFee;
}

std::string Order::getOrderId() const {
    return orderId;
}

Customer Order::getCustomer() const {
    return customer;
}

const std::vector<CartItem>& Order::getItems() const {
    return items;
}

std::string Order::getOrderDate() const {
    return orderDate;
}

std::string Order::getExpectedDelivery() const {
    return expectedDeliveryDate;
}

double Order::getShippingFee() const {
    return shippingFee;
}

double Order::getTotalAmount() const {
    return totalAmount;
}

std::string Order::getStatus() const {
    return status;
}

void Order::setStatus(const std::string& status) {
    this->status = status;
}

void Order::displayOrder() const {
    std::cout << "\n=========================================================================================\n";
    std::cout << "                                  HOA DON DAT HANG                                       \n";
    std::cout << "=========================================================================================\n";
    std::cout << "  Ma don hang      : " << orderId << '\n';
    std::cout << "  Ngay dat hang    : " << orderDate << " (Lay tu he thong)\n";
    std::cout << "  Ngay giao du kien: " << expectedDeliveryDate << " (+5 ngay)\n";
    std::cout << "  Trang thai don   : " << status << '\n';
    std::cout << "-----------------------------------------------------------------------------------------\n";
    std::cout << "  THONG TIN KHACH HANG:\n";
    std::cout << "  - Ho va ten      : " << customer.getName() << '\n';
    std::cout << "  - So dien thoai  : " << customer.getPhone() << '\n';
    std::cout << "  - Email          : " << customer.getEmail() << '\n';
    std::cout << "  - Dia chi giao   : " << customer.getAddress() << '\n';
    std::cout << "-----------------------------------------------------------------------------------------\n";
    std::cout << "  DANH SACH SAN PHAM:\n";
    std::cout << "  " << std::left << std::setw(8) << "MA SP" 
              << " | " << std::setw(22) << "TEN SAN PHAM" 
              << " | " << std::setw(6) << "SL" 
              << " | " << std::setw(14) << "DON GIA" 
              << " | " << std::setw(16) << "THANH TIEN" << '\n';
    std::cout << "  ---------------------------------------------------------------------------------------\n";

    double itemsTotal = 0.0;
    for (const auto& item : items) {
        std::cout << "  " << item << '\n';
        itemsTotal += item.getSubtotal();
    }

    std::cout << "-----------------------------------------------------------------------------------------\n";
    std::cout << "  Tong tien hang   : " << std::fixed << std::setprecision(0) << std::setw(15) << itemsTotal << " VND\n";
    std::cout << "  Phi giao hang    : " << std::setw(15) << (shippingFee == 0.0 ? "MIEN PHI (0 VND)" : std::to_string(static_cast<int>(shippingFee)) + " VND") << '\n';
    std::cout << "  ---------------------------------------------------------------------------------------\n";
    std::cout << "  TONG THANH TOAN  : " << std::setw(15) << totalAmount << " VND\n";
    std::cout << "=========================================================================================\n";
}

bool Order::operator==(const Order& other) const {
    return this->orderId == other.orderId;
}

std::ostream& operator<<(std::ostream& os, const Order& order) {
    order.displayOrder();
    return os;
}
