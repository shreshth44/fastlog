#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <queue>
#include <math.h>

typedef struct log_entry{
    int year, month, day, hour, minute, second;
    int user;
    int latency;
    std::string level;
    std::string message;
} log_entry;

void get_logs(std::vector<log_entry>& logs);
void count_per_log_level(const std::vector<log_entry>& logs);
void average_latency(const std::vector<log_entry>& logs);
void top_10_users(const std::vector<log_entry>& logs);
void latency_95th(std::vector<log_entry> logs);

int main(){
    std::vector<log_entry> logs;
    auto start_parse = std::chrono::steady_clock::now(); 
    get_logs(logs);
    auto end_parse = std::chrono::steady_clock::now();
    auto start_counts = std::chrono::steady_clock::now();
    count_per_log_level(logs);
    average_latency(logs);
    latency_95th(logs);
    top_10_users(logs);
    auto end_counts = std::chrono::steady_clock::now();
    auto parsing = std::chrono::duration_cast<std::chrono::milliseconds>(end_parse - start_parse);
    auto counts = std::chrono::duration_cast<std::chrono::milliseconds>(end_counts - start_counts);
    std::cout << "Parsing Time: " << parsing.count() << "ms" << std::endl;
    std::cout << "Counting Time: " << counts.count() << "ms" << std::endl;

    return 0;
}

void get_logs(std::vector<log_entry>& logs){
    std::ifstream inputlog("tc2.log"); //log file to read from, change this for diff files for now
    if (!inputlog.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }
    std::string log_line;
    while(std::getline(inputlog, log_line)){
        std::stringstream ss(log_line);
        log_entry new_log;
        std::string timestamp, user, latency, message;
        ss >> timestamp;
        new_log.year = stoi(timestamp.substr(0, 4));
        new_log.month = stoi(timestamp.substr(5, 2));
        new_log.day = stoi(timestamp.substr(8, 2));
        new_log.hour = stoi(timestamp.substr(11, 2));
        new_log.minute = stoi(timestamp.substr(14, 2));
        new_log.second = stoi(timestamp.substr(17, 2));        
        ss >> new_log.level;
        ss >> user;
        new_log.user = stoi(user.substr(4));
        ss >> latency;
        new_log.latency = stoi(latency.substr(0, latency.size() - 2));
        getline(ss, message);
        new_log.message = message.substr(2, message.size() - 3);
        logs.push_back(new_log);
    }

    inputlog.close();
}

void count_per_log_level(const std::vector<log_entry>& logs){
    std::map<std::string, int> counter;
    for(const log_entry& log : logs){
        counter[log.level]++;
    }
    for(const auto &pair : counter){
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

void average_latency(const std::vector<log_entry>& logs){
    long long total_latency = 0;
    for(const log_entry& log : logs){
        total_latency += log.latency;
    }
    std::cout << "Average Latency: " << (double) total_latency/logs.size() << std::endl;
}

void top_10_users(const std::vector<log_entry>& logs){
    std::unordered_map<int, int> freq;
    for(const log_entry&log : logs){
        freq[log.user]++;
    }
    auto cmp = [&freq](int a, int b){
        return freq[a] > freq[b];
    };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> min_heap(cmp);
    for(const auto& [id, activity] : freq){
        min_heap.push(id);
        if(min_heap.size() > 10){
            min_heap.pop();
        }
    }
    
    std::vector<int> reverse_heap;
    while(!min_heap.empty()){
        reverse_heap.push_back(min_heap.top());
        min_heap.pop();
    }
    std::cout << "Top 10 Users by activity:" << std::endl;
    for(auto it = reverse_heap.rbegin(); it != reverse_heap.rend(); it++){
        std::cout << "user" << *it << ", activity: " << freq[*it] << std::endl;
    }

}

void latency_95th(std::vector<log_entry> logs){
    size_t index = std::ceil(5 * logs.size()/100) - 1;
    std::nth_element(logs.begin(), logs.begin() + index, logs.end(), [](const log_entry&a, const log_entry&b){
        return a.latency > b.latency;
    });
    std::cout << "95th percentile latency: " << logs[index].latency << std::endl;
}