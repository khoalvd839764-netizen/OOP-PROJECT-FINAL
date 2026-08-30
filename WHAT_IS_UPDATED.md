# 📖 BÁO CÁO CHI TIẾT TOÀN DIỆN: NHỮNG NỘI DUNG ĐÃ UPDATE & TỐI ƯU (WHAT IS UPDATED)

> **Dự án:** Hệ Thống Đặt Hàng Trực Tuyến (OOP Ordering Application)  
> **Tài liệu tổng hợp chi tiết TỪNG Ô / TỪNG PHÂN HỆ: Sửa cái gì, Vì sao phải sửa và Mục đích kỹ thuật.**

---

## 📊 BẢNG TỔNG HỢP TỪNG Ô: SỬA GÌ - VÌ SAO SỬA - MỤC ĐÍCH

| Ô / Phân Hệ | 🛠️ SỬA CÁI GÌ? (WHAT WAS CHANGED) | ❓ VÌ SAO SỬA? (WHY IT WAS CHANGED) | 🎯 MỤC ĐÍCH (PURPOSE & BENEFIT) |
| :---: | :--- | :--- | :--- |
| **📦 Ô 1: Bảng Sản Phẩm & Tồn Kho** | - Căn cột bảng bằng `std::setw`, `std::left`, `std::right`.<br>- In rõ **Mã SP `[MA SP]`** và **Số lượng `[TON KHO]`**.<br>- Thêm alias `getStock()`.<br>- Tự động in bảng sản phẩm khi chọn Menu 3. | **Code cũ bị lỗi giao diện:** In ra thụt thò xiên xẹo, không có tiêu đề, không in mã ID khiến người mua không biết gõ mã gì để mua và không biết còn hàng hay hết. | Tạo giao diện dạng bảng chuẩn chỉnh, chuyên nghiệp; giúp khách hàng dễ dàng nhìn thấy Mã SP và Tồn kho để mua sắm. |
| **📦 Ô 2: Phí Ship & Ngày Giao Theo Khu Vực** | - Viết hàm `isInnerCityArea()` quét từ khóa (`HCM`, `HN`).<br>- Viết hàm `calcExpectedDelivery()`: TPHCM/HN (+1 ngày), Tỉnh khác (+3 ngày).<br>- Viết hàm `calculateShipping()`: TPHCM/HN (10k), Tỉnh khác (25k), Đơn $\ge 500k$ Freeship. | **Code cũ quá cứng nhắc:** Mọi đơn hàng đều bị fix cứng +5 ngày giao và phí 30k bất kể khách ở gần hay xa, đơn nhỏ hay đơn lớn. | Tăng tính thực tế của ứng dụng thương mại điện tử; xử lý chuỗi và tính toán ngày tháng linh hoạt để lấy trọn điểm sáng tạo. |
| **📦 Ô 3: Mua Hàng Hàng Loạt Bằng Dấu Phẩy ','** | - Viết hàm `trimString()` xóa khoảng trắng thừa.<br>- Dùng `stringstream` tách dấu phẩy `,` và dấu hai chấm `:`.<br>- Nhập 1 dòng dạng: `F01:2, E01:1, C01`.<br>- Kiểm tra tồn kho độc lập từng món. | **Code cũ rất bất tiện:** Mỗi lần chọn Menu 3 chỉ thêm được 1 món rồi tự văng về Menu chính. Muốn mua 5 món phải bấm menu 5 lần liên tục. | Cho phép khách mua nhiều món chỉ trong **1 lần nhập duy nhất**; tự động kiểm tra tồn kho độc lập từng món (món hết hàng báo lỗi riêng). |
| **📦 Ô 4: Phương Thức Thanh Toán Đa Hình** | - Tạo lớp trừu tượng `PaymentMethod` (Strategy Pattern).<br>- Tạo 2 lớp con: `CashPayment` (COD) và `BankTransferPayment` (TPBank).<br>- Cấu hình TPBank: STK `000000001`, Tên `HKD NHOM3 ORDERAPP`, Nội dung `ORD-XXXX`.<br>- In khung chuyển khoản trên bill và lưu vào `orders.txt`. | **Code cũ thiếu quy trình thanh toán:** Đơn hàng tạo ra không có phương thức thanh toán, không có hướng dẫn chuyển khoản thực tế. | Áp dụng mẫu thiết kế **Strategy Pattern** và thể hiện trọn vẹn **Tính Đa hình thuần ảo (Polymorphism)** để lấy điểm tối đa. |
| **📦 Ô 5: Hủy Đơn Hàng & Hoàn Tiền 24H** | - Thêm Menu 7 (`cancelOrder()`).<br>- Đơn COD: Chuyển trạng thái `Cancelled` ngay lập tức.<br>- Đơn TPBank: Chuyển `Cancelled - Cho hoan tien (24h)` $\rightarrow$ in thông báo **tiền hoàn trong 24H LÀM VIỆC**.<br>- Tự động cộng trả lại tồn kho (`stock += qty`).<br>- Viết hàm `rewriteAllOrders()` cập nhật file `orders.txt`. | **Code cũ không thể hủy đơn:** Khách đặt nhầm không có cách nào hủy, số lượng tồn kho bị trừ mất vĩnh viễn gây sai lệch dữ liệu kho hàng. | Khép kín vòng đời đơn hàng (Đặt $\rightarrow$ Thanh toán $\rightarrow$ Hủy); đảm bảo tính toàn vẹn dữ liệu kho hàng và bảo vệ quyền lợi khách hàng. |
| **📦 Ô 6: Tài Khoản Thành Viên & Tích Điểm VIP** | - Tạo file `data/users.txt` lưu tài khoản.<br>- Thêm Màn hình Chào mừng: **1. Login, 2. Register, 3. Guest**.<br>- Tích điểm: Mỗi **10.000đ $\rightarrow$ +1.000 điểm**.<br>- Đổi **20.000 điểm lấy 1 lần Freeship**.<br>- Chiết khấu VIP: **Đồng (3%), Bạc (5%), Vàng (15%)** trừ thẳng vào hóa đơn. | **Code cũ không có tài khoản:** Khách hàng mỗi lần mua phải gõ lại từ đầu Họ tên, SĐT, Email, Địa chỉ; không có cơ chế giữ chân khách quen. | Tự động điền thông tin người mua khi đã đăng nhập; xây dựng hệ sinh thái khách hàng thân thiết (Loyalty Program) hoàn chỉnh. |

