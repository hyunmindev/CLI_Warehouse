//
// Created by 정현민 on 2021/03/25.
//

#include "warehouse_controller.h"

WarehouseController::WarehouseController() {
  this->ReadWarehouse();
}

WarehouseController::~WarehouseController() = default;

void WarehouseController::ReadWarehouse() {
  std::ifstream read_warehouse_file;
  read_warehouse_file.open("warehouse.txt", std::ios::in); //file name
  if (read_warehouse_file.is_open()) {
    while (!read_warehouse_file.eof()) {
      std::string line = "\n";
      getline(read_warehouse_file, line, '\n');
      if (line.empty()) continue;
      std::vector<std::string> user_information = StringHandler::SplitString(line, '\t');

    }
  } else {
    std::ofstream new_file("auth.txt");
    new_file.close();
  }
  read_warehouse_file.close();
}