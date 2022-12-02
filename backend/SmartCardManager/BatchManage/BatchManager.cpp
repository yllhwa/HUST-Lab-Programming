//
// Created by yllhwa on 2022/2/21.
//

#include "BatchManager.h"
#include <queue>
#include <iostream>
#include <ctime>
#include <sstream>
#include <cstdlib>
#include <cmath>


std::vector<info *> BatchManager::merge_k(std::vector<std::vector<info *>> &array) {
    clock_t start = clock();
    std::vector<info *> result;
    result.reserve(3000000);
    std::priority_queue<info *, std::vector<info *>, compare> pq;
    std::vector<std::vector<info *>::iterator> iter_list;
    std::vector<std::vector<info *>::iterator> iter_end_list;
    for (auto &iter: array) {
        iter_list.push_back(iter.begin());
        iter_end_list.push_back(iter.end());
    }
    for (int i = 0; i < array.size(); i++) {
        if (iter_list[i] != iter_end_list[i]) {
            pq.push(*iter_list[i]);
            iter_list[i]++;
        }
    }
    while (!pq.empty()) {
        info *temp = pq.top();
        pq.pop();
        result.push_back(temp);
        int _window = temp->window;
        if (iter_list[_window] != iter_end_list[_window]) {
            pq.push(*iter_list[_window]);
            iter_list[_window]++;
        }
    }
    std::cout << "merge_k time: " << (clock() - start) / (double) CLOCKS_PER_SEC << "s" << std::endl;
    return result;
}

//std::vector<info *> BatchManager::merge_k(std::vector<std::vector<info *>> &array) {
//    clock_t start = clock();
//    std::vector<info*> result;
//    result.reserve(3000000);
//    std::priority_queue<info*, std::vector<info*>, compare> pq;
//    for(int i = 0; i < array.size(); i++){
//        if(array[i].size() > 0){
//            pq.push(array[i][0]);
//        }
//    }
//    while(!pq.empty()){
//        info *tmp = pq.top();
//        pq.pop();
//        result.push_back(tmp);
//        int _window = tmp->window;
//        array[_window].erase(array[_window].begin());
//        if (array[_window].size() > 0) {
//            pq.push(array[_window][0]);
//        }
//    }
//    std::cout<<"merge_k time: "<<(clock() - start)/(double)CLOCKS_PER_SEC<<"s"<<std::endl;
//    return result;
//}

int BatchManager::loadOperation() {
    std::ifstream xfFile(this->xfFilePath);
    std::ifstream czFile(this->czFilePath);
    std::string line;
    // Read xfFile
    xfFile >> line;
    if (line != "XF") {
        std::cout << "not XF file!!!" << std::endl;
    }
    this->opList.reserve(100);
    int window_id = -1;
    while (xfFile >> line && line != "") {
        if (line[0] == 'W') {
            this->opList.emplace_back();
            window_id += 1;
        } else {
            info *tmp = new info;
            tmp->type = 0;
            tmp->time = line.substr(8, 8) + line.substr(17, 8);
            tmp->content = line.substr(0, 7) + " " + line.substr(26, line.length() - 27);
            tmp->window = window_id;
            this->opList.back().emplace_back(tmp);
        }
    }
    xfFile.close();

    // Read czFile
    czFile >> line;
    if (line != "CZ") {
        std::cout << "not CZ file!!!" << std::endl;
    }
    this->opList.emplace_back();
    window_id++;
    while (czFile >> line && line != "") {
        info *tmp = new info;
        tmp->type = 1;
        tmp->time = line.substr(0, 16);
        tmp->content = line.substr(17, line.length() - 18);
        tmp->window = window_id;
        this->opList.back().emplace_back(tmp);
    }
    this->opQueue = this->merge_k(this->opList);
    return 0;
}

BatchManager::BatchManager(CardManager *cardManager, PosManager *posManager) {
    this->cardManager = cardManager;
    this->posManager = posManager;
}

std::vector<std::string> _split(const std::string &str, const char pattern) {
    std::vector<std::string> res;
    std::stringstream input(str);
    std::string temp;
    while (getline(input, temp, pattern)) {
        res.push_back(temp);
    }
    return res;
}

