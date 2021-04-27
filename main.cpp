#include <functional>
#include <filesystem>

#include "view/auth_view.h"
#include "view/warehouse_view.h"
#include "handler/output_handler.h"

void OutputHelp() {
  std::cout << "================ Manual ==============" << std::endl;
  std::cout << ">> exit" << std::endl;
  std::cout << "  : Exit program." << std::endl << std::endl;
  std::cout << ">> open [MODE]" << std::endl;
  std::cout << "  : Open mode. Available mode is auth and warehouse" << std::endl;
  std::cout << "======================================" << std::endl;
}

void OutputPrint() {
  std::cout << "================ Manual ==============" << std::endl;
  std::cout << "auth: 인증 명령어 모드" << std::endl;
  std::cout << "warehouse: 창고 명령어 모드" << std::endl;
  std::cout << "======================================" << std::endl;
}

std::vector<std::string> GetInputs() {
  std::string input;
  std::cout << ">> ";
  std::getline(std::cin, input, '\n');
  std::vector<std::string> inputs = StringHandler::SplitString(input);
  return inputs;
}

void ProcessInput(const std::vector<std::string> &inputs,
                  const std::function<void()> &on_open_auth,
                  const std::function<void()> &on_open_warehouse,
                  const std::function<void()> &on_help,
                  const std::function<void()> &on_print) {
  if (inputs.size() > 2) {
    OutputHandler::Error(ErrorType::MANY_ARGUMENT);
    return;
  }
  std::string command = inputs.at(0);
  if (command == "open") {
    if (inputs[1] == "auth") {
      on_open_auth();
    } else if (inputs[1] == "warehouse") {
      on_open_warehouse();
    } else {
      OutputHandler::Error(ErrorType::WRONG_ARGUMENT);
    }
  } else if (command == "help") {
    on_help();
  } else if (command == "print") {
    if (inputs[1] == "mode") {
      on_print();
    } else {
      OutputHandler::Error(ErrorType::WRONG_ARGUMENT);
    }
  } else {
    OutputHandler::Error(ErrorType::WRONG_COMMAND);
  }
}

int main() {
  std::cout << "데이터 파일 경로 : " << std::filesystem::current_path() << std::endl;

  AuthView auth_view("Auth");
  WarehouseView warehouse_view("Warehouse");
  OutputHelp();
  while (true) {
    if (auth_view.GetIsViewActivated()) {
      auth_view.Interact();
    } else if (warehouse_view.GetIsViewActivated()) {
      warehouse_view.SetIsSinged(auth_view.GetIsSinged());
      warehouse_view.SetPossiblePermission(auth_view.GetPossiblePermission());
      warehouse_view.Interact();
    } else {
      std::vector<std::string> inputs = GetInputs();
      if (inputs.empty()) {
        OutputHandler::Error(ErrorType::WRONG_COMMAND);
        continue;
      }
      if (inputs.at(0) == "exit") {
        break;
      }
      ProcessInput(inputs, [&auth_view] {
        auth_view.ActivateView(); // on open auth
      }, [&warehouse_view] {
        warehouse_view.ActivateView(); // on open warehouse
      }, [] { // on help
        OutputHelp();
      }, [] {
        OutputPrint();
      });
    }
  }
}
