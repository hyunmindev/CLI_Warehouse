//
// Created by 정현민 on 2021/03/25.
//

#include "warehouse_controller.h"

WarehouseController::WarehouseController() {
  this->ReadWarehouse();
  this->ReadItem();
  this->ReadStoreState();
}

WarehouseController::~WarehouseController() = default;

void WarehouseController::ReadItem() {
  std::ifstream read_item_file;
  read_item_file.open("item.txt", std::ios::in); //file name
  if (read_item_file.is_open()) {
    while (!read_item_file.eof()) {
      std::string line = "\n";
      getline(read_item_file, line, '\n');
      if (line.empty() || line == "\n" || line == "\t") continue;
      std::vector<std::string> item_information = StringHandler::SplitString(line, '\t');
      ItemModel item(std::move(item_information[0]),
                     StringHandler::StringToInteger(item_information[1]),
                     StringHandler::StringToInteger(item_information[2]));
      if (std::find(this->all_items_.begin(), this->all_items_.end(), item) == this->all_items_.end()) {
        this->all_items_.push_back(item);
      }
    }
  } else {
    std::ofstream new_file("item.txt");
    new_file.close();
  }
  read_item_file.close();
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
      WarehouseModel find_warehouse(store_state_information[0], 0, 0, 0);
      WarehouseModel warehouse = *std::find(this->all_warehouses_.begin(), this->all_warehouses_.end(), find_warehouse);
      int index = 0;
      for (index = 0; index < this->all_items_.size(); ++index) {
        if (store_state_information[1] == this->all_items_[index].GetIdentifier()) {
          break;
        }
      }
      bool insert = false;
      for (int i = 0; i < this->warehouse_state_.size(); ++i) {
        if (this->warehouse_state_[i].warehouse == warehouse) {
          bool insert_item = false;
          for (int j = 0; j < this->warehouse_state_[i].items_state.size(); ++j) {
            if (this->warehouse_state_[i].items_state[j].first == this->all_items_[index]) {
              this->warehouse_state_[i].items_state[j].second =
                  StringHandler::StringToInteger(store_state_information[2]);
              insert_item = true;
            }
          }
          if (!insert_item) {
            this->warehouse_state_[i].items_state.push_back({this->all_items_[index],
                                                             StringHandler::StringToInteger(store_state_information[2])});
          }
          insert = true;
          break;
        }
      }
      if (!insert) {
        std::vector<std::pair<ItemModel, int>> item;
        item.push_back({this->all_items_[index],
                        StringHandler::StringToInteger(
                            store_state_information[2])});
        this->warehouse_state_.push_back({warehouse, item});
      }
    }
  } else {
    std::ofstream new_file("store_state.txt");
    new_file.close();
  }
  for (int i = 0; i < this->warehouse_state_.size(); ++i) {
    std::cout << warehouse_state_[i].warehouse.GetIdentifier() << ":\n";
    for (int j = 0; j < warehouse_state_[i].items_state.size(); ++j) {
      std::cout << warehouse_state_[i].items_state[j].first.GetIdentifier() << warehouse_state_[i].items_state[j].second
                << "개\t";
    }
    std::cout << std::endl;
  }
  read_store_state_file.close();
}

void WarehouseController::ReadWarehouse() {
  std::ifstream read_warehouse_file;
  read_warehouse_file.open("warehouse.txt", std::ios::in); //file name
  if (read_warehouse_file.is_open()) {
    while (!read_warehouse_file.eof()) {
      std::string line = "\n";
      getline(read_warehouse_file, line, '\n');\
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