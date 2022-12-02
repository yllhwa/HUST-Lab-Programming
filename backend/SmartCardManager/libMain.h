#ifndef SMARTCARDMANAGER_LIBMAIN_H
#define SMARTCARDMANAGER_LIBMAIN_H

#include <sstream>
#include "CardManage/CardManager.h"
#include "iostream"
#include "PosManage/PosManager.h"
#include "BatchManage/BatchManager.h"
#include "Analyzer/Analyzer.h"
#include "regex"
#include <stdlib.h>
extern "C" {
__declspec(dllexport) CardManager cardManager;
__declspec(dllexport) PosManager posManager(&cardManager);
__declspec(dllexport) BatchManager batchManager(&cardManager, &posManager);
__declspec(dllexport) Analyzer analyzer(&cardManager, &posManager);

__declspec(dllexport) int CreateAccount(const char *stu_id, const char *stu_name, const char *valid_date, const char *time){
    return cardManager.CreateAccount(stu_id, stu_name, valid_date, time);
}

__declspec(dllexport) int CreateCard(const char *stu_id, const char *time){
    return cardManager.CreateCard(stu_id, time);
}

__declspec(dllexport) int DeleteAccount(const char *stu_id, const char *time) {
    return cardManager.DeleteAccount(stu_id, time);
}

__declspec(dllexport) int LockAccount(const char *stu_id, const char *time) {
    return cardManager.LockAccount(stu_id, time);
}

__declspec(dllexport) int UnLockAccount(const char *stu_id, const char *time) {
    return cardManager.UnLockAccount(stu_id, time);
}

__declspec(dllexport) int ChargeMoney(const char *stu_id, int new_money, const char *time) {
    return cardManager.ChargeMoney(stu_id, new_money, time);
}

__declspec(dllexport) account *GetInfoByStuId(const char *stu_id) {
    return cardManager.GetInfoByStuId(stu_id);
}
__declspec(dllexport) char *SearchByStuId(const char *patten) {
    return cardManager.SearchByStuId(patten);
}

__declspec(dllexport) void m_free(char *ptr) {
    free(ptr);
}

__declspec(dllexport) void registerPos(int pos_id, int current_log_size){
    posManager.registerPos(pos_id, current_log_size);
}

__declspec(dllexport) int Pay(int pos_id, const char *card_id, const char *date, const char *time, int amount, const char* password){
    std::cout << card_id<< "|" << date<< "|" << time<< "|" << amount << std::endl;
    return posManager.Pay(pos_id, card_id, date, time, amount, password);
}

__declspec(dllexport) char* GetLog(int pos_id, int size){
    return posManager.GetLog(pos_id, size);
}

__declspec(dllexport) int loadAll(){
    return batchManager.loadAll();
}
std::vector<pay_info*> analyzer_merge_result;
__declspec(dllexport) int analyzer_merge(int sort_by){
    analyzer_merge_result = analyzer.merge_k(sort_by);
    std::hash<std::string> hash_fn;
    std::ofstream outfile("analyze_merge.txt");
    std::ofstream outfile_check("analyze_merge_check.txt");
    for(int i = 0; i < analyzer_merge_result.size(); i++){
        auto iter = cardManager.CardIdMap.find(analyzer_merge_result[i]->card_id);
        std::string stu_id, stu_name;
        if(iter != cardManager.CardIdMap.end()){
            stu_id = iter->second->stu_id;
            stu_name = iter->second->stu_name;
        }
        std::stringstream ss;
        ss << analyzer_merge_result[i]->card_id << "|" << analyzer_merge_result[i]->amount << "|" << analyzer_merge_result[i]->status_code << "|" << analyzer_merge_result[i]->current_money << "|" << analyzer_merge_result[i]->date<< "|"<< analyzer_merge_result[i]->time << "|" << stu_id <<"|"<<stu_name<<"\n";
        outfile << ss.str();
        outfile_check << hash_fn(ss.str()) << "\n";
    }
    outfile.close();
    outfile_check.close();
    system("certutil -hashfile analyze_merge_check.txt SHA256 > analyze_merge_check_hash.txt");
    return 0;
}

__declspec(dllexport) int get_merge_data_by_stu_id(const char* stu_id_patten){
    std::string patten_str;
    patten_str.assign(stu_id_patten, strlen(stu_id_patten));
    std::ofstream outfile("analyze_merge_by_stu_id.txt");
    unsigned long long index;
    while ((index = patten_str.find('?')) != std::string::npos) {
        patten_str.replace(index, 1, "(.{0,1})");
    }
    while ((index = patten_str.find('*')) != std::string::npos) {
        patten_str.replace(index, 1, "(.{0,})");
    }
    std::regex patten_re(patten_str);
    for(int i=0;i<analyzer_merge_result.size();i++){
        auto _iter = cardManager.CardIdMap.find(analyzer_merge_result[i]->card_id);
        std::string stu_id, stu_name;
        if(_iter != cardManager.CardIdMap.end()){
            stu_id = _iter->second->stu_id;
            stu_name = _iter->second->stu_name;
        }
        if(std::regex_match(stu_id, patten_re)){
            outfile << analyzer_merge_result[i]->card_id << "|" << analyzer_merge_result[i]->amount << "|" << analyzer_merge_result[i]->status_code << "|" << analyzer_merge_result[i]->current_money << "|" << analyzer_merge_result[i]->date<< "|"<< analyzer_merge_result[i]->time << "|" << stu_id <<"|"<<stu_name<<"\n";
        }
    }
    outfile.close();
    return 0;
}

__declspec(dllexport) int get_merge_data_by_stu_name(const char* stu_name_patten){
    std::string patten_str;
    patten_str.assign(stu_name_patten, strlen(stu_name_patten));
    std::ofstream outfile("analyze_merge_by_stu_name.txt");
    unsigned long long index;
    while ((index = patten_str.find('?')) != std::string::npos) {
        patten_str.replace(index, 1, "(.{0,3})");
    }
    while ((index = patten_str.find('*')) != std::string::npos) {
        patten_str.replace(index, 1, "(.{0,})");
    }
    std::regex patten_re(patten_str);
    for(int i=0;i<analyzer_merge_result.size();i++){
        auto _iter = cardManager.CardIdMap.find(analyzer_merge_result[i]->card_id);
        std::string stu_name, stu_id;
        if(_iter != cardManager.CardIdMap.end()){
            stu_name = _iter->second->stu_name;
            stu_id = _iter->second->stu_id;
        }
        if(std::regex_match(stu_name, patten_re)){
            outfile << analyzer_merge_result[i]->card_id << "|" << analyzer_merge_result[i]->amount << "|" << analyzer_merge_result[i]->status_code << "|" << analyzer_merge_result[i]->current_money << "|" << analyzer_merge_result[i]->date<< "|"<< analyzer_merge_result[i]->time << "|" << stu_id <<"|"<<stu_name<<"\n";
        }
    }
    outfile.close();
    return 0;
}

__declspec(dllexport) int get_merge_data_by_date_range(const char* start_date, const char* end_date){
    std::ofstream outfile("analyze_merge_by_date_range.txt");
    std::string start_date_str(start_date), end_date_str(end_date);
    std::cout << start_date_str << " " << end_date_str << std::endl;
    for(int i=0;i<analyzer_merge_result.size();i++){
        if (analyzer_merge_result[i]->date >= start_date && analyzer_merge_result[i]->date <= end_date) {
            auto _iter = cardManager.CardIdMap.find(analyzer_merge_result[i]->card_id);
            std::string stu_id, stu_name;
            if(_iter != cardManager.CardIdMap.end()){
                stu_id = _iter->second->stu_id;
                stu_name = _iter->second->stu_name;
            }
            outfile << analyzer_merge_result[i]->card_id << "|" << analyzer_merge_result[i]->amount << "|" << analyzer_merge_result[i]->status_code << "|" << analyzer_merge_result[i]->current_money << "|" << analyzer_merge_result[i]->date<< "|"<< analyzer_merge_result[i]->time << "|" << stu_id <<"|"<<stu_name<<"\n";
        }
    }
    outfile.close();
    return 0;
}

__declspec(dllexport) void _flush(){
    cardManager.logger._flush();
}

__declspec(dllexport) char* find_friends(const char* stu_id){
    std::vector<std::string> res;
    std::string string_builder;
    res = batchManager.find_friends(stu_id);
    for(auto & re : res){
        string_builder += re;
        string_builder += "|";
    }
    char * res_char = new char[string_builder.length()+1];
    strcpy_s(res_char, string_builder.length()+1, string_builder.c_str());
    return res_char;
}

};


#endif //SMARTCARDMANAGER_LIBMAIN_H
