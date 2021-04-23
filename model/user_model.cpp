//
// Created by 정현민 on 2021/03/20.
//

#include "user_model.h"

#include <utility>

UserModel::UserModel(std::string username, std::string password)
    : username_(std::move(username)),
      password_(std::move(password)),
      permission_(Permission::COMMON) {
}

UserModel::UserModel(std::string username, std::string password, Permission permission)
    : username_(std::move(username)),
      password_(std::move(password)),
      permission_(permission) {
}

UserModel::~UserModel() = default;

const std::string &UserModel::GetUsername() const {
  return username_;
}

const std::string &UserModel::GetPassword() const {
  return password_;
}

Permission UserModel::GetPermission() const {
  return permission_;
}

void UserModel::SetUsername(const std::string &username) {
  username_ = username;
}

void UserModel::SetPassword(const std::string &password) {
  password_ = password;
}

void UserModel::SetPermission(Permission permission) {
  permission_ = permission;
}

Permission UserModel::ConvertStringPermissionToEnum(const std::string &permission) {
  if (permission == "manager" || permission == "Manager") {
    return Permission::Manager;
  } else if (permission == "staff" || permission == "Staff") {
    return Permission::STAFF;
  } else if (permission == "common" || permission == "Common") {
    return Permission::COMMON;
  } else {
    return Permission();
  }
}

std::string UserModel::ConvertEnumPermissionToString(const Permission &permission) {
  if (permission == Permission::Manager) {
    return "Manager";
  } else if (permission == Permission::STAFF) {
    return "Staff";
  } else {
    return "Common";
  }
}
