//
// Created by 정현민 on 2021/03/26.
//

#include "warehouse_view.h"

WarehouseView::WarehouseView(const std::string &view_title) : View(view_title) {}
WarehouseView::~WarehouseView() = default;

void WarehouseView::ProcessCommand(const std::string &command) {
  if (command == "help") {
    this->PrintManual();
  } else if (command == "exit") {
    this->DeactivateView();
  } else if (command == "release") {

  } else if (command == "release") {

  } else {
    std::cout << this->_view_title << ": command not found " << command << std::endl;
  }
}

void WarehouseView::PrintManual() {

}
