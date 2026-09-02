#ifndef ORDERING_APP_H
#define ORDERING_APP_H

#include <vector>
#include <memory>
#include <iostream>
#include <string>

// [FIX - 30/08/2026]: Sua lai dung duong dan subfolder products/ va viet hoa Order.h (Linux case-sensitive)
#include "../models/products/Product.h"
#include "../models/person/Customer.h"
#include "../models/person/Admin.h"
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

    // [FIX - 31/08/2026]: Phan quyen Quan tri vien (Admin Portal)
    Admin currentAdmin;
    bool isAdminLoggedIn;

    bool authMenu();
    bool loginUser();
    bool registerUser();
    void viewProfile();
    void logout();

    // Menu khach hang
    void customerMenu();
    void showProducts();
    void searchProducts();
    void addToCart();
    void viewCart();
    void placeOrder();
    void viewOrderHistory();
    void cancelOrder();

    // [FIX - 31/08/2026]: 4 Chuc nang quan tri danh rieng cho Admin
    void adminMenu();
    void adminManageInventory(); // 1. Quan ly kho hang (Them/Sua gia/Nhap kho/Xoa SP)
    void adminManageUsers();     // 2. Quan ly khach hang (Xem danh sach/Sua diem VIP/Xoa tai khoan)
    void adminManageOrders();    // 3. Giam sat don hang & Cap nhat trang thai giao hang
    void adminViewAnalytics();   // 4. Bao cao doanh thu & Top 3 san pham ban chay

public:
    OrderingApp();
    void run();
};

#endif // ORDERING_APP_H