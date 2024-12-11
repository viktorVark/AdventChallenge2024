#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <fstream>
#include <bits/stdc++.h>


using namespace std;

bool is_report_safe(vector<int>&);
bool is_report_safe_with_toleration(vector<int>&);


int main(){
    ifstream inputFile("input.txt");
    string line;
    vector<string> list1;

    //filling vectors with numbers
    while(getline(inputFile, line)){
        list1.push_back(line);
    }
    inputFile.close();


    vector<int> report;
    string str;
    int safe_reports{0};
    int safe_reports_with_toleration{0};

    for(string s: list1){
        report.clear();
        stringstream stream(s);
        while(getline(stream, str, ' ')){
            report.push_back(stoi(str));
        }

        if(is_report_safe(report)){
            safe_reports++;
        }

        if(is_report_safe_with_toleration(report)){
            safe_reports_with_toleration++;
        }
    }

    cout << "Number of safe reports is: " << to_string(safe_reports) << endl;
    cout << "Number of safe reports with toleration is: " << to_string(safe_reports_with_toleration) << endl;
}

bool is_report_safe(vector<int> &rep){
    bool is_next_greater = false; 
    bool is_next_lesser = false; 

    if(rep.at(0) > rep.at(1) && rep.at(0) - rep.at(1) <= 3){
        
        for(size_t i = 1; i < rep.size(); i++){
            is_next_lesser = (rep.at(i-1) > rep.at(i) && rep.at(i-1) - rep.at(i) <= 3);
            if(!is_next_lesser){
                return false;
            }
        }

    }else if(rep.at(0) < rep.at(1) && rep.at(1) - rep.at(0) <= 3){
        for(size_t i = 1; i < rep.size(); i++){
            is_next_greater = (rep.at(i-1) < rep.at(i) && rep.at(i) - rep.at(i-1) <= 3);
            if(!is_next_greater){
                return false;
            }
        }
    }else{
        return false;
    }

    return true;
}

bool is_report_safe_with_toleration(vector<int> &rep){
    bool is_next_greater = false; 
    bool is_next_lesser = false; 
    bool tolerated_once = false;
    bool to_skip = false;
    bool is_safe = true;

        
    for(size_t i = 1; i < rep.size(); i++){
        is_next_lesser = (rep.at(i-1) > rep.at(i) && rep.at(i-1) - rep.at(i) <= 3);
        if(to_skip){
            to_skip = false;
            continue;
        }

        if(!is_next_lesser){
            if(!tolerated_once && i+1 >= rep.size() ){
                continue;
            }
            else if(!tolerated_once && (rep.at(i-1) > rep.at(i+1) && rep.at(i-1) - rep.at(i+1) <= 3))
            {
                to_skip = true;
                tolerated_once = true;
                continue;
            }else{
                is_safe = false;
                break;
            }
        }

        is_safe=true;
    }

    if(is_safe)
        return true;

    tolerated_once = false;
    to_skip = false;

    for(size_t i = 1; i < rep.size(); i++){
        is_next_greater = (rep.at(i-1) < rep.at(i) && rep.at(i) - rep.at(i-1) <= 3);
        if(to_skip){
            to_skip = false;
            continue;
        }

        if(!is_next_greater){
            if(!tolerated_once && i+1 >= rep.size() ){
                continue;
            }
            else if (!tolerated_once && (rep.at(i-1) < rep.at(i+1) && rep.at(i+1) - rep.at(i-1) <= 3))
            {
                tolerated_once = true;
                to_skip = true;
                continue;
            }else{
                is_safe = false;
                break;
            }
        }

        is_safe=true;
    }


    return is_safe;
}

