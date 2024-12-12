#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <bits/stdc++.h>
#include <algorithm>



using namespace std;

bool is_right_order(map<string, vector<string>>&, vector<string>&);
vector<string> ordering_pages(map<string, vector<string>>&, vector<string>&);


int main(){
    ifstream inputFile("input_pages.txt");
    ifstream pageOrderFile("page_orders.txt");
    string line;

    map<string, vector<string>> page_weights;
    string order_rule, page_update; 
    vector<vector<string>> page_orders;


    //filling map with key of page ordering rules
    //and value of vectors of page order updates
    while(getline(inputFile, line)){
        order_rule = line.substr(0, line.find('|'));
        page_update = line.substr(line.find('|')+1, line.size()-order_rule.size()-1);
        if(page_weights.count(order_rule) == 0){
            page_weights[order_rule] = vector<string>{page_update};
        }else{
            page_weights[order_rule].push_back(page_update);
        }

    }
    inputFile.close();

    //filling vector with all of the page orders
    size_t counter{0};
    int pos{0};
    while(getline(pageOrderFile, line)){
        page_orders.push_back(vector<string>{});
        while((pos = line.find(',')) != string::npos){
            page_orders.at(counter).push_back(line.substr(0, pos));
            line.erase(0, pos+1);
        }
        page_orders.at(counter).push_back(line);
        counter++;
    }
    pageOrderFile.close();


    //finding indecies of orders that are correct
    vector<size_t> true_oreders, false_orders;
    for(size_t c{0}; c<page_orders.size(); c++){
        if(is_right_order(page_weights,page_orders.at(c))){
            //appending vector with the index of the page order
            true_oreders.push_back(c);
        }
        else{
            false_orders.push_back(c);
        }
    }

    //going through page orders that are true
    int sum_of_middle{0};
    for(size_t o{0}; o<true_oreders.size(); o++){
        auto curr_page_ord = page_orders.at(true_oreders.at(o));
        auto middle_index = ((curr_page_ord).size()-1)/2;

        //adding the middle number to sum
        sum_of_middle += stoi(curr_page_ord.at(middle_index));

    }

    cout<<"Sum of the middle pages " << sum_of_middle << endl;

    vector<vector<string>> wrong_page_orders;
    for(auto f: false_orders){
        wrong_page_orders.push_back(page_orders.at(f));
    }

    vector<vector<string>> updated_order;
    for(size_t c{0}; c<wrong_page_orders.size(); c++){
        updated_order.push_back(ordering_pages(page_weights, wrong_page_orders.at(c)));
    }

    int middle_index{0}, middle_num{0};
    //going through page orders that are true
    int sum_of_middle_corrected{0};
    for(auto w: updated_order){
        middle_index = (w.size())/2;
        middle_num = stoi(w.at(middle_index));
        //adding the middle number to sum
        sum_of_middle_corrected += middle_num;

    }

    cout<<"Sum of the corrected middle pages " << sum_of_middle_corrected << endl;
}

//finding if page orders are correct
bool is_right_order(map<string, vector<string>> &pages, vector<string> &orders){
    bool is_right = false;
    vector<string>::iterator order_begin, order_end;

    //going number by number in vector of page orders
    for(size_t i {0}; i < orders.size()-1; i++){
        //picking map element by key
        order_begin = pages.at(orders.at(i)).begin();
        order_end = pages.at(orders.at(i)).end();

        //iterating through ech next number
        for(size_t j{i+1}; j < orders.size()-i-1; j++){

            //checking if next number is in the map with key of given page number
            if(find(order_begin, order_end, orders.at(j)) != order_end){
                is_right = true;
            }else{

                //instant false if not in map
                return false;
            }
        }
    }
    return is_right;
}


vector<string> ordering_pages(map<string, vector<string>> &pages, vector<string> &orders){
    vector<string>::iterator order_begin, order_end;
    string temp_page;

    //going number by number in vector of page orders
    for(size_t i {0}; i < orders.size()-1; i++){
        

        //iterating through ech next number
        for(size_t j{i+1}; j < orders.size(); j++){
            //picking map element by key
            order_begin = pages.at(orders.at(i)).begin();
            order_end = pages.at(orders.at(i)).end();
            //checking if next number is in the map with key of given page number
            if(find(order_begin, order_end, orders.at(j)) == order_end){
                //changing order of numbers
                temp_page = orders.at(j);
                orders.erase(orders.begin()+j);
                orders.insert(orders.begin()+i,temp_page);
                i--;
                break;
            }
        }
    }

    return orders;
}
