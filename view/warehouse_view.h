//
// Created by 정현민 on 2021/03/26.
//

#ifndef PROJECT_VIEW_WAREHOUSE_VIEW_H_
#define PROJECT_VIEW_WAREHOUSE_VIEW_H_

#include <string>

#include "../controller/warehouse_controller.h"
#include "view.h"

enum class Prompt : char {
  Main = 1,
  Volume,
  Weight,
  WarehouseIdentifier,
  WarehouseIdentifiers
};

class WarehouseView : public View {
 public:
  explicit WarehouseView(const std::string &view_title);
  ~WarehouseView();
  void ProcessInputs(const std::vector<std::string> &inputs) override;
  void ProcessReceive(std::string& item_id, int count); // 입고 명령어 처리
  void ProcessRelease(std::string& item_id, int count); // 출고 명령어 처리
  void ReceiveSubPromptWeight(int weight);      //  입고 무게 부프롬포트
  void ReceiveSubPromptVolume(int volume);      //  입고 부피 부프롬포트
  void ReceiveSubPromptIdentifier(std::string &identifier);     //  입고 식별자 부프롬포트
  void ProcessReleaseSubPrompt(std::vector<std::string> &identifiers); // 출고 부프롬프트
  void ProcessMove(std::string& item_id, int count); // 이동 명령어 처리
  void ProcessExit();
  void ProcessPrint(); // 출력 명령어 처리

  void OutputHelp() const override;

 private:
  Prompt prompt_;
};

#endif //PROJECT_VIEW_WAREHOUSE_VIEW_H_
