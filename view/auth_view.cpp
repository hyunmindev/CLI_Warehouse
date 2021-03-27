//
// Created by 정현민 on 2021/03/26.
//

#include "auth_view.h"

AuthView::AuthView(const std::string &view_title) : View(view_title) {}
AuthView::~AuthView() = default;

void AuthView::ProcessCommand(const std::string &command) {
  if (command == "help") {
    this->PrintManual();
  } else if (command == "exit") {
    this->DeactivateView();
  } else if (command == "signin") {
    std::cout << "sign in success" << std::endl;
  } else if (command == "signup") {
    std::cout << "sign up success" << std::endl;
  } else {
    std::cout << this->view_title_ << ": command not found " << command << std::endl;
  }
}

void AuthView::PrintManual() {
  std::cout << this->view_title_ << "Manual" << std::endl;
  std::cout << "signin [username] [password]" << std::endl;
  std::cout << "signup [username] [password] [confirm password]" << std::endl;
}