//
// Created by 정현민 on 2021/03/20.
//

#ifndef PROJECT_USER_USER_H_
#define PROJECT_USER_USER_H_

#include <string>

class UserModel {
 public:
  UserModel(std::string username, std::string password, std::string authority);
  ~UserModel();
  bool CheckAdministratorAuthority(std::string authority);
  bool CheckEmployeeAuthority(std::string authority);
  bool CheckNormalAuthority(std::string authority);
  bool operator==(const UserModel &user) {
    return this->username_ == user.username_ && this->password_ == user.password_;
  }
  const std::string &GetAuthority() const;
  void SetAuthority(const std::string &authority);
  const std::string &GetUsername() const;
  const std::string &GetPassword() const;
  void SetUsername(const std::string &username);
  void SetPassword(const std::string &password);
 private:
  std::string username_;
  std::string password_;
  std::string authority_;
};

#endif //PROJECT_MODEL_USER_MODE_H_
