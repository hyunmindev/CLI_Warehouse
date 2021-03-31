//
// Created by 정현민 on 2021/03/26.
//

#include "auth_controller.h"

AuthController::AuthController() : current_user_(nullptr) {
  this->ReadUsers();
}

AuthController::~AuthController() = default;

void AuthController::ReadUsers() {
  // TODO txt 유저 읽어오기
  UserModel User("test", "test");
  this->users_.push_back(User);
}

void AuthController::SingIn(const std::string &username, const std::string &password) {
  UserModel user(username, password);
  if (std::find(this->users_.begin(), this->users_.end(), user) != this->users_.end()) {
    this->current_user_ = &user;
  }
}

UserModel *AuthController::getCurrentUser() {
  return this->current_user_;
}
