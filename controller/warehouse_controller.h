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

struct WarehouseState{
  WarehouseModel warehouse;
  std::vector<std::pair<ItemModel,int>> items_state;
};

class WarehouseController {
 public:
  explicit WarehouseController();
  ~WarehouseController();
  void ReadWarehouse();
  void Receive();
 private:
  std::vector<WarehouseState> warehouse_state_;
};

#endif //PROJECT_CONTROLLER_WAREHOUSE_CONTROLLER_H_
