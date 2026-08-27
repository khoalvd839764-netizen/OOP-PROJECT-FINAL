# 📊 BẢNG THEO DÕI TIẾN ĐỘ DỰ ÁN (PROJECT PROGRESS)

> **Dự án:** Ordering Application (Project 1 - OOP Final Project)  
> **Cập nhật lần cuối:** 27/08/2026  
> **Tổng tiến độ hoàn thành:** `[██████████████░░░░░░] 70%`

---

## 🎯 1. TỔNG QUAN TIẾN ĐỘ CÁC PHÂN HỆ

| STT | Phân hệ / Khối chức năng | Thư mục | Số Class | Trạng thái | Tiến độ |
| :---: | :--- | :--- | :---: | :---: | :---: |
| **1** | **Khối Sản Phẩm (Product Hierarchy)** | `models/products/` | 4/4 | ✅ **Đã hoàn thành** | **100%** |
| **2** | **Khối Người Dùng (Person & Customer)** | `models/person/` | 2/2 | ✅ **Đã hoàn thành** | **100%** |
| **3** | **Khối Giỏ Hàng & Đơn Hàng (Cart & Order)** | `models/cart/`, `models/order/` | 3/3 | ✅ **Đã hoàn thành** | **100%** |
| **4** | **Khối Quản Lý Dữ Liệu & File (Managers)** | `managers/` | 2/2 | ⏳ **Đang chờ code** | **0%** |
| **5** | **Khối Điều Khiển Ứng Dụng (App Controller)** | `app/`, `main.cpp` | 1/1 | ⏳ **Đang chờ code** | **0%** |

---

## 📝 2. CHI TIẾT TIẾN ĐỘ TỪNG FILE

### 📦 Khối 1: Sản Phẩm (`models/products/`) — [ĐÃ XONG 100% ✅]

| File | Class | Chức năng hoàn thành | Trạng thái |
| :--- | :--- | :--- | :---: |
| `Product.h` / `.cpp` | `Product` | Lớp cha trừu tượng, 4 hàm thuần ảo, nạp chồng `==`, `<`, `<<`, `>>` | ✅ **Xong** |
| `FoodProduct.h` / `.cpp` | `FoodProduct` | Kế thừa, HSD, hữu cơ, tính giá $+5\%$ | ✅ **Xong** |
| `ElectronicsProduct.h` / `.cpp` | `ElectronicsProduct` | Kế thừa, bảo hành, hãng, tính giá $+5\%$ | ✅ **Xong** |
| `ClothingProduct.h` / `.cpp` | `ClothingProduct` | Kế thừa, size, chất liệu, tính giá $+10\%$ | ✅ **Xong** |

---

### 👤 Khối 2: Người Dùng (`models/person/`) — [ĐÃ XONG 100% ✅]

| File | Class | Chức năng hoàn thành | Trạng thái |
| :--- | :--- | :--- | :---: |
| `Person.h` / `.cpp` | `Person` | Lớp cha trừu tượng (tên, SĐT, email), hàm thuần ảo `displayInfo() = 0` | ✅ **Xong** |
| `Customer.h` / `.cpp` | `Customer` | Kế thừa `Person`, mã KH, địa chỉ nhận hàng, lịch sử đơn hàng | ✅ **Xong** |

---

### 🛒 Khối 3: Giỏ Hàng & Đơn Hàng (`models/cart/` & `models/order/`) — [ĐÃ XONG 100% ✅]

| File | Class | Chức năng hoàn thành | Trạng thái |
| :--- | :--- | :--- | :---: |
| `CartItem.h` / `.cpp` | `CartItem` | Chứa `shared_ptr<Product>` + số lượng, tính `getSubtotal()` | ✅ **Xong** |
| `ShoppingCart.h` / `.cpp` | `ShoppingCart` | Chứa `vector<CartItem>`, hàm `addItem` dồn số lượng, `getTotal()` | ✅ **Xong** |
| `Order.h` / `.cpp` | `Order` | Hóa đơn: ngày hệ thống `<ctime>`, tính ngày giao (+5 ngày), phí ship, tổng tiền | ✅ **Xong** |

---

### ⚙️ Khối 4: Quản Lý Dữ Liệu & Đọc File (`managers/`) — [KẾ HOẠCH TIẾP THEO ⏳]

| File | Class | Chức năng cần làm | Trạng thái |
| :--- | :--- | :--- | :---: |
| `DataManager.h` | `DataManager<T>` | Template class quản lý kho (thêm, xóa, tìm kiếm `filter`, sắp xếp `sort`) | ⏳ Chưa xong |
| `FileManager.h` / `.cpp` | `FileManager` | Đọc file `products.txt`, nạp đối tượng đa hình, lưu hóa đơn ra file | ⏳ Chưa xong |

---

### 🎮 Khối 5: Điều Khiển Ứng Dụng & Cấu Hình Build — [CHỜ LÀM ⏳]

| File | Thành phần | Chức năng cần làm | Trạng thái |
| :--- | :--- | :--- | :---: |
| `OrderingApp.h` / `.cpp` | `OrderingApp` | Menu tương tác Console 6 chức năng chính | ⏳ Chưa xong |
| `main.cpp` | `main` | Khởi động chương trình | ⏳ Chưa xong |
| `data/products.txt` | Data File | Dữ liệu mẫu 6 sản phẩm | ✅ **Xong** |
| `Makefile` | Build Script | Lệnh `make` biên dịch tự động toàn bộ project | ✅ **Xong** |

---

## 🏆 3. CHECKLIST YÊU CẦU ĐỀ BÀI PROJECT 1

- [x] Đọc danh sách sản phẩm từ file `.txt` (Đã chuẩn bị format `data/products.txt`).
- [x] Hiển thị danh sách sản phẩm (Đã hoàn thiện hàm `displayInfo()` đa hình cho 3 loại sản phẩm).
- [x] Thêm sản phẩm vào giỏ hàng nhiều lần (Đã hoàn thiện logic dồn số lượng trong `ShoppingCart`).
- [x] Xem giỏ hàng & tính thành tiền (Đã hoàn thiện trong `CartItem` và `ShoppingCart`).
- [x] Đặt hàng & Nhập thông tin khách hàng, địa chỉ (Đã hoàn thiện trong `Customer`).
- [x] Hiển thị & xác nhận đơn hàng (Đã hoàn thiện trong `Order`: ngày đặt hệ thống, ngày giao dự kiến, phí ship, tổng tiền).
- [x] Áp dụng đầy đủ OOP (Đóng gói, Kế thừa, Đa hình, Lớp trừu tượng, Nạp chồng toán tử).
- [x] Sử dụng STL Container (`vector`, `string`, `shared_ptr`, `iomanip`, `ctime`).
