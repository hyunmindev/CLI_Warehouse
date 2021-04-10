//
// Created by 정현민 on 2021/03/20.
//

#include "user_model.h"

#include <utility>
UserModel::UserModel(std::string username, std::string password)
    : username_(std::move(username)), password_(std::move(password)) {
}

std::string UserModel::GetUsername() {
  return this->username_;
}

std::string UserModel::GetPassword() {
  return this->password_;
}

void UserModel::SetUsername(std::string username) {
  this->username_ = username;
}

void UserModel::SetPassword(std::string password) {
  this->password_ = password;
}