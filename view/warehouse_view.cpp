//
// Created by 정현민 on 2021/03/26.
//

#include "warehouse_view.h"

WarehouseView::WarehouseView(const std::string &view_title) : View(view_title) {}
WarehouseView::~WarehouseView() = default;

void WarehouseView::ProcessInputs(const std::vector<std::string> &inputs) {
  if (inputs.empty()) {
    OutputHandler::Error(ErrorType::NO_COMMAND);
    return;
  }
  const std::string command = inputs.at(0);
  const std::vector<std::string> arguments{inputs.begin() + 1, inputs.end()};
  if (command == "help") {
    this->OutputHelp();
  } else if (command == "exit") {
    this->DeactivateView();
  } else if (command == "receive") { // 입고
    if (!View::CheckArguments(arguments, 2, 3)) {
      return;
    }
    std::string item_id = arguments.at(0);
    std::string count_string = arguments.at(1);
    this->ProcessReceive(item_id, std::stoi(count_string));
  } else if (command == "release") { // 출고
    if (!View::CheckArguments(arguments, 2, 3)) {
      return;
    }
    std::string item_id = arguments.at(0);
    std::string count_string = arguments.at(1);
    this->ProcessRelease(item_id, std::stoi(count_string));
  } else if (command == "move") {
    if (!View::CheckArguments(arguments, 2, 3)) {
      return;
    }
    std::string item_id = arguments.at(0);
    std::string count_string = arguments.at(1);
    this->ProcessMove(item_id, std::stoi(count_string));
  } else {
    OutputHandler::Error(ErrorType::WRONG_COMMAND, command);
  }
}

void WarehouseView::ProcessReceive(const std::string& item_id, int count) {

}

void WarehouseView::ProcessRelease(const std::string &item_id, int count) {

}

void WarehouseView::ProcessMove(const std::string& item_id, int count) {

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
