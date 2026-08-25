#include "Product.h"


void Product::setPrice(double price) {
  if (price >= 0) {
    this->price = price;
  }
}
void Product::setStockQuantity(int stockQuantity) {
  if (stockQuantity >= 0) {
    this->stockQuantity = stockQuantity;
  }
}


bool Product::operator==(const Product& other) const { return this->id == other.id; }
bool Product::operator<(const Product& other) const { return this->price < other.price; }

ostream &operator<<(ostream &os, const Product &p) {
  os << "ID: " << p.id << endl;
  os << "Name: " << p.name << endl;
  os << "Category: " << p.category << endl;
  os << "Price: " << p.price << endl;
  os << "Stock Quantity: " << p.stockQuantity << endl;
  return os;
}
istream &operator>>(istream &is, Product &p) {
  cout << "Enter ID: ";
  is >> p.id;       
  cout << "Enter Name: ";
  is >> p.name;
  cout << "Enter Category: ";
  is >> p.category;
  cout << "Enter Price: ";
  is >> p.price;
  cout << "Enter Stock Quantity: ";
  is >> p.stockQuantity;
  return is;
}
