#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"
#include <vector>
#include <string>

// Lop Khach hang & Tai khoan thanh vien (Tich diem, Doi Freeship, Phan hang VIP)
class Customer : public Person {
private:
    std::string customerId;
    std::string address;
    std::vector<std::string> orderHistory; // Danh sach ma don hang da dat
    
    // [FIX - 30/08/2026]: Bo sung tai khoan thanh vien, diem thuong va phan hang VIP
    std::string username;
    std::string password;
    int loyaltyPoints;

public:
    Customer();
    Customer(const std::string& id, const std::string& name, const std::string& phone,
             const std::string& email, const std::string& address,
             const std::string& username = "", const std::string& password = "",
             int loyaltyPoints = 0);

    std::string getCustomerId() const;
    std::string getAddress() const;
    void setAddress(const std::string& address);

    std::string getUsername() const;
    void setUsername(const std::string& username);
    std::string getPassword() const;
    void setPassword(const std::string& password);
    int getLoyaltyPoints() const;
    void setLoyaltyPoints(int points);
    void addLoyaltyPoints(int points);
    void deductLoyaltyPoints(int points); // [FIX - 31/08/2026]: Thu hoi diem khi huy don hang
    bool usePointsForFreeship(); // Doi 20.000 diem lay 1 lan Freeship

    // Phan hang thanh vien va chiet khau: Dong (3%), Bac (5%), Vang (15%)
    std::string getMembershipTier() const;
    double getTierDiscountRate() const;

    void addOrderHistory(const std::string& orderId);
    const std::vector<std::string>& getOrderHistory() const;
    int getOrderCount() const;

    void displayInfo() const override;
};

#endif // CUSTOMER_H
