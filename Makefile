CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SRCS = main.cpp \
       app/OrderingApp.cpp \
       managers/FileManager.cpp \
       models/products/Product.cpp \
       models/products/FoodProduct.cpp \
       models/products/ElectronicsProduct.cpp \
       models/products/ClothingProduct.cpp \
       models/person/Person.cpp \
       models/person/Customer.cpp \
       models/person/Admin.cpp \
       models/cart/CartItem.cpp \
       models/cart/ShoppingCart.cpp \
       models/order/Order.cpp

OBJS = $(SRCS:.cpp=.o)
TARGET = ordering_app

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean
