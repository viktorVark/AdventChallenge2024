#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <bits/stdc++.h>
#include <regex>


using namespace std;

void find_occurence(map<int,string>&, string, string);


int main(){
    ifstream inputFile("input.txt");
    string line;
    vector<string> list1;
    string full_memory;

    //filling vectors with instances of mul(num,num)
    while(getline(inputFile, line)){

        //matching regex
        regex words_regex("mul\\([0-9]{1,3},[0-9]{1,3}\\)");
        auto mul_begin = sregex_iterator(line.begin(), line.end(), words_regex);
        auto mul_end = sregex_iterator();
    
        //iterating through regex
        for (sregex_iterator i = mul_begin; i != mul_end; ++i){
            smatch match = *i;
            string match_str = match.str();
            list1.push_back(match_str);
        }

        //compressing into one string
        full_memory += line;
    }
    inputFile.close();



    //extracting numbers and multiplying them into sum
    int num1{0}, num2{0}, sum{0};
    int begin1{0}, end1{0}, begin2{0}, end2{0};
    for(string s: list1){

        //substring of first number
        begin1 = s.find_first_of('(')+1;
        end1 =  s.find_first_of(',')-begin1;
        num1 = stoi(s.substr(begin1,end1));

        //substrig of second number
        begin2 = s.find_first_of(',')+1;
        end2 =  s.find_first_of(')')-begin2;
        num2 = stoi(s.substr(begin2,end2));

        sum += num1 * num2;
    }

    cout << "The sum of all multiplications is: " << sum << endl;

    map<int, string> do_donts;
    map<int, string> multipls;
    vector<int> do_dont_keys;

    //mapping the occurences of do() and don't() in the input
    //map's key is the position of the word in the string
    //map's value is the string value
    find_occurence(do_donts, full_memory, "do()");
    find_occurence(do_donts, full_memory, "don't()");

    //mapping each occurence of the multiplicatiopn
    for(auto d: do_donts){
        do_dont_keys.push_back(d.first);
    }

    //vector of the keys from the do-s and don't-s
    for(string s: list1){
        multipls[full_memory.find(s)] = s;
    }

    //itaraing throught the keys
    int sum_of_enabled{0};
    for(size_t i = 0; i < do_dont_keys.size(); i++){

        //checking if the key's value a do()
        if(do_donts[do_dont_keys[i]] == "do()"){
            if(i+1<do_dont_keys.size()){

                //itarating throught the mul()-s that are between the do() and next value in the map 
                for(auto m: multipls){
                    if(m.first > do_dont_keys[i] && m.first < do_dont_keys[i+1]){
                        begin1 = m.second.find_first_of('(')+1;
                        end1 =  m.second.find_first_of(',')-begin1;
                        num1 = stoi(m.second.substr(begin1,end1));

                        begin2 = m.second.find_first_of(',')+1;
                        end2 =  m.second.find_first_of(')')-begin2;
                        num2 = stoi(m.second.substr(begin2,end2));

                        sum_of_enabled += num1 * num2;
                    }
                }
            }else{

                //case for the last element in the do_dont map
                for(auto m: multipls){
                    if(m.first > do_dont_keys[i]){
                        begin1 = m.second.find_first_of('(')+1;
                        end1 =  m.second.find_first_of(',')-begin1;
                        num1 = stoi(m.second.substr(begin1,end1));

                        begin2 = m.second.find_first_of(',')+1;
                        end2 =  m.second.find_first_of(')')-begin2;
                        num2 = stoi(m.second.substr(begin2,end2));

                        sum_of_enabled += num1 * num2;
                    }
                }
            }
        }
    }

    //itarating through the mul()-s before the first element from the map do_donts
    for(auto m: multipls){
        if(m.first < do_dont_keys[0]){
            begin1 = m.second.find_first_of('(')+1;
            end1 =  m.second.find_first_of(',')-begin1;
            num1 = stoi(m.second.substr(begin1,end1));

            begin2 = m.second.find_first_of(',')+1;
            end2 =  m.second.find_first_of(')')-begin2;
            num2 = stoi(m.second.substr(begin2,end2));

            sum_of_enabled += num1 * num2;
        }
    }

    cout << "The sum of all multiplications that were enabled are: " << sum_of_enabled << endl;

    
}

//finding occurences of a substring in a string
//mapping it's position as key and it's value as value
void find_occurence(map<int,string> &map, string text_search, string to_find){
    int position{0};
    string replace_str;
    while(text_search.find(to_find) != std::string::npos){
        position = text_search.find(to_find);
        map.insert({position, to_find});
        replace_str = string(to_find.size(), 'X');
        text_search.replace(position, to_find.size(), replace_str);
    }
}
