//
// Created by 정현민 on 2021/03/26.
//

#include "auth_controller.h"

#include <utility>

AuthController::AuthController() : current_user_(nullptr) {
  this->ReadUsers();
}

AuthController::~AuthController() = default;

UserModel AuthController::VectorToUserModel(std::vector<std::string> &user_information) {
  UserModel user(user_information[0], user_information[1], user_information[2]);
  return user;
}

void AuthController::ReadUsers() {
  std::ifstream read_auth_file;
  read_auth_file.open("auth.txt"); //file name
  if (read_auth_file.is_open()) {
    while (!read_auth_file.eof()) {
      std::string line = "\n";
      getline(read_auth_file, line, '\n');
      std::cout << line << std::endl;
      if (line.empty()) continue;
      std::vector<std::string> user_information = StringHandler::SplitString(line);
      UserModel user(user_information[0], user_information[1], user_information[2]);
      if (std::find(this->all_users_.begin(), this->all_users_.end(), user) == this->all_users_.end()) {
        this->all_users_.push_back(this->VectorToUserModel(user_information));
      }
    }
  }
  for (int i = 0; i < this->all_users_.size(); ++i) {
    std::cout<<all_users_[i].GetUsername()<<std::endl;
  }
  read_auth_file.close();
}

bool AuthController::SingIn(std::string username, std::string password) {
  this->ReadUsers();
  UserModel user(std::move(username), std::move(password));
  user = this->FindUser(user);
  if (!(user == *this->all_users_.end())) {
    this->current_user_ = &user;
    return true;
  }
  return false;
}

bool AuthController::SingUp(std::string username, std::string password) {
  this->ReadUsers();
  UserModel user(std::move(username), std::move(password));
  if (this->FindUserUsername(user) == *this->all_users_.end()) {
    std::ofstream write_auth_file("auth.txt", std::ios::app);
    write_auth_file << "\n" << user.GetUsername() << "\t" << user.GetPassword() << "\t"
                    << UserModel::ConvertEnumAuthorityToString(user.GetAuthority());
    write_auth_file.close();
    return true;
  }
  return false;
}

void AuthController::SingOut() {
  this->current_user_ = nullptr;
}

UserModel *AuthController::getCurrentUser() const {
  return this->current_user_;
}

UserModel AuthController::FindUser(const UserModel &user) const {
  return *std::find(this->all_users_.begin(), this->all_users_.end(), user);
}

UserModel AuthController::FindUserUsername(const UserModel user) const {
  for (const auto &index : this->all_users_) {
    if ((index).GetUsername() == user.GetUsername()) {
      return index;
    }
  }
  return *this->all_users_.end();
}