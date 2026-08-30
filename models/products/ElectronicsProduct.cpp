#include "ElectronicsProduct.h"
#include <iomanip>

ElectronicsProduct::ElectronicsProduct(string id, string name, double price, int stock, 
                                       int warrantyMonths, string brand)
    : Product(id, name, "Electronics", price, stock), 
      warrantyMonths(warrantyMonths), brand(brand) {}

int ElectronicsProduct::getWarrantyMonths() const {
    return warrantyMonths;
}

string ElectronicsProduct::getBrand() const {
    return brand;
}

// [FIX - 30/08/2026]: Can chinh cot bang displayInfo() thang hang, deu cot dep mat
void ElectronicsProduct::displayInfo() const {
    cout << left << setw(12) << "ELECTRONICS"
         << " | " << setw(6) << id
         << " | " << setw(22) << name
         << " | " << right << setw(10) << fixed << setprecision(0) << price << " VND"
         << " | " << setw(7) << stockQuantity
         << " | Hang: " << left << setw(11) << brand
         << " | Bao hanh: " << warrantyMonths << " thang\n";
}

double ElectronicsProduct::calculateFinalPrice() const {
    if (warrantyMonths > 12) {
        return price * 1.05;
    }
    return price;
}

string ElectronicsProduct::getType() const {
    return "ELECTRONICS";
}

Product* ElectronicsProduct::clone() const {
    return new ElectronicsProduct(*this);
}