//
// Created by 정현민 on 2021/03/26.
//

#include "auth_controller.h"

AuthController::AuthController() = default;
AuthController::~AuthController() = default;

std::vector<std::string> split(std::string userInformation, char delimiter) {
  std::vector<std::string> subStringVector;
  std::stringstream ss(userInformation);
  std::string temp;

  while (getline(ss, temp, delimiter)) {
    if (!temp.empty()) {
      subStringVector.push_back(temp);
    }
  }

  return subStringVector;
}

bool compareUserFile(std::string &username, std::string &password) {    //name 수정해야됨
  std::ifstream userFile;
  userFile.open("../user.txt");
  std::string line;
  if (userFile.is_open()) {
    while (!userFile.eof()) {
      getline(userFile, line);
      std::vector<std::string> linePair = split(line, ' ');
      if (username == linePair[0] && password == linePair[1]) {
        return true;
      }
    }
  }
  return false;
}

void AuthController::SetUserInformation() {
  std::string bufferString;
  getline(std::cin, bufferString);
  this->userInformation = split(bufferString, ' ');
}

void AuthController::SingInEvent() {
  this->SetUserInformation();
  std::string username, password;
  if (this->userInformation.empty()) {
    std::cout << "username과 password를 입력해주세요." << std::endl;
    std::cout << "username>>";
    std::cin >> username;
    std::cout << "password>>";
    std::cin >> password;
  } else if (this->userInformation.size() == 1) {
    std::cout << "password를 입력해주세요. //여기서 간편로그인 기능을 신청한 유저라면 로그인 가능 여부 확인" << std::endl;
    std::cout << "password>>";
    std::cin >> password;
  }
  if (!username.empty()) {
    this->userInformation.push_back(username);
  }
  if (!password.empty()) {
    this->userInformation.push_back(password);
  }
  SetIsValidateUser();
}

void AuthController::SetIsValidateUser() {
  this->is_validateUser = compareUserFile(this->userInformation[0], this->userInformation[1]);
}

bool AuthController::GetIsValidateUser() const {
  return this->is_validateUser;
}

void AuthController::UpdateUserModel() {

}

