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

void ElectronicsProduct::displayInfo() const {
    cout << "[ELECTRONICS] " << name 
         << " | " << fixed << setprecision(0) << price << " VND"
         << " | Hang: " << brand 
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