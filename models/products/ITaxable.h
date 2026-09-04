#ifndef I_TAXABLE_H
#define I_TAXABLE_H

#include <iostream>

// Giao dien (Interface) quy dinh nghia vu chiu Thue Gia Tri Gia Tang (VAT)
// Dung de minh hoa tinh chat ĐA KẾ THỪA (Multiple Inheritance) trong OOP C++
class ITaxable {
public:
    virtual ~ITaxable() = default;

    // Ty le thue VAT (vi du: 0.10 cho 10%)
    virtual double getVATRate() const = 0;

    // Tinh so tien thue VAT = Don gia * Ty le thue
    virtual double calculateVAT() const = 0;

    // Hien thi thong tin thue VAT
    virtual void displayTaxInfo() const = 0;
};

#endif // I_TAXABLE_H
