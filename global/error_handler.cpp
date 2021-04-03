//
// Created by 정현민 on 2021/04/03.
//

#include "error_handler.h"

ErrorHandler::ErrorHandler() = default;

void ErrorHandler::PrintError(const Error error) {
  switch (error) {
    case TOO_MANY_ARGUMENT:
      std::cout << "Error: Too many argument" << std::endl;
      break;
    case NOT_ENOUGH_ARGUMENT:
      std::cout << "Error: Not enough argument" << std::endl;
      break;
    case WRONG_COMMAND:
      std::cout << "Error: Wrong command" << std::endl;
      break;
    case WRONG_ARGUMENT:
      std::cout << "Error: Wrong argument" << std::endl;
      break;
    default:
      std::cout << "Error: Unknown error" << std::endl;
  }
}
