#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "../models/products/Product.h"
#include "../models/order/Order.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>

class FileManager {
public:
    static std::vector<std::shared_ptr<Product>> loadProducts(const std::string& filename);
    static void saveOrder(const Order& order, const std::string& filename);
};

#endif
