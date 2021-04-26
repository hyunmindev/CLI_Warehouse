//
// Created by 정현민 on 2021/03/26.
//

#include "auth_controller.h"

AuthController::AuthController() : current_user_(nullptr) {
  this->ReadUsers();
}

AuthController::~AuthController() = default;

void AuthController::ReadUsers() {
  this->all_users_.clear();
  std::ifstream read_auth_file;
  read_auth_file.open("./auth.txt", std::ios::in); //file name
  if (read_auth_file.is_open()) {
    while (!read_auth_file.eof()) {
      std::string line = "\n";
      getline(read_auth_file, line, '\n');
      if (line.empty()) continue;
      std::vector<std::string> user_information = StringHandler::SplitString(line, '\t');
      UserModel
          user(std::move(user_information[0]),
               std::move(user_information[1]),
               UserModel::ConvertStringPermissionToEnum(user_information[2]));
      this->all_users_.push_back(user);
    }
  } else {
    std::ofstream new_file("./auth.txt");
    new_file.close();
  }
  read_auth_file.close();
}

void AuthController::SingIn(std::string &username, std::string &password) {
  if (!AuthController::CheckUsername(username)
      || !AuthController::CheckPassword(username, password)) {
    OutputHandler::Error(ErrorType::WRONG_ARGUMENT);
    return;
  }
  this->ReadUsers();
  UserModel user(username, std::move(password));
  int index = this->FindUserIndex(user);
  if (index != -1) {
    this->current_user_ =
        new UserModel(this->all_users_[index].GetUsername(),
                      this->all_users_[index].GetPassword(),
                      this->all_users_[index].GetPermission());
    OutputHandler::Success(SuccessType::COMPLETE_SIGN_IN);
    return;
  }
  OutputHandler::Error(ErrorType::IS_NOT_HAS_EQUAL_USERNAME);
}

void AuthController::SingUp(std::string &username,
                            std::string &password,
                            std::string &confirm_password) {
  if (!AuthController::CheckUsername(username)
      || !AuthController::CheckPassword(username, password)) {
    OutputHandler::Error(ErrorType::WRONG_ARGUMENT);
    return;
  }
  this->ReadUsers();
  if (password != confirm_password) {
    OutputHandler::Error(ErrorType::NOT_MATCH_PASSWORD_CONFIRM_PASSWORD);
    return;
  }
  UserModel user(std::move(username), std::move(password));
  if (this->FindUsernameIndex(user) != -1) {
    OutputHandler::Error(ErrorType::IS_HAS_EQUAL_USERNAME);
    return;
  }
  std::ofstream write_auth_file("./auth.txt", std::ios::app);
  write_auth_file << "\n" << user.GetUsername() << "\t" << user.GetPassword() << "\t"
                  << UserModel::ConvertEnumPermissionToString(user.GetPermission());
  write_auth_file.close();
  OutputHandler::Success(SuccessType::COMPLETE_SIGNUP);
}

void AuthController::SingOut() {
  if (this->current_user_ == nullptr) {
    OutputHandler::Error(ErrorType::NOT_SIGNED_IN);
    return;
  }
  OutputHandler::Success(SuccessType::COMPLETE_SIGN_OUT);
  this->current_user_ = nullptr;
}

void AuthController::Change(std::string &username, Permission &permission) {
  if (!AuthController::CheckUsername(username) || permission == Permission()) {
    OutputHandler::Error(ErrorType::WRONG_ARGUMENT);
    return;
  }
  ReadUsers();
  if (this->current_user_->GetPermission() != Permission::Manager) {
    OutputHandler::Error(ErrorType::PERMISSION_DENIED);
    return;
  } else if (permission == Permission::Manager) {
    OutputHandler::Error(ErrorType::CANNOT_CHANGED_BY_MANAGER);
    return;
  }
  UserModel user(std::move(username), "");\
  int find_index = this->FindUsernameIndex(user);
  if (find_index == -1) {
    OutputHandler::Error(ErrorType::IS_NOT_HAS_EQUAL_USERNAME);
    return;
  }
  this->all_users_[find_index].SetPermission(permission);
  std::ofstream write_auth_file("./auth.txt", std::ios::trunc);
  for (int i = 0; i < this->all_users_.size(); ++i) {
    if (i != 0) write_auth_file << std::endl;
    write_auth_file << this->all_users_[i].GetUsername() << "\t"
                    << this->all_users_[i].GetPassword() << "\t"
                    << UserModel::ConvertEnumPermissionToString(this->all_users_[i].GetPermission());
  }
  OutputHandler::Success(SuccessType::COMPLETE_CHANGE);
}

UserModel *AuthController::getCurrentUser() const {
  return this->current_user_;
}

int AuthController::FindUserIndex(const UserModel &user) const {
  for (int i = 0; i < this->all_users_.size(); ++i) {
    if (this->all_users_[i] == user) {
      return i;
    }
  }
  return -1;
}

int AuthController::FindUsernameIndex(const UserModel &user) const {
  for (int i = 0; i < this->all_users_.size(); ++i) {
    if (this->all_users_[i].GetUsername() == user.GetUsername()) {
      return i;
    }
  }
  return -1;
}

const std::vector<UserModel> &AuthController::getAllUsers() const {
  return this->all_users_;
}

bool AuthController::CheckUsername(const std::string &username) {
  if (username.size() < 3) {
    return false;
  }
  return true;
}

bool AuthController::CheckPassword(const std::string &username, const std::string &password) {
  if (password.size() >= 8 && password.size() <= 16
      && password.find(username) == std::string::npos) {
    int count = 0;
    bool numberCheck = false;
    bool englishCheck = false;
    bool specialCheck = false;
    for (int i = 0; i < password.size(); ++i) {
      if (!numberCheck) numberCheck = std::isdigit(password[i]);
      if (!englishCheck) englishCheck = std::isalpha(password[i]);
      if (!specialCheck) {
        if ((password[i] >= 33 && password[i] <= 47) || (password[i] >= 58 && password[i] <= 64)
            || (password[i] >= 91 && password[i] <= 96)
            || (password[i] > 123 && password[i] <= 126)) {
          specialCheck = true;
        }
      }
    }
    if (numberCheck) count++;
    if (englishCheck) count++;
    if (specialCheck) count++;
    if (count >= 2) {
      return true;
    }
  }
  return false;
}
