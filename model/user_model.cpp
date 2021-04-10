//
// Created by 정현민 on 2021/03/20.
//

#include "user_model.h"

#include <utility>
UserModel::UserModel(std::string username, std::string password, std::string authority = "일반")
    : username_(std::move(username)), password_(std::move(password)) {
  this->authority_ = (this->CheckAdministratorAuthority(authority) || this->CheckNormalAuthority(authority)
      || this->CheckNormalAuthority(authority))? authority : "일반";
}

UserModel::~UserModel() = default;

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

const std::string &UserModel::GetAuthority() const {
  return authority_;
}

bool UserModel::CheckAdministratorAuthority(std::string authority) {
  return authority == "관리자";
}

bool UserModel::CheckEmployeeAuthority(std::string authority) {
  return authority == "직원";
}

bool UserModel::CheckNormalAuthority(std::string authority) {
  return authority == "일반"
}