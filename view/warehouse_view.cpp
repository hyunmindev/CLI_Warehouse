//
// Created by 정현민 on 2021/03/26.
//

#include "warehouse_view.h"

WarehouseView::WarehouseView(const std::string &view_title) : View(view_title), prompt_(Prompt::Main) {
}
WarehouseView::~WarehouseView() = default;

void WarehouseView::ProcessInputs(const std::vector<std::string> &inputs) {
  if (inputs.empty()) {
    OutputHandler::Error(ErrorType::NO_COMMAND);
    return;
  }
  const std::string command = inputs.at(0);
  const std::vector<std::string> arguments{inputs.begin() + 1, inputs.end()};
  if (command == "help") {
    this->OutputHelp();
  } else if (command == "exit") {
    this->ProcessExit();
  } else if (command == "print") {
    if (!View::CheckArguments(arguments, 1, 3)) {
      return;
    }
    std::string mode_type = arguments.at(0);
    std::string argument;
    if (arguments.size() == 2) {
      argument = arguments.at(1);
    }
    this->ProcessPrint(mode_type, argument);
  } else if (command == "receive" && this->prompt_ == Prompt::Main) { // 입고
    if (!View::CheckArguments(arguments, 2, 3)) {
      return;
    }
    std::string item_id = arguments.at(0);
    int count = StringHandler::StringToInteger(arguments.at(1));
    if (count == -1) {
      OutputHandler::Error(ErrorType::WRONG_ARGUMENT);
      return;
    }
    this->ProcessReceive(item_id, count);
  } else if (command == "release" && this->prompt_ == Prompt::Main) { // 출고
    if (!View::CheckArguments(arguments, 2, 3)) {
      return;
    }
    std::string item_id = arguments.at(0);
    int count = StringHandler::StringToInteger(arguments.at(1));
    if (count == -1) {
      OutputHandler::Error(ErrorType::WRONG_ARGUMENT);
      return;
    }
    this->ProcessRelease(item_id, count);
  } else if (command == "move" && this->prompt_ == Prompt::Main) {
    if (!View::CheckArguments(arguments, 2, 3)) {
      return;
    }
    std::string item_id = arguments.at(0);
    int count = StringHandler::StringToInteger(arguments.at(1));
    if (count == -1) {
      OutputHandler::Error(ErrorType::WRONG_ARGUMENT);
      return;
    }
    this->ProcessMove(item_id, count);
  } else if (this->prompt_ == Prompt::Weight) {
    if (command.empty()) {
      OutputHandler::Error(ErrorType::FEW_ARGUMENT);
      return;
    }
    if (!View::CheckArguments(arguments, 0, 1)) {
      return;
    }
    int weight = StringHandler::StringToInteger(command);
    if (weight == -1) {
      OutputHandler::Error(ErrorType::WRONG_ARGUMENT);
      return;
    }
    this->ReceiveSubPromptWeight(weight);
  } else if (this->prompt_ == Prompt::Volume) {
    if (command.empty()) {
      OutputHandler::Error(ErrorType::FEW_ARGUMENT);
      return;
    }
    if (!View::CheckArguments(arguments, 0, 1)) {
      return;
    }
    int volume = StringHandler::StringToInteger(command);
    if (volume == -1) {
      OutputHandler::Error(ErrorType::WRONG_ARGUMENT);
      return;
    }
    this->ReceiveSubPromptVolume(volume);
  } else if (this->prompt_ == Prompt::WarehouseIdentifier) {
    if (command.empty()) {
      OutputHandler::Error(ErrorType::FEW_ARGUMENT);
      return;
    }
    if (!View::CheckArguments(arguments, 0, 1)) {
      return;
    }
    std::string item_identifier = command;
    this->ReceiveSubPromptIdentifier(item_identifier);
  } else if (this->prompt_ == Prompt::WarehouseIdentifiers) {
    if (command.empty()) {
      OutputHandler::Error(ErrorType::FEW_ARGUMENT);
      return;
    }
    std::vector<std::string> identifiers = {command};
    identifiers.insert(identifiers.end(), arguments.begin(), arguments.end());
    this->ProcessReleaseSubPrompt(identifiers);
  } else if (this->prompt_ == Prompt::MoveIdentifiers) {
    if (command.empty()) {
      OutputHandler::Error(ErrorType::FEW_ARGUMENT);
      return;
    }
    std::vector<std::string> identifiers = {command};
    identifiers.insert(identifiers.end(), arguments.begin(), arguments.end());
    this->ProcessMoveSubPromptIdentifiers(identifiers);
  } else {
    OutputHandler::Error(ErrorType::WRONG_COMMAND, command);
  }
}

