cmake_minimum_required(VERSION 3.17)
project(project)

set(CMAKE_CXX_STANDARD 17)

add_executable(project main.cpp model/item_model.cpp model/item_model.h model/user_model.cpp model/user_model.h model/warehouse_model.cpp model/warehouse_model.h view/io_view.cpp view/io_view.h controller/warehouse_controller.cpp controller/warehouse_controller.h controller/user_controller.cpp controller/user_controller.h)