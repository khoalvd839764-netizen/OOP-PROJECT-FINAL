# 📋 WORK TODAY: Phân Công Triển Khai Nhóm Sản Phẩm (Product Hierarchy)

> **Mục tiêu hôm nay:** Hoàn thiện 100% tầng dữ liệu Sản phẩm gồm 4 class (`Product`, `FoodProduct`, `ElectronicsProduct`, `ClothingProduct`) và chạy test nghiệm thu tính Đa hình.

---

## 👥 BẢNG PHÂN CÔNG NHIỆM VỤ (Điền tên thành viên vào đây)

| Task | Module / File phụ trách | Người thực hiện (Assignee) | Trạng thái |
| :---: | :--- | :--- | :---: |
| **Task 1** | **Lớp cha `Product`** (`Product.h`, `Product.cpp`) | `👤 [ ĐĂNG KHOA ]` | ⏳ Chưa xong |
| **Task 2** | **Lớp con `FoodProduct`** (`FoodProduct.h`, `FoodProduct.cpp`) | `👤 [ TUẤN PHONG ]` | ⏳ Chưa xong |
| **Task 3** | **Lớp con `ElectronicsProduct`** (`ElectronicsProduct.h`, `ElectronicsProduct.cpp`) | `👤 [ TRƯỜNG ]` | ⏳ Chưa xong |
| **Task 4** | **Lớp con `ClothingProduct`** (`ClothingProduct.h`, `ClothingProduct.cpp`) | `👤 [ KIM HUỆ ]` | ⏳ Chưa xong |
| **Task 5** | **Viết code Test nghiệm thu** (`main.cpp`, kiểm tra build) | `👤 [ ĐĂNG KHOA ]` | ⏳ Chưa xong |

---

## 📝 CHI TIẾT TỪNG PHẦN VIỆC

---

### 🔹 TASK 1: Lớp Cha Cơ Sở `Product` (Abstract Base Class)
* **👤 Người thực hiện:** `ĐĂNG KHOA`
* **📁 File cần code:** `models/Product.h` và `models/Product.cpp`
* **Nhiệm vụ cụ thể:**
  - [ ] Khai báo 5 thuộc tính `protected`: `id` (string), `name` (string), `price` (double), `stockQuantity` (int), `category` (string).
  - [ ] Viết hàm tạo mặc định `Product()` và hàm tạo có tham số `Product(id, name, price, stock, category)`.
  - [ ] Viết hàm tạo sao chép `Product(const Product& other)`.
  - [ ] **Bắt buộc:** Khai báo hàm hủy ảo `virtual ~Product() = default;`.
  - [ ] Viết các hàm Getter: `getId()`, `getName()`, `getPrice()`, `getStock()`, `getCategory()`.
  - [ ] Viết các hàm Setter có validate: `setPrice(double p)` (kiểm tra $p \ge 0$), `setStock(int q)` (kiểm tra $q \ge 0$).
  - [ ] Khai báo 4 hàm thuần ảo:
    * `virtual void displayInfo() const = 0;`
    * `virtual double calculateFinalPrice() const = 0;`
    * `virtual std::string getType() const = 0;`
    * `virtual Product* clone() const = 0;`
  - [ ] Nạp chồng toán tử: `operator==` (so sánh theo ID), `operator<` (so sánh theo giá), `friend operator<<`, `friend operator>>`.

---

### 🔹 TASK 2: Lớp Con Thực Phẩm `FoodProduct`
* **👤 Người thực hiện:** `TUẤN PHONG`
* **📁 File cần code:** `models/FoodProduct.h` và `models/FoodProduct.cpp`
* **Nhiệm vụ cụ thể:**
  - [ ] Kế thừa lớp cha: `class FoodProduct : public Product`.
  - [ ] Khai báo 2 thuộc tính riêng (`private`): `expiryDate` (string, hạn sử dụng), `isOrganic` (bool, hữu cơ).
  - [ ] Viết hàm tạo: Gọi `Product(id, name, price, stock, "Food")` trong danh sách khởi tạo + gán `expiryDate`, `isOrganic`.
  - [ ] Viết Getter: `getExpiryDate()`, `getIsOrganic()`.
  - [ ] **Override 4 hàm thuần ảo:**
    * `void displayInfo() const override`: In ra console dạng `[FOOD] Tên | Giá VND | HSD: yyyy-mm-dd | Hữu cơ: Có/Không`.
    * `double calculateFinalPrice() const override`: Nếu `isOrganic == true` $\rightarrow$ trả về `price * 1.05`, ngược lại trả về `price`.
    * `std::string getType() const override`: Trả về chuỗi `"FOOD"`.
    * `Product* clone() const override`: Trả về `new FoodProduct(*this)`.

---

