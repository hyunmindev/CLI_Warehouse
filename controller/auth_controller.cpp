//
// Created by 정현민 on 2021/03/26.
//

#include "auth_controller.h"

AuthController::AuthController() = default;
AuthController::~AuthController() = default;

std::vector<std::string> Split(std::string user_information, char delimiter) {
  std::vector<std::string> sub_strings;
  std::stringstream ss(user_information);
  std::string temp;
  while (getline(ss, temp, delimiter)) {
    if (!temp.empty()) {
      sub_strings.push_back(temp);
    }
  }
  return sub_strings;
}

bool CompareUserFile(std::string &username, std::string &password) {    //name 수정해야됨
  std::ifstream user_file;
  user_file.open("../user.txt");
  std::string line;
  if (user_file.is_open()) {
    while (!user_file.eof()) {
      getline(user_file, line);
      std::vector<std::string> line_pair = Split(line, ' ');
      if (username == line_pair[0] && password == line_pair[1]) {
        return true;
      }
    }
  }
  return false;
}

void AuthController::SetUserInformation() {
  std::string buffer_string;
  getline(std::cin, buffer_string);
  this->user_informations_ = Split(buffer_string, ' ');
}

void AuthController::SingInEvent() {
  this->SetUserInformation();
  std::string username, password;
  if (this->user_informations_.empty()) {
    std::cout << "username과 password를 입력해주세요." << std::endl;
    std::cout << "username>>";
    std::cin >> username;
    std::cout << "password>>";
    std::cin >> password;
  } else if (this->user_informations_.size() == 1) {
    std::cout << "password를 입력해주세요. //여기서 간편로그인 기능을 신청한 유저라면 로그인 가능 여부 확인" << std::endl;
    std::cout << "password>>";
    std::cin >> password;
  }
  if (!username.empty()) {
    this->user_informations_.push_back(username);
  }
  if (!password.empty()) {
    this->user_informations_.push_back(password);
  }
  SetIsValidateUser();
}

void AuthController::SetIsValidateUser() {
  this->is_validate_user_ = CompareUserFile(this->user_informations_[0], this->user_informations_[1]);
}

bool AuthController::GetIsValidateUser() const {
  return this->is_validate_user_;
}

void AuthController::UpdateUserModel() {

}

