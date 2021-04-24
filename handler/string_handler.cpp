//
// Created by 정현민 on 2021/03/31.
//

#include "string_handler.h"

std::vector<std::string> StringHandler::SplitString(const std::string &original_string,
                                                    char delimiter) {
  std::vector<std::string> sub_strings;
  std::stringstream string_stream(original_string);
  std::string temp;
  while (getline(string_stream, temp, delimiter)) {
    if (!temp.empty()) {
      sub_strings.push_back(temp);
    }
  }
  return sub_strings;
}

int StringHandler::StringToInteger(const std::string &original_string) {
  for (int i = 0; i < original_string.size(); ++i) {
    if (!std::isdigit(original_string[i]))
      return -1;
  }
  return std::stoi(original_string);
}

std::string StringHandler::IntegerToString(const int &original_int) {
  return std::to_string(original_int);
}

StringHandler::StringHandler() = default;
