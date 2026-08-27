#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

class Person {
protected:
    std::string name;
    std::string phone;
    std::string email;

public:
    Person();
    Person(const std::string& name, const std::string& phone, const std::string& email);
    Person(const Person& other);
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

#endif
