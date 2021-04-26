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
    case ErrorType::NOT_MATCH_PASSWORD_CONFIRM_PASSWORD:std::cout << "[Error] not match password and confirm password.";
      break;
    case ErrorType::IS_HAS_EQUAL_USERNAME: std::cout << "[Error] 이미 동일한 이름으로 가입한 이용자가 존재합니다.";
      break;
    case ErrorType::IS_NOT_HAS_EQUAL_USERNAME: std::cout << "[Error] 해당 이름을 사용하는 이용자가 존재하지 않습니다.";
      break;
    case ErrorType::NOT_SIGNED_IN: std::cout << "[Error] not signed in";
      break;
    case ErrorType::PERMISSION_DENIED: std::cout << "[Error] 기능을 사용할 수 없는 권한입니다.";
      break;
    case ErrorType::CANNOT_CHANGED_BY_MANAGER: std::cout << "[Error] cannot be changed by manager permission.";
      break;
    case ErrorType::EXISTING_ITEM: std::cout << "[Error] the item has already received.";
      break;        //  error? warning?
    case ErrorType::NO_EXISTING_ITEM: std::cout << "[Error] the item does not exist.";
      break;
    case ErrorType::NO_EXISTING_WAREHOUSE: std::cout << "[Error] the warehouse does not exist.";
      break;
    case ErrorType::FEW_ITEM_COUNT: std::cout << "[Error] 창고에 해당 물품의 수량이 부족합니다.";
      break;
    case ErrorType::WRONG_WAREHOUSE: std::cout << "[Error] 해당 창고에는 물품이 존재하지 않습니다. 창고";
      break;
    case ErrorType::FEW_ACCEPTED_VOLUME: std::cout << "[Error] 해당 창고에는 여유공간이 없습니다.";
      break;
    case ErrorType::UNACCEPTABLE_WEIGHT: std::cout << "[Error] 해당 창고는 해당 물품의 무게를 수용하지 못합니다.";
      break;
  }
  if (!option.empty()) {
    std::cout << ": " << option << std::endl;
  } else {
    std::cout << std::endl;
  }
}

void OutputHandler::Warning(const WarningType warning_type) {
  PrintWarning(warning_type);
}

void OutputHandler::PrintWarning(const WarningType warning) {
  switch (warning) {
    case WarningType::EXISTING_ITEM: std::cout << "[Warning] 이미 입고된 물티슈 품목이 있습니다 :";
  }
  std::cout << std::endl;
}

void OutputHandler::Success(const SuccessType success, const std::string &option1, const std::string &option2) {
  PrintSuccess(success, option1, option2);
}

void OutputHandler::PrintSuccess(const SuccessType success, const std::string &option1, const std::string &option2) {
  switch (success) {
    case SuccessType::COMPLETE_SIGN_IN: std::cout << "[Notice] complete signin";
      break;
    case SuccessType::COMPLETE_SIGNUP: std::cout << "[Notice] complete signup";
      break;
    case SuccessType::COMPLETE_SIGN_OUT: std::cout << "[Notice] complete signout";
      break;
    case SuccessType::COMPLETE_CHANGE: std::cout << "[Notice] complete change permission";
      break;
    case SuccessType::COMPLETE_RELEASE: std::cout << "[Notice] 창고 " << option1 << "에서 " << option2 << "개 출고됐습니다.";
      break;
    case SuccessType::COMPLETE_RECEIVE: std::cout << "[Notice] 창고 " << option1 << "에 " << option2 << "개 입고됐습니다.";
      break;
  }
  std::cout << std::endl;
}