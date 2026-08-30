# 📊 BẢNG THEO DÕI TIẾN ĐỘ DỰ ÁN (PROJECT PROGRESS)

> **Dự án:** Ordering Application (Project 1 - OOP Final Project)  
> **Cập nhật lần cuối:** 30/08/2026  
> **Tổng tiến độ hoàn thành:** `[████████████████████] 100% HOÀN TẤT 🏆`

---

## 🎯 1. TỔNG QUAN TIẾN ĐỘ CÁC PHÂN HỆ

| STT | Phân hệ / Khối chức năng | Thư mục | Số Class | Trạng thái | Tiến độ |
| :---: | :--- | :--- | :---: | :---: | :---: |
| **1** | **Khối Sản Phẩm (Product Hierarchy)** | `models/products/` | 4/4 | ✅ **Đã hoàn thành** | **100%** |
| **2** | **Khối Người Dùng (Person & Customer)** | `models/person/` | 2/2 | ✅ **Đã hoàn thành** | **100%** |
| **3** | **Khối Giỏ Hàng & Đơn Hàng (Cart & Order)** | `models/cart/`, `models/order/` | 3/3 | ✅ **Đã hoàn thành** | **100%** |
| **4** | **Khối Quản Lý Dữ Liệu & File (Managers)** | `managers/` | 2/2 | ✅ **Đã hoàn thành** | **100%** |
| **5** | **Khối Điều Khiển Ứng Dụng (App Controller)** | `app/`, `main.cpp` | 1/1 | ✅ **Đã hoàn thành** | **100%** |

---

## 📝 2. CHI TIẾT TIẾN ĐỘ TỪNG FILE & NGƯỜI PHỤ TRÁCH

### 📦 Khối 1: Sản Phẩm (`models/products/`) — [ĐÃ XONG 100% ✅]

| File | Class | Người phụ trách | Chức năng hoàn thành | Trạng thái |
| :--- | :--- | :--- | :--- | :---: |
| `Product.h` / `.cpp` | `Product` | **👤 Đăng Khoa** | Lớp cha trừu tượng, 4 hàm thuần ảo, nạp chồng `==`, `<`, `<<`, `>>` | ✅ **Xong** |
| `FoodProduct.h` / `.cpp` | `FoodProduct` | **👤 Tuấn Phong** | Kế thừa, HSD, hữu cơ, tính giá $+5\%$ | ✅ **Xong** |
| `ElectronicsProduct.h` / `.cpp` | `ElectronicsProduct` | **👤 Tường** | Kế thừa, bảo hành, hãng, tính giá $+5\%$ | ✅ **Xong** |
| `ClothingProduct.h` / `.cpp` | `ClothingProduct` | **👤 Kim Huệ** | Kế thừa, size, chất liệu, tính giá $+10\%$ | ✅ **Xong** |

---

### 👤 Khối 2: Người Dùng (`models/person/`) — [ĐÃ XONG 100% ✅]

| File | Class | Người phụ trách | Chức năng hoàn thành | Trạng thái |
| :--- | :--- | :--- | :--- | :---: |
| `Person.h` / `.cpp` | `Person` | **👤 Đăng Khoa** | Lớp cha trừu tượng (tên, SĐT, email), hàm thuần ảo `displayInfo() = 0` | ✅ **Xong** |
| `Customer.h` / `.cpp` | `Customer` | **👤 Đăng Khoa** | Kế thừa `Person`, mã KH, địa chỉ nhận hàng, lịch sử đơn hàng | ✅ **Xong** |

---

### 🛒 Khối 3: Giỏ Hàng & Đơn Hàng (`models/cart/` & `models/order/`) — [ĐÃ XONG 100% ✅]

| File | Class | Người phụ trách | Chức năng hoàn thành | Trạng thái |
| :--- | :--- | :--- | :--- | :---: |
| `CartItem.h` / `.cpp` | `CartItem` | **👤 Đăng Khoa** | Chứa `shared_ptr<Product>` + số lượng, tính `getSubtotal()` | ✅ **Xong** |
| `ShoppingCart.h` / `.cpp` | `ShoppingCart` | **👤 Đăng Khoa** | Chứa `vector<CartItem>`, hàm `addItem` dồn số lượng, `getTotal()` | ✅ **Xong** |
| `Order.h` / `.cpp` | `Order` | **👤 Đăng Khoa** | Hóa đơn: ngày hệ thống `<ctime>`, tính ngày giao (+5 ngày), phí ship, tổng tiền | ✅ **Xong** |

---

### ⚙️ Khối 4: Quản Lý Dữ Liệu & Đọc File (`managers/`) — [ĐÃ XONG 100% ✅]

| File | Class | Người phụ trách | Chức năng cần làm | Trạng thái |
| :--- | :--- | :--- | :--- | :---: |
| `DataManager.h` | `DataManager<T>` | **👤 Kim Huệ** | Template class quản lý kho (thêm, xóa, tìm kiếm `filter`, sắp xếp `sort`) | ✅ **Xong** |
| `FileManager.h` / `.cpp` | `FileManager` | **👤 Tuấn Phong** | Đọc file `products.txt`, nạp đối tượng đa hình, lưu hóa đơn ra file | ✅ **Xong** |

---

### 🎮 Khối 5: Điều Khiển Ứng Dụng & Cấu Hình Build — [ĐÃ XONG 100% ✅]

| File | Thành phần | Người phụ trách | Chức năng cần làm | Trạng thái |
| :--- | :--- | :--- | :--- | :---: |
| `OrderingApp.h` / `.cpp` | `OrderingApp` | **👤 Tường** | Menu tương tác Console 6 chức năng chính | ✅ **Xong** |
| `main.cpp` | `main` | **👤 Đăng Khoa (Leader)** | Khởi động chương trình, nghiệm thu toàn bộ app | ✅ **Xong** |
| `data/products.txt` | Data File | **👤 Cả nhóm** | Dữ liệu mẫu 6 sản phẩm | ✅ **Xong** |
| `Makefile` | Build Script | **👤 Đăng Khoa** | Lệnh `make` biên dịch tự động toàn bộ project | ✅ **Xong** |

---

## 🏆 3. CHECKLIST YÊU CẦU ĐỀ BÀI PROJECT 1 (100% PASS)

- [x] Đọc danh sách sản phẩm từ file `.txt` (Đã hoàn thiện trong `FileManager::loadProducts`).
- [x] Hiển thị danh sách sản phẩm (Đã hoàn thiện hàm `displayInfo()` đa hình cho 3 loại sản phẩm).
- [x] Thêm sản phẩm vào giỏ hàng nhiều lần (Đã hoàn thiện logic dồn số lượng trong `ShoppingCart::addItem`).
- [x] Xem giỏ hàng & tính thành tiền (Đã hoàn thiện trong `CartItem` và `ShoppingCart`).
- [x] Đặt hàng & Nhập thông tin khách hàng, địa chỉ (Đã hoàn thiện trong `Customer` và `OrderingApp::placeOrder`).
- [x] Hiển thị & xác nhận đơn hàng (Đã hoàn thiện trong `Order`: ngày đặt hệ thống, ngày giao dự kiến, phí ship, tổng tiền).
- [x] Áp dụng đầy đủ OOP (Đóng gói, Kế thừa, Đa hình, Lớp trừu tượng, Nạp chồng toán tử, Templates).
- [x] Sử dụng STL Container (`vector`, `string`, `shared_ptr`, `iomanip`, `ctime`, `algorithm`, `functional`).
