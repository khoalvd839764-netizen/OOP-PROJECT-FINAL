#include "OrderingApp.h"
#include "../models/products/FoodProduct.h"
#include "../models/products/ElectronicsProduct.h"
#include "../models/products/ClothingProduct.h"
#include <iomanip>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

// Ham phu tro: Xoa khoang trang o dau va cuoi chuoi
static string trimString(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

// ============================================================================
// 1. KHOI TAO & NAP DU LIEU (CONSTRUCTOR)
// ============================================================================
// Doc danh sach san pham tu data/products.txt va danh sach nguoi dung tu data/users.txt
OrderingApp::OrderingApp() : isLoggedIn(false), isGuest(false), isAdminLoggedIn(false) {
    vector<shared_ptr<Product>> loaded = FileManager::loadProducts("data/products.txt");
    for (const auto& prod : loaded) {
        productManager.add(prod);
    }
    users = FileManager::loadUsers("data/users.txt");
}

// ============================================================================
// 2. XAC THUC NGUOI DUNG (AUTHENTICATION & USER PROFILE)
// ============================================================================

// Man hinh chao mung ban dau: Cho phep Dang nhap, Dang ky, hoac Chon che do Khach vang lai
bool OrderingApp::authMenu() {
    while (true) {
        cout << "\n===============================================================================\n";
        cout << "                     HE THONG DAT HANG ONLINE - CHAO MUNG                      \n";
        cout << "===============================================================================\n";
        cout << "  1. Dang nhap tai khoan (Khach hang hoac Admin)\n";
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
            isAdminLoggedIn = false;
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

// Xu ly dang nhap: Kiem tra tai khoan Admin (admin/123) hoac tai khoan Khach hang trong users.txt
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

    // Kiem tra neu la tai khoan Quan tri vien Admin (admin / 123)
    if (username == "admin" && password == "123") {
        isAdminLoggedIn = true;
        isLoggedIn = false;
        isGuest = false;
        currentAdmin = Admin("Nguyen Van Admin", "0909999999", "admin@orderingapp.com", "admin", "123", "Quan tri vien he thong");
        cout << "\n[THANH CONG] Dang nhap voi quyen QUAN TRI VIEN (ADMIN)!\n";
        cout << "Chuc vu: " << currentAdmin.getAdminRole() << '\n';
        return true;
    }

    // Kiem tra danh sach tai khoan khach hang
    for (auto& u : users) {
        if (u.getUsername() == username && u.getPassword() == password) {
            currentCustomer = u;
            isLoggedIn = true;
            isGuest = false;
            isAdminLoggedIn = false;
            cout << "\n[THANH CONG] Dang nhap thanh cong! Xin chao " << u.getName() << "!\n";
            cout << "Hang thanh vien : " << u.getMembershipTier() << '\n';
            cout << "Diem thuong     : " << u.getLoyaltyPoints() << " pts\n";
            return true;
        }
    }

    cout << "[LOI] Sai ten dang nhap hoac mat khau!\n";
    return false;
}

// Xu ly dang ky tai khoan moi: Validate thong tin va luu vao data/users.txt
bool OrderingApp::registerUser() {
    cin.ignore(1000, '\n');
    cout << "\n--- DANG KY TAI KHOAN MOI ---\n";
    cout << "Ten tai khoan (Username): ";
    string username;
    getline(cin, username);
    username = trimString(username);

    if (username.empty()) {
        cout << "[LOI] Tai khoan khong duoc de trong!\n";
        return false;
    }

    if (username == "admin") {
        cout << "[LOI] Ten tai khoan 'admin' la danh rieng cho he thong!\n";
        return false;
    }

    for (const auto& u : users) {
        if (u.getUsername() == username) {
            cout << "[LOI] Ten tai khoan nay da ton tai! Vui long chon ten khac.\n";
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
    isAdminLoggedIn = false;

    cout << "\n[THANH CONG] Dang ky tai khoan thanh cong va tu dong dang nhap!\n";
    return true;
}

// Xem thong tin ho so tai khoan, hang thanh vien va diem thuong tich luy
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

// Dang xuat: Reset trang thai phien lam viec
void OrderingApp::logout() {
    isLoggedIn = false;
    isGuest = false;
    isAdminLoggedIn = false;
    currentCustomer = Customer();
    currentAdmin = Admin();
    cout << "\n-> Da dang xuat tai khoan thanh cong!\n";
}

// ============================================================================
// 3. VONG LAP DIEU KHIEN CHINH (MAIN APPLICATION CONTROLLER)
// ============================================================================
// Dieu phoi luong chuong trinh dua tren vai tro (Admin hoac Khach hang)
void OrderingApp::run() {
    while (true) {
        if (!isLoggedIn && !isGuest && !isAdminLoggedIn) {
            if (!authMenu()) {
                cout << "Cam on ban da su dung dich vu!\n";
                return;
            }
        }

        if (isAdminLoggedIn) {
            adminMenu();
        } else {
            customerMenu();
        }
    }
}

// ============================================================================
// 4. PHAN HE KHACH HANG (CUSTOMER PORTAL)
// ============================================================================
// Menu chinh cho khach hang mua sam, xem gio hang, dat hang va tra cuu
void OrderingApp::customerMenu() {
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
        return;
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
            exit(0);
        default:
            cout << "Lua chon khong ton tai. Vui long chon lai!\n";
            break;
    }
}

// ============================================================================
// 5. PHAN HE QUAN TRI VIEN (ADMIN PORTAL)
// ============================================================================
// Menu danh rieng cho Quan tri vien: Quan ly kho hang, Nguoi dung, Don hang va Doanh thu
void OrderingApp::adminMenu() {
    int choice = -1;
    cout << "\n===============================================================================\n";
    cout << "                     BANG DIEU KHIEN QUAN TRI VIEN (ADMIN PORTAL)              \n";
    cout << "  Xin chao: " << currentAdmin.getName() 
         << " | Chuc vu: [" << currentAdmin.getAdminRole() << "]\n";
    cout << "===============================================================================\n";
    cout << "1. Quan ly kho hang (Them SP moi / Sua gia / Nhap kho / Xoa SP)\n";
    cout << "2. Quan ly khach hang (Danh sach / Cap diem VIP / Xoa tai khoan)\n";
    cout << "3. Giam sat don hang & Cap nhat trang thai giao hang\n";
    cout << "4. Bao cao doanh thu & Top 3 san pham ban chay\n";
    cout << "5. Dang xuat tai khoan Admin\n";
    cout << "0. Thoat chuong trinh\n";
    cout << "-------------------------------------------------------------------------------\n";
    cout << "Nhap lua chon cua ban: ";

    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Lua chon khong hop le! Vui long nhap lai.\n";
        return;
    }

    switch (choice) {
        case 1:
            adminManageInventory();
            break;
        case 2:
            adminManageUsers();
            break;
        case 3:
            adminManageOrders();
            break;
        case 4:
            adminViewAnalytics();
            break;
        case 5:
            logout();
            break;
        case 0:
            cout << "Cam on ban da su dung he thong!\n";
            exit(0);
        default:
            cout << "Lua chon khong ton tai. Vui long chon lai!\n";
            break;
    }
}

// 5.1 Quan ly kho hang: Them moi, Cap nhat don gia / Nhap kho, Xoa san pham va dong bo file
void OrderingApp::adminManageInventory() {
    while (true) {
        cout << "\n--- [ADMIN] QUAN LY KHO HANG ---\n";
        showProducts();
        cout << "\n1. Them san pham moi (FOOD / ELECTRONICS / CLOTHING)\n";
        cout << "2. Sua don gia & Nhap them so luong ton kho (Restock)\n";
        cout << "3. Xoa san pham khoi danh muc\n";
        cout << "0. Quay lai Menu Quan tri\n";
        cout << "---------------------------------------------------\n";
        cout << "Nhap lua chon: ";

        int opt;
        if (!(cin >> opt)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (opt == 0) break;

        if (opt == 1) { // Them san pham moi
            cout << "\nChon loai san pham muon them:\n";
            cout << "1. Thuc pham (FOOD)\n";
            cout << "2. Thiet bi dien tu (ELECTRONICS)\n";
            cout << "3. Quan ao / Thoi trang (CLOTHING)\n";
            cout << "Chon loai (1-3): ";
            int typeChoice;
            cin >> typeChoice;
            cin.ignore(1000, '\n');

            string id, name;
            double price;
            int stock;

            cout << "Nhap Ma san pham (vi du: F04, E03, C03): ";
            getline(cin, id);
            id = trimString(id);

            // Kiem tra trung ma san pham
            auto dupCheck = productManager.filter([&id](const shared_ptr<Product>& p) {
                return p && p->getId() == id;
            });
            if (!dupCheck.empty()) {
                cout << "[LOI] Ma san pham '" << id << "' da ton tai trong he thong!\n";
                continue;
            }

            cout << "Nhap Ten san pham: ";
            getline(cin, name);
            cout << "Nhap Don gia goc (VND): ";
            cin >> price;
            cout << "Nhap So luong ton kho ban dau: ";
            cin >> stock;
            cin.ignore(1000, '\n');

            shared_ptr<Product> newProd = nullptr;
            if (typeChoice == 1) {
                string exp;
                int org;
                cout << "Nhap Han su dung (YYYY-MM-DD): ";
                getline(cin, exp);
                cout << "Co phai Thuc pham huu co (Organic) khong? (1: Co, 0: Khong): ";
                cin >> org;
                newProd = make_shared<FoodProduct>(id, name, price, stock, exp, org == 1);
            } else if (typeChoice == 2) {
                int warranty;
                string brand;
                cout << "Nhap So thang bao hanh: ";
                cin >> warranty;
                cin.ignore(1000, '\n');
                cout << "Nhap Hang san xuat / Thuong hieu: ";
                getline(cin, brand);
                newProd = make_shared<ElectronicsProduct>(id, name, price, stock, warranty, brand);
            } else if (typeChoice == 3) {
                string size, mat;
                cout << "Nhap Kich co (S, M, L, XL, FreeSize): ";
                getline(cin, size);
                cout << "Nhap Chat lieu (Cotton, Silk, Leather, Jean): ";
                getline(cin, mat);
                newProd = make_shared<ClothingProduct>(id, name, price, stock, size, mat);
            }

            if (newProd) {
                productManager.add(newProd);
                FileManager::saveProducts(productManager.getAll(), "data/products.txt");
                cout << "[THANH CONG] Da them san pham [" << id << " - " << name << "] va dong bo vao file products.txt!\n";
            }
        } else if (opt == 2) { // Sua gia & Nhap kho (Restock)
            cin.ignore(1000, '\n');
            cout << "Nhap Ma san pham can cap nhat: ";
            string id;
            getline(cin, id);
            id = trimString(id);

            auto pPtr = productManager.find([&id](const shared_ptr<Product>& p) {
                return p && p->getId() == id;
            });

            if (!pPtr || !(*pPtr)) {
                cout << "[LOI] Khong tim thay ma san pham: " << id << '\n';
                continue;
            }

            auto prod = *pPtr;
            cout << "Dang chon: [" << prod->getId() << " - " << prod->getName() << "] (Gia hien tai: " 
                 << fixed << setprecision(0) << prod->getPrice() << " VND, Ton kho: " << prod->getStock() << ")\n";
            cout << "Nhap Don gia moi (nhap -1 neu khong doi): ";
            double newP;
            cin >> newP;
            if (newP >= 0) prod->setPrice(newP);

            cout << "Nhap So luong hang NHAP THEM vao kho (nhap 0 neu khong nhap them): ";
            int addStock;
            cin >> addStock;
            if (addStock > 0) prod->setStockQuantity(prod->getStock() + addStock);

            FileManager::saveProducts(productManager.getAll(), "data/products.txt");
            cout << "[THANH CONG] Da cap nhat thong tin san pham va dong bo vao file products.txt!\n";
        } else if (opt == 3) { // Xoa san pham khoi danh muc
            cin.ignore(1000, '\n');
            cout << "Nhap Ma san pham can XOA: ";
            string id;
            getline(cin, id);
            id = trimString(id);

            int foundIdx = -1;
            for (size_t i = 0; i < productManager.count(); ++i) {
                if (productManager[i] && productManager[i]->getId() == id) {
                    foundIdx = static_cast<int>(i);
                    break;
                }
            }

            if (foundIdx != -1) {
                productManager.remove(foundIdx);
                FileManager::saveProducts(productManager.getAll(), "data/products.txt");
                cout << "[THANH CONG] Da xoa san pham [" << id << "] khoi he thong!\n";
            } else {
                cout << "[LOI] Khong tim thay ma san pham: " << id << '\n';
            }
        }
    }
}

// 5.2 Quan ly nguoi dung: Xem danh sach tai khoan, cap/tru diem VIP, xoa tai khoan
void OrderingApp::adminManageUsers() {
    while (true) {
        cout << "\n===============================================================================================================\n";
        cout << "                                         DANH SACH TAI KHOAN KHACH HANG                                        \n";
        cout << "===============================================================================================================\n";
        cout << left << setw(10) << "MA KH"
             << " | " << setw(15) << "TAI KHOAN"
             << " | " << setw(20) << "HO VA TEN"
             << " | " << setw(12) << "SDT"
             << " | " << right << setw(12) << "DIEM THUONG"
             << " | " << left << setw(30) << "HANG THANH VIEN" << '\n';
        cout << "---------------------------------------------------------------------------------------------------------------\n";

        for (const auto& u : users) {
            cout << left << setw(10) << u.getCustomerId()
                 << " | " << setw(15) << u.getUsername()
                 << " | " << setw(20) << u.getName()
                 << " | " << setw(12) << u.getPhone()
                 << " | " << right << setw(12) << u.getLoyaltyPoints()
                 << " | " << left << setw(30) << u.getMembershipTier() << '\n';
        }
        cout << "===============================================================================================================\n";

        cout << "1. Cap / Chinh sua diem thuong VIP cho khach hang\n";
        cout << "2. Xoa tai khoan khach hang\n";
        cout << "0. Quay lai Menu Quan tri\n";
        cout << "---------------------------------------------------\n";
        cout << "Nhap lua chon: ";

        int opt;
        if (!(cin >> opt)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (opt == 0) break;

        if (opt == 1) { // Chinh sua diem VIP cho khach hang
            cin.ignore(1000, '\n');
            cout << "Nhap Ten tai khoan (Username) muon chinh sua diem: ";
            string uname;
            getline(cin, uname);
            uname = trimString(uname);

            Customer* target = nullptr;
            for (auto& u : users) {
                if (u.getUsername() == uname) {
                    target = &u;
                    break;
                }
            }

            if (!target) {
                cout << "[LOI] Khong tim thay tai khoan: " << uname << '\n';
                continue;
            }

            cout << "Khach hang: " << target->getName() << " (Diem hien tai: " << target->getLoyaltyPoints() << " pts)\n";
            cout << "Nhap So diem thuong moi: ";
            int newPts;
            cin >> newPts;
            if (newPts >= 0) {
                target->setLoyaltyPoints(newPts);
                FileManager::saveUsers(users, "data/users.txt");
                cout << "[THANH CONG] Da cap nhat diem cho [" << uname << "] thanh " 
                     << newPts << " pts (" << target->getMembershipTier() << ") va dong bo users.txt!\n";
            }
        } else if (opt == 2) { // Xoa tai khoan khach hang
            cin.ignore(1000, '\n');
            cout << "Nhap Ten tai khoan (Username) muon XOA: ";
            string uname;
            getline(cin, uname);
            uname = trimString(uname);

            auto it = users.end();
            for (auto iter = users.begin(); iter != users.end(); ++iter) {
                if (iter->getUsername() == uname) {
                    it = iter;
                    break;
                }
            }

            if (it != users.end()) {
                users.erase(it);
                FileManager::saveUsers(users, "data/users.txt");
                cout << "[THANH CONG] Da xoa tai khoan [" << uname << "] khoi he thong!\n";
            } else {
                cout << "[LOI] Khong tim thay tai khoan: " << uname << '\n';
            }
        }
    }
}

// 5.3 Giam sat don hang: Xem toan bo don hang toan san, chi tiet hoa don, cap nhat trang thai
void OrderingApp::adminManageOrders() {
    while (true) {
        if (orders.empty()) {
            cout << "\n[Thong bao] Hien tai chua co don hang nao trong he thong!\n";
            return;
        }

        cout << "\n===============================================================================================================\n";
        cout << "                                         DANH SACH DON HANG TOAN HE THONG                                      \n";
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

        cout << "1. Xem chi tiet hoa don theo Ma don hang\n";
        cout << "2. Cap nhat trang thai don hang (Giao hang / Hoan tat)\n";
        cout << "0. Quay lai Menu Quan tri\n";
        cout << "---------------------------------------------------\n";
        cout << "Nhap lua chon: ";

        int opt;
        if (!(cin >> opt)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (opt == 0) break;

        if (opt == 1) { // Xem chi tiet don hang
            cin.ignore(1000, '\n');
            cout << "Nhap Ma don hang (vi du: ORD-1001): ";
            string id;
            getline(cin, id);
            id = trimString(id);

            bool found = false;
            for (const auto& ord : orders) {
                if (ord.getOrderId() == id) {
                    ord.displayOrder();
                    found = true;
                    break;
                }
            }
            if (!found) cout << "[LOI] Khong tim thay don hang: " << id << '\n';
        } else if (opt == 2) { // Cap nhat trang thai don hang
            cin.ignore(1000, '\n');
            cout << "Nhap Ma don hang can cap nhat: ";
            string id;
            getline(cin, id);
            id = trimString(id);

            Order* target = nullptr;
            for (auto& ord : orders) {
                if (ord.getOrderId() == id) {
                    target = &ord;
                    break;
                }
            }

            if (!target) {
                cout << "[LOI] Khong tim thay don hang: " << id << '\n';
                continue;
            }

            cout << "Chon trang thai moi cho don hang [" << id << "]:\n";
            cout << "1. Confirmed (Da xac nhan)\n";
            cout << "2. Dang giao hang (In Transit)\n";
            cout << "3. Giao thanh cong (Delivered)\n";
            cout << "4. Cancelled (Huy don)\n";
            cout << "Chon (1-4): ";
            int stChoice;
            cin >> stChoice;

            if (stChoice == 1) target->setStatus("Confirmed");
            else if (stChoice == 2) target->setStatus("Dang giao hang");
            else if (stChoice == 3) target->setStatus("Giao thanh cong");
            else if (stChoice == 4) target->setStatus("Cancelled");

            FileManager::rewriteAllOrders(orders, "data/orders.txt");
            cout << "[THANH CONG] Da cap nhat trang thai don [" << id << "] thanh '" 
                 << target->getStatus() << "' va dong bo file orders.txt!\n";
        }
    }
}

// 5.4 Bao cao doanh thu & Xep hang ban chay: Thong ke doanh thu theo nganh hang va Top 3 san pham
void OrderingApp::adminViewAnalytics() {
    cout << "\n===============================================================================================================\n";
    cout << "                                      BAO CAO DOANH THU & THONG KE KINH DOANH                                  \n";
    cout << "===============================================================================================================\n";

    double totalRevenue = 0.0;
    double foodRevenue = 0.0;
    double elecRevenue = 0.0;
    double clothRevenue = 0.0;

    int totalOrdersCount = static_cast<int>(orders.size());
    int successOrdersCount = 0;
    int cancelledOrdersCount = 0;

    // Map thong ke san pham ban chay: ProductID -> {ProductName, totalQuantitySold}
    map<string, pair<string, int>> productSales;

    for (const auto& ord : orders) {
        if (ord.getStatus().find("Cancelled") != string::npos) {
            cancelledOrdersCount++;
        } else {
            successOrdersCount++;
            totalRevenue += ord.getTotalAmount();

            for (const auto& item : ord.getItems()) {
                if (item.getProduct()) {
                    string pid = item.getProduct()->getId();
                    string pname = item.getProduct()->getName();
                    string ptype = item.getProduct()->getType();
                    double itemSubtotal = item.getSubtotal();

                    if (ptype == "FOOD") foodRevenue += itemSubtotal;
                    else if (ptype == "ELECTRONICS") elecRevenue += itemSubtotal;
                    else if (ptype == "CLOTHING") clothRevenue += itemSubtotal;

                    productSales[pid].first = pname;
                    productSales[pid].second += item.getQuantity();
                }
            }
        }
    }

    double cancelRate = (totalOrdersCount > 0) ? (static_cast<double>(cancelledOrdersCount) / totalOrdersCount * 100.0) : 0.0;

    cout << "  TONG QUAN HOAT DONG KINH DOANH:\n";
    cout << "  - Tong doanh thu thuc nhan  : " << fixed << setprecision(0) << totalRevenue << " VND\n";
    cout << "  - Tong so don hang da tao   : " << totalOrdersCount << " don\n";
    cout << "  - So don hop le / dang giao : " << successOrdersCount << " don\n";
    cout << "  - So don da bi huy          : " << cancelledOrdersCount << " don (Ty le huy: " << setprecision(1) << cancelRate << "%)\n";
    cout << "---------------------------------------------------------------------------------------------------------------\n";
    cout << "  DOANH THU THEO TUNG NGANH HANG:\n";
    cout << "  - Thuc pham (FOOD)          : " << fixed << setprecision(0) << setw(12) << foodRevenue << " VND\n";
    cout << "  - Thiet bi dien tu (ELEC)   : " << setw(12) << elecRevenue << " VND\n";
    cout << "  - Thoi trang / May mac      : " << setw(12) << clothRevenue << " VND\n";
    cout << "---------------------------------------------------------------------------------------------------------------\n";
    cout << "  TOP 3 SAN PHAM BAN CHAY NHAT TOAN SAN:\n";

    // Chuyen map thanh vector de sap xep
    vector<pair<string, pair<string, int>>> sortedSales(productSales.begin(), productSales.end());
    sort(sortedSales.begin(), sortedSales.end(), [](const auto& a, const auto& b) {
        return a.second.second > b.second.second;
    });

    if (sortedSales.empty()) {
        cout << "  (Chua co du lieu ban hang)\n";
    } else {
        int rank = 1;
        for (const auto& entry : sortedSales) {
            if (rank > 3) break;
            cout << "  #" << rank << ". [" << entry.first << "] " 
                 << left << setw(25) << entry.second.first 
                 << " - Da ban: " << entry.second.second << " san pham\n";
            rank++;
        }
    }
    cout << "===============================================================================================================\n";
}

// ============================================================================
// 6. CHUC NANG DANH CHO KHACH HANG (STORE FRONT & SHOPPING)
// ============================================================================

// Hien thi bang danh muc san pham toan bo he thong
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

// Tim kiem san pham theo tu khoa ten bang bieu thuc Lambda
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

// Them san pham vao gio hang: Ho tro nhap hang loat qua cu phap dau phay (vi du: F01:2, E01:1, C01)
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

// Xem danh sach cac mat hang trong gio va tong tien
void OrderingApp::viewCart() {
    cout << "\n--- CHI TIET GIO HANG ---\n";
    cout << cart;
}

// Dat hang: Tu dong ap dung giam gia theo Hang VIP, Doi voucher Freeship, Chon thanh toan va Tich diem
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

    // Xu ly doi diem Freeship (20.000 diem doi mien phi van chuyen)
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

    // Chon phuong thuc thanh toan da hinh (Strategy Pattern: COD hoac Chuyen khoan TPBank)
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

        // Tru so luong ton kho va dong bo ngay vao data/products.txt
        for (const auto& item : newOrder.getItems()) {
            if (item.getProduct()) {
                string prodId = item.getProduct()->getId();
                auto prodPtr = productManager.find([&prodId](const shared_ptr<Product>& p) {
                    return p && p->getId() == prodId;
                });
                if (prodPtr && *prodPtr) {
                    int curStock = (*prodPtr)->getStockQuantity();
                    int rem = (curStock >= item.getQuantity()) ? (curStock - item.getQuantity()) : 0;
                    (*prodPtr)->setStockQuantity(rem);
                }
            }
        }
        FileManager::saveProducts(productManager.getAll(), "data/products.txt");

        cart.clear();
        cout << "\n[THANH CONG] DAT HANG THANH CONG!\n";

        // Tich diem thuong cho tai khoan thanh vien (10.000 VND = 1 diem)
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

            cout << "Ban duoc cong them: +" << earned << " diem thuong!\n";
            cout << "Tong diem hien tai: " << currentCustomer.getLoyaltyPoints() 
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

// Xem lich su toan bo don hang da dat trong phien lam viec
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

// Huy don hang: Tu dong hoan tra ton kho san pham, hoan tien chuyen khoan va thu hoi/hoan tra diem VIP
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
    // Dong bo ngay kho hang vao products.txt sau khi hoan tra
    FileManager::saveProducts(productManager.getAll(), "data/products.txt");

    // Kiem tra phuong thuc thanh toan de xu ly hoan tien
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

    // Thu hoi diem tich luy va hoan tra diem voucher Freeship cho tai khoan thanh vien
    string buyerUsername = foundOrder->getCustomer().getUsername();
    if (!buyerUsername.empty()) {
        int earnedPts = foundOrder->getEarnedPoints();
        bool freeshipUsed = foundOrder->getIsFreeshipApplied();

        for (auto& u : users) {
            if (u.getUsername() == buyerUsername) {
                u.deductLoyaltyPoints(earnedPts); // Thu hoi diem thuong
                if (freeshipUsed) {
                    u.addLoyaltyPoints(20000);   // Hoan tra 20k diem voucher
                }
                if (isLoggedIn && currentCustomer.getUsername() == buyerUsername) {
                    currentCustomer = u;          // Dong bo trang thai tai khoan hien tai
                }
                break;
            }
        }
        FileManager::saveUsers(users, "data/users.txt");

        cout << "---------------------------------------------------------------------------------\n";
        cout << "  [THU HOI DIEM]       : -" << earnedPts << " pts (Diem thuong cua don hang da bi thu hoi)\n";
        if (freeshipUsed) {
            cout << "  [HOAN TRA VOUCHER]   : +20.000 pts (Da hoan lai diem voucher Freeship vao vi)\n";
        }
        if (isLoggedIn && currentCustomer.getUsername() == buyerUsername) {
            cout << "  [SO DU DIEM MOI]     : " << currentCustomer.getLoyaltyPoints() << " pts (" << currentCustomer.getMembershipTier() << ")\n";
        }
        cout << "---------------------------------------------------------------------------------\n";
    }

    // Ghi de cap nhat lai file orders.txt
    FileManager::rewriteAllOrders(orders, "data/orders.txt");
    cout << "-> Da tu dong hoan tra lai so luong san pham vao kho va cap nhat file du lieu!\n";
}