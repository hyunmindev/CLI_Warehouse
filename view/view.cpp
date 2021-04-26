//
// Created by 정현민 on 2021/03/27.
//

#include "view.h"

View::View(std::string view_title) : view_title_(std::move(view_title)) {
}

View::~View() {
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

