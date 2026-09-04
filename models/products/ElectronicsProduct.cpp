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
         << " | Bao hanh: " << warrantyMonths << " thang"
         << " (VAT: 10%)\n";
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

// ============================================================================
// [FIX - 05/09/2026]: CAI DAT CAC PHUONG THUC CUA INTERFACE ITaxable (ĐA KẾ THỪA)
// ============================================================================
double ElectronicsProduct::getVATRate() const {
    return 0.10; // Thue VAT 10% ap dung cho thiet bi dien tu
}

double ElectronicsProduct::calculateVAT() const {
    return calculateFinalPrice() * getVATRate();
}

void ElectronicsProduct::displayTaxInfo() const {
    cout << "  [THUE VAT 10%] San pham [" << id << " - " << name << "]: "
         << fixed << setprecision(0) << calculateVAT() << " VND (Da bao gom trong don gia)\n";
}