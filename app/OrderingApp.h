#ifndef ORDERING_APP_H
#define ORDERING_APP_H

#include <vector>
#include <memory>
#include <iostream>
#include <string>

#include "../models/Product.h"
#include "../models/person/Customer.h"
#include "../models/cart/ShoppingCart.h"
#include "../models/order/order.h"
#include "../managers/DataManager.h"
#include "../managers/FileManager.h"

using namespace std;

class OrderingApp {
private:
    DataManager<shared_ptr<Product>> productManager;
    ShoppingCart cart;
    Customer currentCustomer;
    vector<Order> orders;

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