#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <regex>


using namespace std;

int count_by_regex(string, string);
int num_of_occurences(string&, string);



int main(){
    ifstream inputFile("input.txt");
    string line;
    vector<string> list_lines;
    string full_string;
    int num_of_xmas{0};

    //filling vectors with each line from input
    //concatenating string with each line
    while(getline(inputFile, line)){
        list_lines.push_back(line);
        full_string +=  line + ";";
    }
    inputFile.close();

    //number of horizontal XMAS formards and backwards
    //num_of_xmas += count_by_regex(full_string, "XMAS|SAMX");
    num_of_xmas += num_of_occurences(full_string, "XMAS");
    num_of_xmas += num_of_occurences(full_string, "SAMX");

    cout << "Number of horizontal XMAS " << num_of_xmas << "\n";

    string vertical_xmas;

    //counting number of vertical XMAS forwards and backwards
    for(size_t i {3}; i < list_lines.size(); i++){
        for(size_t j {0}; j < list_lines.at(i).size(); j++){
            vertical_xmas.clear();
            //concatenating string with letters in the same column
            vertical_xmas += list_lines.at(i).at(j); 
            vertical_xmas += list_lines.at(i-1).at(j);
            vertical_xmas += list_lines.at(i-2).at(j);
            vertical_xmas += list_lines.at(i-3).at(j);


            if(vertical_xmas == "XMAS" || vertical_xmas == "SAMX"){
                num_of_xmas++;
            }
        }
    }
    
    cout << "Number of horizontal and vertical XMAS " << num_of_xmas << "\n";

    string right_diagonal;

    //counting number of right diagonal (/) XMAS forwards and backwards
    for(size_t i {3}; i < list_lines.size(); i++){
        for(size_t j {3}; j < list_lines.at(i).size(); j++){
            right_diagonal.clear();
            //concatenating string with letters diagonally
            right_diagonal += list_lines.at(i).at(j-3); 
            right_diagonal += list_lines.at(i-1).at(j-2);
            right_diagonal += list_lines.at(i-2).at(j-1);
            right_diagonal += list_lines.at(i-3).at(j);


            if(right_diagonal == "XMAS" || right_diagonal == "SAMX"){
                num_of_xmas++;
            }
        }
    }
    
    cout << "Number of horizontal, vertical and right diagonal XMAS " << num_of_xmas << "\n";

    string left_diagonal;

    //counting number of left diagonal (\) XMAS forwards and backwards
    for(size_t i {3}; i < list_lines.size(); i++){
        for(size_t j {3}; j < list_lines.at(i).size(); j++){
            left_diagonal.clear();
            //concatenating string with letters diagonally
            left_diagonal += list_lines.at(i-3).at(j-3); 
            left_diagonal += list_lines.at(i-2).at(j-2);
            left_diagonal += list_lines.at(i-1).at(j-1);
            left_diagonal += list_lines.at(i).at(j);


            if(left_diagonal == "XMAS" || left_diagonal == "SAMX"){
                num_of_xmas++;
            }
        }
    }
    
    cout << "Number of horizontal, vertical, right and left diagonal XMAS " << num_of_xmas << "\n";


    string mas_diagonal_1, mas_diagonal_2;
    int num_X_mas{0};

    //counting number of left diagonal (\) XMAS forwards and backwards
    for(size_t i {2}; i < list_lines.size(); i++){
        for(size_t j {2}; j < list_lines.at(i).size(); j++){
            mas_diagonal_1.clear();
            mas_diagonal_2.clear();

            //concatenating string with letters diagonally
            mas_diagonal_1 += list_lines.at(i).at(j); 
            mas_diagonal_1 += list_lines.at(i-1).at(j-1);
            mas_diagonal_1 += list_lines.at(i-2).at(j-2);


            mas_diagonal_2 += list_lines.at(i).at(j-2);
            mas_diagonal_2 += list_lines.at(i-1).at(j-1);
            mas_diagonal_2 += list_lines.at(i-2).at(j);


            if((mas_diagonal_1 == "MAS" || mas_diagonal_1 == "SAM") && (mas_diagonal_2 == "MAS" || mas_diagonal_2 == "SAM")){
                num_X_mas++;
            }
        }
    }
    
    cout << "Number of X-MAS " << num_X_mas << "\n";
}


//counting number of apperences in a string with regex
int count_by_regex(string search_string, string regex_string){
    int count{0};
    //matching regex
    regex words_regex(regex_string);
    auto mul_begin = sregex_iterator(search_string.begin(), search_string.end(), words_regex);
    auto mul_end = sregex_iterator();

    //iterating through regex
    for (sregex_iterator i = mul_begin; i != mul_end; ++i){
        smatch match = *i;
        string match_str = match.str();
        count++;
    }

    return count;
}


int num_of_occurences(string &search_string, string find_string){
    int num_of_occur{0};
    for(size_t i = 0; i < search_string.size(); i++){
        if(search_string.substr(i, find_string.size()) == find_string)
        {
            num_of_occur++;
        }
    }

    return num_of_occur;
}
