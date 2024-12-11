#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <bits/stdc++.h>
#include <regex>


using namespace std;


int main(){
    ifstream inputFile("input.txt");
    string line;
    vector<string> list1;
    string full_memory;

    //filling vectors with numbers
    while(getline(inputFile, line)){
        regex words_regex("mul\\([0-9]{1,3},[0-9]{1,3}\\)");
        auto mul_begin = sregex_iterator(line.begin(), line.end(), words_regex);
        auto mul_end = sregex_iterator();
 
        for (sregex_iterator i = mul_begin; i != mul_end; ++i){
            smatch match = *i;
            string match_str = match.str();
            list1.push_back(match_str);
        }

        full_memory += line;
    }
    inputFile.close();

    int num1{0}, num2{0}, sum{0};
    int begin1{0}, end1{0}, begin2{0}, end2{0};
    for(string s: list1){
        begin1 = s.find_first_of('(')+1;
        end1 =  s.find_first_of(',')-begin1;
        num1 = stoi(s.substr(begin1,end1));

        begin2 = s.find_first_of(',')+1;
        end2 =  s.find_first_of(')')-begin2;
        num2 = stoi(s.substr(begin2,end2));

        sum += num1 * num2;
    }

    cout << "The sum of all multiplications is: " << sum << endl;


    regex words_regex("mul\\([0-9]{1,3},[0-9]{1,3}\\)");
    auto mul_begin = sregex_iterator(full_memory.begin(), full_memory.end(), words_regex);
    auto mul_end = sregex_iterator();

    for (sregex_iterator i = mul_begin; i != mul_end; ++i){
        smatch match = *i;
        string match_str = match.str();
        list1.push_back(match_str);
    }
}