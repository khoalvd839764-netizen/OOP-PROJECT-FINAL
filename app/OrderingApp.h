#ifndef ORDERING_APP_H
#define ORDERING_APP_H

#include <vector>
#include <memory>
#include <iostream>
#include <string>

#include "../models/Product.h"
#include "../models/Customer.h"
#include "../models/ShoppingCart.h"
#include "../models/Order.h"
#include "../services/DataManager.h"
#include "../services/FileManager.h"

class OrderingApp {
private:
    DataManager<std::shared_ptr<Product>> productManager;
    ShoppingCart cart;
    Customer currentCustomer;
    std::vector<Order> orders;

    void showProducts();
    void searchProducts();
    void addToCart();
    void viewCart();
    void placeOrder();
    void viewOrderHistory();

public:
    OrderingApp();
    void run();
};

#endif