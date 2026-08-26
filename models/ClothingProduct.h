#ifndef CLOTHING_PRODUCT_H
#define CLOTHING_PRODUCT_H

#include "Product.h"
#include <string>

class ClothingProduct : public Product {
private:
    std::string size;
    std::string material;

public:
    ClothingProduct();
    ClothingProduct(const std::string& id, const std::string& name, double price,
                    int stockQuantity, const std::string& size, const std::string& material);

    std::string getSize() const;
    std::string getMaterial() const;

    void displayInfo() const override;
    double calculateFinalPrice() const override;
    std::string getType() const override;
    Product* clone() const override;
};

#endif
