//
// Created by 정현민 on 2021/03/27.
//

#ifndef PROJECT_VIEW_VIEW_H_
#define PROJECT_VIEW_VIEW_H_

#include <iostream>

class View {
 public:
  explicit View(std::string view_title);
  ~View();
  void ActivateView();
  void DeactivateView();
  void Input();
  bool GetIsViewActivated() const;
  std::string GetCommand();
  virtual void ProcessCommand(const std::string &string);
  virtual void PrintManual() = 0;

 protected:
  std::string _view_title;
  bool _is_view_activated = false;
};

#endif //PROJECT_VIEW_VIEW_H_