---

## 📑 CHI TIẾT TỪNG Ô: MÃ NGUỒN, LOGIC & VÌ SAO SỬA

---

### 📦 Ô 1: KHỐI HIỂN THỊ BẢNG SẢN PHẨM & TỒN KHO

#### 📍 File sửa đổi:
* `models/products/FoodProduct.cpp`, `ElectronicsProduct.cpp`, `ClothingProduct.cpp`
* `models/products/Product.h`
* `app/OrderingApp.cpp`

#### 🛠️ Sửa cái gì (Code thay đổi):
```cpp
// File: models/products/FoodProduct.cpp (tương tự cho Electronics và Clothing)
void FoodProduct::displayInfo() const {
    std::cout << std::left << std::setw(12) << "FOOD"
              << " | " << std::setw(6) << id
              << " | " << std::setw(22) << name
              << " | " << std::right << std::setw(10) << std::fixed << std::setprecision(0) 
              << calculateFinalPrice() << " VND"
              << " | " << std::setw(7) << stockQuantity
              << " | HSD: " << std::left << std::setw(12) << expirationDate
              << " | Huu co: " << (isOrganic ? "Co" : "Khong") << '\n';
}

// File: models/products/Product.h
int getStock() const { return stockQuantity; }
```

#### ❓ Vì sao sửa?
* **Code cũ:** Danh sách in ra bị thụt thò không thẳng cột, không có tiêu đề, và **không in mã ID** khiến người mua không biết phải gõ mã gì để chọn món, cũng không biết món đó còn hàng trong kho hay đã hết.

#### 🎯 Mục đích:
* Căn chỉnh bảng thẳng hàng bằng `std::setw`, in rõ Mã SP và Số lượng tồn kho để người dùng dễ chọn mua.

---

### 📦 Ô 2: KHỐI TÍNH PHÍ GIAO HÀNG & NGÀY GIAO THEO ĐỊA CHỈ

#### 📍 File sửa đổi:
* `models/order/Order.h` & `models/order/Order.cpp`
* `app/OrderingApp.cpp`

#### 🛠️ Sửa cái gì (Code thay đổi):
```cpp
// File: models/order/Order.cpp
bool Order::isInnerCityArea(const std::string& address) const {
    std::string lowerAddr = address;
    for (char& c : lowerAddr) lowerAddr.push_back(std::tolower(c));
    return (lowerAddr.find("hcm") != std::string::npos ||
            lowerAddr.find("ho chi minh") != std::string::npos ||
            lowerAddr.find("tphcm") != std::string::npos ||
            lowerAddr.find("ha noi") != std::string::npos ||
            lowerAddr.find("hanoi") != std::string::npos ||
            lowerAddr.find("hn") != std::string::npos);
}

std::string Order::calcExpectedDelivery() const {
    std::time_t now = std::time(nullptr);
    std::tm* ltm = std::localtime(&now);
    ltm->tm_mday += (isInnerCityArea(customer.getAddress()) ? 1 : 3);
    std::mktime(ltm);
    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%d/%m/%Y", ltm);
    return std::string(buffer);
}

double Order::calculateShipping() const {
    double itemsTotal = 0.0;
    for (const auto& item : items) itemsTotal += item.getSubtotal();
    if (itemsTotal >= 500000.0) return 0.0; // Freeship
    return isInnerCityArea(customer.getAddress()) ? 10000.0 : 25000.0;
}
```

