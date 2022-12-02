//
// Created by yllhwa on 2022/2/19.
//

#include "CardManageLogger.h"
#include <iomanip>

CardManageLogger::CardManageLogger() {
//    this->logFile.open("CardManageLog.txt", std::ios::app);
    this->logFile.open("CardManageLog.txt", std::ios::out);
}

CardManageLogger::~CardManageLogger() {
    this->logFile.close();
}

void CardManageLogger::log(const char *time, const char *operation, const char *level, const char *msg) {
    this->logFile << time << " " << std::setw(20) << operation << " " << std::setw(6) << level << " " << msg << "\n";
}

void CardManageLogger::_flush() {
    this->logFile.flush();
}
