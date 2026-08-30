# 🛒 ORDERING APPLICATION (OOP FINAL PROJECT)

> **Môn học:** Lập trình Hướng đối tượng (Object-Oriented Programming - OOP)  
> **Đề tài:** Hệ thống Đặt hàng Trực tuyến (Online Ordering App)  
> **Ngôn ngữ:** C++ (Chuẩn C++17)  
> **Trạng thái:** Hoàn tất 100% - Đạt chuẩn Rubric & Điểm thưởng Sáng tạo 🏆

---

## 👥 1. THÀNH VIÊN NHÓM & PHÂN CÔNG NHIỆM VỤ

| STT | Họ và Tên | Vai trò | Nhiệm vụ chính (Task) | Phân hệ phụ trách |
| :---: | :--- | :---: | :---: | :--- |
| 1 | **Lê Võ Đăng Khoa** | **Nhóm trưởng** | **Task 4** | Khởi chạy App, Test tích hợp, Quản lý tiến độ (`main.cpp`, Build/Debug) |
| 2 | **Nguyễn Thị Kim Huệ** | **Thành viên** | **Task 1** | Tầng Quản lý dữ liệu dùng chung (`managers/DataManager.h`) |
| 3 | **Nguyễn Tuấn Phong** | **Thành viên** | **Task 2** | Tầng Đọc/Ghi tập tin dữ liệu (`managers/FileManager.h / .cpp`) |
| 4 | **Trường** | **Thành viên** | **Task 3** | Tầng Điều khiển giao diện Console (`app/OrderingApp.h / .cpp`) |

---

## 🏗️ 2. KIẾN TRÚC DỰ ÁN & MÔ HÌNH HƯỚNG ĐỐI TƯỢNG (OOP)

Ứng dụng đáp ứng trọn vẹn và đầy đủ 4 tính chất OOP cùng các tiêu chuẩn nâng cao:

```
oop final project/
├── .vscode/                 # Cấu hình Run & Debug F5 trên IDE
├── app/                     # Controller - Điều khiển luồng ứng dụng
│   ├── OrderingApp.h
│   └── OrderingApp.cpp
├── build/                   # Thư mục chứa object files (.o) khi build
├── data/                    # Dữ liệu vĩnh viễn (products, users, orders)
│   ├── products.txt
│   ├── users.txt
│   └── orders.txt
├── docs/                    # Tài liệu báo cáo & theo dõi tiến độ nhóm
│   ├── TIENDO.md
│   ├── WorkToday.md
│   └── GIT_GUIDE.md
├── managers/                # Business Layer & Generic Container
│   ├── DataManager.h        # Template Generic Class với Lambda filter/sort/find
│   ├── FileManager.h
│   └── FileManager.cpp
├── models/                  # Domain Models
│   ├── cart/                # CartItem, ShoppingCart
│   ├── order/               # Order, Shipping & Delivery Logic
│   ├── payment/             # Strategy Pattern (Cash, TPBank Transfer)
│   ├── person/              # Person (Abstract/Base), Customer
│   └── products/            # Product (Abstract), Food, Electronics, Clothing
├── .gitignore               # Bộ lọc Git chuẩn C++
├── FINALUPDATE.md           # Tóm tắt các tính năng tối ưu cốt lõi
├── Makefile                 # Build script tự động
├── README.md                # Tài liệu tổng quan dự án
└── main.cpp                 # Điểm khởi chạy (Entry Point)
```

### 💎 Các nguyên lý OOP được áp dụng:
1. **Tính Đóng Gói (Encapsulation):** Mọi thuộc tính đều là `private`, truy xuất qua các phương thức `getter`/`setter` và phương thức nghiệp vụ.
2. **Tính Kế Thừa (Inheritance):** 
   * `Product` $\rightarrow$ `FoodProduct`, `ElectronicsProduct`, `ClothingProduct`.
   * `Person` $\rightarrow$ `Customer`.
   * `PaymentMethod` $\rightarrow$ `CashPayment`, `BankTransferPayment`.
3. **Tính Đa Hình (Polymorphism):** Ghi đè phương thức ảo `calculateFinalPrice()`, `displayInfo()`, `getPaymentDetails()`, `displayGuide()`.
4. **Tính Trừu Tượng (Abstraction):** Lớp cơ sở trừu tượng thuần ảo `Product`, `PaymentMethod`.
5. **Generic Template & STL:** `DataManager<T>` hỗ trợ lọc bằng Lambda, sử dụng `std::vector`, `std::shared_ptr`, `std::stringstream`, `std::iomanip`.

---

## 🌟 3. CÁC TÍNH NĂNG NỔI BẬT (ĐIỂM SÁNG TẠO ⭐)

1. **Khởi động có Màn hình Chào mừng (Auth Screen):** Đăng nhập, Đăng ký thành viên, Khách vãng lai.
2. **Tích điểm thưởng & Phân hạng VIP:**
   * Mỗi **10.000 VND** chi tiêu $\rightarrow$ Cộng **+1.000 điểm**.
   * Đổi **20.000 điểm** lấy **1 lần Freeship**.
   * Chiết khấu hạng VIP: **ĐỒNG (3%)**, **BẠC (5%)**, **VÀNG (15%)** trừ trực tiếp vào hóa đơn.
3. **Tính phí ship & Ngày giao linh hoạt:** TPHCM/HN (1 ngày, 10k), Tỉnh khác (3 ngày, 25k), Đơn $\ge 500k$ Freeship.
4. **Thêm giỏ hàng hàng loạt (Batch Add):** Nhập 1 dòng duy nhất `F01:2, E01:1, C01:3`.
5. **Chọn Phương thức Thanh toán:** Tiền mặt (COD) hoặc Chuyển khoản TPBank (STK `000000001`, Tên `HKD NHOM3 ORDERAPP`, Nội dung `ORD-XXXX`).
6. **Hủy đơn hàng thông minh:** COD hủy ngay, Chuyển khoản tiếp nhận hoàn tiền trong 24h, tự động cộng trả lại tồn kho.

---

## 🚀 4. HƯỚNG DẪN BIÊN DỊCH & CHẠY ỨNG DỤNG

### 🔹 Cách 1: Chạy bằng Terminal
```bash
# Biên dịch sạch sẽ và build ra file thực thi
make clean && make

# Chạy ứng dụng
./ordering_app

# Hoặc vừa build vừa chạy bằng 1 lệnh:
make run
```

### 🔹 Cách 2: Chạy trực tiếp trên VS Code / Antigravity IDE
* Nhấn phím **`F5`** (hoặc `Ctrl + F5`) $\rightarrow$ IDE sẽ tự động build qua `make` và mở ứng dụng trong Terminal tích hợp.
