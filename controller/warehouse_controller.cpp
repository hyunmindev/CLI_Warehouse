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
  read_item_file.open("./item.txt", std::ios::in); //file name
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
    std::ofstream new_file("./item.txt");
    new_file.close();
  }
  read_item_file.close();
}

void WarehouseController::ReadStoreState() {
  this->warehouse_state_.clear();
  std::ifstream read_store_state_file;
  read_store_state_file.open("./store_state.txt", std::ios::in); //file name
  if (read_store_state_file.is_open()) {
    while (!read_store_state_file.eof()) {
      std::string line = "\n";
      getline(read_store_state_file, line, '\n');
      if (line.empty()) continue;
      std::vector<std::string> store_state_information = StringHandler::SplitString(line, '\t');
      WarehouseModel find_warehouse(store_state_information[0], 0, 0, 0);
      WarehouseModel warehouse = *std::find(this->all_warehouses_.begin(), this->all_warehouses_.end(),
                                            find_warehouse);
      int index = 0;
      for (index = 0; index < this->all_items_.size(); ++index) {
        if (store_state_information[1] == this->all_items_[index].GetIdentifier()) {
          break;
        }
      }
      bool insert = false;
      for (int i = 0; i < this->warehouse_state_.size(); ++i) {
        if (this->warehouse_state_[i].warehouse == warehouse) {
          this->warehouse_state_[i].items_state.emplace_back(this->all_items_[index].GetIdentifier(),
                                                           StringHandler::StringToInteger(
                                                               store_state_information[2]));
          insert = true;
          break;
        }
      }
      if (!insert) {
        std::vector<std::pair<std::string, int>> item;
        item.push_back({this->all_items_[index].GetIdentifier(),
                        StringHandler::StringToInteger(
                            store_state_information[2])});
        this->warehouse_state_.push_back({warehouse, item});
      }
    }
  } else {
    std::ofstream new_file("./store_state.txt");
    new_file.close();
  }
  read_store_state_file.close();
}

void WarehouseController::ReadWarehouse() {
  std::ifstream read_warehouse_file;
  read_warehouse_file.open("./warehouse.txt", std::ios::in); //file name
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
    std::ofstream new_file("./warehouse.txt");
    new_file.close();
  }
  read_warehouse_file.close();
}

void WarehouseController::WriteStoreState() const {
  std::ofstream write_store_state_file("./store_state.txt", std::ios::trunc);
  for (int i = 0; i < this->warehouse_state_.size(); ++i) {
    if (i != 0 && !warehouse_state_[i].items_state.empty()) write_store_state_file << std::endl;
    for (int j = 0; j < this->warehouse_state_[i].items_state.size(); ++j) {
      if (j != 0) write_store_state_file << std::endl;
      write_store_state_file << this->warehouse_state_[i].warehouse.GetIdentifier() << "\t"
                             << this->warehouse_state_[i].items_state[j].first << "\t"
                             << this->warehouse_state_[i].items_state[j].second;
    }
  }
  write_store_state_file.close();
}

void WarehouseController::WriteItem() const {
  std::ofstream write_item_file("./item.txt", std::ios::trunc);
  for (int i = 0; i < this->all_items_.size(); ++i) {
    if (i != 0) write_item_file << std::endl;
    write_item_file << this->all_items_[i].GetIdentifier() << "\t"
                    << this->all_items_[i].GetVolume() << "\t"
                    << this->all_items_[i].GetWeight();
  }
  write_item_file.close();
}

void WarehouseController::WriteWarehouse() const {
  std::ofstream write_warehouse_file("./warehouse.txt", std::ios::trunc);
  for (int i = 0; i < this->all_warehouses_.size(); ++i) {
    if (i != 0) write_warehouse_file << std::endl;
    write_warehouse_file << this->all_warehouses_[i].GetIdentifier() << "\t"
                         << this->all_warehouses_[i].GetAcceptableVolume() << "\t"
                         << this->all_warehouses_[i].GetAllowMinWeight() << "\t"
                         << this->all_warehouses_[i].GetAllowMaxWeight();
  }
  write_warehouse_file.close();
}

