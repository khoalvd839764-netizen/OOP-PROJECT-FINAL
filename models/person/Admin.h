#ifndef ADMIN_H
#define ADMIN_H

#include "Person.h"
#include <string>
#include <iostream>

// [FIX - 31/08/2026]: Lop Admin ke thua tu Person, dai dien cho Quan tri vien he thong
class Admin : public Person {
private:
    std::string username;
    std::string password;
    std::string adminRole; // Chuc vu (vi du: "Quan tri vien he thong", "Quan ly kho")

public:
    Admin();
    Admin(const std::string& name, const std::string& phone, const std::string& email,
          const std::string& username = "admin", const std::string& password = "123",
          const std::string& adminRole = "Quan tri vien he thong");

    std::string getUsername() const;
    std::string getPassword() const;
    std::string getAdminRole() const;

    void setPassword(const std::string& newPassword);
    void setAdminRole(const std::string& role);

    void displayInfo() const override;
};

#endif // ADMIN_H
