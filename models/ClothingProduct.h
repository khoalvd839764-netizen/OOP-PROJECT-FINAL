#ifndef CLOTHING_PRODUCT_H
#define CLOTHING_PRODUCT_H

#include "Product.h"
#include <string>

using namespace std;

class ClothingProduct : public Product {
private:
    string size;
    string material;

public:
    ClothingProduct(
        string id = "",
        string name = "",
        double price = 0,
        int stockQuantity = 0,
        string size = "",
        string material = ""
    );

    string getSize() const;
    string getMaterial() const;

    void displayInfo() const override;
    double calculateFinalPrice() const override;
    string getType() const override;
    Product* clone() const override;
};

#endif
