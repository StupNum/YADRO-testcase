#ifndef GAMECLUB_H
#define GAMECLUB_H


#include <string>
#include <unordered_map>
#include "Time.h"
#include "FileHandler.h"



class GameClub {
public:

    GameClub();

    bool ClientComing(Time time, std::string client_name);

    bool Client2Table(Time time, std::string client_name, int table_id);

    bool FreeTable(Time time, int table_id);

    bool ClientWaiting(Time time, std::string client_name);

    bool Close();

    bool IncomingClientLeaves(Time time, std::string client_name);

    void OutgoingClientLeaves(Time time, std::string client_name);

    void ProceedError(Time time, std::string error);

    long long GetFreeTable() const;

    static void ProccessFileInfo(GameClub& GC, FileHandler& FH);

private:
    std::vector<std::pair<std::string, Time>> table_list;
    std::unordered_map<std::string, int> client_list;
    std::vector<Time> table_usage;
    std::vector<int> table_revenue;
    int table_count;
    Time opening_time, closing_time;
    int price;
};

#endif // GAMECLUB_H