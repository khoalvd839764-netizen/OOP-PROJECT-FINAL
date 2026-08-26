#ifndef CLOTHING_PRODUCT_H
#define CLOTHING_PRODUCT_H

#include "Product.h"
#include <string>

class ClothingProduct : public Product {
private:
    string size;
    string material;

public:
    ClothingProduct();
    ClothingProduct(const string& id, const string& name, double price,
                    int stockQuantity, const string& size, const string& material);

    string getSize() const;
    string getMaterial() const;

    void displayInfo() const override;
    double calculateFinalPrice() const override;
    string getType() const override;
    Product* clone() const override;
};

#endif