void WarehouseView::ProcessReceive(std::string &item_id, int count) {
  if (!this->is_signed_) {
    OutputHandler::Error(ErrorType::NOT_SIGNED_IN);
    return;
  } else if (!this->possible_permission_) {
    OutputHandler::Error(ErrorType::PERMISSION_DENIED);
    return;
  }
  int ret_val = this->warehouse_controller_.Receive(item_id, count);
  if (ret_val == 1) {
    this->view_title_ = "Warehouse : " + item_id + " : 무게";
    this->prompt_ = Prompt::Weight;
  } else if (ret_val == 2) {
    this->view_title_ = "Warehouse : " + item_id + " : 부피";
    this->prompt_ = Prompt::Volume;
  } else {
    this->view_title_ = "Warehouse : " + item_id + " : 창고 식별자";
    this->prompt_ = Prompt::WarehouseIdentifier;
  }
}

void WarehouseView::ReceiveSubPromptWeight(int weight) {
  if (this->warehouse_controller_.ReceiveSubPromptWeight(weight)) {
    this->view_title_ = "Warehouse : " + this->warehouse_controller_.GetReceiveItem()->GetIdentifier() + " : 부피";
    this->prompt_ = Prompt::Volume;
  }
}

void WarehouseView::ReceiveSubPromptVolume(int volume) {
  if (this->warehouse_controller_.ReceiveSubPromptVolume(volume)) {
    this->view_title_ = "Warehouse : " + this->warehouse_controller_.GetReceiveItem()->GetIdentifier() + " : 창고식별자";
    this->prompt_ = Prompt::WarehouseIdentifier;
  }
}

void WarehouseView::ReceiveSubPromptIdentifier(std::string &item_id) {
  if (this->warehouse_controller_.ReceiveSubPromptIdentifier(item_id)) {
    this->view_title_ = "Warehouse";
    this->prompt_ = Prompt::Main;
  }
}

void WarehouseView::ProcessRelease(std::string &item_id, int count) {
  if (!this->is_signed_) {
    OutputHandler::Error(ErrorType::NOT_SIGNED_IN);
    return;
  } else if (!this->possible_permission_) {
    OutputHandler::Error(ErrorType::PERMISSION_DENIED);
    return;
  }
  if (this->warehouse_controller_.Release(item_id, count)) {
    this->view_title_ = "Warehouse : " + item_id + " : 창고 식별자";
    this->prompt_ = Prompt::WarehouseIdentifiers;
  }
}

void WarehouseView::ProcessReleaseSubPrompt(std::vector<std::string> &identifiers) {
  if (this->warehouse_controller_.ReleaseSubPrompt(identifiers)) {
    this->view_title_ = "Warehouse";
    this->prompt_ = Prompt::Main;
  }
}

void WarehouseView::ProcessMove(std::string &item_id, int count) {
  if (!this->is_signed_) {
    OutputHandler::Error(ErrorType::NOT_SIGNED_IN);
    return;
  } else if (!this->possible_permission_) {
    OutputHandler::Error(ErrorType::PERMISSION_DENIED);
    return;
  }
  if (this->warehouse_controller_.Release(item_id, count)) {
    this->view_title_ = "Warehouse : " + item_id + " : 창고 식별자";
    this->prompt_ = Prompt::MoveIdentifiers;
  }
}

void WarehouseView::ProcessMoveSubPromptIdentifiers(std::vector<std::string> &identifiers) {
  if (this->warehouse_controller_.ReleaseSubPrompt(identifiers)) {
    this->view_title_ = "Warehouse : " + this->warehouse_controller_.GetReceiveItem()->GetIdentifier() + " : 입고 식별자";
    this->prompt_ = Prompt::WarehouseIdentifier;
  }
}

