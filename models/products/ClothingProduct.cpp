#include "ClothingProduct.h"
#include <iostream>

using namespace std;

ClothingProduct::ClothingProduct()
    : Product("", "", "Clothing", 0, 0), size(""), material("") {}

ClothingProduct::ClothingProduct(
    const string& id,
    const string& name,
    double price,
    int stockQuantity,
    const string& size,
    const string& material
)
    : Product(id, name, "Clothing", price, stockQuantity),
      size(size),
      material(material)
{
}

string ClothingProduct::getSize() const {
    return size;
}

string ClothingProduct::getMaterial() const {
    return material;
}

void ClothingProduct::displayInfo() const {
    cout << "[CLOTHING] "
         << getName()
         << " | " << getPrice() << " VND"
         << " | Size: " << size
         << " | Chất liệu: " << material
         << endl;
}

double ClothingProduct::calculateFinalPrice() const {
    if (material == "Silk" || material == "Leather") {
        return getPrice() * 1.10;
    }
    return getPrice();
}

string ClothingProduct::getType() const {
    return "CLOTHING";
}

Product* ClothingProduct::clone() const {
    return new ClothingProduct(*this);
}
