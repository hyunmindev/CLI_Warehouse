//
// Created by 정현민 on 2021/03/20.
//

#ifndef PROJECT_MODEL_USER_MODEL_H_
#define PROJECT_MODEL_USER_MODEL_H_

#include <string>

enum class Permission : char {
  Manager = 1,
  STAFF,
  COMMON
};

class UserModel {
 public:
  UserModel(std::string username, std::string password);
  UserModel(std::string username, std::string password, Permission permission);
  ~UserModel();
  bool operator==(const UserModel &user) const {
    return this->username_ == user.username_ && this->password_ == user.password_;
  }
  [[nodiscard]] const std::string &GetUsername() const;
  [[nodiscard]] const std::string &GetPassword() const;
  [[nodiscard]] Permission GetPermission() const;
  void SetUsername(const std::string &username);
  void SetPassword(const std::string &password);
  void SetPermission(Permission permission);
  static Permission ConvertStringPermissionToEnum(const std::string &permission);
  static std::string ConvertEnumPermissionToString(const Permission &permission);

 private:
  std::string username_;
  std::string password_;
  Permission permission_;
};

#endif //PROJECT_MODEL_USER_MODEL_H_