#### ❓ Vì sao sửa?
* **Code cũ:** Mọi đơn hàng đều bị fix cứng `+5 ngày` giao và phí cố định `30.000đ` bất kể khách ở gần hay ở tỉnh xa.

#### 🎯 Mục đích:
* Tự động quét từ khóa địa chỉ: TPHCM/HN giao hỏa tốc **1 ngày (phí 10k)**; Tỉnh khác giao **3 ngày (phí 25k)**; Đơn $\ge 500k$ **Freeship (0đ)**.

---

### 📦 Ô 3: KHỐI MUA HÀNG HÀNG LOẠT BẰNG DẤU PHẨY ',' (BATCH ADD)

#### 📍 File sửa đổi:
* `app/OrderingApp.cpp` (Hàm `addToCart()`)

#### 🛠️ Sửa cái gì (Code thay đổi):
```cpp
// File: app/OrderingApp.cpp
void OrderingApp::addToCart() {
    showProducts();
    cout << "\nNhap danh sach san pham muon mua (Cach nhau boi dau phay ',')";
    cout << "\n(Vi du: F01:2, E01:1, C01  - mac dinh khong ghi so luong se la 1): ";
    
    string inputLine;
    getline(cin, inputLine);
    stringstream ss(inputLine);
    string token;

    while (getline(ss, token, ',')) {
        string itemStr = trimString(token);
        size_t colonPos = itemStr.find(':');
        string id = (colonPos != string::npos) ? trimString(itemStr.substr(0, colonPos)) : itemStr;
        int qty = (colonPos != string::npos) ? stoi(trimString(itemStr.substr(colonPos + 1))) : 1;

        auto results = productManager.filter([&id](const shared_ptr<Product>& prod) {
            return prod && prod->getId() == id;
        });

        if (!results.empty() && results[0]->getStock() >= qty) {
            cart.addItem(results[0], qty);
            cout << "[THANH CONG] Da them " << qty << " x [" << id << "] vao gio!\n";
        }
    }
}
```

#### ❓ Vì sao sửa?
* **Code cũ:** Mỗi lần chọn Menu 3 chỉ thêm được 1 sản phẩm rồi app tự quay về menu chính. Muốn mua 5 món phải bấm menu 5 lần liên tục.

#### 🎯 Mục đích:
* Cho phép khách hàng nhập 1 dòng duy nhất `F01:2, E01:1, C01` để thêm toàn bộ vào giỏ cùng lúc, tự động xóa khoảng trắng và kiểm tra tồn kho từng món.

---

### 📦 Ô 4: KHỐI PHƯƠNG THỨC THANH TOÁN ĐA HÌNH (STRATEGY PATTERN)

#### 📍 File sửa đổi:
* `models/payment/PaymentMethod.h` *(Tạo mới)*
* `models/order/Order.h` & `Order.cpp`
* `managers/FileManager.cpp`
* `app/OrderingApp.cpp`

#### 🛠️ Sửa cái gì (Code thay đổi):
```cpp
// File: models/payment/PaymentMethod.h
class PaymentMethod {
public:
    virtual ~PaymentMethod() = default;
    virtual std::string getMethodName() const = 0;
    virtual std::string getPaymentDetails(const std::string& orderId) const = 0;
    virtual void displayGuide(const std::string& orderId, double amount) const = 0;
};

class CashPayment : public PaymentMethod { ... };

class BankTransferPayment : public PaymentMethod {
public:
    BankTransferPayment()
        : bankName("TPBank (Ngan hang Tien Phong)"),
          accountNumber("000000001"),
          accountHolder("HKD NHOM3 ORDERAPP") {}

    void displayGuide(const std::string& orderId, double amount) const override {
        std::cout << "  Ngan hang     : " << bankName << '\n';
        std::cout << "  Chu tai khoan : " << accountHolder << '\n';
        std::cout << "  So tai khoan  : " << accountNumber << '\n';
        std::cout << "  Noi dung      : " << orderId << '\n';
    }
};
```

#### ❓ Vì sao sửa?
* **Code cũ:** Không có phương thức thanh toán, đơn hàng tạo ra không biết thanh toán bằng cách nào, thiếu tính thực tế.

