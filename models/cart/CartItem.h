#ifndef CART_ITEM_H
#define CART_ITEM_H

#include "../products/Product.h"
#include <memory>
#include <iostream>

class CartItem {
private:
    std::shared_ptr<Product> product;
    int quantity;

public:
    CartItem();
    CartItem(std::shared_ptr<Product> product, int quantity);
    CartItem(const CartItem& other);

    std::shared_ptr<Product> getProduct() const;
    int getQuantity() const;
    void setQuantity(int qty);

    double getSubtotal() const;

    bool operator==(const CartItem& other) const;
    CartItem operator+(int extraQty) const;

    friend std::ostream& operator<<(std::ostream& os, const CartItem& item);
};

#endif
