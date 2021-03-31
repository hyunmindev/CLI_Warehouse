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

class AuthController {
 public:
  explicit AuthController();
  ~AuthController();
  void ReadUsers();
  void SingIn(const std::string &username, const std::string &password);
  UserModel *getCurrentUser();

 private:
  UserModel *current_user_;
  std::vector<UserModel> users_;
};

#endif //PROJECT_CONTROLLER_AUTH_CONTROLLER_H_
