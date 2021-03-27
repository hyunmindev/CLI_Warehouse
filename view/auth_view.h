//
// Created by 정현민 on 2021/03/26.
//

#ifndef PROJECT_VIEW_AUTH_VIEW_H_
#define PROJECT_VIEW_AUTH_VIEW_H_

#include <iostream>

#include "../controller/auth_controller.h"
#include "view.h"

class AuthView : public View {
 public:
  explicit AuthView(const std::string& view_title);
  ~AuthView();
  void ProcessCommand(const std::string &string) override;
  void PrintManual() override;

 private:
  bool is_authenticated_ = false;
};

#endif //PROJECT_VIEW_AUTH_VIEW_H_