void WarehouseView::OutputHelp() const {
  std::cout << "================ Manual ==============" << std::endl;
  std::cout << ">> receive [물품식별자] [입고할 개수]" << std::endl;
  std::cout << "  : 입고 명령어 입니다.(입력한 물품이 없을 시 무게와 부피도 입력 받습니다.)(직원 권한이상만 가능한 명령어 입니다.)" << std::endl;
  std::cout << ">> release [물품식별자] [출고할 개수]" << std::endl;
  std::cout << "  : 출고 명령어 입니다." << std::endl << std::endl;
  std::cout << ">> move [물품식별자] [옮길 개수]" << std::endl;
  std::cout << "  : 권한 변경 명령어 입니다. (직원 권한이상만 가능한 명령어 입니다.)" << std::endl;
  std::cout << ">> exit" << std::endl;
  std::cout << "  : 모드 선택모드로 돌아가는 명령어 입니다." << std::endl;
  std::cout << "======================================" << std::endl;
}

void WarehouseView::ProcessExit() {
  if (this->prompt_ != Prompt::Main) {
    this->view_title_ = "Warehouse";
    this->prompt_ = Prompt::Main;
    this->warehouse_controller_.FindItemIndexClear();
  } else this->DeactivateView();
}

void WarehouseView::ProcessPrint(std::string &mode_type, std::string &identifier) {
  if (mode_type == "warehouse") {
    std::cout << "=================== Print Warehouse ===================" << std::endl;
    if (identifier == "") {
      for (int i = 0; i < this->warehouse_controller_.GetAllWarehouses().size(); ++i) {
        std::cout << "창고 : " << this->warehouse_controller_.GetAllWarehouses()[i].GetIdentifier() << "\t수용가능 부피 : "
                  << this->warehouse_controller_.GetAllWarehouses()[i].GetAcceptableVolume() << "L\t현재수용 부피 : "
                  << this->warehouse_controller_.GetAllWarehouses()[i].GetAcceptableVolume()
                      - this->warehouse_controller_.GetStateAcceptableVolume(this->warehouse_controller_.GetAllWarehouses()[i].GetIdentifier())
                  << "L\t수용가능 무게 범위" << this->warehouse_controller_.GetAllWarehouses()[i].GetAllowMinWeight() << "KG - "
                  << this->warehouse_controller_.GetAllWarehouses()[i].GetAllowMaxWeight() << "KG" << std::endl;
      }
      return;
    } else {
      int i = this->warehouse_controller_.FindWarehouse(identifier);
      if (i == -1) {
        OutputHandler::Error(ErrorType::NO_EXISTING_WAREHOUSE);
        return;
      } else {
        std::cout << "창고 : " << this->warehouse_controller_.GetAllWarehouses()[i].GetIdentifier() << "\t수용가능 부피 : "
                  << this->warehouse_controller_.GetAllWarehouses()[i].GetAcceptableVolume() << "L\t현재수용 부피 : "
                  << this->warehouse_controller_.GetAllWarehouses()[i].GetAcceptableVolume()
                      - this->warehouse_controller_.GetStateAcceptableVolume(this->warehouse_controller_.GetAllWarehouses()[i].GetIdentifier())
                  << "L\t수용가능 무게 범위" << this->warehouse_controller_.GetAllWarehouses()[i].GetAllowMinWeight() << "KG - "
                  << this->warehouse_controller_.GetAllWarehouses()[i].GetAllowMaxWeight() << "KG" << std::endl;
      }
    }
  } else if (mode_type == "item") {
    bool is_in_warehouse = this->warehouse_controller_.GetItemInfo(identifier);
    if (!is_in_warehouse) {
      OutputHandler::Error(ErrorType::NO_EXISTING_ITEM);
      return;
    }
  } else {
    OutputHandler::Error(ErrorType::WRONG_ARGUMENT);
  }
}

void WarehouseView::SetIsSinged(bool is_singed) {
  this->is_signed_ = is_singed;
}

void WarehouseView::SetPossiblePermission(bool possible_permission) {
  this->possible_permission_ = possible_permission;
}