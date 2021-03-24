//
// Created by 정현민 on 2021/03/20.
//

#include "user_model.h"

#include <utility>
UserModel::UserModel(std::string username, std::string password)
    : username_(std::move(username)), password_(std::move(password)) {

}
