//
// Created by 정현민 on 2021/03/27.
//

#include "view.h"

View::View(std::string view_title) : _view_title(std::move(view_title)) {
  std::cout << _view_title << " view class constructed" << std::endl;
}

View::~View() {
  std::cout << _view_title << " view class destructed" << std::endl;
}

void View::ActivateView() {
  this->_is_view_activated = true;

}

void View::DeactivateView() {
  this->_is_view_activated = false;
}

void View::Input() {
  std::string command = this->GetCommand();
  this->ProcessCommand(command);
}

std::string View::GetCommand() {
  std::cout << this->_view_title << ": >> ";
  std::string input_string;
  std::cin >> input_string;
  return input_string;
}

void View::ProcessCommand(const std::string &string) {

}

bool View::GetIsViewActivated() const {
  return _is_view_activated;
}


