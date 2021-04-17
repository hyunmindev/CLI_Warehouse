//
// Created by 정현민 on 2021/03/26.
//

#include "auth_view.h"

AuthView::AuthView(const std::string &view_title) : View(view_title) {}
AuthView::~AuthView() = default;

void AuthView::ProcessInputs(const std::vector<std::string> &inputs) {
  std::string command = inputs[0];
  if (command == "help") {
    this->OutputHelp();
  } else if (command == "exit") {
    this->DeactivateView();
  } else if (command == "signin") {
    if (inputs.size() < 3) {
      OutputHandler::Error(ErrorType::FEW_ARGUMENT);
      return;
    } else if (inputs.size() > 3) {
      OutputHandler::Error(ErrorType::MANY_ARGUMENT);
      return;
    }
    std::string username = inputs.at(1);
    std::string password = inputs.at(2);
    std::cout << inputs.size() << std::endl;
    ProcessSignIn(username, password);
  } else if (command == "signup") {
    std::string username = inputs.at(1);
    std::string password = inputs.at(2);
    std::string confirm_password = inputs.at(3);
    ProcessSignUp(username, password, confirm_password);
  } else if (command == "change") {
    ProcessChange();
  } else {
    OutputHandler::Error(ErrorType::WRONG_COMMAND, command);
  }
}

void AuthView::ProcessSignIn(const std::string &username, const std::string &password) const {
  this->auth_controller_.SingIn(username, password);
  if (this->auth_controller_.getCurrentUser() != nullptr) {
    // TODO Handle warning, error, notice
    std::cout << "sign in failed" << std::endl;
  } else {
    // TODO Handle warning, error, notice
    std::cout << "sign in success" << std::endl;
  }
}

void AuthView::ProcessSignUp(const std::string &username,
                             const std::string &password,
                             const std::string &confirm_password) const {

}

void AuthView::ProcessChange() const {

}

void AuthView::OutputHelp() const {
  std::cout << "================ Manual ==============" << std::endl;
  std::cout << ">> signin [username] [password]" << std::endl;
  std::cout << "  : 로그인 명령어 입니다." << std::endl << std::endl;
  std::cout << "signup [username] [password] [confirm password]" << std::endl;
  std::cout << "  : 회원가입 명령어 입니다." << std::endl << std::endl;
  std::cout << "change [username] [password] [confirm password]" << std::endl;
  std::cout << "  : 권한 변경 명령어 입니다. (관리자 권한만 사용가능합니다.)" << std::endl;
  std::cout << "======================================" << std::endl;
}
