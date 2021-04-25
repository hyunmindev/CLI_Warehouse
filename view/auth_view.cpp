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
    std::string permission_string = arguments.at(1);
    this->
        ProcessChange(username, UserModel::ConvertStringPermissionToEnum(permission_string)
    );
  } else {
    OutputHandler::Error(ErrorType::WRONG_COMMAND, command
    );
  }
}

void AuthView::ProcessSignIn(std::string &username, std::string &password) {
  this->auth_controller_.SingIn(username, password);
  if (this->auth_controller_.getCurrentUser() != nullptr) {
    this->is_signed_ = true;
    if (this->auth_controller_.getCurrentUser()->GetPermission() != Permission::COMMON) {
      this->possible_permission_ = true;
    }
  }
}

void AuthView::ProcessSignUp(std::string &username,
                             std::string &password,
                             std::string &confirm_password) {
  this->auth_controller_.SingUp(username, password, confirm_password);
}

void AuthView::ProcessSignOut() {
  this->auth_controller_.SingOut();
  this->is_signed_ = false;
}

void AuthView::ProcessChange(std::string &username, Permission permission) {
  this->auth_controller_.Change(username, permission);
}

void AuthView::ProcessPrint(const std::string &argument) const {
  if (this->auth_controller_.getCurrentUser() == nullptr) {
    OutputHandler::Error(ErrorType::NOT_SIGNED_IN);
    return;
  }
  Permission current_permission = this->auth_controller_.getCurrentUser()->GetPermission();
  std::cout << "=================== Print Auth ===================" << std::endl;
  if (argument == "") {
    if (current_permission == Permission::Manager) {
      std::vector<UserModel> users = this->auth_controller_.getAllUsers();
      for (int i = 0; i < users.size(); ++i) {
        std::cout << "[Username: " << users[i].GetUsername() << "]\t" << "[Password: " << users[i].GetPassword()
                  << "]\t"
                  << "[Permission: " << UserModel::ConvertEnumPermissionToString(users[i].GetPermission()) << "]"
                  << std::endl;
      }
    } else {
      std::cout << "[Username: " << this->auth_controller_.getCurrentUser()->GetUsername() << "]\t"
                << "[Password: " << this->auth_controller_.getCurrentUser()->GetPassword() << "]\t"
                << "[Permission: "
                << UserModel::ConvertEnumPermissionToString(this->auth_controller_.getCurrentUser()->GetPermission())
                << "]" << std::endl;
    }
  } else {
    if (current_permission == Permission::Manager) {
      UserModel user(argument, "");
      int find_index = this->auth_controller_.FindUsernameIndex(user);
      if (find_index == -1) {
        OutputHandler::Error(ErrorType::IS_NOT_HAS_EQUAL_USERNAME);
        return;
      }
      user = this->auth_controller_.getAllUsers()[find_index];
      std::cout << "[Username: " << user.GetUsername() << "]\t" << "[Password: " << user.GetPassword() << "]\t"
                << "[Permission: " << UserModel::ConvertEnumPermissionToString(user.GetPermission()) << "]"
                << std::endl;
    } else {
      OutputHandler::Error(ErrorType::PERMISSION_DENIED);
    }
  }
}

void AuthView::OutputHelp() const {
  std::cout << "================ Manual ==============" << std::endl;
  std::cout << "signin [username] [password]" << std::endl;
  std::cout << "  : 로그인 명령어 입니다." << std::endl << std::endl;
  std::cout << "signup [username] [password] [confirm password]" << std::endl;
  std::cout << "  : 회원가입 명령어 입니다." << std::endl << std::endl;
  std::cout << "change [username] [password] [confirm password]" << std::endl;
  std::cout << "  : 권한 변경 명령어 입니다. (관리자 권한만 사용가능합니다.)" << std::endl;
  std::cout << "exit" << std::endl;
  std::cout << "  : 모드 선택모드로 돌아가는 명령어 입니다." << std::endl;
  std::cout << "======================================" << std::endl;
}

bool AuthView::GetIsSinged() const {
  return this->is_signed_;
}

bool AuthView::GetPossiblePermission() const {
  return this->possible_permission_;
}