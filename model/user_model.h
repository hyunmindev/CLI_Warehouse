//
// Created by 정현민 on 2021/03/20.
//

#ifndef PROJECT_MODEL_USER_MODEL_H_
#define PROJECT_MODEL_USER_MODEL_H_

#include <string>

enum class Authority : char {
  Manager = 1,
  STAFF,
  COMMON
};

class UserModel {
 public:
  UserModel(std::string username, std::string password);
  UserModel(std::string username, std::string password, std::string authority);
  ~UserModel();
  bool operator==(const UserModel &user) {
    return this->username_ == user.username_ && this->password_ == user.password_;
  }
  [[nodiscard]] const std::string &GetUsername() const;
  [[nodiscard]] const std::string &GetPassword() const;
  [[nodiscard]] Authority GetAuthority() const;
  void SetUsername(const std::string &username);
  void SetPassword(const std::string &password);
  void SetAuthority(Authority authority);
  static Authority ConvertStringAuthorityToEnum(const std::string &authority);

 private:
  std::string username_;
  std::string password_;
  Authority authority_;
};

#endif //PROJECT_MODEL_USER_MODEL_H_
