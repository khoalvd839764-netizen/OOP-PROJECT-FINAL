# 📋 WORK TODAY: Hướng Dẫn Hoàn Thiện Tầng Managers & App Controller

> **Mục tiêu chặng cuối:** Hoàn thiện 100% tầng Quản lý (`managers/`), Giao diện điều khiển (`app/`) và chạy toàn bộ chương trình `main.cpp` để hoàn thành đồ án!

---

## 🗺️ THỨ TỰ BẮT BUỘC PHẢI LÀM (Dependency Order)

```
[BƯỚC 1: XONG ĐẦU TIÊN] ──► managers/DataManager.h      (Template class quản lý kho)
         │
         ▼
[BƯỚC 2: XONG THỨ HAI]  ──► managers/FileManager.h/.cpp (Đọc products.txt & Ghi file)
         │
         ▼
[BƯỚC 3: XONG THỨ BA]   ──► app/OrderingApp.h/.cpp      (Menu Console điều khiển app)
         │
         ▼
[BƯỚC 4: VỀ ĐÍCH 🏆]     ──► main.cpp & Makefile        (Chạy toàn bộ ứng dụng từ A-Z)
```

> **Lý do thứ tự này:**
> 1. `DataManager<T>` hoàn toàn độc lập, là "cái kho" để chứa dữ liệu.
> 2. `FileManager` là "thợ đọc/ghi file", đọc file xong sẽ nạp dữ liệu vào `DataManager`.
> 3. `OrderingApp` cần cả 2 class trên để hoạt động (lấy kho từ `DataManager` và gọi `FileManager` lưu đơn).
> 4. `main.cpp` chỉ việc bật `OrderingApp` lên chạy.

---

## 👥 BẢNG PHÂN CÔNG NHIỆM VỤ

| Task | File phụ trách | Người thực hiện (Assignee) | Độ ưu tiên | Trạng thái |
| :---: | :--- | :--- | :---: | :---: |
| **Task 1** | `managers/DataManager.h` | `👤 KIM HUỆ` | 🔴 **Ưu tiên 1 (Làm trước)** | ✅ **Đã hoàn thành** |
| **Task 2** | `managers/FileManager.h / .cpp` | `👤 TUẤN PHONG` | 🟠 **Ưu tiên 2 (Làm kế tiếp)** | ✅ **Đã hoàn thành** |
| **Task 3** | `app/OrderingApp.h / .cpp` | `👤 TRƯỜNG` | 🟡 **Ưu tiên 3 (Làm sau 1 & 2)** | ⏳ Chưa xong |
| **Task 4** | `main.cpp` & Test Nghiệm Thu | `👤 ĐĂNG KHOA (Leader)` | 🟢 **Ưu tiên 4 (Về đích)** | ⏳ Chưa xong |

---

## 📝 CHI TIẾT HƯỚNG DẪN TỪNG BƯỚC

---

### 🔹 TASK 1: Hoàn thiện `managers/DataManager.h` (Làm đầu tiên)
* **👤 Người thực hiện:** `KIM HUỆ`
* **📁 File cần code:** `managers/DataManager.h`
* **Đặc điểm:** Là **Template Class** (Header-only, chỉ có file `.h`, không cần `.cpp`).
* **Nhiệm vụ cụ thể:**
  - [x] Khai báo template: `template <typename T> class DataManager { ... };`
  - [x] Thuộc tính `private`: `std::vector<T> items;`
  - [x] Viết hàm `void add(const T& item)`: `items.push_back(item);`
  - [x] Viết hàm `bool remove(int index)`: Kiểm tra `index` hợp lệ rồi `erase`.
  - [x] Viết hàm `const std::vector<T>& getAll() const`: Trả về `items`.
  - [x] Viết hàm `size_t count() const`: Trả về `items.size()`.
  - [x] Viết hàm `T& operator[](int index)` và `const T& operator[](int index) const`.
  - [x] **Template lồng Lambda:**
    * `template <typename Func> std::vector<T> filter(Func condition)`: Duyệt `items`, nếu `condition(item) == true` thì gom vào kết quả trả về (dùng tìm kiếm SP).
    * `template <typename Func> void sort(Func comparator)`: Gọi `std::sort(items.begin(), items.end(), comparator)` (dùng sắp xếp SP).
    * `template <typename Func> T* find(Func condition)`: Tìm phần tử đầu tiên thỏa mãn, trả về con trỏ `&item` hoặc `nullptr` (dùng tìm SP theo ID).

---

