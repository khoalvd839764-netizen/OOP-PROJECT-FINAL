#ifndef FOOD_PRODUCT_H
#define FOOD_PRODUCT_H

#include "Product.h"

// Lop Thuc pham: co han su dung va dac tinh huu co (Organic tang 5% gia)
class FoodProduct : public Product {
private:
    std::string expiryDate; // Han su dung (YYYY-MM-DD)
    bool isOrganic;         // Co huu co

public:
    FoodProduct();
    FoodProduct(const std::string& id, const std::string& name, double price,
                int stock, const std::string& expiryDate, bool isOrganic);

    std::string getExpiryDate() const;
    bool getIsOrganic() const;

    void displayInfo() const override;
    double calculateFinalPrice() const override;
    std::string getType() const override;
    Product* clone() const override;
};

#endif // FOOD_PRODUCT_H
