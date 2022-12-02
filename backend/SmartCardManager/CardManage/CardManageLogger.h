//
// Created by yllhwa on 2022/2/19.
//

#ifndef SMARTCARDMANAGER_CARDMANAGELOGGER_H
#define SMARTCARDMANAGER_CARDMANAGELOGGER_H
#include <fstream>

class CardManageLogger {
public:
    CardManageLogger();
    ~CardManageLogger();
    void log(const char *time, const char *operation, const char *level, const char *msg);
    void _flush();

private:
    std::ofstream logFile;
};


#endif //SMARTCARDMANAGER_CARDMANAGELOGGER_H
