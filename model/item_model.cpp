//
// Created by 정현민 on 2021/03/20.
//

#include "item_model.h"
ItemModel::ItemModel(std::string identifier, int volume, int weight)
    : identifier_(std::move(identifier)), volume_(volume), weight_(weight) {
}

const std::string &ItemModel::GetIdentifier() const {
  return identifier_;
}

int ItemModel::GetVolume() const {
  return volume_;
}

int ItemModel::GetWeight() const {
  return weight_;
}

void ItemModel::SetVolume(int volume) {
  volume_ = volume;
}

void ItemModel::SetWeight(int weight) {
  weight_ = weight;
}
