#ifndef ORDER_H
#define ORDER_H

#include "../person/Customer.h"
#include "../cart/CartItem.h"
#include "../payment/PaymentMethod.h"
#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include <memory>

class Order {
private:
    std::string orderId;
    Customer customer;
    std::vector<CartItem> items;
    std::string orderDate;
    std::string expectedDeliveryDate;
    double shippingFee;
    double totalAmount;
    std::string status;
    
    // [FIX - 30/08/2026]: Bo sung thuoc tinh Phuong thuc thanh toan (Strategy Pattern)
    std::shared_ptr<PaymentMethod> paymentMethod;
    // [FIX - 30/08/2026]: Bo sung thong tin giam gia VIP, voucher Freeship va diem tich luy
    double discountAmount;
    bool isFreeshipApplied;
    int earnedPoints;

    static std::string generateOrderId();
    static std::string getSystemDate();
    // [FIX - 30/08/2026]: Cap nhat tinh phi giao hang va thoi gian giao theo khu vuc (TPHCM/HN 10k/1ngay, tinh khac 25k/3ngay)
    bool isInnerCityArea(const std::string& address) const;
    std::string calcExpectedDelivery() const;
    double calculateShipping() const;
    double calculateTotal() const;

public:
    Order();
    Order(const Customer& customer, const std::vector<CartItem>& items, 
          std::shared_ptr<PaymentMethod> paymentMethod = nullptr, bool useFreeshipVoucher = false);

    std::string getOrderId() const;
    Customer getCustomer() const;
    const std::vector<CartItem>& getItems() const;
    std::string getOrderDate() const;
    std::string getExpectedDelivery() const;
    double getShippingFee() const;
    double getTotalAmount() const;
    double getDiscountAmount() const;
    int getEarnedPoints() const;
    bool getIsFreeshipApplied() const;
    std::string getStatus() const;
    std::shared_ptr<PaymentMethod> getPaymentMethod() const;

    void setStatus(const std::string& status);

    void displayOrder() const;

    bool operator==(const Order& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Order& order);
};

#endif // ORDER_H
