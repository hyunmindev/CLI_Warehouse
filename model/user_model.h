//
// Created by 정현민 on 2021/03/20.
//

#ifndef PROJECT_USER_USER_H_
#define PROJECT_USER_USER_H_

#include <string>

class UserModel {
 public:
  UserModel(std::string username, std::string password);
  std::string GetUsername();
  std::string GetPassword();
  void SetUsername(std::string username);
  void SetPassword(std::string password);
  bool operator==(const UserModel &user) {
    return this->username_ == user.username_ && this->password_ == user.password_;
  }
 private:
  std::string username_;
  std::string password_;
};

#endif //PROJECT_MODEL_USER_MODE_H_
