#ifndef ELECTRONICS_PRODUCT_H
#define ELECTRONICS_PRODUCT_H

#include "Product.h"
#include <string>
#include <iostream>
using namespace std;

class ElectronicsProduct : public Product {
private:
    int warrantyMonths;
    string brand;

public:
    ElectronicsProduct(string id ="", string name ="", double price = 0.0, int stock = 0, 
                       int warrantyMonths = 0, string brand = "");

    int getWarrantyMonths() const;
    string getBrand() const;

    void displayInfo() const override;
    double calculateFinalPrice() const override;
    string getType() const override;
    Product* clone() const override;
};

#endif
