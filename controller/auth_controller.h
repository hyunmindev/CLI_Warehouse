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
#include "../handler/output_handler.h"

class AuthController {
 public:
  explicit AuthController();
  ~AuthController();
  void ReadUsers();
  UserModel FindUser(const UserModel &user) const;
  int FindUsernameIndex(const UserModel& user) const;
  void SingIn(std::string &username, std::string &password);
  void SingUp(std::string &username, std::string &password, std::string &confirm_password);
  void SingOut();
  void Change(std::string &username, Permission &permission);
  [[nodiscard]] UserModel *getCurrentUser() const;
  const std::vector<UserModel> &getAllUsers() const;
  static bool CheckUsername(const std::string &username);
  static bool CheckPassword(const std::string &username, const std::string &password);

 private:
  std::vector<UserModel> all_users_;
  UserModel *current_user_;
};

#endif //PROJECT_CONTROLLER_AUTH_CONTROLLER_H_
