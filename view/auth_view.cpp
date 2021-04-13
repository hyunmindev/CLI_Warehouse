//
// Created by 정현민 on 2021/03/26.
//

#include "auth_view.h"

AuthView::AuthView(const std::string &view_title) : View(view_title) {}
AuthView::~AuthView() = default;

void AuthView::ProcessInputs(const std::vector<std::string> &inputs) const {
  std::string command = inputs[0];
  if (command == "help") {
    this->OutputHelp();
  } else if (command == "exit") {
    this->DeactivateView();
  } else if (command == "signin") {
    std::string username = inputs[1];
    std::string password = inputs[2];
    if (username.empty() || password.empty()) {
      // TODO Handle warning, error, notice
      std::cout << "필요한 입력인자가 부족합니다. 도움말(help)을 확인해주세요." << std::endl;
    } else {
      this->auth_controller_.SingIn(username, password);
      if (this->auth_controller_.getCurrentUser() != nullptr) {
        // TODO Handle warning, error, notice
        std::cout << "sign in failed" << std::endl;
      } else {
        // TODO Handle warning, error, notice
        std::cout << "sign in success" << std::endl;
      }
    }
  } else if (command == "signup") {
    // TODO

  } else {
    std::cout << this->view_title_ << ": command not found " << command << std::endl;
  }
}

void AuthView::OutputHelp() {
  std::cout << this->view_title_ << " Manual" << std::endl;
  std::cout << "signin [username] [password]" << std::endl;
  std::cout << "signup [username] [password] [confirm password]" << std::endl;
}