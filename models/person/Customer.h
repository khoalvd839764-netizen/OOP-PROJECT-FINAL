#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"
#include <vector>
#include <string>

class Customer : public Person {
private:
    std::string customerId;
    std::string address;
    std::vector<std::string> orderHistory; // Danh sach ma don hang da dat

public:
    Customer();
    Customer(const std::string& id, const std::string& name, const std::string& phone,
             const std::string& email, const std::string& address);

    std::string getCustomerId() const;
    std::string getAddress() const;
    void setAddress(const std::string& address);

    void addOrderHistory(const std::string& orderId);
    const std::vector<std::string>& getOrderHistory() const;
    int getOrderCount() const;

    void displayInfo() const override;
};

#endif
