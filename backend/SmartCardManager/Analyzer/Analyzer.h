//
// Created by yllhwa on 2022/2/23.
//

#ifndef SMARTCARDMANAGER_ANALYZER_H
#define SMARTCARDMANAGER_ANALYZER_H
#include "../CardManage/CardManager.h"
#include "../PosManage/PosManager.h"

class Analyzer {
public:
    Analyzer(CardManager *cardManager, PosManager *posManager);

    std::vector<pay_info *> merge_k(int sort_by);

private:
    CardManager *cardManager;
    PosManager *posManager;
    int MergeData();

};


#endif //SMARTCARDMANAGER_ANALYZER_H
