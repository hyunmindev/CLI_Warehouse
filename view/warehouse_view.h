//
// Created by 정현민 on 2021/03/26.
//

#ifndef PROJECT_VIEW_WAREHOUSE_VIEW_H_
#define PROJECT_VIEW_WAREHOUSE_VIEW_H_

#include <string>

#include "view.h"

class WarehouseView : public View {
 public:
  explicit WarehouseView(const std::string &view_title);
  void ProcessCommand(const std::string &string) override;
  void PrintManual() override;

 private:
  int size;
};

#endif //PROJECT_VIEW_WAREHOUSE_VIEW_H_
