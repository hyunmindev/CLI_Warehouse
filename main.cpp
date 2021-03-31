#include "view/auth_view.h"
#include "view/warehouse_view.h"

void PrintManual() {
//  std::cout << "0: Exit" << std::endl;
//  std::cout << "1: " << auth_view_title << std::endl;
//  std::cout << "2: " << warehouse_view_title << std::endl;
}

int main() {
  std::string auth_view_title = "Auth";
  std::string warehouse_view_title = "Warehouse";
  AuthView auth_view(auth_view_title);
  WarehouseView warehouse_view(warehouse_view_title);
  PrintManual();
  while (true) {
    if (auth_view.GetIsViewActivated()) {
      auth_view.Input();
    } else if (warehouse_view.GetIsViewActivated()) {
      warehouse_view.Input();
    } else {
      std::cout << ">> ";
      std::string input;
      std::cin >> input;
      std::cin.ignore();
      if (input == "0") {
        return 0;
      } else if (input == "1" || input == auth_view_title) {
        auth_view.ActivateView();
      } else if (input == "2" || input == warehouse_view_title) {
        warehouse_view.ActivateView();
      } else {
        std::cout << "Error: Wrong input" << std::endl;
      }
    }
  }
}
