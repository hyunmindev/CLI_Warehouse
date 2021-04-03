//
// Created by 정현민 on 2021/03/31.
//

#ifndef PROJECT__STRING_PROCESSOR_H_
#define PROJECT__STRING_PROCESSOR_H_

#include <string>
#include <vector>
#include <sstream>

class StringProcessor {
 public:
  static std::vector<std::string> SplitString(const std::string &original_string,
                                              char delimiter = ' ');
 private:
  StringProcessor();
};

#endif //PROJECT__STRING_PROCESSOR_H_
