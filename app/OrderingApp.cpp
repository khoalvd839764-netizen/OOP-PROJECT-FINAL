#include "OrderingApp.h"

using namespace std;

OrderingApp::OrderingApp() {
    vector<shared_ptr<Product>> loaded = FileManager::loadProducts("data/products.txt");
    for (const auto& prod : loaded) {
        productManager.add(prod);
    }
}

void OrderingApp::run() {
    int choice = -1;
    while (true) {
        cout << "\n=============================================\n";
        cout << "           HE THONG DAT HANG ONLINE          \n";
        cout << "=============================================\n";
        cout << "1. Xem danh sach san pham\n";
        cout << "2. Tim kiem san pham theo ten\n";
        cout << "3. Them san pham vao gio hang\n";
        cout << "4. Xem chi tiet gio hang\n";
        cout << "5. Tien hanh dat hang & Thanh toan\n";
        cout << "6. Xem lich su cac don hang da dat\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "---------------------------------------------\n";
        cout << "Nhap lua chon cua ban: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Lua chon khong hop le! Vui long nhap lai.\n";
            continue;
        }

        switch (choice) {
            case 1:
                showProducts();
                break;
            case 2:
                searchProducts();
                break;
            case 3:
                addToCart();
                break;
            case 4:
                viewCart();
                break;
            case 5:
                placeOrder();
                break;
            case 6:
                viewOrderHistory();
                break;
            case 0:
                cout << "Cam on ban da su dung dich vu!\n";
                return;
            default:
                cout << "Lua chon khong ton tai. Vui long chon lai!\n";
                break;
        }
    }
}

void OrderingApp::showProducts() {
    auto list = productManager.getAll();
    if (list.empty()) {
        cout << "Danh sach san pham trong!\n";
        return;
    }
    cout << "\n--- DANH SACH SAN PHAM ---\n";
    for (const auto& prod : list) {
        if (prod) {
            prod->displayInfo();
        }
    }
}

void OrderingApp::searchProducts() {
    cin.ignore(1000, '\n');
    cout << "Nhap tu khoa tim kiem: ";
    string keyword;
    getline(cin, keyword);

    auto results = productManager.filter([&keyword](const shared_ptr<Product>& prod) {
        return prod && prod->getName().find(keyword) != string::npos;
    });

    if (results.empty()) {
        cout << "Khong tim thay san pham nao voi tu khoa: " << keyword << "\n";
        return;
    }

    cout << "\n--- KET QUA TIM KIEM ---\n";
    for (const auto& prod : results) {
        prod->displayInfo();
    }
}

void OrderingApp::addToCart() {
    cin.ignore(1000, '\n');
    cout << "Nhap ma san pham: ";
    string id;
    getline(cin, id);

    auto results = productManager.filter([&id](const shared_ptr<Product>& prod) {
        return prod && prod->getId() == id;
    });

    if (results.empty()) {
        cout << "Khong tim thay ma san pham nay!\n";
        return;
    }

    auto selectedProd = results[0];
    cout << "Nhap so luong can mua: ";
    int qty = 0;
    cin >> qty;

    if (qty <= 0) {
        cout << "So luong phai lon hon 0!\n";
        return;
    }

    if (selectedProd->getStock() < qty) {
        cout << "Khong du so luong trong kho! (Con lai: " << selectedProd->getStock() << ")\n";
        return;
    }

    cart.addItem(selectedProd, qty);
    cout << "Them vao gio hang thanh cong!\n";
}

void OrderingApp::viewCart() {
    cout << "\n--- CHI TIET GIO HANG ---\n";
    cout << cart;
}

void OrderingApp::placeOrder() {
    if (cart.isEmpty()) {
        cout << "Gio hang dang trong! Vui long chon san pham truoc khi thanh toan.\n";
        return;
    }

    cin.ignore(1000, '\n');
    string name, phone, email, address;

    cout << "\n--- NHAP THONG TIN GIAO HANG ---\n";
    cout << "Ho va ten: ";
    getline(cin, name);
    cout << "So dien thoai: ";
    getline(cin, phone);
    cout << "Email: ";
    getline(cin, email);
    cout << "Dia chi giao hang: ";
    getline(cin, address);

    currentCustomer = Customer(name, phone, email, address);
    Order newOrder(currentCustomer, cart.getItems());

    cout << "\n--- THONG TIN HOA DON ---\n";
    newOrder.displayOrder();

    cout << "\nXac nhan dat hang? (Y/N): ";
    char confirm;
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        orders.push_back(newOrder);
        FileManager::saveOrder(newOrder, "data/orders.txt");
        cart.clear();
        cout << "Dat hang thanh cong!\n";
    } else {
        cout << "Da huy thao tac dat hang.\n";
    }
}

void OrderingApp::viewOrderHistory() {
    if (orders.empty()) {
        cout << "Lich su don hang trong!\n";
        return;
    }

    cout << "\n=============================================\n";
    cout << "           LICH SU CAC DON HANG             \n";
    cout << "=============================================\n";
    for (size_t i = 0; i < orders.size(); ++i) {
        cout << "\n[Don hang #" << (i + 1) << "]\n";
        orders[i].displayOrder();
    }
}