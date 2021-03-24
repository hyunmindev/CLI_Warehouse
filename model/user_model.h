//
// Created by 정현민 on 2021/03/20.
//

#ifndef PROJECT_USER_USER_H_
#define PROJECT_USER_USER_H_

#include <string>

class UserModel {
 public:
  UserModel(std::string username, std::string password);

 private:
  std::string username_;
  std::string password_;
};

#endif //PROJECT_USER_USER_H_
