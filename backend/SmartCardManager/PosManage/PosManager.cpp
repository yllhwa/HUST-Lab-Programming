//
// Created by yllhwa on 2022/2/19.
//

#include <iostream>
#include <cstring>
#include "PosManager.h"

void PosManager::registerPos(int pos_id, int current_log_size) {
    auto *pos_device = new PosDevice(pos_id, current_log_size);
    this->PosList.insert(std::pair<int, PosDevice*>(pos_id, pos_device));
}

PosManager::PosManager(CardManager *cardManager) {
    this->cardManager = cardManager;
}

int PosManager::Pay(int pos_id,const char *card_id,const char *date,const char *time, int amount, const char*password) {
    if (this->PosList.find(pos_id) == this->PosList.end()) {
        return -1;
    }
    auto *pos_device = this->PosList.find(pos_id)->second;
    return pos_device->Pay(this->cardManager, card_id, amount, date, time, password);
}

char *PosManager::GetLog(int pos_id, int size) {
    if (this->PosList.find(pos_id) == this->PosList.end()) {
        return nullptr;
    }
    auto *pos_device = this->PosList.find(pos_id)->second;
    std::string out_str = pos_device->GetLog(size);
    char *ret_str = (char *) malloc(out_str.length() + 1);
    out_str.copy(ret_str, out_str.size(), 0);
    ret_str[out_str.size()] = 0;
    return ret_str;
}
