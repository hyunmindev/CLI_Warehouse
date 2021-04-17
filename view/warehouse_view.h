//
// Created by 정현민 on 2021/03/26.
//

#ifndef PROJECT_VIEW_WAREHOUSE_VIEW_H_
#define PROJECT_VIEW_WAREHOUSE_VIEW_H_

#include <string>

#include "../controller/warehouse_controller.h"
#include "view.h"

class WarehouseView : public View {
 public:
  explicit WarehouseView(const std::string &view_title);
  ~WarehouseView();
  void ProcessInputs(const std::vector<std::string> &inputs) override;
  void ProcessReceive() const; // 입고 명령어 처리
  void ProcessRelease() const; // 출고 명령어 처리
  void ProcessMove() const; // 이동 명령어 처리
  void ProcessPrint() const; // 출력 명령어 처리

  void OutputHelp() const override;

 private:
  WarehouseController warehouse_controller_;
};

#endif //PROJECT_VIEW_WAREHOUSE_VIEW_H_
