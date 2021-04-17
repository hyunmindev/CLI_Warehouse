//
// Created by 정현민 on 2021/03/26.
//

#include "warehouse_view.h"

WarehouseView::WarehouseView(const std::string &view_title) : View(view_title) {}
WarehouseView::~WarehouseView() = default;

void WarehouseView::ProcessInputs(const std::vector<std::string> &inputs) {
  std::string command = inputs[0];
  if (command == "help") {
    this->OutputHelp();
  } else if (command == "exit") {
    this->DeactivateView();
  } else if (command == "receive") {
    std::cout << "receive success" << std::endl;
  } else if (command == "release") {
    std::cout << "release success" << std::endl;
  } else if (command == "move") {
    std::cout << "move success" << std::endl;
  } else {
    OutputHandler::Error(ErrorType::WRONG_COMMAND, command);
  }
}

void WarehouseView::OutputHelp() const {
  std::cout << "================ Manual ==============" << std::endl;
  std::cout << ">> signin [username] [password]" << std::endl;
  std::cout << "로그인 명령어 입니다." << std::endl << std::endl;
  std::cout << "signup [username] [password] [confirm password]" << std::endl;
  std::cout << "회원가입 명령어 입니다." << std::endl << std::endl;
  std::cout << "change [username] [password] [confirm password]" << std::endl;
  std::cout << "권한 변경 명령어 입니다. (관리자 권한만 사용가능합니다.)" << std::endl;
  std::cout << "======================================" << std::endl;
}