### 🔹 TASK 2: Hoàn thiện `managers/FileManager.h` & `FileManager.cpp` (Làm thứ hai)
* **👤 Người thực hiện:** `TUẤN PHONG`
* **📁 File cần code:** `managers/FileManager.h` và `managers/FileManager.cpp`
* **Đặc điểm:** Chỉ chứa các hàm `static`, không cần tạo đối tượng.
* **Nhiệm vụ cụ thể:**
  - [x] **Hàm 1:** `static std::vector<std::shared_ptr<Product>> loadProducts(const std::string& filename);`
    * Dùng `std::ifstream` mở file `data/products.txt`.
    * Đọc bỏ qua dòng header đầu tiên.
    * Dùng `std::stringstream` và `getline(ss, token, '|')` để tách từng cột dữ liệu.
    * Đọc `type` ("FOOD", "ELECTRONICS", "CLOTHING") $\rightarrow$ ép kiểu `price` (`stod`), `stock` (`stoi`).
    * Dựa vào `type` gọi `std::make_shared<FoodProduct/ElectronicsProduct/ClothingProduct>(...)` và `push_back` vào vector.
    * Đóng file và trả về vector sản phẩm.
  - [x] **Hàm 2:** `static void saveOrder(const Order& order, const std::string& filename);`
    * Dùng `std::ofstream` mở file ở chế độ ghi tiếp `std::ios::app`.
    * Ghi đầy đủ thông tin hóa đơn: Mã đơn, ngày đặt, ngày giao, tên KH, SĐT, địa chỉ, danh sách món hàng, phí ship, tổng tiền.
    * Đóng file.

---

### 🔹 TASK 3: Hoàn thiện `app/OrderingApp.h` & `OrderingApp.cpp` (Làm thứ ba)
* **👤 Người thực hiện:** `TRƯỜNG`
* **📁 File cần code:** `app/OrderingApp.h` và `app/OrderingApp.cpp`
* **Đặc điểm:** "Bộ não" điều phối tương tác Console giữa người dùng và toàn bộ hệ thống.
* **Thuộc tính trong `OrderingApp`:**
  ```cpp
  DataManager<std::shared_ptr<Product>> productManager; // Kho sản phẩm
  ShoppingCart cart;                                     // Giỏ hàng hiện tại
  Customer currentCustomer;                             // Khách hàng hiện tại
  std::vector<Order> orders;                            // Danh sách đơn đã đặt
  ```
* **Nhiệm vụ cụ thể:**
  - [ ] **Constructor `OrderingApp()`:** Gọi `FileManager::loadProducts("data/products.txt")` rồi nạp vào `productManager`.
  - [ ] **Hàm `run()`:** Vòng lặp `while (true)` hiển thị menu 6 chức năng:
    ```
    ================================================
               HE THONG DAT HANG ONLINE             
    ================================================
    1. Xem danh sach san pham
    2. Tim kiem san pham theo ten
    3. Them san pham vao gio hang
    4. Xem chi tiet gio hang
    5. Tien hanh dat hang & Thanh toan
    6. Xem lich su cac don hang da dat
    0. Thoat chuong trinh
    ------------------------------------------------
    Nhap lua chon cua ban: 
    ```
  - [ ] **Chức năng 1 (`showProducts`):** Lấy danh sách từ `productManager.getAll()` và gọi `displayInfo()` (đa hình).
  - [ ] **Chức năng 2 (`searchProducts`):** Nhập từ khóa $\rightarrow$ gọi `productManager.filter(...)` $\rightarrow$ in kết quả.
  - [ ] **Chức năng 3 (`addToCart`):** Nhập mã SP $\rightarrow$ tìm trong `productManager` $\rightarrow$ kiểm tra tồn kho $\rightarrow$ gọi `cart.addItem(prod, qty)`.
  - [ ] **Chức năng 4 (`viewCart`):** Gọi `cout << cart` (in bảng giỏ hàng).
  - [ ] **Chức năng 5 (`placeOrder`):** 
    * Kiểm tra giỏ hàng có rỗng không.
    * Nhập thông tin khách hàng (Họ tên, SĐT, Email, Địa chỉ giao hàng).
    * Tạo `Customer` $\rightarrow$ Tạo `Order(customer, cart.getItems())`.
    * In hóa đơn ra màn hình và hỏi xác nhận `(Y/N)`.
    * Nếu `Y`: Lưu vào `orders`, gọi `FileManager::saveOrder(...)`, dọn sạch giỏ `cart.clear()`.
  - [ ] **Chức năng 6 (`viewOrderHistory`):** Duyệt `orders` và in các đơn đã đặt.

---

### 🔹 TASK 4: `main.cpp` & Test Toàn Bộ Ứng Dụng (Về đích)
* **👤 Người thực hiện:** `ĐĂNG KHOA (Leader)`
* **📁 File cần code:** `main.cpp`
* **Trong `main.cpp`:**
  ```cpp
  #include "app/OrderingApp.h"

  int main() {
      OrderingApp app;
      app.run();
      return 0;
  }
  ```
* **Lệnh Build & Chạy toàn bộ ứng dụng:**
  ```bash
  make clean && make
  ./ordering_app
  ```

---

## ⚠️ Lưu ý kỹ thuật quan trọng:
1. **Xử lý trôi lệnh bàn phím:** Khi vừa nhập số (`cin >> choice`) xong chuyển sang nhập chuỗi (`getline`), phải dùng `cin.ignore(10000, '\n');` để xóa bộ đệm.
2. **Kiểm tra file tồn tại:** Trong `FileManager::loadProducts`, nếu file `data/products.txt` không mở được phải in cảnh báo rõ ràng.
