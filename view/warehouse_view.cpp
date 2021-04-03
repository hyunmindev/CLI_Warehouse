//
// Created by 정현민 on 2021/03/26.
//

#include "warehouse_view.h"

WarehouseView::WarehouseView(const std::string &view_title) : View(view_title) {}
WarehouseView::~WarehouseView() = default;

void WarehouseView::ProcessInputs(const std::vector<std::string> &string) {
  if (string[0] == "help") {
    this->PrintManual();
  } else if (string[0] == "exit") {
    this->DeactivateView();
  } else if (string[0] == "receive") {
    std::cout << "receive success" << std::endl;
  } else if (string[0] == "release") {
    std::cout << "release success" << std::endl;
  } else {
    std::cout << this->view_title_ << ": command not found " << string[0] << std::endl;
  }
}

void WarehouseView::PrintManual() {

}
