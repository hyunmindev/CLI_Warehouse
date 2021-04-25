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
  std::vector<std::pair<std::string, int>> items_state;
};

class WarehouseController {
 public:
  explicit WarehouseController();
  ~WarehouseController();
  void ReadWarehouse();
  void ReadStoreState();
  void ReadItem();
  void ReadFiles();
  void WriteStoreState() const;
  void WriteItem() const;
  void WriteWarehouse() const;
  int FindItem(std::string &identifier);
  int FindWarehouse(std::string &identifier);
  int Receive(std::string &identifier, int item_count);
  bool Release(std::string &identifier, int item_count);
  bool ReceiveSubPromptWeight(int weight);
  bool ReceiveSubPromptVolume(int volume);
  bool ReceiveSubPromptIdentifier(std::string &identifier);
  bool ReleaseSubPrompt(std::vector<std::string> &identifiers);
  int FindWarehouseItemIndex(std::string &item_identifier);
  void FindItemIndexClear();
  static bool CheckWarehouseIdentifier(std::string &warehouse_identifier);
  ItemModel *GetReceiveItem() const;
 private:
  std::vector<WarehouseState> warehouse_state_;
  std::vector<ItemModel> all_items_;
  std::vector<WarehouseModel> all_warehouses_;
  std::vector<std::pair<int, int>> find_item_index_;
  ItemModel *receive_item_;
  int item_count_;
};

#endif //PROJECT_CONTROLLER_WAREHOUSE_CONTROLLER_H_
