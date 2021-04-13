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
  void FindUser(const UserModel& user) const;
  void SingIn(std::string username, std::string password) const;
  void SingUp(std::string username, std::string password) const;
  void SingOut();
  UserModel *getCurrentUser();

 private:
  UserModel *current_user_;
};

#endif //PROJECT_CONTROLLER_AUTH_CONTROLLER_H_
