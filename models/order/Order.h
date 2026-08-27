#ifndef ORDER_H
#define ORDER_H

#include "../person/Customer.h"
#include "../cart/CartItem.h"
#include <vector>
#include <string>
#include <ctime>
#include <iostream>

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

    static std::string generateOrderId();
    static std::string getSystemDate();
    static std::string calcExpectedDelivery();
    double calculateShipping() const;
    double calculateTotal() const;

public:
    Order();
    Order(const Customer& customer, const std::vector<CartItem>& items);

    std::string getOrderId() const;
    Customer getCustomer() const;
    const std::vector<CartItem>& getItems() const;
    std::string getOrderDate() const;
    std::string getExpectedDelivery() const;
    double getShippingFee() const;
    double getTotalAmount() const;
    std::string getStatus() const;

    void setStatus(const std::string& status);

    void displayOrder() const;

    bool operator==(const Order& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Order& order);
};

#endif
