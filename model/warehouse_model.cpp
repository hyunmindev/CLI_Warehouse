//
// Created by 정현민 on 2021/03/25.
//

#include "warehouse_model.h"

WarehouseModel::WarehouseModel(std::string identifier,
                               int allow_min_weight,
                               int allow_max_weight,
                               int acceptable_volume)
    : identifier_(std::move(identifier)),
      allow_min_weight_(allow_min_weight),
      allow_max_weight_(allow_max_weight),
      acceptable_volume(acceptable_volume) {
}

WarehouseModel::~WarehouseModel() = default;

const std::string &WarehouseModel::GetIdentifier() const {
  return identifier_;
}

int WarehouseModel::GetAllowMinWeight() const {
  return allow_min_weight_;
}

int WarehouseModel::GetAllowMaxWeight() const {
  return allow_max_weight_;
}

int WarehouseModel::GetAcceptableVolume() const {
  return acceptable_volume;
}

void WarehouseModel::SetAllowMinWeight(int allow_min_weight) {
  allow_min_weight_ = allow_min_weight;
}

void WarehouseModel::SetAllowMaxWeight(int allow_max_weight) {
  allow_max_weight_ = allow_max_weight;
}

void WarehouseModel::SetAcceptableVolume(int acceptable_volume) {
  WarehouseModel::acceptable_volume = acceptable_volume;
}

bool WarehouseModel::CheckWeightRange(int weight) {
  return this->allow_min_weight_ <= weight && this->allow_max_weight_ >= weight;
}