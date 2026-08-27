#ifndef SHOPPING_CART_H
#define SHOPPING_CART_H

#include "CartItem.h"
#include <vector>
#include <iostream>
#include <string>

class ShoppingCart {
private:
    std::vector<CartItem> items;

public:
    ShoppingCart();

    void addItem(std::shared_ptr<Product> product, int quantity);
    bool removeItem(const std::string& productId);
    bool updateQuantity(const std::string& productId, int newQty);

    const std::vector<CartItem>& getItems() const;
    double getTotal() const;
    int getItemCount() const;
    int getTotalQuantity() const;

    void clear();
    bool isEmpty() const;
    void displayCart() const;

    ShoppingCart& operator+=(const CartItem& item);
    CartItem& operator[](int index);
    const CartItem& operator[](int index) const;

    friend std::ostream& operator<<(std::ostream& os, const ShoppingCart& cart);
};

#endif
