//
// Created by 정현민 on 2021/03/26.
//

#ifndef PROJECT_CONTROLLER_AUTH_CONTROLLER_H_
#define PROJECT_CONTROLLER_AUTH_CONTROLLER_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

class AuthController {
 public:
  explicit AuthController();
  ~AuthController();
  void SingInEvent();
  void UpdateUserModel();
  void SetUserInformation();
  bool GetIsValidateUser() const;
  void SetIsValidateUser();
 private:
  bool is_validateUser;
  std::vector<std::string> userInformation;
};

#endif //PROJECT_CONTROLLER_AUTH_CONTROLLER_H_
