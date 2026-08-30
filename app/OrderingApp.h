#ifndef ORDERING_APP_H
#define ORDERING_APP_H

#include <vector>
#include <memory>
#include <iostream>
#include <string>

// [FIX - 30/08/2026]: Sua lai dung duong dan subfolder products/ va viet hoa Order.h (Linux case-sensitive)
#include "../models/products/Product.h"
#include "../models/person/Customer.h"
#include "../models/cart/ShoppingCart.h"
#include "../models/order/Order.h"
#include "../managers/DataManager.h"
#include "../managers/FileManager.h"

using namespace std;

class OrderingApp {
private:
    DataManager<shared_ptr<Product>> productManager;
    ShoppingCart cart;
    Customer currentCustomer;
    vector<Order> orders;
    // [FIX - 30/08/2026]: Danh sach tai khoan thanh vien va trang thai dang nhap
    vector<Customer> users;
    bool isLoggedIn;
    bool isGuest;

    bool authMenu();
    bool loginUser();
    bool registerUser();
    void viewProfile();
    void logout();

    void showProducts();
    void searchProducts();
    void addToCart();
    void viewCart();
    void placeOrder();
    void viewOrderHistory();
    // [FIX - 30/08/2026]: Bo sung chuc nang Huy don hang (COD huy ngay, Chuyen khoan hoan tien trong 24h)
    void cancelOrder();

public:
    OrderingApp();
    void run();
};

#endif