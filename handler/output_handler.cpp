//
// Created by 정현민 on 2021/04/03.
//

#include "output_handler.h"

OutputHandler::OutputHandler() = default;

void OutputHandler::Error(const ErrorType error_type, const std::string &option) {
  PrintError(error_type, option);
}

void OutputHandler::PrintError(const ErrorType error, const std::string &option) {
  switch (error) {
    case ErrorType::MANY_ARGUMENT: std::cout << "[Error] Too many argument";
      break;
    case ErrorType::FEW_ARGUMENT: std::cout << "[Error] Not enough argument";
      break;
    case ErrorType::WRONG_COMMAND: std::cout << "[Error] Wrong command";
      break;
    case ErrorType::WRONG_ARGUMENT: std::cout << "[Error] Wrong argument";
      break;
    case ErrorType::UNKNOWN: std::cout << "[Error] Unknown error";
  }
  if (!option.empty()) {
    std::cout << ": " << option << std::endl;
  }
}
