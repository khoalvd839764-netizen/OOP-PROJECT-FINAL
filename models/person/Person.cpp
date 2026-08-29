#include "Person.h"

Person::Person()
    : name(""), phone(""), email("") {}

Person::Person(const std::string& name, const std::string& phone, const std::string& email)
    : name(name), phone(phone), email(email) {}

Person::Person(const Person& other)
    : name(other.name), phone(other.phone), email(other.email) {}

std::string Person::getName() const {
    return name;
}

std::string Person::getPhone() const {
    return phone;
}

std::string Person::getEmail() const {
    return email;
}

void Person::setName(const std::string& name) {
    this->name = name;
}

void Person::setPhone(const std::string& phone) {
    this->phone = phone;
}

void Person::setEmail(const std::string& email) {
    this->email = email;
}

std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << "Ho ten: " << p.name
       << " | SDT: " << p.phone
       << " | Email: " << p.email;
    return os;
}

std::istream& operator>>(std::istream& is, Person& p) {
    std::cout << "Nhap ho ten: ";
    std::getline(is >> std::ws, p.name);
    std::cout << "Nhap SDT: ";
    is >> p.phone;
    std::cout << "Nhap email: ";
    is >> p.email;
    return is;
}
