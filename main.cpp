#include <functional>

#include "view/auth_view.h"
#include "view/warehouse_view.h"
#include "global/error_handler.h"

void OutputHelp() {
  std::cout << "================ Manual ==============" << std::endl;
  std::cout << ">> exit" << std::endl;
  std::cout << "  : program exit command." << std::endl;
  std::cout << ">> open [MODE]" << std::endl;
  std::cout << "  : open Mode command. Available mode : auth, warehouse" << std::endl;
  std::cout << "======================================" << std::endl;
}

std::vector<std::string> GetInputs() {
  std::string input;
  std::cout << ">> ";
  std::getline(std::cin, input, '\n');
  std::vector<std::string> inputs = StringProcessor::SplitString(input);
  return inputs;
}

void ProcessInput(const std::vector<std::string> &inputs,
                  const std::function<void()> &on_open_auth,
                  const std::function<void()> &on_open_warehouse,
                  const std::function<void()> &on_help) {
  if (inputs.size() > 2) {
    ErrorHandler::PrintError(TOO_MANY_ARGUMENT);
    return;
  }
  std::string command = inputs[0];
  if (command == "open") {
    if (inputs[1] == "auth") {
      on_open_auth();
    } else if (inputs[1] == "warehouse") {
      on_open_warehouse();
    } else {
      ErrorHandler::PrintError(WRONG_ARGUMENT);
    }
  } else if (command == "help") {
    on_help();
  } else {
    ErrorHandler::PrintError(WRONG_COMMAND);
  }
}

int main() {
  AuthView auth_view("Auth");
  WarehouseView warehouse_view("Warehouse");
  OutputHelp();
  while (true) {
    if (auth_view.GetIsViewActivated()) {
      auth_view.Interact();
    } else if (warehouse_view.GetIsViewActivated()) {
      warehouse_view.Interact();
    } else {
      std::vector<std::string> inputs = GetInputs();
      if (inputs[0] == "exit") {
        break;
      }
      ProcessInput(inputs, [&auth_view] {
        auth_view.ActivateView(); // on open auth
      }, [&warehouse_view] {
        warehouse_view.ActivateView(); // on open warehouse
      }, [] { // on help
        OutputHelp();
      });
    }
  }
}
