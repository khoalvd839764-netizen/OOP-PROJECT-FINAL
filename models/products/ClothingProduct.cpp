#include "ClothingProduct.h"
#include <iostream>
#include <iomanip>

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

// [FIX - 30/08/2026]: Can chinh cot bang displayInfo() thang hang, deu cot dep mat
void ClothingProduct::displayInfo() const {
    cout << left << setw(12) << "CLOTHING"
         << " | " << setw(6) << getId()
         << " | " << setw(22) << getName()
         << " | " << right << setw(10) << fixed << setprecision(0) << getPrice() << " VND"
         << " | " << setw(7) << getStockQuantity()
         << " | Size: " << left << setw(11) << size
         << " | Chat lieu: " << material
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