void WarehouseController::ReadFiles() {
  this->ReadItem();
  this->ReadWarehouse();
  this->ReadStoreState();
}

int WarehouseController::Receive(std::string &identifier, int item_count) {
  this->ReadFiles();
  int item_index = this->FindItem(identifier);
  this->item_count_ = item_count;
  this->receive_item_ = new ItemModel(identifier, 0, 0);
  if (item_index == -1) {
    return 1;       //  goto 무게부피 입력 부프롬포
  } else {
    ItemModel item = this->all_items_[item_index];
    OutputHandler::Warning(WarningType::EXISTING_ITEM);
    std::cout << "\t개별무게: " << item.GetWeight()
              << "\t개별부피: " << item.GetVolume() << std::endl;
    this->receive_item_->SetVolume(item.GetVolume());
    this->receive_item_->SetWeight(item.GetWeight());
    this->FindItemIndexClear();
    this->FindWarehouseItemIndex(identifier);
    for (int i = 0; i < this->find_item_index_.size(); ++i) {
      std::cout << "\t창고: " << this->warehouse_state_[this->find_item_index_[i].first].warehouse.GetIdentifier()
                << "\t개수"
                << this->warehouse_state_[this->find_item_index_[i].first].items_state[this->find_item_index_[i].second].second
                << std::endl;
    }
    return 3; //  goto identifier 부프롬포트
  }
}

bool WarehouseController::ReceiveSubPromptWeight(int weight) {
  this->receive_item_->SetWeight(weight);
  return true;
}

bool WarehouseController::ReceiveSubPromptVolume(int volume) {
  this->receive_item_->SetVolume(volume);
  return true;
}

bool WarehouseController::ReceiveSubPromptIdentifier(std::string &identifier) {
  this->ReadFiles();
  if (!WarehouseController::CheckWarehouseIdentifier(identifier)) {
    OutputHandler::Error(ErrorType::WRONG_ARGUMENT);
    return false;
  }
  std::string item_identifier = this->receive_item_->GetIdentifier();
  if (this->FindItem(item_identifier) == -1) {
    this->all_items_.push_back(*this->receive_item_);
  }
  int warehouse_index = this->FindWarehouse(identifier);
  if (warehouse_index == -1) {
    OutputHandler::Error(ErrorType::NO_EXISTING_WAREHOUSE, identifier);
    return false;
  }
  int acceptable_volume = this->GetStateAcceptableVolume(identifier);
  std::cout << acceptable_volume << std::endl;
  if (acceptable_volume < this->receive_item_->GetVolume() * this->item_count_) {
    OutputHandler::Error(ErrorType::FEW_ACCEPTED_VOLUME);
    return false;
  }
  if (!this->all_warehouses_[warehouse_index].CheckWeightRange(this->receive_item_->GetWeight())) {
    OutputHandler::Error(ErrorType::UNACCEPTABLE_WEIGHT);
    std::cout << identifier << ":"
              << this->all_warehouses_[warehouse_index].GetAllowMinWeight() << "KG ~ "
              << this->all_warehouses_[warehouse_index].GetAllowMaxWeight()
              << "Kg 범위의 물품을 수용할 수 있습니다." << std::endl;
    return false;
  }
  WarehouseModel warehouse(identifier, 0, 0, 0);
  int is_receive = false;
  for (int i = 0; i < this->warehouse_state_.size(); ++i) {
    if (this->warehouse_state_[i].warehouse == warehouse) {
      for (int j = 0; j < this->warehouse_state_[i].items_state.size(); ++j) {
        if (this->warehouse_state_[i].items_state[j].first
            == this->receive_item_->GetIdentifier()) {
          this->warehouse_state_[i].items_state[j].second += this->item_count_;
          is_receive = true;
        }
      }
      if (!is_receive) {
        this->warehouse_state_[i].items_state.emplace_back(this->receive_item_->GetIdentifier(),
                                                         this->item_count_);
        is_receive = true;
      }
      break;
    }
  }
  if (!is_receive) {
    std::vector<std::pair<std::string, int>> item = {{this->receive_item_->GetIdentifier(), this->item_count_}};
    this->warehouse_state_.push_back({this->all_warehouses_[warehouse_index], item});
  }
  this->WriteItem();
  this->WriteWarehouse();
  this->WriteStoreState();
  this->ReadFiles();
  OutputHandler::Success(SuccessType::COMPLETE_RECEIVE, identifier, StringHandler::IntegerToString(this->item_count_));
  return true;
}

