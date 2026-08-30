#ifndef ELECTRONICS_PRODUCT_H
#define ELECTRONICS_PRODUCT_H

#include "Product.h"
#include <string>
#include <iostream>

using namespace std;

// Lop San pham Dien tu: co thoi gian bao hanh va hang san xuat (bao hanh > 12 thang tang 5% gia)
class ElectronicsProduct : public Product {
private:
    int warrantyMonths; // So thang bao hanh
    string brand;       // Hang san xuat

public:
    ElectronicsProduct(string id = "", string name = "", double price = 0.0, int stock = 0, 
                       int warrantyMonths = 0, string brand = "");

    int getWarrantyMonths() const;
    string getBrand() const;

    void displayInfo() const override;
    double calculateFinalPrice() const override;
    string getType() const override;
    Product* clone() const override;
};

#endif // ELECTRONICS_PRODUCT_H
