//
// Created by 정현민 on 2021/03/27.
//

#ifndef PROJECT_VIEW_VIEW_H_
#define PROJECT_VIEW_VIEW_H_

#include <iostream>

#include "../global/string_processor.h"

class View {
 public:
  explicit View(std::string view_title);
  ~View();
  void ActivateView();
  void DeactivateView();
  void Interact();
  [[nodiscard]] bool GetIsViewActivated() const;
  std::vector<std::string> GetInputs();
  virtual void ProcessInput(const std::vector<std::string> &string) = 0;
  virtual void PrintManual() = 0;

 protected:
  std::string view_title_;
  bool is_view_activated_ = false;
};

#endif //PROJECT_VIEW_VIEW_H_
