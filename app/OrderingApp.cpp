#include "OrderingApp.h"
#include <iomanip>
#include <sstream>

using namespace std;

// Ham phu tro xoa khoang trang dau va cuoi chuoi
static string trimString(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

// [FIX - 30/08/2026]: Khoi tao app, load san pham va load danh sach nguoi dung tu users.txt
OrderingApp::OrderingApp() : isLoggedIn(false), isGuest(false) {
    vector<shared_ptr<Product>> loaded = FileManager::loadProducts("data/products.txt");
    for (const auto& prod : loaded) {
        productManager.add(prod);
    }
    users = FileManager::loadUsers("data/users.txt");
}

// [FIX - 30/08/2026]: Man hinh chao mung dau tien (1. Dang nhap, 2. Dang ky, 3. Khach vang lai)
bool OrderingApp::authMenu() {
    while (true) {
        cout << "\n===============================================================================\n";
        cout << "                     HE THONG DAT HANG ONLINE - CHAO MUNG                      \n";
        cout << "===============================================================================\n";
        cout << "  1. Dang nhap tai khoan thanh vien (Login)\n";
        cout << "  2. Dang ky tai khoan thanh vien moi (Register)\n";
        cout << "  3. Mua hang voi tu cach Khach vang lai (Guest Mode)\n";
        cout << "  0. Thoat chuong trinh\n";
        cout << "-------------------------------------------------------------------------------\n";
        cout << "Nhap lua chon cua ban: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Lua chon khong hop le! Vui long nhap lai.\n";
            continue;
        }

        if (choice == 1) {
            if (loginUser()) return true;
        } else if (choice == 2) {
            if (registerUser()) return true;
        } else if (choice == 3) {
            isLoggedIn = false;
            isGuest = true;
            currentCustomer = Customer("GUEST", "Khach Vang Lai", "", "", "");
            cout << "\n-> Da vao che do Khach vang lai! Ban van co the dat hang binh thuong.\n";
            return true;
        } else if (choice == 0) {
            return false;
        } else {
            cout << "Lua chon khong ton tai. Vui long chon lai!\n";
        }
    }
}

// [FIX - 30/08/2026]: Xu ly dang nhap tai khoan thanh vien
bool OrderingApp::loginUser() {
    cin.ignore(1000, '\n');
    cout << "\n--- DANG NHAP TAI KHOAN ---\n";
    cout << "Tai khoan (Username): ";
    string username, password;
    getline(cin, username);
    username = trimString(username);

    cout << "Mat khau (Password): ";
    getline(cin, password);
    password = trimString(password);

    for (auto& u : users) {
        if (u.getUsername() == username && u.getPassword() == password) {
            currentCustomer = u;
            isLoggedIn = true;
            isGuest = false;
            cout << "\n🎉 Dang nhap thanh cong! Xin chao " << u.getName() << "!\n";
            cout << "💎 Hang thanh vien : " << u.getMembershipTier() << '\n';
            cout << "⭐ Diem thuong      : " << u.getLoyaltyPoints() << " pts\n";
            return true;
        }
    }

    cout << "❌ [LOI] Sai ten dang nhap hoac mat khau!\n";
    return false;
}

// [FIX - 30/08/2026]: Xu ly dang ky tai khoan thanh vien moi va luu vao users.txt
bool OrderingApp::registerUser() {
    cin.ignore(1000, '\n');
    cout << "\n--- DANG KY TAI KHOAN MOI ---\n";
    cout << "Ten tai khoan (Username): ";
    string username;
    getline(cin, username);
    username = trimString(username);

    if (username.empty()) {
        cout << "❌ Tai khoan khong duoc de trong!\n";
        return false;
    }

    for (const auto& u : users) {
        if (u.getUsername() == username) {
            cout << "❌ [LOI] Ten tai khoan nay da ton tai! Vui long chon ten khac.\n";
            return false;
        }
    }

    cout << "Mat khau (Password): ";
    string password, name, phone, email, address;
    getline(cin, password);
    password = trimString(password);

    cout << "Ho va ten: ";
    getline(cin, name);
    cout << "So dien thoai: ";
    getline(cin, phone);
    cout << "Email: ";
    getline(cin, email);
    cout << "Dia chi mac dinh (TPHCM/HN/Tinh khac): ";
    getline(cin, address);

    string custId = "USER-" + to_string(users.size() + 1);
    Customer newUser(custId, name, phone, email, address, username, password, 0);
    users.push_back(newUser);
    FileManager::saveUsers(users, "data/users.txt");

    currentCustomer = newUser;
    isLoggedIn = true;
    isGuest = false;

    cout << "\n🎉 Dang ky tai khoan thanh cong va tu dong dang nhap!\n";
    return true;
}

