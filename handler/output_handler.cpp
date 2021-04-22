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
      break;
    case ErrorType::NO_COMMAND: std::cout << "[Error] No Command";
      break;
    case ErrorType::NO_USER: std::cout << "[Error] 정보에 맞는 이용자가 없습니다.";
      break;
    case ErrorType::NOT_MATCH_PASSWORD_CONFIRM_PASSWORD: std::cout << "[Error] not match password and confirm password";
      break;
    case ErrorType::IS_HAS_EQUAL_USERNAME: std::cout << "[Error] 이미 동일한 이름으로 가입한 이용자가 존재합니다.";
      break;
    case ErrorType::NOT_SIGNED_IN: std::cout << "[Error] not signed in";
      break;
    case ErrorType::LACK_OF_AUTHORITY: std::cout << "[Error] 기능을 사용할 수 없는 권한입니다.";
      break;
  }
  if (!option.empty()) {
    std::cout << ": " << option << std::endl;
  } else {
    std::cout << std::endl;
  }
}

void OutputHandler::Warning() {

}

void OutputHandler::Success(const SuccessType success) {
  switch (success) {
    case SuccessType::COMPLETE_SIGN_IN: std::cout << "[Notice] complete signin";
      break;
    case SuccessType::COMPLETE_SIGNUP: std::cout << "[Notice] complete signup";
      break;
    case SuccessType::COMPLETE_SIGN_OUT: std::cout << "[Notice] complete signout";
      break;
  }
  std::cout << std::endl;
}
