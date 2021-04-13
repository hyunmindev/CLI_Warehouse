//
// Created by 정현민 on 2021/03/26.
//

#include "auth_controller.h"

#include <utility>

AuthController::AuthController() : current_user_(nullptr) {
  this->ReadUsers();
}

AuthController::~AuthController() = default;

void AuthController::ReadUsers() {
  // TODO txt 유저 읽어오기
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

UserModel *AuthController::getCurrentUser() {
  return this->current_user_;
}

void AuthController::FindUser(const UserModel &user) const {

}
