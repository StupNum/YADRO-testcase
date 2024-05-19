#include "GameClub.h"

#include <algorithm>
#include <iostream>
#include "common.h"

GameClub::GameClub() : table_list(), client_list(), table_usage(), table_revenue(),
        table_count(0), opening_time(), closing_time(), price(0) {}

bool GameClub::ClientComing(Time time, std::string client_name) {
    if (opening_time > time) {
        ProceedError(time, "NotOpenYet");
        return false;
    }

    if (client_list.find(client_name) != client_list.end()) {
        ProceedError(time, "YouShallNotPass");
        return false;
    }

    client_list.insert({ client_name, -1 });

}

bool GameClub::Client2Table(Time time, std::string client_name, int table_id) {
    if (client_list.find(client_name) == client_list.end()) {
        ProceedError(time, "ClientUnknown");
        return false;
    }
    if (!table_list[table_id - 1].first.empty()) {
        ProceedError(time, "PlaceIsBusy");
        return false;
    }

    //если стол свободен тогда 
    //2 случая, если клиент уже за столом, или если не за столом
    else {
        if (client_list[client_name] > -1) { // уже за столом
            //освобождение текущего стола
            FreeTable(time, client_list[client_name] - 1);

            //пересадка
            table_list[table_id - 1].first = client_name;
            table_list[table_id - 1].second = time;
        }


        else { //еще не за столом
            table_list[table_id - 1].first = client_name;
            table_list[table_id - 1].second = time;
        }

        client_list[client_name] = table_id;

    }
    return true;
}

bool GameClub::FreeTable(Time time, int table_id) {
    //расчет стоимости и времени
    Time diff_time = time - table_list[table_id - 1].second;
    table_usage[table_id - 1] = table_usage[table_id - 1] + diff_time;
    table_revenue[table_id - 1] += diff_time.GetRoundedHours() * price;
    //освобождение
    table_list[table_id - 1].first = "";
    table_list[table_id - 1].second = Time();
    return true;
}

bool GameClub::ClientWaiting(Time time, std::string client_name) {
    if (GetFreeTable() > -1) {
        ProceedError(time, "ICanWaitNoLonger!");
        return false;
    }

    //подсчет клиентов в очереди
    size_t count = 0;
    for (const auto& [key, value] : client_list) {
        if (value == -1)
            count++;
    }

    if (count > table_count) {
        OutgoingClientLeaves(time, client_name);
    }
    return true;
}

bool GameClub::Close() {
    std::vector<std::pair<std::string, int>> client_vector;

    // Копирование элементов из unordered_map в вектор
    for (const auto& client : client_list) {
        client_vector.push_back(client);
    }

    // Сортировка вектора в алфавитном порядке
    std::sort(client_vector.begin(), client_vector.end(),
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.first < b.first;
        });

    // Вывод или использование отсортированного вектора
    for (const auto& client : client_vector) {
        if (client.second != -1) {
            FreeTable(closing_time, client.second);
        }
        OutgoingClientLeaves(closing_time, client.first);
    }




    return true;
}

bool GameClub::IncomingClientLeaves(Time time, std::string client_name) { //id4
    if (client_list.find(client_name) == client_list.end()) {
        ProceedError(time, "ClientUnknown");
        return false;
    }

    if (client_list[client_name] != -1) {
        FreeTable(time, client_list[client_name]);
        for (const auto& [key, value] : client_list) {
            if (value == -1) {
                Client2Table(time, key, client_list[client_name]);
                std::cout << time << ' ' << 12 << ' ' << key << ' ' << client_list[client_name] << '\n';
                break;
            }
        }
    }
    client_list.erase(client_name);
    return true;
}

void GameClub::OutgoingClientLeaves(Time time, std::string client_name) { //id11
    std::cout << time << ' ' << 11 << ' ' << client_name << '\n';
    client_list.erase(client_name);
}


void GameClub::ProceedError(Time time, std::string error) {
    std::cout << time << ' ' << 13 << ' ' << error << '\n';
}

//возвращает -1 если свободного стола не или индекс первого свободного стола
long long GameClub::GetFreeTable() const {
    for (size_t i = 0; i < table_list.size(); i++) {
        if (table_list[i].first.empty())
            return i;
    }
    return -1;
}



void GameClub::ProccessFileInfo(GameClub& GC, FileHandler& FH) {
    if (!FH.ReadFile())
        throw std::runtime_error("File opening error!\n");

    auto lines = FH.GetFileContent();
    auto index = FH.ValidateInput();
    if (index == -2) {
        throw std::runtime_error("Incorrect input!\n");
    }
    if (index != -1) {
        throw std::runtime_error(vec2string(lines[index]));
    }

    GC.table_count = std::stoi(lines[0][0]);
    GC.opening_time = Time(lines[1][0]);
    GC.closing_time = Time(lines[1][1]);
    GC.price = std::stoi(lines[2][0]);

    GC.table_list = std::vector<std::pair<std::string, Time>>(GC.table_count);
    GC.table_usage = std::vector<Time>(GC.table_count);
    GC.table_revenue = std::vector<int>(GC.table_count);

    std::vector<std::string> line;

    std::cout << GC.opening_time << '\n';
    for (size_t i = 3; i < lines.size(); i++) {
        line = lines[i];
        std::cout << vec2string(line) << '\n';
        switch (std::stoi(line[1])) {
        case 1:
            GC.ClientComing(Time(line[0]), line[2]);
            break;
        case 2:
            GC.Client2Table(Time(line[0]), line[2], std::stoi(line[3]));
            break;
        case 3:
            GC.ClientWaiting(Time(line[0]), line[2]);
            break;
        case 4:
            GC.IncomingClientLeaves(Time(line[0]), line[2]);
            break;
        }
    }
    GC.Close();
    std::cout << GC.closing_time << '\n';
    for (size_t i = 0; i < GC.table_count; i++) {
        std::cout << i + 1 << ' ' << GC.table_revenue[i] << ' ' << GC.table_usage[i] << '\n';
    }
}
