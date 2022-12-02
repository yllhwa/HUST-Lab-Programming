//
// Created by yllhwa on 2022/1/13.
//

#include "CardManager.h"
#include <cstdlib>
#include <cstring>
#include <regex>
#include "iostream"


char get_card_id_valid_num(const char *card_id) {
    int valid_num = 0;
    for (int i = 0; i < 6; i++) {
        valid_num += card_id[i] - '0';
    }
    valid_num %= 10;
    valid_num = 9 - valid_num;
    return (char) (valid_num + '0');
}

void set_card_id(char *card_id, char client_num, int card_num) {
    memset(card_id, 0, 8);
    card_id[0] = client_num;
    snprintf(card_id + 1, 6, "%05d", card_num);
    card_id[6] = get_card_id_valid_num(card_id);
}

int get_card_id(const char *card_id) {
    int card_num = 0;
    sscanf(card_id + 1, "%5d", &card_num);
    return card_num;
}

int CardManager::CreateAccount(const char *stu_id, const char *stu_name, const char *valid_date, const char *time) {
    if (this->StuIdMap.find(stu_id) != this->StuIdMap.end()) {  //重复学号
        std::string string_builder;
        string_builder += "error:学号重复";string_builder += "|";
        string_builder += "学号:";string_builder += stu_id;string_builder += "|";
        string_builder += "姓名:";string_builder += stu_name;string_builder += "|";
        string_builder += "过期时间:";string_builder += valid_date;string_builder += "|";
        this->logger.log(time, "CreateAccount", "Error", string_builder.c_str());
        return 1;
    }
    auto *new_account = new account;
    new_account->stu_id = (char *) malloc(11);
    new_account->stu_name = (char *) malloc(13);
    new_account->valid_date = (char *) malloc(10);
    new_account->money = 0;
    new_account->status = 0;
    memcpy(new_account->stu_id, stu_id, 11);
    memcpy(new_account->stu_name, stu_name, 13);
    memcpy(new_account->valid_date, valid_date, 10);

    this->StuIdMap.insert(std::pair<std::string, account *>(stu_id, new_account));

    std::string string_builder;
    string_builder += "success";string_builder += "|";
    string_builder += "学号:";string_builder += stu_id;string_builder += "|";
    string_builder += "姓名:";string_builder += stu_name;string_builder += "|";
    string_builder += "过期时间:";string_builder += valid_date;string_builder += "|";
    this->logger.log(time, "CreateAccount", "Success", string_builder.c_str());
    return 0;
}

int CardManager::DeleteAccount(const char *stu_id, const char *time) {
    auto account_item = this->StuIdMap.find(stu_id);
    if (account_item == this->StuIdMap.end()) {
        std::string  string_builder;
        string_builder += "error:学号不存在";string_builder += "|";
        string_builder += "学号:";string_builder += stu_id;string_builder += "|";
        this->logger.log(time, "DeleteAccount", "Error", string_builder.c_str());
        return 1;
    } else {
        account_item->second->status = -1;
        std::string string_builder;
        string_builder += "success";string_builder += "|";
        string_builder += "学号:";string_builder += stu_id;string_builder += "|";
        this->logger.log(time, "DeleteAccount", "Success", string_builder.c_str());
        return 0;
    }
}

int CardManager::CreateCard(const char *stu_id, const char *time) {
    auto account_item = this->StuIdMap.find(stu_id);
    if (account_item == this->StuIdMap.end()) {  //无此学号
        std::string string_builder;
        string_builder += "error:学号不存在";string_builder += "|";
        string_builder += "学号:";string_builder += stu_id;string_builder += "|";
        this->logger.log(time, "CreateCard", "Error", string_builder.c_str());
        return 1;
    } else if (!account_item->second->CardId.empty()) {  //补卡
        char *card_id = (char *) malloc(sizeof(char) * 8);
        set_card_id(card_id, '3', ++(this->lastCardNum));
        this->CardIdMap.insert(std::pair<std::string, account *>(card_id, account_item->second));
        account_item->second->status = 1;
        account_item->second->CardId.emplace_back(card_id);

        std::string string_builder;
        string_builder += "success";string_builder += "|";
        string_builder += "学号:";string_builder += stu_id;string_builder += "|";
        string_builder += "卡号:";string_builder += card_id;string_builder += "|";
        this->logger.log(time, "CreateCard", "Success", string_builder.c_str());
        return 0;
    } else {
        char *card_id = (char *) malloc(sizeof(char) * 8);
        set_card_id(card_id, '3', ++(this->lastCardNum));
        this->CardIdMap.insert(std::pair<std::string, account *>(card_id, account_item->second));
        account_item->second->status = 1;
        account_item->second->CardId.emplace_back(card_id);

        std::string string_builder;
        string_builder += "success";string_builder += "|";
        string_builder += "学号:";string_builder += stu_id;string_builder += "|";
        string_builder += "卡号:";string_builder += card_id;string_builder += "|";
        string_builder += "姓名:";string_builder += account_item->second->stu_name;string_builder += "|";
        this->logger.log(time, "CreateCard", "Success", string_builder.c_str());
        return 0;
    }

}

