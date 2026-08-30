#ifndef CART_ITEM_H
#define CART_ITEM_H

#include "../products/Product.h"
#include <memory>
#include <iostream>

// Lop CartItem: Dai dien cho 1 dong san pham trong gio hang
class CartItem {
private:
    std::shared_ptr<Product> product; // Con tro thong minh quan ly san pham da hinh
    int quantity;                     // So luong mua

public:
    CartItem();
    CartItem(std::shared_ptr<Product> product, int quantity);
    CartItem(const CartItem& other);

    std::shared_ptr<Product> getProduct() const;
    int getQuantity() const;
    void setQuantity(int qty);

    double getSubtotal() const; // Tinh thanh tien = So luong * Don gia cuoi

    bool operator==(const CartItem& other) const;
    CartItem operator+(int extraQty) const; // Cong don so luong

    friend std::ostream& operator<<(std::ostream& os, const CartItem& item);
};

#endif // CART_ITEM_H
