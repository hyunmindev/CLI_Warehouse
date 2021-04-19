//
// Created by 정현민 on 2021/03/26.
//

#include "auth_view.h"

AuthView::AuthView(const std::string &view_title) : View(view_title) {}
AuthView::~AuthView() = default;

void AuthView::ProcessInputs(const std::vector<std::string> &inputs) {
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
  } else if (command == "signin") {
    if (!View::CheckArguments(arguments, 2, 3)) {
      return;
    }
    std::string username = arguments.at(0);
    std::string password = arguments.at(1);
    this->ProcessSignIn(username, password);
  } else if (command == "signup") {
    if (!View::CheckArguments(arguments, 3, 4)) {
      return;
    }
    std::string username = arguments.at(0);
    std::string password = arguments.at(1);
    std::string confirm_password = arguments.at(2);
    this->ProcessSignUp(username, password, confirm_password);
  } else if (command == "signout") {
    if (!View::CheckArguments(arguments, 0, 1)) {
      return;
    }
    this->ProcessSignOut();
  } else if (command == "change") {
    if (!View::CheckArguments(arguments, 2, 3)) {
      return;
    }
    std::string username = arguments.at(0);
    std::string authority_string = arguments.at(1);
    this->ProcessChange(username, UserModel::ConvertStringAuthorityToEnum(authority_string));
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

void AuthView::ProcessSignOut() {
  this->auth_controller_.SingOut();
}

void AuthView::ProcessChange(const std::string &username, Authority authority) {
//  this->auth_controller_.Change();
}

void AuthView::ProcessPrint() const {

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