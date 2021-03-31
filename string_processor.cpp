//
// Created by 정현민 on 2021/03/31.
//

#include "string_processor.h"

std::vector<std::string> StringProcessor::SplitString(const std::string &original_string,
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