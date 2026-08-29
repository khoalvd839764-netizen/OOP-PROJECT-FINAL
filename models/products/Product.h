#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Product {
    protected:
    string id, name, category;
    double price;
    int stockQuantity;
    public:
    Product(string id="", string name="", string category="", double price=0, int stockQuantity=0){
        this->id = id;
        this->name = name;
        this->category = category;
        this->price = (price >= 0) ? price : 0;
        this->stockQuantity = (stockQuantity >= 0) ? stockQuantity : 0;
    }
    Product(const Product& other){
        this->id = other.id;
        this->name = other.name;
        this->category = other.category;
        this->price = other.price;
        this->stockQuantity = other.stockQuantity;
    }
    virtual ~Product() = default;


    string getId() const {return id;}
    string getName() const {return name;}
    string getCategory() const {return category;}
    double getPrice() const {return price;}
    int getStockQuantity() const {return stockQuantity;}

    void setPrice(double price);
    void setStockQuantity(int stockQuantity);
    
    virtual void displayInfo() const = 0;
    virtual double calculateFinalPrice() const = 0;
    virtual string getType() const = 0;
    virtual Product* clone() const = 0;

    bool operator==(const Product& other) const;
    bool operator<(const Product& other) const;
    friend ostream& operator<<(ostream &os, const Product &p);
    friend istream& operator>>(istream &is, Product &p);
};

#endif
