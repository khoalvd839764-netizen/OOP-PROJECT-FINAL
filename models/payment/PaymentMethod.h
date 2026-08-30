#ifndef PAYMENT_METHOD_H
#define PAYMENT_METHOD_H

#include <string>
#include <iostream>
#include <iomanip>

// [FIX - 30/08/2026]: Bo sung he thong Phuong thuc thanh toan da hinh (Strategy Pattern)
class PaymentMethod {
public:
    virtual ~PaymentMethod() = default;
    virtual std::string getMethodName() const = 0;
    virtual std::string getPaymentDetails(const std::string& orderId) const = 0;
    virtual void displayGuide(const std::string& orderId, double amount) const = 0;
};

// 1. Thanh toan tien mat (COD)
class CashPayment : public PaymentMethod {
public:
    std::string getMethodName() const override {
        return "Tien mat khi nhan hang (COD)";
    }

    std::string getPaymentDetails(const std::string& /*orderId*/) const override {
        return "Thanh toan tien mat cho Shipper khi nhan hang";
    }

    void displayGuide(const std::string& /*orderId*/, double /*amount*/) const override {
        std::cout << "  -> Quy khach vui long chuan bi tien mat khi nhan hang tu Shipper.\n";
    }
};

// 2. Thanh toan chuyen khoan Ngan hang (TPBank)
class BankTransferPayment : public PaymentMethod {
private:
    std::string bankName;
    std::string accountNumber;
    std::string accountHolder;

public:
    BankTransferPayment()
        : bankName("TPBank (Ngan hang Tien Phong)"),
          accountNumber("000000001"),
          accountHolder("HKD NHOM3 ORDERAPP") {}

    std::string getMethodName() const override {
        return "Chuyen khoan Ngan hang (TPBank)";
    }

    std::string getPaymentDetails(const std::string& orderId) const override {
        return "TPBank | STK: " + accountNumber + " | Chu TK: " + accountHolder + " | ND: " + orderId;
    }

    void displayGuide(const std::string& orderId, double amount) const override {
        std::cout << "\n  =================== THONG TIN CHUYEN KHOAN TPBANK ===================\n";
        std::cout << "  Ngan hang        : " << bankName << '\n';
        std::cout << "  Chu tai khoan    : " << accountHolder << '\n';
        std::cout << "  So tai khoan     : " << accountNumber << '\n';
        std::cout << "  So tien          : " << std::fixed << std::setprecision(0) << amount << " VND\n";
        std::cout << "  Noi dung chuyen  : " << orderId << '\n';
        std::cout << "  ---------------------------------------------------------------------\n";
        std::cout << "  [Luu y]: Vui long ghi dung Noi dung chuyen khoan la '" << orderId << "'\n";
        std::cout << "  =====================================================================\n";
    }
};

#endif