### 🔹 TASK 3: Lớp Con Đồ Điện Tử `ElectronicsProduct`
* **👤 Người thực hiện:** `TRƯỜNG`
* **📁 File cần code:** `models/ElectronicsProduct.h` và `models/ElectronicsProduct.cpp`
* **Nhiệm vụ cụ thể:**
  - [ ] Kế thừa lớp cha: `class ElectronicsProduct : public Product`.
  - [ ] Khai báo 2 thuộc tính riêng (`private`): `warrantyMonths` (int, số tháng bảo hành), `brand` (string, thương hiệu).
  - [ ] Viết hàm tạo: Gọi `Product(id, name, price, stock, "Electronics")` trong danh sách khởi tạo + gán `warrantyMonths`, `brand`.
  - [ ] Viết Getter: `getWarrantyMonths()`, `getBrand()`.
  - [ ] **Override 4 hàm thuần ảo:**
    * `void displayInfo() const override`: In ra console dạng `[ELECTRONICS] Tên | Giá VND | Hãng: Brand | Bảo hành: X tháng`.
    * `double calculateFinalPrice() const override`: Nếu `warrantyMonths > 12` $\rightarrow$ trả về `price * 1.05` (+5% phí bảo hành), ngược lại trả về `price`.
    * `std::string getType() const override`: Trả về chuỗi `"ELECTRONICS"`.
    * `Product* clone() const override`: Trả về `new ElectronicsProduct(*this)`.

---

### 🔹 TASK 4: Lớp Con Thời Trang `ClothingProduct`
* **👤 Người thực hiện:** `KIM HUỆ`
* **📁 File cần code:** `models/ClothingProduct.h` và `models/ClothingProduct.cpp`
* **Nhiệm vụ cụ thể:**
  - [ ] Kế thừa lớp cha: `class ClothingProduct : public Product`.
  - [ ] Khai báo 2 thuộc tính riêng (`private`): `size` (string, size áo/quần), `material` (string, chất liệu).
  - [ ] Viết hàm tạo: Gọi `Product(id, name, price, stock, "Clothing")` trong danh sách khởi tạo + gán `size`, `material`.
  - [ ] Viết Getter: `getSize()`, `getMaterial()`.
  - [ ] **Override 4 hàm thuần ảo:**
    * `void displayInfo() const override`: In ra console dạng `[CLOTHING] Tên | Giá VND | Size: L | Chất liệu: Cotton`.
    * `double calculateFinalPrice() const override`: Nếu `material` là `"Silk"` hoặc `"Leather"` $\rightarrow$ trả về `price * 1.10` (+10% hàng cao cấp), ngược lại trả về `price`.
    * `std::string getType() const override`: Trả về chuỗi `"CLOTHING"`.
    * `Product* clone() const override`: Trả về `new ClothingProduct(*this)`.

---

### 🔹 TASK 5: Test & Nghiệm Thu Nhóm Sản Phẩm (Dành cho Leader)
* **👤 Người thực hiện:** `ĐĂNG KHOA (Leader)`
* **📁 File cần code:** `main.cpp`
* **Nhiệm vụ cụ thể:**
  - [ ] Ghép 4 task trên lại và viết code test trong `main.cpp`:

```cpp
#include "models/Product.h"
#include "models/FoodProduct.h"
#include "models/ElectronicsProduct.h"
#include "models/ClothingProduct.h"
#include <iostream>
#include <vector>
#include <memory>

int main() {
    std::cout << "====================================================\n";
    std::cout << "   TEST NGHIEM THU NHOM SAN PHAM (POLYMORPHISM)     \n";
    std::cout << "====================================================\n\n";

    // 1. Tao danh sach da hinh chua 3 loai san pham
    std::vector<std::shared_ptr<Product>> testList;

    testList.push_back(std::make_shared<FoodProduct>("F01", "Sua tuoi TH", 32000, 100, "2026-12-31", true));
    testList.push_back(std::make_shared<ElectronicsProduct>("E01", "Tai nghe Sony", 350000, 50, 24, "Sony"));
    testList.push_back(std::make_shared<ClothingProduct>("C01", "Vay lua Ha Dong", 500000, 20, "M", "Silk"));

    // 2. Duyet danh sach va goi cac phuong thuc da hinh
    for (size_t i = 0; i < testList.size(); ++i) {
        std::cout << "[" << (i + 1) << "] ";
        testList[i]->displayInfo(); // Test da hinh 1: In thong tin
        std::cout << "    -> Gia goc: " << testList[i]->getPrice() 
                  << " VND | Gia sau tinh phi/thue: " << testList[i]->calculateFinalPrice() << " VND\n";
        std::cout << "    -> Nhan dien kieu (getType): " << testList[i]->getType() << "\n\n";
    }

    std::cout << "====================================================\n";
    std::cout << "  [SUCCESS] 4 CLASS SAN PHAM HOAT DONG CHINH XAC!   \n";
    std::cout << "====================================================\n";

    return 0;
}
```

* **Lệnh chạy kiểm tra:**
  ```bash
  g++ -std=c++17 main.cpp models/Product.cpp models/FoodProduct.cpp models/ElectronicsProduct.cpp models/ClothingProduct.cpp -o test_products
  ./test_products
  ```
