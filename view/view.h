//
// Created by 정현민 on 2021/03/27.
//

#ifndef PROJECT_VIEW_VIEW_H_
#define PROJECT_VIEW_VIEW_H_

#include <iostream>

#include "../handler/string_handler.h"
#include "../handler/output_handler.h"
#include "../controller/auth_controller.h"
#include "../controller/warehouse_controller.h"


class View {
 public:
  explicit View(std::string view_title);
  ~View();
  void ActivateView();
  void DeactivateView();
  void Interact();
  [[nodiscard]] bool GetIsViewActivated() const;
  [[nodiscard]] std::vector<std::string> GetInputs() const;
  virtual void ProcessInputs(const std::vector<std::string> &string) = 0;
  virtual void OutputHelp() const = 0;
  static bool CheckArguments(const std::vector<std::string> &arguments, int begin, int end);

 protected:
  std::string view_title_;
  bool is_view_activated_ = false;
  AuthController auth_controller_;
  WarehouseController warehouse_controller_;
  static bool is_signed;
};

#endif //PROJECT_VIEW_VIEW_H_
