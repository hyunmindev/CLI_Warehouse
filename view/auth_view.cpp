//
// Created by 정현민 on 2021/03/26.
//

#include "auth_view.h"

AuthView::AuthView(const std::string &view_title) : View(view_title) {
}
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
  } else if (command == "print") {
    if (!View::CheckArguments(arguments, 1, 3)) {
      return;
    }
    std::string mode_type = arguments.at(0);
    std::string argument = "";
    if (arguments.size() == 2) {
      argument = arguments.at(1);
    }
    if (mode_type == "auth") {
      this->ProcessPrint(argument);
    }
  } else if (command == "signin") {
    if (!View::CheckArguments(arguments, 2, 3)) {
      return;
    }
    std::string username = arguments.at(0);
    std::string password = arguments.at(1);
    this->ProcessSignIn(username, password);
  } else if (command == "signup") {
    if (!
        View::CheckArguments(arguments,
                             3, 4)) {
      return;
    }
    std::string username = arguments.at(0);
    std::string password = arguments.at(1);
    std::string confirm_password = arguments.at(2);
    this->
        ProcessSignUp(username, password, confirm_password
    );
  } else if (command == "signout") {
    if (!
        View::CheckArguments(arguments,
                             0, 1)) {
      return;
    }
    this->
        ProcessSignOut();
  } else if (command == "change") {
    if (!
        View::CheckArguments(arguments,
                             2, 3)) {
      return;
    }
    std::string username = arguments.at(0);
    std::string authority_string = arguments.at(1);
    this->
        ProcessChange(username, UserModel::ConvertStringAuthorityToEnum(authority_string)
    );
  } else {
    OutputHandler::Error(ErrorType::WRONG_COMMAND, command
    );
  }
}

void AuthView::ProcessSignIn(std::string &username, std::string &password) {
  if (!View::CheckUsername(username)) return;
  if (!View::CheckPassword(username, password)) return;
  if (this->auth_controller_.SingIn(username, password) == false) {
    OutputHandler::Error(ErrorType::NO_USER);
  } else {
    OutputHandler::Success(SuccessType::COMPLETE_SIGN_IN);
  }
}

void AuthView::ProcessSignUp(std::string &username,
                             std::string &password,
                             const std::string &confirm_password) {
  if (!View::CheckUsername(username)) return;
  if (!View::CheckPassword(username, password)) return;
  if (password != confirm_password) {
    OutputHandler::Error(ErrorType::NOT_MATCH_PASSWORD_CONFIRM_PASSWORD);
  } else {
    if (this->auth_controller_.SingUp(username, password)) {
      OutputHandler::Success(SuccessType::COMPLETE_SIGNUP);
    } else {
      OutputHandler::Error(ErrorType::IS_HAS_EQUAL_USERNAME);
    }
  }
}

void AuthView::ProcessSignOut() {
  if (this->auth_controller_.getCurrentUser() == nullptr) {
    OutputHandler::Error(ErrorType::NOT_SIGNED_IN);
  } else {
    this->auth_controller_.SingOut();
    OutputHandler::Success(SuccessType::COMPLETE_SIGN_OUT);
  }
}

void AuthView::ProcessChange(std::string &username, Authority authority) {
  if (!View::CheckUsername(username)) return;
  else if (authority == Authority()) {
    OutputHandler::Error(ErrorType::WRONG_ARGUMENT);
    return;
  } else if (this->auth_controller_.getCurrentUser() == nullptr) {
    OutputHandler::Error(ErrorType::NOT_SIGNED_IN);
    return;
  } else if (this->auth_controller_.getCurrentUser()->GetAuthority() == Authority::Manager) {
    if (authority == Authority::Manager) {
      OutputHandler::Error(ErrorType::CANNOT_CHANGED_BY_MANAGER);
      return;
    }
    if (this->auth_controller_.Change(username, authority)) {
      OutputHandler::Success(SuccessType::COMPLETE_CHANGE);
    } else {
      OutputHandler::Error(ErrorType::IS_NOT_HAS_EQUAL_USERNAME);
    }
  } else {
    OutputHandler::Error(ErrorType::LACK_OF_AUTHORITY);
  }
}

void AuthView::ProcessPrint(const std::string &argument) const {
  if (this->auth_controller_.getCurrentUser() == nullptr) {
    OutputHandler::Error(ErrorType::NOT_SIGNED_IN);
    return;
  }
  Authority current_authority = this->auth_controller_.getCurrentUser()->GetAuthority();
  std::cout << "=================== Print Auth ===================" << std::endl;
  if (argument == "") {
    if (current_authority == Authority::Manager) {
      std::vector<UserModel> users = this->auth_controller_.getAllUsers();
      for (int i = 0; i < users.size(); ++i) {
        std::cout << "[Username: " << users[i].GetUsername() << "]\t" << "[Password: " << users[i].GetPassword()
                  << "]\t"
                  << "[Authority: " << UserModel::ConvertEnumAuthorityToString(users[i].GetAuthority()) << "]"
                  << std::endl;
      }
    } else {
      std::cout << "[Username: " << this->auth_controller_.getCurrentUser()->GetUsername() << "]\t"
                << "[Password: " << this->auth_controller_.getCurrentUser()->GetPassword() << "]\t"
                << "[Authority: "
                << UserModel::ConvertEnumAuthorityToString(this->auth_controller_.getCurrentUser()->GetAuthority())
                << "]" << std::endl;
    }
  } else {
    if (current_authority == Authority::Manager) {
      UserModel user(argument, "");
      int find_index = this->auth_controller_.FindUsernameIndex(user);
      if(find_index==-1){
        OutputHandler::Error(ErrorType::IS_NOT_HAS_EQUAL_USERNAME);
        return;
      }
      user = this->auth_controller_.getAllUsers()[find_index];
      std::cout << "[Username: " << user.GetUsername() << "]\t" << "[Password: " << user.GetPassword() << "]\t"
                << "[Authority: " << UserModel::ConvertEnumAuthorityToString(user.GetAuthority()) << "]" << std::endl;
    } else {
      OutputHandler::Error(ErrorType::LACK_OF_AUTHORITY);
    }
  }
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