// [FIX - 30/08/2026]: Xem thong tin tai khoan, hang thanh vien va diem thuong
void OrderingApp::viewProfile() {
    cout << "\n===============================================================================\n";
    cout << "                             THONG TIN TAI KHOAN                               \n";
    cout << "===============================================================================\n";
    if (isLoggedIn) {
        cout << "  Tai khoan        : " << currentCustomer.getUsername() << '\n';
        cout << "  Ho va ten        : " << currentCustomer.getName() << '\n';
        cout << "  So dien thoai    : " << currentCustomer.getPhone() << '\n';
        cout << "  Email            : " << currentCustomer.getEmail() << '\n';
        cout << "  Dia chi mac dinh : " << currentCustomer.getAddress() << '\n';
        cout << "  Hang thanh vien  : " << currentCustomer.getMembershipTier() << '\n';
        cout << "  Diem thuong      : " << currentCustomer.getLoyaltyPoints() << " pts\n";
        cout << "  Uu dai giam gia  : Giam " << fixed << setprecision(0) << (currentCustomer.getTierDiscountRate() * 100) << "% tren tong don hang\n";
    } else {
        cout << "  Che do           : Khach vang lai (Guest Mode)\n";
        cout << "  Ghi chu          : Dang nhap de tich diem va nhan uu dai giam gia VIP len den 15%!\n";
    }
    cout << "===============================================================================\n";
}

// [FIX - 30/08/2026]: Dang xuat tai khoan
void OrderingApp::logout() {
    isLoggedIn = false;
    isGuest = false;
    currentCustomer = Customer();
    cout << "\n-> Da dang xuat tai khoan thanh cong!\n";
}

