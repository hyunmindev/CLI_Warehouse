//
// Created by 정현민 on 2021/03/27.
//

#include "view.h"

View::View(std::string view_title) : view_title_(std::move(view_title)) {
  std::cout << view_title_ << " view class constructed" << std::endl;
}

View::~View() {
  std::cout << view_title_ << " view class destructed" << std::endl;
}

void View::ActivateView() {
  this->is_view_activated_ = true;

}

void View::DeactivateView() {
  this->is_view_activated_ = false;
}

void View::Input() {
  std::string command = this->GetCommand();
  this->ProcessCommand(command);
}

std::string View::GetCommand() {
  std::cout << this->view_title_ << " >> ";
  std::string input_string;
  std::cin >> input_string;
  return input_string;
}

void View::ProcessCommand(const std::string &string) {

}

bool View::GetIsViewActivated() const {
  return is_view_activated_;
}


