//
// Created by 정현민 on 2021/03/26.
//

#ifndef PROJECT_CONTROLLER_AUTH_CONTROLLER_H_
#define PROJECT_CONTROLLER_AUTH_CONTROLLER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "../model/user_model.h"
#include "../handler/string_handler.h"

class AuthController {
 public:
  explicit AuthController();
  ~AuthController();
  void ReadUsers();
  UserModel FindUser(const UserModel &user) const;
  UserModel FindUserUsername(const UserModel user) const;
  bool SingIn(std::string username, std::string password);
  bool SingUp(std::string username, std::string password);
  void SingOut();
  [[nodiscard]] UserModel *getCurrentUser() const;
  UserModel VectorToUserModel(std::vector<std::string> &user_information);

 private:
  std::vector<UserModel> all_users_;
  UserModel *current_user_;
};

#endif //PROJECT_CONTROLLER_AUTH_CONTROLLER_H_