void OrderingApp::run() {
    while (true) {
        if (!isLoggedIn && !isGuest) {
            if (!authMenu()) {
                cout << "Cam on ban da su dung dich vu!\n";
                return;
            }
        }

        int choice = -1;
        cout << "\n===============================================================================\n";
        cout << "                          HE THONG DAT HANG ONLINE                             \n";
        if (isLoggedIn) {
            cout << "  Xin chao: " << currentCustomer.getName() 
                 << " | Hang: [" << currentCustomer.getMembershipTier() 
                 << "] | Diem: [" << currentCustomer.getLoyaltyPoints() << " pts]\n";
        } else {
            cout << "  Che do: KHACH VANG LAI (Chua dang nhap)\n";
        }
        cout << "===============================================================================\n";
        cout << "1. Xem danh sach san pham\n";
        cout << "2. Tim kiem san pham theo ten\n";
        cout << "3. Them san pham vao gio hang\n";
        cout << "4. Xem chi tiet gio hang\n";
        cout << "5. Tien hanh dat hang & Thanh toan\n";
        cout << "6. Xem lich su cac don hang da dat\n";
        cout << "7. Huy don hang da dat\n";
        cout << "8. Xem thong tin tai khoan & Diem thuong\n";
        cout << "9. Dang xuat tai khoan\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "-------------------------------------------------------------------------------\n";
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
            case 7:
                cancelOrder();
                break;
            case 8:
                viewProfile();
                break;
            case 9:
                logout();
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

// [FIX - 30/08/2026]: In tieu de bang va dong phan cach thang hang dep mat cho danh sach san pham
void OrderingApp::showProducts() {
    auto list = productManager.getAll();
    if (list.empty()) {
        cout << "Danh sach san pham trong!\n";
        return;
    }

    cout << "\n===============================================================================================================\n";
    cout << "                                              DANH SACH SAN PHAM                                               \n";
    cout << "===============================================================================================================\n";
    cout << left << setw(12) << "LOAI"
         << " | " << setw(6) << "MA SP"
         << " | " << setw(22) << "TEN SAN PHAM"
         << " | " << right << setw(14) << "DON GIA"
         << " | " << setw(7) << "TON KHO"
         << " | THONG TIN CHI TIET\n";
    cout << "---------------------------------------------------------------------------------------------------------------\n";

    for (const auto& prod : list) {
        prod->displayInfo();
    }
    cout << "===============================================================================================================\n";
}

void OrderingApp::searchProducts() {
    cin.ignore(1000, '\n');
    cout << "\nNhap ten san pham can tim: ";
    string keyword;
    getline(cin, keyword);

    auto results = productManager.filter([&keyword](const shared_ptr<Product>& prod) {
        return prod && prod->getName().find(keyword) != string::npos;
    });

    if (results.empty()) {
        cout << "Khong tim thay san pham nao voi tu khoa: " << keyword << "\n";
        return;
    }

    cout << "\n===============================================================================================================\n";
    cout << "                                               KET QUA TIM KIEM                                                \n";
    cout << "===============================================================================================================\n";
    cout << left << setw(12) << "LOAI"
         << " | " << setw(6) << "MA SP"
         << " | " << setw(22) << "TEN SAN PHAM"
         << " | " << right << setw(14) << "DON GIA"
         << " | " << setw(7) << "TON KHO"
         << " | THONG TIN CHI TIET\n";
    cout << "---------------------------------------------------------------------------------------------------------------\n";
    for (const auto& prod : results) {
        prod->displayInfo();
    }
    cout << "===============================================================================================================\n";
}

// [FIX - 30/08/2026]: Cho phep them nhieu san pham cung luc cach nhau boi dau phay (vi du: F01:2, E01:1, C01)
void OrderingApp::addToCart() {
    showProducts();
    cin.ignore(1000, '\n');
    cout << "\nNhap danh sach san pham muon mua (Cach nhau boi dau phay ',')";
    cout << "\n(Vi du: F01:2, E01:1, C01  - mac dinh khong ghi so luong se la 1): ";
    
    string inputLine;
    getline(cin, inputLine);

    if (trimString(inputLine).empty()) {
        cout << "Ban chua nhap san pham nao!\n";
        return;
    }

    stringstream ss(inputLine);
    string token;
    int successCount = 0;

    cout << "\n--- TIEN TRINH THEM VAO GIO HANG ---\n";
    while (getline(ss, token, ',')) {
        string itemStr = trimString(token);
        if (itemStr.empty()) continue;

        string id;
        int qty = 1;

        size_t colonPos = itemStr.find(':');
        if (colonPos != string::npos) {
            id = trimString(itemStr.substr(0, colonPos));
            string qtyStr = trimString(itemStr.substr(colonPos + 1));
            try {
                qty = stoi(qtyStr);
            } catch (...) {
                qty = 1;
            }
        } else {
            id = itemStr;
            qty = 1;
        }

        if (id.empty()) continue;

        auto results = productManager.filter([&id](const shared_ptr<Product>& prod) {
            return prod && prod->getId() == id;
        });

        if (results.empty()) {
            cout << "[LOI] Khong tim thay ma san pham: " << id << '\n';
            continue;
        }

        auto selectedProd = results[0];

        if (qty <= 0) {
            cout << "[LOI] So luong mua cua [" << id << "] phai lon hon 0!\n";
            continue;
        }

        if (selectedProd->getStock() < qty) {
            cout << "[LOI] San pham [" << id << " - " << selectedProd->getName() 
                 << "] khong du ton kho! (Con lai: " << selectedProd->getStock() 
                 << ", can mua: " << qty << ")\n";
            continue;
        }

        cart.addItem(selectedProd, qty);
        cout << "[THANH CONG] Da them " << qty << " x [" << id << " - " 
             << selectedProd->getName() << "] vao gio hang!\n";
        successCount++;
    }

    if (successCount > 0) {
        cout << "---------------------------------------------\n";
        cout << "Da them thanh cong " << successCount << " loai san pham vao gio hang!\n";
    } else {
        cout << "Khong co san pham nao duoc them vao gio hang.\n";
    }
}

void OrderingApp::viewCart() {
    cout << "\n--- CHI TIET GIO HANG ---\n";
    cout << cart;
}

// [FIX - 30/08/2026]: Dat hang tu dong ap dung Giam gia VIP, Voucher Freeship 20k diem va Tich diem thuong
void OrderingApp::placeOrder() {
    if (cart.isEmpty()) {
        cout << "Gio hang dang trong! Vui long chon san pham truoc khi thanh toan.\n";
        return;
    }

    cin.ignore(1000, '\n');
    string name, phone, email, address;

    if (isLoggedIn) {
        name = currentCustomer.getName();
        phone = currentCustomer.getPhone();
        email = currentCustomer.getEmail();
        address = currentCustomer.getAddress();

        cout << "\n--- THONG TIN KHACH HANG (DA DANG NHAP) ---\n";
        cout << "Ho va ten        : " << name << '\n';
        cout << "So dien thoai    : " << phone << '\n';
        cout << "Email            : " << email << '\n';
        cout << "Dia chi mac dinh : " << address << '\n';
        cout << "Hang thanh vien  : " << currentCustomer.getMembershipTier() << '\n';
        cout << "Diem thuong      : " << currentCustomer.getLoyaltyPoints() << " pts\n";

        cout << "\nBan co muon thay doi dia chi giao hang khong? (Y/N): ";
        char changeAddr;
        if (cin >> changeAddr && (changeAddr == 'y' || changeAddr == 'Y')) {
            cin.ignore(1000, '\n');
            cout << "Dia chi giao hang moi (TPHCM/HN phi 10k - 1 ngay; Tinh khac phi 25k - 3 ngay): ";
            getline(cin, address);
            currentCustomer.setAddress(address);
        }
    } else {
        cout << "\n--- NHAP THONG TIN GIAO HANG (KHACH VANG LAI) ---\n";
        cout << "Ho va ten: ";
        getline(cin, name);
        cout << "So dien thoai: ";
        getline(cin, phone);
        cout << "Email: ";
        getline(cin, email);
        cout << "Dia chi giao hang (TPHCM/HN phi 10k - 1 ngay; Tinh khac phi 25k - 3 ngay): ";
        getline(cin, address);
        currentCustomer = Customer("GUEST-" + to_string(orders.size() + 1), name, phone, email, address);
    }

    // Xu ly doi diem Freeship
    bool useFreeship = false;
    if (isLoggedIn && currentCustomer.getLoyaltyPoints() >= 20000) {
        cout << "\n[UU DAI VIP]: Ban dang co " << currentCustomer.getLoyaltyPoints() 
             << " diem. Ban co muon dung 20.000 diem de DOI FREESHIP khong? (Y/N): ";
        char fsChoice;
        if (cin >> fsChoice && (fsChoice == 'y' || fsChoice == 'Y')) {
            useFreeship = true;
            currentCustomer.usePointsForFreeship();
            cout << "-> Da ap dung Voucher Freeship thanh cong! (Tru 20.000 diem)\n";
        }
    }

    // Chon phuong thuc thanh toan
    cout << "\n--- CHON PHUONG THUC THANH TOAN ---\n";
    cout << "1. Thanh toan tien mat khi nhan hang (COD)\n";
    cout << "2. Chuyen khoan Ngan hang (TPBank)\n";
    cout << "Chon phuong thuc thanh toan (1 hoac 2): ";
    int paymentChoice = 1;
    if (!(cin >> paymentChoice)) {
        cin.clear();
        cin.ignore(1000, '\n');
        paymentChoice = 1;
    }

    shared_ptr<PaymentMethod> selectedPayment = nullptr;
    if (paymentChoice == 2) {
        selectedPayment = make_shared<BankTransferPayment>();
    } else {
        selectedPayment = make_shared<CashPayment>();
    }

    Order newOrder(currentCustomer, cart.getItems(), selectedPayment, useFreeship);

    cout << "\n--- THONG TIN HOA DON ---\n";
    newOrder.displayOrder();

    cout << "\nXac nhan dat hang? (Y/N): ";
    char confirm;
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        orders.push_back(newOrder);
        FileManager::saveOrder(newOrder, "data/orders.txt");
        cart.clear();
        cout << "\n🎉 DAT HANG THANH CONG!\n";

        // Tich diem thuong cho tai khoan thanh vien
        if (isLoggedIn) {
            int earned = newOrder.getEarnedPoints();
            currentCustomer.addLoyaltyPoints(earned);
            
            // Cap nhat vao vector users va ghi de file users.txt
            for (auto& u : users) {
                if (u.getUsername() == currentCustomer.getUsername()) {
                    u = currentCustomer;
                    break;
                }
            }
            FileManager::saveUsers(users, "data/users.txt");

            cout << "⭐ Ban duoc cong them: +" << earned << " diem thuong!\n";
            cout << "💎 Tong diem hien tai: " << currentCustomer.getLoyaltyPoints() 
                 << " pts (" << currentCustomer.getMembershipTier() << ")\n";
        }
    } else {
        // Neu da tru 20k diem doi voucher freeship nhung huy thi hoan lai diem
        if (useFreeship && isLoggedIn) {
            currentCustomer.addLoyaltyPoints(20000);
        }
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

// [FIX - 30/08/2026]: Bo sung chuc nang Huy don hang (COD huy ngay, Chuyen khoan hoan tien trong 24h va tu dong hoan tra ton kho)
void OrderingApp::cancelOrder() {
    if (orders.empty()) {
        cout << "Hien tai chua co don hang nao trong he thong de huy!\n";
        return;
    }

    cout << "\n===============================================================================================================\n";
    cout << "                                          DANH SACH DON HANG HIEN CO                                           \n";
    cout << "===============================================================================================================\n";
    cout << left << setw(12) << "MA DON"
         << " | " << setw(12) << "NGAY DAT"
         << " | " << setw(20) << "KHACH HANG"
         << " | " << right << setw(14) << "TONG TIEN"
         << " | " << left << setw(35) << "TRANG THAI" << '\n';
    cout << "---------------------------------------------------------------------------------------------------------------\n";

    for (const auto& ord : orders) {
        cout << left << setw(12) << ord.getOrderId()
             << " | " << setw(12) << ord.getOrderDate()
             << " | " << setw(20) << ord.getCustomer().getName()
             << " | " << right << setw(10) << fixed << setprecision(0) << ord.getTotalAmount() << " VND"
             << " | " << left << setw(35) << ord.getStatus() << '\n';
    }
    cout << "===============================================================================================================\n";

    cin.ignore(1000, '\n');
    cout << "\nNhap ma don hang muon huy (vi du: ORD-1001) hoac an Enter de thoat: ";
    string targetId;
    getline(cin, targetId);
    targetId = trimString(targetId);

    if (targetId.empty()) {
        cout << "Da huy thao tac.\n";
        return;
    }

    Order* foundOrder = nullptr;
    for (auto& ord : orders) {
        if (ord.getOrderId() == targetId) {
            foundOrder = &ord;
            break;
        }
    }

    if (!foundOrder) {
        cout << "Khong tim thay ma don hang: " << targetId << '\n';
        return;
    }

    if (foundOrder->getStatus() != "Confirmed") {
        cout << "Don hang nay dang o trang thai '" << foundOrder->getStatus() << "', khong the huy lai!\n";
        return;
    }

    // Tu dong cong tra lai so luong san pham vao kho
    for (const auto& item : foundOrder->getItems()) {
        if (item.getProduct()) {
            string prodId = item.getProduct()->getId();
            auto prodPtr = productManager.find([&prodId](const shared_ptr<Product>& p) {
                return p && p->getId() == prodId;
            });
            if (prodPtr && *prodPtr) {
                (*prodPtr)->setStockQuantity((*prodPtr)->getStockQuantity() + item.getQuantity());
            }
        }
    }

    // Kiem tra phuong thuc thanh toan
    auto pm = foundOrder->getPaymentMethod();
    bool isBankTransfer = (pm && pm->getMethodName().find("TPBank") != string::npos);

    if (isBankTransfer) {
        foundOrder->setStatus("Cancelled - Cho hoan tien (24h)");
        cout << "\n  ============================== THONG BAO HOAN TIEN ==============================\n";
        cout << "  Ma don hang      : " << foundOrder->getOrderId() << '\n';
        cout << "  So tien can hoan : " << fixed << setprecision(0) << foundOrder->getTotalAmount() << " VND\n";
        cout << "  Hinh thuc TT     : " << pm->getMethodName() << '\n';
        cout << "  Trang thai moi   : Cancelled - Cho hoan tien (24h)\n";
        cout << "  -------------------------------------------------------------------------------\n";
        cout << "  [XAC NHAN]: Yeu cau huy don chuyen khoan da duoc tiep nhan thanh cong!\n";
        cout << "  [LUU Y]   : So tien se duoc he thong hoan tra ve tai khoan cua quy khach trong\n";
        cout << "              vong 24H LAM VIEC!\n";
        cout << "  =================================================================================\n";
    } else {
        foundOrder->setStatus("Cancelled");
        cout << "\n  ============================== THONG BAO HUY DON ==============================\n";
        cout << "  Ma don hang      : " << foundOrder->getOrderId() << '\n';
        cout << "  Hinh thuc TT     : Tien mat khi nhan hang (COD)\n";
        cout << "  Trang thai moi   : Cancelled (Da huy)\n";
        cout << "  -------------------------------------------------------------------------------\n";
        cout << "  [THANH CONG]: Don hang COD da duoc huy thanh cong! Khong phat sinh chi phi.\n";
        cout << "  =================================================================================\n";
    }

    // Ghi de cap nhat lai file orders.txt
    FileManager::rewriteAllOrders(orders, "data/orders.txt");
    cout << "-> Da tu dong hoan tra lai so luong san pham vao kho va cap nhat file du lieu!\n";
}