bool WarehouseController::Release(std::string &identifier, int item_count) {
  this->ReadFiles();
  int item_index = this->FindItem(identifier);
  if (item_index == -1) {
    OutputHandler::Error(ErrorType::NO_EXISTING_ITEM);
    return false;
  }
  this->receive_item_ =
      new ItemModel(identifier, this->all_items_[item_index].GetVolume(), this->all_items_[item_index].GetWeight());
  int current_item_count = FindWarehouseItemIndex(identifier);
  if (current_item_count < item_count) OutputHandler::Error(ErrorType::FEW_ITEM_COUNT);
  for (int i = 0; i < this->find_item_index_.size(); ++i) {
    std::cout << "창고: " << this->warehouse_state_[this->find_item_index_[i].first].warehouse.GetIdentifier()
              << "\t개수: "
              << this->warehouse_state_[this->find_item_index_[i].first].items_state[this->find_item_index_[i].second].second
              << std::endl;
  }
  if (current_item_count < item_count) {
    this->FindItemIndexClear();
    return false;
  }
  this->item_count_ = item_count;
  return true; //goto 부프롬프트
}

bool WarehouseController::ReleaseSubPrompt(std::vector<std::string> &identifiers) {
  this->ReadFiles();
  for (int i = 0; i < identifiers.size(); ++i) {
    if (!WarehouseController::CheckWarehouseIdentifier(identifiers[i])) {
      OutputHandler::Error(ErrorType::WRONG_ARGUMENT);
      return false;
    }
  }
  std::vector<std::pair<int, int>> index_item_in_warehouse;
  std::vector<std::string> error_warehouse;
  bool is_possible = false;
  for (int i = 0; i < identifiers.size(); ++i) {
    if (is_possible) break;
    bool has_warehouse_item = false;
    WarehouseModel warehouse(identifiers[i], 0, 0, 0);
    for (int j = 0; j < this->find_item_index_.size(); ++j) {
      if (warehouse_state_[this->find_item_index_[j].first].warehouse == warehouse) {
        int count =
            this->warehouse_state_[this->find_item_index_[j].first].items_state[this->find_item_index_[j].second].second;
        index_item_in_warehouse.emplace_back(this->find_item_index_[j].first, this->find_item_index_[j].second);
        if (this->item_count_ > count) {
          this->item_count_ -= count;
        } else {
          is_possible = true;
        }
        has_warehouse_item = true;
        break;
      }
    }
    if (!has_warehouse_item) error_warehouse.push_back(identifiers[i]);
  }
  if (!error_warehouse.empty()) {
    for (int i = 0; i < error_warehouse.size(); ++i) {
      OutputHandler::Error(ErrorType::WRONG_WAREHOUSE, error_warehouse[i]);
    }
    return false;
  }
  if (!is_possible) {
    OutputHandler::Error(ErrorType::FEW_ITEM_COUNT);
    return false;
  }
  for (int i = 0; i < index_item_in_warehouse.size(); ++i) {
    int item_index = this->FindItem(this->warehouse_state_[index_item_in_warehouse[index_item_in_warehouse.size()
        - 1].first].items_state[index_item_in_warehouse[i].second].first);
    if (i == index_item_in_warehouse.size() - 1
        && this->warehouse_state_[index_item_in_warehouse[i].first].items_state[index_item_in_warehouse[i].second].second
            != this->item_count_) {
      this->warehouse_state_[index_item_in_warehouse[index_item_in_warehouse.size()
          - 1].first].items_state[index_item_in_warehouse[i].second].second -=
          this->item_count_;
      OutputHandler::Success(SuccessType::COMPLETE_RELEASE,
                             this->warehouse_state_[index_item_in_warehouse[i].first].warehouse.GetIdentifier(),
                             StringHandler::IntegerToString(this->item_count_));
      break;
    }
    OutputHandler::Success(SuccessType::COMPLETE_RELEASE,
                           this->warehouse_state_[index_item_in_warehouse[i].first].warehouse.GetIdentifier(),
                           StringHandler::IntegerToString(this->warehouse_state_[index_item_in_warehouse[i].first]
                                                              .items_state[index_item_in_warehouse[i].second].second));

    this->warehouse_state_[index_item_in_warehouse[i].first].items_state.erase(
        this->warehouse_state_[index_item_in_warehouse[i].first].items_state.begin()
            + index_item_in_warehouse[i].second);
  }
  this->WriteStoreState();
  this->FindItemIndexClear();
  return true;
}