int CardManager::LockAccount(const char *stu_id, const char *time) {
    auto account_item = this->StuIdMap.find(stu_id);
    if (account_item == this->StuIdMap.end()) {  //无此学号
        std::string string_builder;
        string_builder += "error:学号不存在";string_builder += "|";
        string_builder += "学号:";string_builder += stu_id;string_builder += "|";
        this->logger.log(time, "LockAccount", "Error", string_builder.c_str());
        return 1;
    } else if (account_item->second->status != 1) {
        std::string string_builder;
        string_builder += "error:账户非正常状态";string_builder += "|";
        string_builder += "学号:";string_builder += stu_id;string_builder += "|";
        this->logger.log(time, "LockAccount", "Error", string_builder.c_str());
        return 2;
    } else {
        account_item->second->status = 2;

        std::string string_builder;
        string_builder += "success";string_builder += "|";
        string_builder += "学号:";string_builder += stu_id;string_builder += "|";
        this->logger.log(time, "LockAccount", "Info", string_builder.c_str());
        return 0;
    }
}

int CardManager::UnLockAccount(const char *stu_id, const char *time) {
    auto account_item = this->StuIdMap.find(stu_id);
    if (account_item == this->StuIdMap.end()) {  //无此学号
        std::string string_builder;
        string_builder += "error:学号不存在";string_builder += "|";
        string_builder += "学号:";string_builder += stu_id;string_builder += "|";
        this->logger.log(time, "UnLockAccount", "Error", string_builder.c_str());
        return 1;
    } else if (account_item->second->status != 2) {
        std::string string_builder;
        string_builder += "error:账户非锁定状态";string_builder += "|";
        string_builder += "学号:";string_builder += stu_id;string_builder += "|";
        this->logger.log(time, "UnLockAccount", "Error", string_builder.c_str());
        return 2;
    } else {
        account_item->second->status = 1;

        std::string string_builder;
        string_builder += "success";string_builder += "|";
        string_builder += "学号:";string_builder += stu_id;string_builder += "|";
        this->logger.log(time, "UnLockAccount", "Info", string_builder.c_str());
        return 0;
    }
}

int CardManager::ChargeMoney(const char *stu_id, int new_money, const char *time) {
    auto account_item = this->StuIdMap.find(stu_id);
    if (account_item == this->StuIdMap.end()) {  //无此学号
        std::string string_builder;
        string_builder += "error:学号不存在";string_builder += "|";
        string_builder += "学号:";string_builder += stu_id;string_builder += "|";
        this->logger.log(time, "ChargeMoney", "Error", string_builder.c_str());
        return 1;
    } else if (account_item->second->money + new_money > 99999) {
        std::string string_builder;
        string_builder += "error:账户余额超限";string_builder += "|";
        string_builder += "学号:";string_builder += stu_id;string_builder += "|";
        string_builder += "余额:";string_builder += std::to_string(account_item->second->money);string_builder += "|";
        string_builder += "充值:";string_builder += std::to_string(new_money);string_builder += "|";
        string_builder += "账户余额超限|";
        this->logger.log(time, "ChargeMoney", "Error", string_builder.c_str());
        return 2;
    } else if (account_item->second->status!=1){
        std::string string_builder;
        string_builder += "error:账户非正常状态";string_builder += "|";
        string_builder += "学号:";string_builder += stu_id;string_builder += "|";
        this->logger.log(time, "ChargeMoney", "Error", string_builder.c_str());
        return 3;
    } else {
        account_item->second->money += new_money;

        std::string string_builder;
        string_builder += "success";string_builder += "|";
        string_builder += "学号:";string_builder += stu_id;string_builder += "|";
        string_builder += "姓名:";string_builder += account_item->second->stu_name;string_builder += "|";
        string_builder += "余额:";string_builder += std::to_string(account_item->second->money);string_builder += "|";
        string_builder += "充值:";string_builder += std::to_string(new_money);string_builder += "|";
        this->logger.log(time, "ChargeMoney", "Success", string_builder.c_str());
        return 0;
    }
}

account *CardManager::GetInfoByStuId(const char *stu_id) {
    auto account_item = this->StuIdMap.find(stu_id);
    if (account_item == this->StuIdMap.end()) {  //无此学号
        return NULL;
    } else {
        return account_item->second;
    }
}

account *CardManager::GetInfoByCardId(const char *card_id) {
    auto account_item = this->CardIdMap.find(card_id);
    if (account_item == this->CardIdMap.end()) {  //无此卡号
        return nullptr;
    } else {
        return account_item->second;
    }
}


char *CardManager::SearchByStuId(const char *patten) {
    std::string patten_str = patten;
    int index;
    while ((index = patten_str.find("?")) != patten_str.npos) {
        patten_str.replace(index, 1,
                           );
    }
    while ((index = patten_str.find("*")) != patten_str.npos) {
        patten_str.replace(index, 1, "(.{0,})");
    }
    std::regex patten_re(patten_str);
    auto iter = this->StuIdMap.begin();
    std::string out_str;
    while (iter != this->StuIdMap.end()) {
        if (std::regex_match(iter->second->stu_id, patten_re)) {
            out_str.append(iter->second->stu_id);
            out_str.append(",");
        }
        iter++;
    }
    char *ret_str = (char *) malloc(out_str.length() + 1);
    out_str.copy(ret_str, out_str.size(), 0);
    ret_str[out_str.size()] = 0;
    return ret_str;
}

int CardManager::PayMoney(const char *card_id, int money, const char *password) {
    auto account_item = this->CardIdMap.find(card_id);
    if (account_item == this->CardIdMap.end()) {  //无此卡号
        return 1;
    } else if(account_item->second->status!=1){  //账户非正常状态
        return 2;
    }
    else if (account_item->second->money < money) {  //余额不足
        return 3;
    } else if(strcmp(account_item->second->CardId.back().c_str(), card_id)!=0)
    {
        return 4;
    }
    else {
        account_item->second->money -= money;
        return 0;
    }
}
