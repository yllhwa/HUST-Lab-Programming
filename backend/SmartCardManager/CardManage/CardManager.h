//
// Created by yllhwa on 2022/1/13.
//

#ifndef REAL_CODE_CARDMANAGER_H
#define REAL_CODE_CARDMANAGER_H

#include <string>
#include <unordered_map>
#include <vector>
#include "CardManageLogger.h"

typedef struct account {
    char *stu_id;
    char *stu_name;
    char *valid_date;
    int money;
    int status;
    std::vector<std::string> CardId;
    std::string lastPayDate="19000000";
    std::string lastPayTime="000000";
    int addUpMoney=0;
    std::string password = "8888";
} account;

class CardManager {

public:
    std::unordered_map<std::string, account *> StuIdMap;
    std::unordered_map<std::string, account *> CardIdMap;
    int lastCardNum = 12345;

    CardManageLogger logger;

    account *GetInfoByStuId(const char *stu_id);

    char *SearchByStuId(const char *patten);

    int CreateAccount(const char *stu_id, const char *stu_name, const char *valid_date, const char *time);

    int DeleteAccount(const char *stu_id, const char *time);

    int CreateCard(const char *stu_id, const char *time);

    int LockAccount(const char *stu_id, const char *time);

    int UnLockAccount(const char *stu_id, const char *time);

    int ChargeMoney(const char *stu_id, int new_money, const char *time);

    int PayMoney(const char *card_id, int money, const char *password);

    account *GetInfoByCardId(const char *card_id);
};


#endif //REAL_CODE_CARDMANAGER_H