void WarehouseController::FindItemIndexClear() {
  this->find_item_index_.clear();
}

int WarehouseController::FindWarehouseState(const std::string &warehouse_identifier) const {
  for (int i = 0; i < this->warehouse_state_.size(); ++i) {
    if (warehouse_state_[i].warehouse.GetIdentifier() == warehouse_identifier) return i;
  }
  return -1;
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

int WarehouseController::FindItem(const std::string &identifier) const {
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
  WarehouseModel warehouse(identifier, 0, 0, 0);
  int index;
  for (index = 0; index < this->all_warehouses_.size(); ++index) {
    if (this->all_warehouses_[index] == warehouse) {
      return index;
    }
  }
  return -1;
}

bool WarehouseController::CheckWarehouseIdentifier(std::string &warehouse_identifier) {
  if (warehouse_identifier.size() >= 4 && warehouse_identifier.size() <= 10 && std::isupper(warehouse_identifier[0])
      && std::isupper(warehouse_identifier[1])) {
    for (int i = 2; i < warehouse_identifier.size(); ++i) {
      if (!std::isdigit(warehouse_identifier[i])) return false;
    }
    return true;
  }
  return false;
}

ItemModel *WarehouseController::GetReceiveItem() const {
  return this->receive_item_;
}

bool WarehouseController::GetItemInfo(std::string &item_id) const {
  int index;
  for (index = 0; index < this->all_items_.size(); ++index) {
    if (this->all_items_[index].GetIdentifier() == item_id) {
      std::cout << "물품: " << item_id << "\t무게: " << all_items_[index].GetWeight() << "\t부피: "
                << all_items_[index].GetVolume() << std::endl;
      return true;
    }
  }
  return false;
}

int WarehouseController::GetStateAcceptableVolume(const std::string &warehouse_identifier) const {
  int index = this->FindWarehouseState(warehouse_identifier);
  int volume = this->warehouse_state_[index].warehouse.GetAcceptableVolume();
//  std::cout<<volume<<std::endl;
  if (index == -1) return volume;
  for (int i = 0; i < this->warehouse_state_[index].items_state.size(); ++i) {
    volume -= this->all_items_[this->FindItem(this->warehouse_state_[index].items_state[i].first)].GetVolume()
        * this->warehouse_state_[index].items_state[i].second;
//    std::cout<<this->all_items_[this->FindItem(this->warehouse_state_[index].items_state[i].first)].GetIdentifier()<<std::endl;
  }
//  std::cout<<volume<<std::endl;
  return volume;
}

std::vector<WarehouseModel> WarehouseController::GetAllWarehouses() const {
  return this->all_warehouses_;
}