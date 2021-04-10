//
// Created by 정현민 on 2021/03/25.
//

#ifndef PROJECT_MODEL_WAREHOUSE_MODEL_H_
#define PROJECT_MODEL_WAREHOUSE_MODEL_H_

#include <string>

class WarehouseModel {
 public:
  WarehouseModel(std::string identifier, int allow_min_weight, int allow_max_weight, int acceptable_volume);
  ~WarehouseModel();
  bool operator==(WarehouseModel &warehouse) {
    return this->identifier_ == warehouse.identifier_;
  }
  int GetAllowMaxWeight() const;
  int GetAcceptableVolume() const;
  const std::string &GetIdentifier() const;
  int GetAllowMinWeight() const;
  void SetAllowMinWeight(int allow_min_weight);
  void SetAllowMaxWeight(int allow_max_weight);
  void SetAcceptableVolume(int acceptable_volume);
  bool CheckWeightRange(int weight);
 private:
  const std::string identifier_;
  int allow_min_weight_;
  int allow_max_weight_;
  int acceptable_volume;
};

#endif //PROJECT_MODEL_WAREHOUSE_MODEL_H_
