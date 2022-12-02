//
// Created by yllhwa on 2022/2/21.
//

#ifndef SMARTCARDMANAGER_BATCHMANAGER_H
#define SMARTCARDMANAGER_BATCHMANAGER_H
#include <string>
#include <vector>
#include "../CardManage/CardManager.h"
#include "../PosManage/PosManager.h"

typedef struct info{
    int type;
    std::string time;
    std::string content;
    int window;
}info;

struct compare {
    bool operator()(info *a, info *b) const {
        return a->time > b->time;
    }
};

class BatchManager {
public:
    BatchManager(CardManager *cardManager, PosManager *posManager);
    std::string xfFilePath = "C:\\Users\\yllhwa\\Desktop\\ProjectDesign\\backend\\fuck_file\\data\\xf014.txt";
    std::string czFilePath = "C:\\Users\\yllhwa\\Desktop\\ProjectDesign\\backend\\fuck_file\\data\\cz002.txt";
    std::string khFilePath = "C:\\Users\\yllhwa\\Desktop\\ProjectDesign\\backend\\fuck_file\\data\\kh001.txt";
    std::string wzFilePath = "C:\\Users\\yllhwa\\Desktop\\ProjectDesign\\backend\\fuck_file\\data\\wz003.txt";
    std::vector<std::vector<info*>> opList;
    std::vector<info*> opQueue;
    std::vector<info*> merge_k(std::vector<std::vector<info*>> &array);
    std::vector<std::string> find_friends(const char* card_id);

    int loadAll();

private:
    CardManager *cardManager;
    PosManager *posManager;
    int loadOperation();
    int doOperation();
    int loadWz();
    int loadKh();
};


#endif //SMARTCARDMANAGER_BATCHMANAGER_H
