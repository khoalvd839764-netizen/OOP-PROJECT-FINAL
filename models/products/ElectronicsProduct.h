#ifndef ELECTRONICS_PRODUCT_H
#define ELECTRONICS_PRODUCT_H

#include "Product.h"
#include "ITaxable.h"
#include <string>
#include <iostream>

using namespace std;

// [FIX - 05/09/2026]: ĐA KẾ THỪA (Multiple Inheritance) - Kế thừa từ Product VÀ ITaxable
class ElectronicsProduct : public Product, public ITaxable {
private:
    int warrantyMonths; // So thang bao hanh
    string brand;       // Hang san xuat

public:
    ElectronicsProduct(string id = "", string name = "", double price = 0.0, int stock = 0, 
                       int warrantyMonths = 0, string brand = "");

    int getWarrantyMonths() const;
    string getBrand() const;

    // Override cac phuong thuc thuan ao tu Product
    void displayInfo() const override;
    double calculateFinalPrice() const override;
    string getType() const override;
    Product* clone() const override;

    // Override cac phuong thuc thuan ao tu ITaxable (Giao dien thue VAT)
    double getVATRate() const override;
    double calculateVAT() const override;
    void displayTaxInfo() const override;
};

#endif // ELECTRONICS_PRODUCT_H
