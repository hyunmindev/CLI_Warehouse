//
// Created by 정현민 on 2021/03/25.
//

#ifndef PROJECT_CONTROLLER_WAREHOUSE_CONTROLLER_H_
#define PROJECT_CONTROLLER_WAREHOUSE_CONTROLLER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "../handler/output_handler.h"
#include "../handler/string_handler.h"
#include "../model/item_model.h"
#include "../model/warehouse_model.h"

struct WarehouseState {
  WarehouseModel warehouse;
  std::vector<std::pair<ItemModel, int>> items_state;
};

class WarehouseController {
 public:
  explicit WarehouseController();
  ~WarehouseController();
  void ReadWarehouse();
  void ReadStoreState(const std::string &identifier);
  void ReadItem();
  void ReadFiles();
  int FindItem(std::string &identifier);
  int FindWarehouse(std::string &identifier);
  bool Receive(std::string& item_id, std::string& warehouse_id, int count);
  bool Release(std::string &identifier, int item_count);
  bool Move(std::string& item_id, int count);
  std::vector<std::pair<int, int>> FindWarehouseItemIndex(ItemModel &item);
 private:
  std::vector<WarehouseState> warehouse_state_;
  std::vector<ItemModel> all_items_;
  std::vector<WarehouseModel> all_warehouses_;
};

#endif //PROJECT_CONTROLLER_WAREHOUSE_CONTROLLER_H_
