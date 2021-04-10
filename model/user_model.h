//
// Created by 정현민 on 2021/03/20.
//

#ifndef PROJECT_USER_USER_H_
#define PROJECT_USER_USER_H_

#include <string>

typedef enum{
  관리자,
  직원,
  일반
}Authority;

class UserModel {
 public:
  UserModel(std::string username, std::string password, Authority authority);
  ~UserModel();
  bool operator==(const UserModel &user) {
    return this->username_ == user.username_ && this->password_ == user.password_;
  }
  const std::string &GetUsername() const;
  const std::string &GetPassword() const;
  Authority GetAuthority() const;
  void SetUsername(const std::string &username);
  void SetPassword(const std::string &password);
  void SetAuthority(Authority authority);
 private:
  std::string username_;
  std::string password_;
  Authority authority_;
};

#endif //PROJECT_MODEL_USER_MODE_H_
