//
// Created by 정현민 on 2021/03/26.
//

#ifndef PROJECT_VIEW_AUTH_VIEW_H_
#define PROJECT_VIEW_AUTH_VIEW_H_

#include <iostream>

#include "view.h"

class AuthView : public View {
 public:
  explicit AuthView(const std::string &view_title);
  ~AuthView();
  void ProcessInputs(const std::vector<std::string> &inputs) override;
  void ProcessSignIn(std::string &username, std::string &password);
  void ProcessSignUp(std::string &username,
                     std::string &password,
                     std::string &confirm_password);
  void ProcessSignOut();
  void ProcessChange(std::string &username, Permission permission);
  void ProcessPrint(const std::string &argument = "") const;

  void OutputHelp() const override;

 private:
};

#endif //PROJECT_VIEW_AUTH_VIEW_H_
