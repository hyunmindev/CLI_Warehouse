//
// Created by 정현민 on 2021/03/25.
//

#include "warehouse_controller.h"

WarehouseController::WarehouseController() {
  this->ReadWarehouse();
}

WarehouseController::~WarehouseController() = default;

void WarehouseController::ReadItem() {
  std::ifstream read_item_file;
  read_item_file.open("item.txt", std::ios::in); //file name
  if (read_item_file.is_open()) {
    while (!read_item_file.eof()) {
      std::string line = "\n";
      getline(read_item_file, line, '\n');
      if (line.empty()) continue;
      std::vector<std::string> item_information = StringHandler::SplitString(line, '\t');
      ItemModel item(std::move(item_information[0]),
                     StringHandler::StringToInteger(item_information[1]),
                     StringHandler::StringToInteger(item_information[2]));
      if (std::find(this->all_items_.begin(), this->all_items_.end(), item) == this->all_items_.end()) {
        this->all_items_.push_back(item);
      }
    }
  }
}

void WarehouseController::ReadStoreState() {
  std::ifstream read_store_state_file;
  read_store_state_file.open("store_state.txt", std::ios::in); //file name
  if (read_store_state_file.is_open()) {
    while (!read_store_state_file.eof()) {
      std::string line = "\n";
      getline(read_store_state_file, line, '\n');
      if (line.empty()) continue;
      std::vector<std::string> store_state_information = StringHandler::SplitString(line, '\t');
      WarehouseModel
    }
  } else {
    std::ofstream new_file("store_state.txt");
    new_file.close();
  }
}

void WarehouseController::ReadWarehouse() {
  std::ifstream read_warehouse_file;
  read_warehouse_file.open("warehouse.txt", std::ios::in); //file name
  if (read_warehouse_file.is_open()) {
    while (!read_warehouse_file.eof()) {
      std::string line = "\n";
      getline(read_warehouse_file, line, '\n');
      std::cout << line << std::endl;
      if (line.empty()) continue;
      std::vector<std::string> warehouse_information = StringHandler::SplitString(line, '\t');
      WarehouseModel
          warehouse(std::move(warehouse_information[0]),
                    StringHandler::StringToInteger(warehouse_information[2]),
                    StringHandler::StringToInteger(warehouse_information[3]),
                    StringHandler::StringToInteger(warehouse_information[1]));
      if (std::find(this->all_warehouses_.begin(), this->all_warehouses_.end(), warehouse)
          == this->all_warehouses_.end()) {
        this->all_warehouses_.push_back(warehouse);
      }
    }
  } else {
    std::ofstream new_file("warehouse.txt");
    new_file.close();
  }
  read_warehouse_file.close();
}