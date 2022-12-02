//
// Created by yllhwa on 2022/2/23.
//

#include <iostream>
#include "Analyzer.h"

Analyzer::Analyzer(CardManager *cardManager, PosManager *posManager) {
    this->cardManager = cardManager;
    this->posManager = posManager;
}

struct cmp_by_time{
    bool operator()(pay_info *a, pay_info *b) const {
        std::string a_time = a->date+a->time;
        std::string b_time = b->date+b->time;
        return a_time > b_time;
    }
};

std::vector<pay_info *> Analyzer::merge_k(int sort_by) {
    clock_t start = clock();
    std::vector<pay_info *> result;
    result.reserve(3000000);
    switch (sort_by) {
        case 0:
            std::vector<std::deque<pay_info*>::iterator> iter_list;
            std::vector<std::deque<pay_info*>::iterator> iter_end_list;
            for(auto &iter:posManager->PosList){
                auto queue_iter = iter.second->log_queue.begin();
                auto queue_end_iter = iter.second->log_queue.end();
                while (queue_iter!=queue_end_iter){
                    if(*queue_iter==nullptr){
                        queue_iter++;
                    } else{
                        break;
                    }
                }
                iter_list.push_back(queue_iter);
                iter_end_list.push_back(queue_end_iter);
            }
            std::priority_queue<pay_info *, std::vector<pay_info *>, cmp_by_time> pq;
            for (int i = 0; i < iter_list.size(); ++i) {
                if (iter_list[i] != iter_end_list[i]) {
                    pq.push(*iter_list[i]);
                }
            }
            pay_info *tmp;
            while (!pq.empty()) {
                tmp = pq.top();
                result.push_back(tmp);
                pq.pop();
                for (int i = 0; i < iter_list.size(); ++i) {
                    if ( iter_list[i]!=iter_end_list[i] && *(iter_list[i])==tmp) {
                        iter_list[i]++;
                        if(iter_list[i]!=iter_end_list[i]){
                            pq.push(*iter_list[i]);
                        }
                    }
                }
            }
            break;
    }
    std::cout<<"merge_k time: "<<(clock() - start)/(double)CLOCKS_PER_SEC<<"s"<<std::endl;
    return result;
}

int Analyzer::MergeData() {
    auto iter = posManager->PosList.begin();
    while (iter != posManager->PosList.end()) {
        auto iter2 = iter->second->log_queue;
        iter++;
    }
    return 0;
}
