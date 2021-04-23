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
  return std::stoi(original_string);
}

StringHandler::StringHandler() = default;
