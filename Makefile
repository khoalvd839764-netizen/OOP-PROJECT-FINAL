CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = ordering_app
BUILD_DIR = build

SRCS = main.cpp \
       models/products/Product.cpp \
       models/products/FoodProduct.cpp \
       models/products/ElectronicsProduct.cpp \
       models/products/ClothingProduct.cpp \
       models/person/Person.cpp \
       models/person/Customer.cpp \
       models/cart/CartItem.cpp \
       models/cart/ShoppingCart.cpp \
       models/order/Order.cpp \
       managers/FileManager.cpp \
       app/OrderingApp.cpp

OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run: all
	./$(TARGET)

.PHONY: all clean run
