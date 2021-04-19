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
  explicit AuthView(const std::string &view_title);
  ~AuthView();
  void ProcessInputs(const std::vector<std::string> &inputs) override;
  void ProcessSignIn(const std::string &username, const std::string &password) const;
  void ProcessSignUp(const std::string &username,
                     const std::string &password,
                     const std::string &confirm_password) const;
  void ProcessSignOut();
  void ProcessChange(const std::string &username, Authority authority);
  void ProcessPrint() const;

  void OutputHelp() const override;

 private:
  AuthController auth_controller_;
};

#endif //PROJECT_VIEW_AUTH_VIEW_H_
