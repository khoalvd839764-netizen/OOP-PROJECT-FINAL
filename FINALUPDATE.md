# 📝 FINAL UPDATE: Tối Ưu & Nâng Cấp Hệ Thống

---

### 📍 1.1. Tính Phí Ship & Ngày Giao Linh Hoạt Theo Khu Vực (Điểm sáng tạo ⭐)
* **Khu vực TP.HCM / Hà Nội:** 
  * ⚡ Thời gian giao: **1 ngày** *(Ngày đặt + 1 ngày)*.
  * 💵 Phí giao hàng: **10.000 VND**.
* **Khu vực Tỉnh thành khác (Ngoài khu vực):** 
  * 🚚 Thời gian giao: **3 ngày** *(Ngày đặt + 3 ngày)*.
  * 💵 Phí giao hàng: **25.000 VND**.
* **Chính sách Freeship:** Đơn hàng $\ge 500.000$ VND được **Miễn phí vận chuyển (0 VND)** trên toàn quốc.
* **Tự động nhận diện:** Quét từ khóa địa chỉ (`TPHCM`, `HCM`, `Ho Chi Minh`, `Ha Noi`, `Hanoi`, `HN`) không phân biệt hoa/thường.

---

### 🎨 1.2. Căn Chỉnh Bảng Danh Sách Sản Phẩm Thẳng Hàng
* Sử dụng `std::setw`, `std::left`, `std::right` trong `displayInfo()` để căn cột thẳng tắp: `LOẠI | MÃ SP | TÊN SP | ĐƠN GIÁ | TỒN KHO | THÔNG TIN CHI TIẾT`.
* Hiển thị rõ **Mã sản phẩm `[ID]`** và **Số lượng `[Tồn kho]`** để người dùng dễ chọn mua.
* Khi chọn **Menu 3 (Thêm vào giỏ)** $\rightarrow$ Tự động in bảng sản phẩm trước khi hỏi nhập mã.

---

### 🛒 1.3. Thêm Nhiều Món Vào Giỏ Hàng Trong 1 Lượt (Batch Add to Cart)
* Cho phép nhập 1 dòng duy nhất chứa nhiều mã sản phẩm cách nhau bởi dấu phẩy `,`.
* Hỗ trợ kèm số lượng (ví dụ: `F01:2, E01:1, C01:3`) hoặc mặc định số lượng = 1 (ví dụ: `F01, E01, C01`).
* Tự động xóa khoảng trắng thừa, kiểm tra tồn kho từng món và in báo cáo kết quả chi tiết.

---

### 💳 1.4. Tùy Chọn Phương Thức Thanh Toán (Strategy Pattern ⭐)
* Cho phép lựa chọn 1 trong 2 hình thức thanh toán:
  1. **Tiền mặt khi nhận hàng (COD)**.
  2. **Chuyển khoản Ngân hàng (TPBank)**:
     * Ngân hàng: `TPBank`
     * Tên chủ tài khoản: `HKD NHOM3 ORDERAPP`
     * Số tài khoản: `000000001`
     * Nội dung chuyển khoản: Tự động điền theo **Mã đơn hàng** của hệ thống (ví dụ: `ORD-1001`).
* In khung hướng dẫn chuyển khoản trực tiếp ra màn hình và lưu vào file `data/orders.txt`.

---

### 🔄 1.5. Chức Năng Hủy Đơn Hàng & Chính Sách Hoàn Tiền (Cancel Order & Refund Policy ⭐)
* **Menu 7:** `7. Huy don hang da dat`
* **Xử lý linh hoạt theo phương thức thanh toán:**
  * 💵 **Đơn COD:** Hủy ngay lập tức $\rightarrow$ Trạng thái chuyển thành `Cancelled` (Không phát sinh chi phí).
  * 🏦 **Đơn Chuyển khoản TPBank:** Tiếp nhận hủy $\rightarrow$ Trạng thái chuyển thành `Cancelled - Cho hoan tien (24h)` $\rightarrow$ In phiếu thông báo **tiền sẽ được hoàn về tài khoản của khách trong vòng 24H LÀM VIỆC**.
* **Tự động hoàn kho (Restock):** Cộng trả lại đúng số lượng các món hàng trong đơn bị hủy vào kho dữ liệu của cửa hàng.

---

### 👑 1.6. Hệ Thống Thành Viên, Tích Điểm & Phân Hạng VIP (Membership & Loyalty System ⭐)
* **Khởi động ứng dụng:** Hiện ngay màn hình Chào mừng: **1. Đăng nhập**, **2. Đăng ký**, **3. Khách vãng lai**.
* **Lưu trữ tài khoản:** Lưu vĩnh viễn trong file **`data/users.txt`**.
* **Tích điểm tự động:** Mỗi **10.000 VND** chi tiêu $\rightarrow$ Cộng **+1.000 điểm** thưởng.
* **Đổi Voucher Freeship:** Dùng **20.000 điểm** để đổi **1 lần Freeship** (giảm phí ship về 0đ).
* **Phân hạng VIP & Giảm giá trực tiếp trên tổng đơn:**
  * 🥉 **Từ 200.000 điểm (Hạng ĐỒNG):** Giảm **3%**.
  * 🥈 **Từ 500.000 điểm (Hạng BẠC):** Giảm **5%**.
  * 🥇 **Từ 1.000.000 điểm (Hạng VÀNG):** Giảm **15%**.
