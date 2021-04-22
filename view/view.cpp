//
// Created by 정현민 on 2021/03/27.
//

#include "view.h"

View::View(std::string view_title) : view_title_(std::move(view_title)) {
//  std::cout << view_title_ << " view class constructed" << std::endl;
}

View::~View() {
//  std::cout << view_title_ << " view class destructed" << std::endl;
}

void View::ActivateView() {
  this->is_view_activated_ = true;
}

void View::DeactivateView() {
  this->is_view_activated_ = false;
}

void View::Interact() {
  std::vector<std::string> inputs = this->GetInputs();
  this->ProcessInputs(inputs);
}

bool View::CheckUsername(const std::string &username) {
  if (username.size() < 3) {
    OutputHandler::Error(ErrorType::WRONG_ARGUMENT);
    return false;
  }
  return true;
}

bool View::CheckPassword(const std::string &username, const std::string &password) {
  std::cout<<password<<std::endl;
  if (password.size() >= 8 && password.size() <= 16 && password.find(username) == std::string::npos) {
    int count = 0;
    bool numberCheck = false;
    bool englishCheck = false;
    bool specialCheck = false;
    for (int i = 0; i < password.size(); ++i) {
      if (!numberCheck) numberCheck = std::isdigit(password[i]);
      if (!englishCheck) englishCheck = std::isalpha(password[i]);
      if (!specialCheck) {
        if ((password[i] >= 33 && password[i] <= 47) || (password[i] >= 58 && password[i] <= 64)
            || (password[i] >= 91 && password[i] <= 96) || (password[i] > 123 && password[i] <= 126)) {
          specialCheck = true;
        }
      }
    }
    if (numberCheck) count++;
    if (englishCheck) count++;
    if (specialCheck) count++;
    std::cout<<count<<std::endl;
    if (count >= 2) {
      return true;
    }
  }
  OutputHandler::Error(ErrorType::WRONG_ARGUMENT);
  return false;
}

bool View::CheckArguments(const std::vector<std::string> &arguments, int begin, int end) {
  if (arguments.size() < begin) {
    OutputHandler::Error(ErrorType::FEW_ARGUMENT);
    return false;
  } else if (arguments.size() >= end) {
    OutputHandler::Error(ErrorType::MANY_ARGUMENT);
    return false;
  } else {
    return true;
  }
}

std::vector<std::string> View::GetInputs() const {
  std::cout << this->view_title_ << " >> ";
  std::string input;
  std::getline(std::cin, input, '\n');
  std::vector<std::string> inputs = StringHandler::SplitString(input);
  return inputs;
}

bool View::GetIsViewActivated() const {
  return is_view_activated_;
}

