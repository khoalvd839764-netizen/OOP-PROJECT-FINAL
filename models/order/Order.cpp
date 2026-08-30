#include "Order.h"
#include <iomanip>
#include <sstream>

Order::Order()
    : orderId(""), customer(), items(), orderDate(""),
      expectedDeliveryDate(""), shippingFee(0.0), totalAmount(0.0), status("Pending"),
      paymentMethod(std::make_shared<CashPayment>()), discountAmount(0.0),
      isFreeshipApplied(false), earnedPoints(0) {}

// [FIX - 30/08/2026]: Khoi tao don hang kem Phuong thuc thanh toan, Giam gia VIP va Voucher Freeship
Order::Order(const Customer& customer, const std::vector<CartItem>& items, 
             std::shared_ptr<PaymentMethod> paymentMethod, bool useFreeshipVoucher)
    : customer(customer), items(items), status("Confirmed"),
      paymentMethod(paymentMethod ? paymentMethod : std::make_shared<CashPayment>()),
      isFreeshipApplied(useFreeshipVoucher) {
    this->orderId = generateOrderId();
    this->orderDate = getSystemDate();
    this->expectedDeliveryDate = calcExpectedDelivery();

    double rawShipping = calculateShipping();
    this->shippingFee = (useFreeshipVoucher ? 0.0 : rawShipping);

    double itemsTotal = 0.0;
    for (const auto& item : items) {
        itemsTotal += item.getSubtotal();
    }
    this->discountAmount = itemsTotal * customer.getTierDiscountRate();
    this->totalAmount = (itemsTotal - this->discountAmount) + this->shippingFee;
    this->earnedPoints = static_cast<int>((this->totalAmount / 10000.0) * 1000.0);
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

// [FIX - 30/08/2026]: Cap nhat tinh phi giao hang va thoi gian giao theo khu vuc (TPHCM/HN 10k/1ngay, tinh khac 25k/3ngay)
bool Order::isInnerCityArea(const std::string& address) const {
    std::string lowerAddr = address;
    for (char& c : lowerAddr) {
        c = std::tolower(static_cast<unsigned char>(c));
    }
    return (lowerAddr.find("hcm") != std::string::npos ||
            lowerAddr.find("ho chi minh") != std::string::npos ||
            lowerAddr.find("tphcm") != std::string::npos ||
            lowerAddr.find("tp.hcm") != std::string::npos ||
            lowerAddr.find("ha noi") != std::string::npos ||
            lowerAddr.find("hanoi") != std::string::npos ||
            lowerAddr.find("hn") != std::string::npos);
}

std::string Order::calcExpectedDelivery() const {
    std::time_t now = std::time(nullptr);
    std::tm* ltm = std::localtime(&now);
    if (isInnerCityArea(customer.getAddress())) {
        ltm->tm_mday += 1; // Noi thanh TPHCM/HN: Giao trong 1 ngay
    } else {
        ltm->tm_mday += 3; // Ngoai thanh / Tinh khac: Giao trong 3 ngay
    }
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
    // Don hang tren 500,000 VND duoc Mien phi ship
    if (subtotalSum >= 500000.0 || items.empty()) {
        return 0.0;
    }
    // TPHCM hoac Ha Noi: phi 10,000 VND; Tinh khac: phi 25,000 VND
    if (isInnerCityArea(customer.getAddress())) {
        return 10000.0;
    }
    return 25000.0;
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

double Order::getDiscountAmount() const {
    return discountAmount;
}

int Order::getEarnedPoints() const {
    return earnedPoints;
}

bool Order::getIsFreeshipApplied() const {
    return isFreeshipApplied;
}

std::string Order::getStatus() const {
    return status;
}

std::shared_ptr<PaymentMethod> Order::getPaymentMethod() const {
    return paymentMethod;
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
    std::cout << "  Ngay giao du kien: " << expectedDeliveryDate 
              << (isInnerCityArea(customer.getAddress()) ? " (Giao hoa toc 1 ngay - TPHCM/HN)\n" : " (Giao tieu chuan 3 ngay - Tinh khac)\n");
    std::cout << "  Trang thai don   : " << status << '\n';
    std::cout << "  Phuong thuc TT   : " << (paymentMethod ? paymentMethod->getMethodName() : "Tien mat (COD)") << '\n';
    std::cout << "  Chi tiet TT      : " << (paymentMethod ? paymentMethod->getPaymentDetails(orderId) : "") << '\n';
    std::cout << "-----------------------------------------------------------------------------------------\n";
    std::cout << "  THONG TIN KHACH HANG:\n";
    std::cout << "  - Ho va ten      : " << customer.getName() << '\n';
    std::cout << "  - So dien thoai  : " << customer.getPhone() << '\n';
    std::cout << "  - Email          : " << customer.getEmail() << '\n';
    std::cout << "  - Dia chi giao   : " << customer.getAddress() << '\n';
    std::cout << "  - Hang thanh vien: " << customer.getMembershipTier() << '\n';
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
    if (discountAmount > 0.0) {
        std::cout << "  Giam gia VIP     : -" << std::setw(14) << discountAmount << " VND (" << customer.getMembershipTier() << ")\n";
    }
    std::cout << "  Phi giao hang    : " << std::setw(15) 
              << (isFreeshipApplied ? "0 VND (Doi 20k diem Freeship)" : (shippingFee == 0.0 ? "MIEN PHI (0 VND)" : std::to_string(static_cast<int>(shippingFee)) + " VND")) << '\n';
    std::cout << "  ---------------------------------------------------------------------------------------\n";
    std::cout << "  TONG THANH TOAN  : " << std::setw(15) << totalAmount << " VND\n";
    std::cout << "  Diem tich luy duoc: +" << earnedPoints << " pts (Moi 10k VND duoc +1.000 diem)\n";
    std::cout << "=========================================================================================\n";

    // In huong dan thanh toan chuyen khoan neu can
    if (paymentMethod) {
        paymentMethod->displayGuide(orderId, totalAmount);
    }
}

bool Order::operator==(const Order& other) const {
    return this->orderId == other.orderId;
}

std::ostream& operator<<(std::ostream& os, const Order& order) {
    order.displayOrder();
    return os;
}
