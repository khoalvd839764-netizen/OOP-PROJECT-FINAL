#ifndef CLOTHING_PRODUCT_H
#define CLOTHING_PRODUCT_H

#include "Product.h"
#include <string>

using namespace std;

// Lop San pham May mac / Thoi trang (chat lieu Silk/Leather tang 10% gia)
class ClothingProduct : public Product {
private:
    string size;     // Kich co (S, M, L, XL)
    string material; // Chat lieu vai (Cotton, Silk, Leather...)

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

#endif // CLOTHING_PRODUCT_H
