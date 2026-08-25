CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = ordering_app

SRCS = main.cpp \
       models/Product.cpp \
       models/FoodProduct.cpp \
       models/ElectronicsProduct.cpp \
       models/ClothingProduct.cpp \
       models/Person.cpp \
       models/Customer.cpp \
       models/CartItem.cpp \
       models/ShoppingCart.cpp \
       models/Order.cpp \
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
