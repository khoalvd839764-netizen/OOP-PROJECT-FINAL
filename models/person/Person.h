#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

// Lop truu tuong co so dai dien cho Nguoi dung
class Person {
protected:
    std::string name;  // Ho ten
    std::string phone; // So dien thoai
    std::string email; // Email

public:
    Person();
    Person(const std::string& name, const std::string& phone, const std::string& email);
    Person(const Person& other);

    // [FIX - 30/08/2026]: Khai bao explicitly operator= default de khong bi warning -Wdeprecated-copy tren gcc/clang
    Person& operator=(const Person& other) = default;
    virtual ~Person() = default;

    std::string getName() const;
    std::string getPhone() const;
    std::string getEmail() const;

    void setName(const std::string& name);
    void setPhone(const std::string& phone);
    void setEmail(const std::string& email);

    virtual void displayInfo() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Person& p);
    friend std::istream& operator>>(std::istream& is, Person& p);
};

#endif // PERSON_H
