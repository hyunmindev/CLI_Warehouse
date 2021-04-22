//
// Created by 정현민 on 2021/03/20.
//

#include "user_model.h"

#include <utility>

UserModel::UserModel(std::string username, std::string password)
    : username_(std::move(username)),
      password_(std::move(password)),
      authority_(Authority::COMMON) {
}

UserModel::UserModel(std::string username, std::string password, std::string authority)
    : username_(std::move(username)),
      password_(std::move(password)),
      authority_(UserModel::ConvertStringAuthorityToEnum(authority)) {
}

UserModel::~UserModel() = default;

const std::string &UserModel::GetUsername() const {
  return username_;
}

const std::string &UserModel::GetPassword() const {
  return password_;
}

Authority UserModel::GetAuthority() const {
  return authority_;
}

void UserModel::SetUsername(const std::string &username) {
  username_ = username;
}

void UserModel::SetPassword(const std::string &password) {
  password_ = password;
}

void UserModel::SetAuthority(Authority authority) {
  authority_ = authority;
}

Authority UserModel::ConvertStringAuthorityToEnum(const std::string &authority) {
  if (authority == "manager" || authority == "Manager") {
    return Authority::Manager;
  } else if (authority == "staff" || authority == "Staff") {
    return Authority::STAFF;
  } else if (authority == "common" || authority == "Common") {
    return Authority::COMMON;
  } else {
    return Authority();
  }
}

std::string UserModel::ConvertEnumAuthorityToString(const Authority &authority) {
  if (authority == Authority::Manager) {
    return "Manager";
  } else if (authority == Authority::STAFF) {
    return "Staff";
  } else {
    return "Common";
  }
}
