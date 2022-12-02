//
// Created by yllhwa on 2022/2/20.
//

#ifndef SMARTCARDMANAGER_POSDEVICE_H
#define SMARTCARDMANAGER_POSDEVICE_H
#include <string>
#include <queue>
#include "../CardManage/CardManager.h"
#include <deque>

typedef struct pay_info{
    std::string card_id;
    std::string stu_id;
    int amount;
    int status_code;
    int current_money;
    std::string date;
    std::string time;
}pay_info;

class PosDevice {
public:
    int pos_id;
    std::deque<pay_info*> log_queue;
    PosDevice(int pos_id, int log_size);
    int Pay(CardManager *cardManager,const char *card_id, int amount,const char* date,const char* time, const char *password);
    std::string GetLog(int size);
};


#endif //SMARTCARDMANAGER_POSDEVICE_H
