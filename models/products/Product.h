#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
#include <memory>

using namespace std;

// Lop co so truu tuong dai dien cho San pham chung
class Product {
protected:
    string id;            // Ma san pham
    string name;          // Ten san pham
    string category;      // Danh muc
    double price;         // Don gia goc
    int stockQuantity;    // So luong ton kho

public:
    Product(string id = "", string name = "", string category = "", double price = 0, int stockQuantity = 0) {
        this->id = id;
        this->name = name;
        this->category = category;
        this->price = (price >= 0) ? price : 0;
        this->stockQuantity = (stockQuantity >= 0) ? stockQuantity : 0;
    }

    Product(const Product& other) {
        this->id = other.id;
        this->name = other.name;
        this->category = other.category;
        this->price = other.price;
        this->stockQuantity = other.stockQuantity;
    }

    virtual ~Product() = default;

    string getId() const { return id; }
    string getName() const { return name; }
    string getCategory() const { return category; }
    double getPrice() const { return price; }
    int getStockQuantity() const { return stockQuantity; }
    
    // [FIX - 30/08/2026]: Them alias getStock() de dong bo voi cach goi ham trong OrderingApp
    int getStock() const { return stockQuantity; }

    void setPrice(double price);
    void setStockQuantity(int stockQuantity);
    
    // Phuong thuc thuan ao bat buoc cac lop con phai override
    virtual void displayInfo() const = 0;
    virtual double calculateFinalPrice() const = 0;
    virtual string getType() const = 0;
    virtual Product* clone() const = 0;

    // Nap chong toan tu
    bool operator==(const Product& other) const;
    bool operator<(const Product& other) const;
    friend ostream& operator<<(ostream &os, const Product &p);
    friend istream& operator>>(istream &is, Product &p);
};

#endif // PRODUCT_H
