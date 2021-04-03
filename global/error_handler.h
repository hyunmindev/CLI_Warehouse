//
// Created by 정현민 on 2021/04/03.
//

#ifndef PROJECT_GLOBAL_ERROR_HANDLER_H_
#define PROJECT_GLOBAL_ERROR_HANDLER_H_

#include <iostream>

enum Error {
  TOO_MANY_ARGUMENT,
  NOT_ENOUGH_ARGUMENT,
  WRONG_COMMAND,
  WRONG_ARGUMENT
};

class ErrorHandler {
 public:
  static void PrintError(Error error);

 private:
  ErrorHandler();
};

#endif //PROJECT_GLOBAL_ERROR_HANDLER_H_
