//
// Created by 정현민 on 2021/03/26.
//

#include "auth_controller.h"

#include <utility>

AuthController::AuthController() : current_user_(nullptr) {
  this->ReadUsers();
}

AuthController::~AuthController() = default;

UserModel AuthController::VectorToUserModel(std::vector<std::string> &user_information) {
  UserModel user(user_information[0], user_information[1], user_information[2]);
  return user;
}

void AuthController::ReadUsers() {
  // TODO txt 유저 읽어오기
  std::ifstream read_auth_file;
  read_auth_file.open("auth.txt"); //file name
  while (!read_auth_file.eof()) {
    if (read_auth_file.is_open()) {
      std::string line;
      getline(read_auth_file, line);
      std::vector<std::string> user_information = StringHandler::SplitString(line);
      UserModel user = VectorToUserModel(user_information);
      if (std::find(this->all_users_.begin(), this->all_users_.end(), user) == this->all_users_.end()) {
        this->all_users_.push_back(VectorToUserModel(user_information));
      }
    }
  }

}

void AuthController::SingIn(std::string username, std::string password) const {
  UserModel user(std::move(username), std::move(password));
  this->FindUser(user);

}

void AuthController::SingUp(std::string username, std::string password) const {
  UserModel user(std::move(username), std::move(password));
  this->FindUser(user);
}

void AuthController::SingOut() {
  this->current_user_ = nullptr;
}

UserModel *AuthController::getCurrentUser() const {
  return this->current_user_;
}

UserModel AuthController::FindUser(const UserModel user)  {
  return *std::find(this->all_users_.begin(), this->all_users_.end(), user);
}
