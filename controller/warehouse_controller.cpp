//
// Created by 정현민 on 2021/03/25.
//

#include "warehouse_controller.h"

WarehouseController::WarehouseController() {
  this->ReadFiles();
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
            if (this->warehouse_state_[i].items_state[j].first == this->all_items_[index].GetIdentifier()) {
              this->warehouse_state_[i].items_state[j].second =
                  StringHandler::StringToInteger(store_state_information[2]);
              insert_item = true;
            }
          }
          if (!insert_item) {
            this->warehouse_state_[i].items_state.push_back({this->all_items_[index].GetIdentifier(),
                                                             StringHandler::StringToInteger(store_state_information[2])});
          }
          insert = true;
          break;
        }
      }
      if (!insert) {
        std::vector<std::pair<std::string , int>> item;
        item.push_back({this->all_items_[index].GetIdentifier(),
                        StringHandler::StringToInteger(
                            store_state_information[2])});
        this->warehouse_state_.push_back({warehouse, item});
      }
    }
  } else {
    std::ofstream new_file("store_state.txt");
    new_file.close();
  }
//  for (int i = 0; i < this->warehouse_state_.size(); ++i) {
//    std::cout << warehouse_state_[i].warehouse.GetIdentifier() << ":\n";
//    for (int j = 0; j < warehouse_state_[i].items_state.size(); ++j) {
//      std::cout << warehouse_state_[i].items_state[j].first.GetIdentifier() << warehouse_state_[i].items_state[j].second
//                << "개\t";
//    }
//    std::cout << std::endl;
//  }
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

void WarehouseController::Receive(const std::string &item_id, const std::string &warehouse_id, int count) {
  remove("store_state.txt");
  std::vector<WarehouseState>::iterator it = warehouse_state_.begin();
  std::ofstream update_store_state;
  update_store_state.open("store_state.txt", std::ios::out); //file name
  if (update_store_state.is_open()) {
    while (it != warehouse_state_.end()) {
      std::string temp_warehouse_id = it->warehouse.GetIdentifier();
      std::vector<std::pair<std::string, int>>::iterator iter = it->items_state.begin();
      while (iter != it->items_state.end()) {
        if (iter->first == item_id) {
          std::string tmp = temp_warehouse_id + '\t' + iter->first + '\t' +
              StringHandler::IntegerToString(count);
          update_store_state.write(tmp.c_str(), tmp.size());
        } else {
          std::string tmp = temp_warehouse_id + '\t' + iter->first + '\t' +
              StringHandler::IntegerToString(iter->second);
          update_store_state.write(tmp.c_str(), tmp.size());
        }
      }

    }
  }
}

void WarehouseController::Move(const std::string &item_id, int count) {

}

void WarehouseController::ReadFiles() {
  this->ReadItem();
  this->ReadWarehouse();
  this->ReadStoreState();
}

bool WarehouseController::Release(std::string &identifier, int item_count) {
  this->ReadFiles();
  int item_index = this->FindItem(identifier);
  if (item_index == -1) {
    OutputHandler::Error(ErrorType::NO_EXISTING_ITEM);
    return false;
  }
  int current_item_count = FindWarehouseItemIndex(identifier);
  if (current_item_count < item_count) OutputHandler::Error(ErrorType::FEW_ITEM_COUNT);
  for (int i = 0; i < this->find_item_index_.size(); ++i) {
    std::cout << "창고: " << this->warehouse_state_[this->find_item_index_[i].first].warehouse.GetIdentifier()
              << "\t개수: "
              << this->warehouse_state_[this->find_item_index_[i].first].items_state[this->find_item_index_[i].second].second
              << std::endl;
  }
  if (current_item_count < item_count) return false;
  this->item_count_ = item_count;
  return true; //goto 부프롬프트
}

void WarehouseController::ReleaseSubPrompt(std::vector<std::string> &identifiers) {
  std::vector<std::pair<int, int>> index_item_in_warehouse;
  bool is_possible = false;
  for (int i = 0; i < identifiers.size(); ++i) {
    if(is_possible) break;
    WarehouseModel warehouse(identifiers[i], 0, 0, 0);
    for (int j = 0; j < this->find_item_index_.size(); ++j) {
      if (warehouse_state_[this->find_item_index_[j].first].warehouse == warehouse) {
        int count =
            this->warehouse_state_[this->find_item_index_[j].first].items_state[this->find_item_index_[j].second].second;

        index_item_in_warehouse.push_back({this->find_item_index_[j].first, this->find_item_index_[j].second});
        if (this->item_count_ > count) {
          this->item_count_ -= count;
        } else {
          is_possible = true;
        }
        break;
      }
    }
  }
  if (!is_possible) {
    OutputHandler::Error(ErrorType::FEW_ITEM_COUNT);
    return;
  }
  for (int i = 0; i < index_item_in_warehouse.size() - 1; ++i) {
    this->warehouse_state_[index_item_in_warehouse[i].first].items_state.erase(
        this->warehouse_state_[index_item_in_warehouse[i].first].items_state.begin()
            + index_item_in_warehouse[i].second);
  }
  this->warehouse_state_[index_item_in_warehouse[index_item_in_warehouse.size()
      - 1].first].items_state[index_item_in_warehouse[index_item_in_warehouse.size() - 1].second].second -=
      this->item_count_;
  std::ofstream write_store_state_file("warehouse.txt", std::ios::trunc);
  for (int i = 0; i < this->warehouse_state_.size(); ++i) {
    if (i != 0) write_store_state_file << std::endl;
    for (int j = 0; j < this->warehouse_state_[i].items_state.size(); ++j) {
      if (j != 0) write_store_state_file << std::endl;
      write_store_state_file << this->warehouse_state_[i].warehouse.GetIdentifier() << "\t"
                             << this->warehouse_state_[i].items_state[j].first << "\t"
                             << this->warehouse_state_[i].items_state[j].second;
    }
  }
  write_store_state_file.close();
  OutputHandler::Success(SuccessType::COMPLETE_CHANGE);
}

int WarehouseController::FindWarehouseItemIndex(std::string &item_identifier) {
  int count = 0;
  for (int i = 0; i < this->warehouse_state_.size(); ++i) {
    for (int j = 0; j < this->warehouse_state_[i].items_state.size(); ++j) {
      if (this->warehouse_state_[i].items_state[j].first == item_identifier) {
        this->find_item_index_.push_back({i, j});
        count += this->warehouse_state_[i].items_state[j].second;
      }
    }
  }
  return count;
}

int WarehouseController::FindItem(std::string &identifier) {
  this->ReadFiles();
  ItemModel item(identifier, 0, 0);
  int index = 0;
  for (index = 0; index < this->all_items_.size(); ++index) {
    if (this->all_items_[index] == item) {
      return index;
    }
  }
  return -1;
}

int WarehouseController::FindWarehouse(std::string &identifier) {
  this->ReadFiles();
  WarehouseModel warehouse(std::move(identifier), 0, 0, 0);
  int index;
  for (index = 0; index < this->all_warehouses_.size(); ++index) {
    if (this->all_warehouses_[index] == warehouse) {
      return index;
    }
  }
  return -1;
}