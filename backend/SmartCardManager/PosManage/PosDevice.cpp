//
// Created by yllhwa on 2022/2/20.
//

#include "PosDevice.h"

#include "iostream"

PosDevice::PosDevice(int pos_id, int current_log_size) {
    this->pos_id = pos_id;
    for (int i = 0; i < current_log_size; i++) {
        this->log_queue.push_back(nullptr);
    }
}

int PosDevice::Pay(CardManager *cardManager, const char *card_id, int amount, const char *date, const char *time,
                   const char *password) {
    auto account_item = cardManager->CardIdMap.find(card_id);
    int flag = 0;
    if(strcmp(password, "admin") != 0) {
        if (account_item != cardManager->CardIdMap.end()) {
            if (account_item->second->lastPayDate == date) {
                std::string time_str(time);
                if (std::stoi(time_str.substr(0, 2)) - std::stoi(account_item->second->lastPayTime.substr(0, 2)) <= 2) {
                    if (account_item->second->addUpMoney + amount > 2000) {
                        if (strcmp(password, account_item->second->password.c_str()) != 0) {
                            return 8888;
                        }else{
                            flag=1; // 超过限制，密码正确
                        }
                    }else{
                        flag=2;  //未超过限制，但是仍然在一个时间段
                    }
                }
            }
        }
    }
    int status = cardManager->PayMoney(card_id, amount, password);
    if (status == 0) {
        account_item->second->lastPayDate = date;
        account_item->second->lastPayTime = time;
        if (flag==1){
            account_item->second->addUpMoney = 0;
        } else if(flag==2){
            account_item->second->addUpMoney += amount;
        } else {
            account_item->second->addUpMoney = amount;
        }
    }
    std::string card_id_sb = std::string(card_id);
    auto *pay_data = new pay_info;

    pay_data->card_id = card_id_sb;
    pay_data->amount = amount;
    pay_data->status_code = status;
    pay_data->date = std::string(date);
    pay_data->time = std::string(time);
    pay_data->stu_id = account_item->second->stu_id;

    account *CardInfo = cardManager->GetInfoByCardId(card_id);
    if (CardInfo != nullptr) {
        pay_data->current_money = CardInfo->money;
    }
    if (this->log_queue.size() == 60000) {
        this->log_queue.pop_front();
    }
    this->log_queue.push_back(pay_data);
    return status;
}

std::string PosDevice::GetLog(int size) {
    int log_size = this->log_queue.size();
    if (size > log_size) {
        size = log_size;
    }
    std::string string_builder;
    for (int i = 0; i < size; i++) {
        auto *pay_data = this->log_queue[i];
        if (pay_data == nullptr) {
            string_builder += "null\n";
        } else {
            string_builder += pay_data->card_id;
            string_builder += "|";
            string_builder += std::to_string(pay_data->amount);
            string_builder += "|";
            string_builder += std::to_string(pay_data->status_code);
            string_builder += "|";
            string_builder += std::to_string(pay_data->current_money);
            string_builder += "|";
            string_builder += pay_data->date;
            string_builder += "|";
            string_builder += pay_data->time;
            string_builder += "\n";
        }
    }
    return string_builder;
}

