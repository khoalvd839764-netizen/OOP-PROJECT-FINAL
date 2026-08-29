CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = ordering_app

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

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
