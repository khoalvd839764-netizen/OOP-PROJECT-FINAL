#include "CartItem.h"
#include <iomanip>

CartItem::CartItem()
    : product(nullptr), quantity(0) {}

CartItem::CartItem(std::shared_ptr<Product> product, int quantity)
    : product(product), quantity((quantity > 0) ? quantity : 1) {}

CartItem::CartItem(const CartItem& other)
    : product(other.product), quantity(other.quantity) {}

std::shared_ptr<Product> CartItem::getProduct() const {
    return product;
}

int CartItem::getQuantity() const {
    return quantity;
}

void CartItem::setQuantity(int qty) {
    if (qty > 0) {
        this->quantity = qty;
    }
}

double CartItem::getSubtotal() const {
    if (product != nullptr) {
        return quantity * product->calculateFinalPrice();
    }
    return 0.0;
}

bool CartItem::operator==(const CartItem& other) const {
    if (this->product && other.product) {
        return this->product->getId() == other.product->getId();
    }
    return false;
}

CartItem CartItem::operator+(int extraQty) const {
    return CartItem(this->product, this->quantity + extraQty);
}

std::ostream& operator<<(std::ostream& os, const CartItem& item) {
    if (item.product != nullptr) {
        os << std::left << std::setw(8) << item.product->getId()
           << " | " << std::setw(22) << item.product->getName()
           << " | SL: " << std::setw(4) << item.quantity
           << " | Don gia: " << std::fixed << std::setprecision(0) << std::setw(10) << item.product->calculateFinalPrice() << " VND"
           << " | Thanh tien: " << std::setw(12) << item.getSubtotal() << " VND";
    }
    return os;
}
