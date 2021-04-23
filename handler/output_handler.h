//
// Created by 정현민 on 2021/04/03.
//

#ifndef PROJECT_GLOBAL_OUTPUT_HANDLER_H_
#define PROJECT_GLOBAL_OUTPUT_HANDLER_H_

#include <iostream>

enum class ErrorType {
  UNKNOWN,
  MANY_ARGUMENT,
  FEW_ARGUMENT,
  WRONG_COMMAND,
  NO_COMMAND,
  WRONG_ARGUMENT,
  NO_USER,
  NOT_MATCH_PASSWORD_CONFIRM_PASSWORD,
  IS_HAS_EQUAL_USERNAME,
  IS_NOT_HAS_EQUAL_USERNAME,
  NOT_SIGNED_IN,
  PERMISSION_DENIED,
  CANNOT_CHANGED_BY_MANAGER,
  EXISTING_ITEM,
  NO_EXISTING_ITEM,
  NO_EXISTING_WAREHOUSE,
  LACK_ITEM_COUNT
};

enum class SuccessType {
  COMPLETE_SIGN_IN,
  COMPLETE_SIGNUP,
  COMPLETE_SIGN_OUT,
  COMPLETE_CHANGE
};

class OutputHandler {
 public:
  static void Error(ErrorType error_type = ErrorType::UNKNOWN, const std::string &option = "");
  static void Warning();
  static void Success(SuccessType success_type);

 private:
  OutputHandler();
  static void PrintError(ErrorType error, const std::string &option);
};

#endif //PROJECT_GLOBAL_OUTPUT_HANDLER_H_
