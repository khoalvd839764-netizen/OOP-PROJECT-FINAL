cmake_minimum_required(VERSION 3.15)
project(OrderingApp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    add_compile_options(/W3 /EHsc)
else()
    add_compile_options(-Wall -Wextra)
endif()

# Source files
set(SOURCES
    main.cpp
    app/OrderingApp.cpp
    managers/FileManager.cpp
    models/products/Product.cpp
    models/products/FoodProduct.cpp
    models/products/ElectronicsProduct.cpp
    models/products/ClothingProduct.cpp
    models/person/Person.cpp
    models/person/Customer.cpp
    models/person/Admin.cpp
    models/cart/CartItem.cpp
    models/cart/ShoppingCart.cpp
    models/order/Order.cpp
)

add_executable(ordering_app ${SOURCES})

# Include directories
target_include_directories(ordering_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/app
    ${CMAKE_CURRENT_SOURCE_DIR}/managers
    ${CMAKE_CURRENT_SOURCE_DIR}/models
)

# Set working directory to project root so that "data/..." files are found when running from Visual Studio
set_target_properties(ordering_app PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
