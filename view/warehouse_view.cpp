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
  } else if (command == "receive") {
    std::cout << "receive success" << std::endl;
  } else if (command == "release") {
    std::cout << "release success" << std::endl;
  } else {
    std::cout << this->view_title_ << ": command not found " << command << std::endl;
  }
}

void WarehouseView::PrintManual() {

}
