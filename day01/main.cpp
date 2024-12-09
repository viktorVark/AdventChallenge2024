#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <fstream>
#include <bits/stdc++.h>


using namespace std;

int difference(int&,int&);
int num_of_occurences(string&, string&);

int main(){
    ifstream inputFile("input.txt");
    string line;
    vector<int> list1, list2;
    int num1{0}, num2{0};
    int total_distance{0};

    //filling vectors with numbers
    while(getline(inputFile, line)){
        num1 = stoi(line.substr(0, line.find(' ')));
        list1.push_back(num1);
        
        num2 = stoi(line.substr(line.find_last_of(' ')+1, line.size()-1));
        list2.push_back(num2);
    }
    inputFile.close();

    //sort lists
    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());

    //calculating the total distance
    for(size_t i{0}; i<list1.size(); i++){
        total_distance += difference(list1.at(i), list2.at(i));
    }

    cout << "The total distence between the lists is: " << to_string(total_distance) << endl;

    string search_list;

    for(int num: list2){
        search_list += to_string(num) + ";";
    }

    int similarity_score{0};
    for(int num: list1){
        string num_str = to_string(num);
        similarity_score += num * num_of_occurences(search_list, num_str);
    }

    cout << "The similarity score between the lists is: " << to_string(similarity_score) << endl;


}

//function for calculating the difference between two integers
int difference(int &num1, int &num2){
    int diff = num1 - num2;
    if(diff<0)
        return -diff;
    
    return diff;
}

int num_of_occurences(string &search_string, string &find_string){
    int num_of_occur{0};
    for(size_t i = 0; i < search_string.size(); i++){
        if(search_string.substr(i, find_string.size()) == find_string)
        {
            num_of_occur++;
        }
    }

    return num_of_occur;
}