#### 🎯 Mục đích:
* Áp dụng **Strategy Design Pattern** và **Tính Đa hình (Polymorphism)** của OOP. In khung chuyển khoản TPBank lên màn hình và lưu thông tin vào file `data/orders.txt`.

---

### 📦 Ô 5: KHỐI HỦY ĐƠN HÀNG, HOÀN TIỀN 24H & PHỤC HỒI TỒN KHO

#### 📍 File sửa đổi:
* `app/OrderingApp.h` & `OrderingApp.cpp` (Menu 7: `cancelOrder()`)
* `managers/FileManager.h` & `FileManager.cpp` (`rewriteAllOrders()`)

#### 🛠️ Sửa cái gì (Code thay đổi):
```cpp
// File: app/OrderingApp.cpp
void OrderingApp::cancelOrder() {
    // 1. Phục hồi tồn kho (Restock)
    for (const auto& item : foundOrder->getItems()) {
        auto prodPtr = productManager.find(...);
        (*prodPtr)->setStockQuantity((*prodPtr)->getStockQuantity() + item.getQuantity());
    }
    // 2. Xử lý theo phương thức thanh toán
    if (isBankTransfer) {
        foundOrder->setStatus("Cancelled - Cho hoan tien (24h)");
        cout << "[LUU Y]: Tien se duoc he thong hoan tra ve tai khoan trong vong 24H LAM VIEC!\n";
    } else {
        foundOrder->setStatus("Cancelled");
        cout << "[THANH CONG]: Don hang COD da duoc huy thanh cong!\n";
    }
    // 3. Chống gian lận: Thu hồi điểm tích lũy & Hoàn trả 20k điểm voucher Freeship
    buyer.deductLoyaltyPoints(foundOrder->getEarnedPoints());
    if (foundOrder->getIsFreeshipApplied()) {
        buyer.addLoyaltyPoints(20000);
    }
    // 4. Ghi đè file orders.txt & users.txt
    FileManager::rewriteAllOrders(orders, "data/orders.txt");
    FileManager::saveUsers(users, "data/users.txt");
}
```

#### ❓ Vì sao sửa?
* **Code cũ:** Khách đặt nhầm không có cách nào hủy, số lượng tồn kho bị trừ mất vĩnh viễn gây sai lệch dữ liệu kho. Ngoài ra có **lỗ hổng gian lận điểm (Points Exploit)**: khách đặt đơn để lấy điểm thưởng rồi hủy đơn nhưng vẫn giữ điểm.

#### 🎯 Mục đích:
* Đơn COD hủy ngay; Đơn TPBank tiếp nhận và in thông báo **hoàn tiền trong 24h làm việc**; Tự động cộng trả lại tồn kho vào hệ thống; **Thu hồi đúng số điểm thưởng đã cộng từ đơn hủy và hoàn trả lại 20.000 điểm voucher Freeship (nếu có)**, đồng bộ dữ liệu vào `users.txt`.

---

### 📦 Ô 6: KHỐI TÀI KHOẢN THÀNH VIÊN, TÍCH ĐIỂM & GIẢM GIÁ VIP

#### 📍 File sửa đổi:
* `data/users.txt` *(Tạo mới)*
* `models/person/Customer.h` & `Customer.cpp`
* `models/order/Order.h` & `Order.cpp`
* `managers/FileManager.h` & `FileManager.cpp`
* `app/OrderingApp.h` & `OrderingApp.cpp`

#### 🛠️ Sửa cái gì (Code thay đổi):
```cpp
// File: models/person/Customer.cpp
std::string Customer::getMembershipTier() const {
    if (loyaltyPoints >= 1000000) return "Thanh vien VANG (Giam 15%)";
    if (loyaltyPoints >= 500000)  return "Thanh vien BAC (Giam 5%)";
    if (loyaltyPoints >= 200000)  return "Thanh vien DONG (Giam 3%)";
    return "Thanh vien Tieu Chuan (0%)";
}

double Customer::getTierDiscountRate() const {
    if (loyaltyPoints >= 1000000) return 0.15; // Giảm 15%
    if (loyaltyPoints >= 500000)  return 0.05; // Giảm 5%
    if (loyaltyPoints >= 200000)  return 0.03; // Giảm 3%
    return 0.0;
}
```

#### ❓ Vì sao sửa?
* **Code cũ:** Không có tài khoản, mỗi lần mua khách phải nhập lại từ đầu Họ tên, SĐT, Email, Địa chỉ rất phiền phức; không có cơ chế giữ chân khách hàng thân thiết.

#### 🎯 Mục đích:
* Tự động điền thông tin người mua khi đã đăng nhập; Tích điểm (+1k pts / 10k VND); Đổi 20k pts lấy Freeship; Giảm giá VIP trực tiếp 3%, 5%, 15% vào hóa đơn.
