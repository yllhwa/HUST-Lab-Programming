//
// Created by yllhwa on 2022/2/19.
//

#ifndef SMARTCARDMANAGER_POSMANAGER_H
#define SMARTCARDMANAGER_POSMANAGER_H
#include <unordered_map>
#include "PosDevice.h"
#include "../CardManage/CardManager.h"

class PosManager {
public:
    std::unordered_map<int, PosDevice*> PosList;

    PosManager(CardManager *cardManager);

    void registerPos(int pos_id, int current_log_size);

    int Pay(int pos_id,const char *card_id,const char *date,const char *time, int amount, const char* password);

    char* GetLog(int pos_id, int size);
private:
    CardManager *cardManager;

};


#endif //SMARTCARDMANAGER_POSMANAGER_H
