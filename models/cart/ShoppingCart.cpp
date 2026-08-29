#include "ShoppingCart.h"
#include <iomanip>

ShoppingCart::ShoppingCart() {}

void ShoppingCart::addItem(std::shared_ptr<Product> product, int quantity) {
    if (!product || quantity <= 0) return;

    // Kiem tra xem san pham da co trong gio chua -> neu co thi tang so luong
    for (auto& item : items) {
        if (item.getProduct() && item.getProduct()->getId() == product->getId()) {
            item.setQuantity(item.getQuantity() + quantity);
            return;
        }
    }

    // Neu chua co thi tao CartItem moi
    items.push_back(CartItem(product, quantity));
}

bool ShoppingCart::removeItem(const std::string& productId) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->getProduct() && it->getProduct()->getId() == productId) {
            items.erase(it);
            return true;
        }
    }
    return false;
}

bool ShoppingCart::updateQuantity(const std::string& productId, int newQty) {
    if (newQty <= 0) {
        return removeItem(productId);
    }
    for (auto& item : items) {
        if (item.getProduct() && item.getProduct()->getId() == productId) {
            item.setQuantity(newQty);
            return true;
        }
    }
    return false;
}

const std::vector<CartItem>& ShoppingCart::getItems() const {
    return items;
}

double ShoppingCart::getTotal() const {
    double total = 0.0;
    for (const auto& item : items) {
        total += item.getSubtotal();
    }
    return total;
}

int ShoppingCart::getItemCount() const {
    return static_cast<int>(items.size());
}

int ShoppingCart::getTotalQuantity() const {
    int totalQty = 0;
    for (const auto& item : items) {
        totalQty += item.getQuantity();
    }
    return totalQty;
}

void ShoppingCart::clear() {
    items.clear();
}

bool ShoppingCart::isEmpty() const {
    return items.empty();
}

void ShoppingCart::displayCart() const {
    if (items.empty()) {
        std::cout << "\n[Thong bao] Gio hang hien tai dang trong!\n";
        return;
    }

    std::cout << "\n=========================================================================================\n";
    std::cout << "                                   CHI TIET GIO HANG                                     \n";
    std::cout << "=========================================================================================\n";
    std::cout << std::left << std::setw(8) << "MA SP" 
              << " | " << std::setw(22) << "TEN SAN PHAM" 
              << " | " << std::setw(6) << "SL" 
              << " | " << std::setw(14) << "DON GIA" 
              << " | " << std::setw(16) << "THANH TIEN" << '\n';
    std::cout << "-----------------------------------------------------------------------------------------\n";

    for (const auto& item : items) {
        std::cout << item << '\n';
    }

    std::cout << "-----------------------------------------------------------------------------------------\n";
    std::cout << std::right << std::setw(60) << "TONG TIEN GIO HANG: " 
              << std::fixed << std::setprecision(0) << std::setw(15) << getTotal() << " VND\n";
    std::cout << "=========================================================================================\n";
}

ShoppingCart& ShoppingCart::operator+=(const CartItem& item) {
    this->addItem(item.getProduct(), item.getQuantity());
    return *this;
}

CartItem& ShoppingCart::operator[](int index) {
    return items[index];
}

const CartItem& ShoppingCart::operator[](int index) const {
    return items[index];
}

std::ostream& operator<<(std::ostream& os, const ShoppingCart& cart) {
    cart.displayCart();
    return os;
}