int BatchManager::doOperation() {
    clock_t start = clock();
    for (int i = 0; i < opQueue.size(); i++) {
        if (opQueue[i]->type == 1) {
            std::vector<std::string> tmp = _split(opQueue[i]->content, ',');
            std::string opName = tmp[0];

            if (opName == "挂失") {
                std::string stu_id = tmp[1];
                cardManager->LockAccount(stu_id.c_str(), opQueue[i]->time.c_str());
            } else if (opName == "解挂") {
                std::string stu_id = tmp[1];
                cardManager->UnLockAccount(stu_id.c_str(), opQueue[i]->time.c_str());
            } else if (opName == "销户") {
                std::string stu_id = tmp[1];
                cardManager->DeleteAccount(stu_id.c_str(), opQueue[i]->time.c_str());
            } else if (opName == "充值") {
                std::string stu_id = tmp[1];
                std::string money = tmp[2];
                cardManager->ChargeMoney(stu_id.c_str(), (int) strtod(money.c_str(), NULL) * 100,
                                         opQueue[i]->time.c_str());
            } else if (opName == "补卡") {
                std::string stu_id = tmp[1];
                cardManager->CreateCard(stu_id.c_str(), opQueue[i]->time.c_str());
            }
        } else if (opQueue[i]->type == 0) {
            std::vector<std::string> tmp = _split(opQueue[i]->content, ' ');
            std::string cardNum = tmp[0];
            std::string amount = tmp[1];
            std::string date = opQueue[i]->time.substr(0, 8);
            std::string time = opQueue[i]->time.substr(8, 8);
            int pos_id = opQueue[i]->window + 1;
            posManager->Pay(pos_id, cardNum.c_str(), date.c_str(), time.c_str(),
                            (int) round((atof(amount.c_str()) * 100)), "admin");
        }
    }
    std::cout << "op time: " << (clock() - start) / (double) CLOCKS_PER_SEC << "s" << std::endl;
    return 0;
}

int BatchManager::loadKh() {
    std::ifstream khFile(this->khFilePath);
    std::string line;
    khFile >> line;
    if (line != "KH") {
        std::cout << "not KH file!!!" << std::endl;
    }
    while (khFile >> line && line != "") {
        std::vector<std::string> tmp = _split(line, ',');
        tmp[1] = tmp[1].substr(0, tmp[1].length() - 1);
        this->cardManager->CreateAccount(tmp[0].c_str(), tmp[1].c_str(), "20240714", "20220301");
        this->cardManager->CreateCard(tmp[0].c_str(), "20220301");
    }
    khFile.close();
    return 0;
}

int BatchManager::loadWz() {
    std::ifstream wzFile(this->wzFilePath);
    std::string line;
    wzFile >> line;
    if (line != "WZ") {
        std::cout << "not WZ file!!!" << std::endl;
    }
    while (wzFile >> line && line != "") {
        std::vector<std::string> tmp = _split(line, ',');
        tmp[1] = tmp[1].substr(0, tmp[1].length() - 1);
        this->posManager->registerPos(strtol(tmp[0].c_str(), NULL, 10), strtol(tmp[1].c_str(), NULL, 10));
    }
    wzFile.close();
    return 0;
}

int BatchManager::loadAll() {
    this->loadKh();
    this->loadWz();
    this->loadOperation();
    this->doOperation();
    return 0;
}

bool map_compare(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
    return a.second > b.second;
}

std::vector<std::string> BatchManager::find_friends(const char *stu_id) {
    std::vector<std::string> res;
    std::unordered_map<std::string, int> count_map;
    std::string find_stu_id_str = stu_id;
    const int range = 1;
    const int time_range = 300;
    for (int i = 1; i < posManager->PosList.size(); i++) { //遍历窗口找用户
        for (int j = 0; j < posManager->PosList[i]->log_queue.size(); j++) { //遍历每个窗口的日志找用户
            if (posManager->PosList[i]->log_queue[j] != nullptr &&
                posManager->PosList[i]->log_queue[j]->stu_id == find_stu_id_str) {
                for (int k = i - range > 0 ? i - range : 1;
                     k <= (i + range > posManager->PosList.size() ? posManager->PosList.size() : i + range); k++) { //遍历附近的窗口找同学
                    int iter = 0;
                    while (iter < posManager->PosList[k]->log_queue.size()) {  //遍历当前窗口找时间接近的
                        if (posManager->PosList[k]->log_queue[iter] == nullptr ||
                            posManager->PosList[k]->log_queue[iter]->date != posManager->PosList[i]->log_queue[j]->date || posManager->PosList[k]->log_queue[iter]->stu_id == find_stu_id_str
                            || std::abs(std::stoi(posManager->PosList[k]->log_queue[iter]->time) - std::stoi(posManager->PosList[i]->log_queue[j]->time)) > time_range) {
                        } else {
                            if (count_map.find(posManager->PosList[k]->log_queue[iter]->stu_id) == count_map.end()) {
                                count_map.insert(std::pair<std::string, int>(posManager->PosList[k]->log_queue[iter]->stu_id,0));
                            } else {
                                count_map.find(posManager->PosList[k]->log_queue[iter]->stu_id)->second++;
                            }
                        }
                        iter++;
                    }
                }
            }
        }
    }
    // get top n in count_map
    std::vector<std::pair<std::string, int>> count_vec;
    count_vec.reserve(count_map.size());
    for (auto &it: count_map) {
        count_vec.emplace_back(it.first, it.second);
    }
    std::sort(count_vec.begin(), count_vec.end(), map_compare);
    const int limit = 10;
    res.reserve(limit);
    for (int i = 0; i < count_vec.size(); i++) {
        if (i > limit) {
            break;
        }
//        std::cout << count_vec[i].first << " " << count_vec[i].second << std::endl;
        res.push_back(count_vec[i].first);
    }
    return res;
}
