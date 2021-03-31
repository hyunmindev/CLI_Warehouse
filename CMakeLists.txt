cmake_minimum_required(VERSION 3.17)
project(project)

set(CMAKE_CXX_STANDARD 17)

add_executable(project main.cpp model/item_model.cpp model/item_model.h model/user_model.cpp model/user_model.h model/warehouse_model.cpp model/warehouse_model.h controller/warehouse_controller.cpp controller/warehouse_controller.h controller/auth_controller.cpp controller/auth_controller.h view/auth_view.cpp view/auth_view.h view/warehouse_view.cpp view/warehouse_view.h view/view.cpp view/view.h string_processor.cpp string_processor.h)