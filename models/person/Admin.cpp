#include "Admin.h"

Admin::Admin()
    : Person("Quan Tri Vien", "0900000000", "admin@orderingapp.com"),
      username("admin"), password("123"), adminRole("Quan tri vien he thong") {}

Admin::Admin(const std::string& name, const std::string& phone, const std::string& email,
             const std::string& username, const std::string& password,
             const std::string& adminRole)
    : Person(name, phone, email),
      username(username), password(password), adminRole(adminRole) {}

std::string Admin::getUsername() const {
    return username;
}

std::string Admin::getPassword() const {
    return password;
}

std::string Admin::getAdminRole() const {
    return adminRole;
}

void Admin::setPassword(const std::string& newPassword) {
    this->password = newPassword;
}

void Admin::setAdminRole(const std::string& role) {
    this->adminRole = role;
}

void Admin::displayInfo() const {
    std::cout << "[ADMIN PORTAL] Ho ten: " << name
              << " | SDT: " << phone
              << " | Email: " << email
              << " | Tai khoan: " << username
              << " | Chuc vu: " << adminRole << '\n';
}
