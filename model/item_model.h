//
// Created by 정현민 on 2021/03/20.
//

#ifndef PROJECT__ITEM_H_
#define PROJECT__ITEM_H_

#include <string>

class ItemModel {
 public:
  ItemModel(std::string identifier, int volume, int weight);
  ~ItemModel();
  bool operator==(const ItemModel &item) {
    return this->identifier_ == item.identifier_;
  }
  const std::string &GetIdentifier() const;
  int GetVolume() const;
  int GetWeight() const;
  void SetVolume(int volume);
  void SetWeight(int weight);
 private:
  const std::string identifier_;
  int volume_;
  int weight_;
};

#endif //PROJECT_MODEL_ITEM_MODEL_H_
