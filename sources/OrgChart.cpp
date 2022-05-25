#include "OrgChart.hpp"
using namespace ariel;
#include <iostream>
#include <ostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <string>
#include <vector>
using namespace std;
    
    OrgChart::~OrgChart(){

    }
    //add the head of chart
    OrgChart& OrgChart::add_root(const string& root){
        Node temp;
        temp.data = root;
        temp.father = "";
        temp.left = "";
        temp.middle = "";
        temp.right = "";
        if(this->chart.empty()){
            this->chart.push_back(temp.data);
            this->chart1.push_back(temp);
        }
        else{
            this->chart.at(0)= temp.data;
            temp.father = this->chart1.at(0).father;
            temp.left = this->chart1.at(0).left;
            temp.middle = this->chart1.at(0).middle;
            temp.right = this->chart1.at(0).right;
            this->chart1.at(0)= temp;
        }
        return *this;
    }

    //add sub to the chart
    OrgChart& OrgChart::add_sub(const string& root, const string& sub){
        Node sun;
        sun.data = sub;
        sun.father = root;
        bool indeed = false;
        for(uint i = 0; i<this->chart1.size();i++){
            string tmp = this->chart1.at(i).data;
            if (tmp == root){
                indeed = true;
                if(this->chart1.at(i).left.empty()){
                    this->chart1.at(i).left = sub;
                }
                else if(this->chart1.at(i).middle.empty()){
                    this->chart1.at(i).middle = sub;
                }
                else if(this->chart1.at(i).right.empty()){
                    this->chart1.at(i).right = sub;
                }
                
            }
        }
        if(!indeed){
            throw runtime_error("can't add sub to non exist root...");
        }
        if(this->chart.empty()){
            throw runtime_error("this chart is empty");
        }
        this->chart.push_back(sun.data);
        this->chart1.push_back(sun);
        return *this;
    }


    //IO stream operators
    ostream& ariel::operator<< (ostream& output, const OrgChart& chart){
        for(uint i = 0; i<chart.chart.size();i++){
            output<<chart.chart.at(i)<<endl;
            output<<"------------"<<endl;
        }
        output<<"end of org"<<endl;
        return output;
    }
    //iterator of the tree with level order
    vector<string>::iterator OrgChart::begin_level_order(){
        set_place();
        vector<string> temp;
        bool same = true;
        for(uint i = 1; i<this->chart1.size();i++){
            if(this->chart1.at(i).data != this->chart1.at(i-1).data){
                same = false;
            }
        }
        if(!same){
            temp.push_back(this->chart.at(0));
            for(uint i = 0; i<this->chart.size();i++){
                for(uint j = i+1; j<this->chart.size();j++){
                    string root = this->chart1.at(i).data;
                    if(this->chart1.at(j).father == root){
                        temp.push_back(this->chart1.at(j).data);
                    }
                }
            }
            this->chart = temp;
        }
        
        this->it = this->chart.begin();
        if(this->chart.empty()){
            throw runtime_error("chart is empty..");
        }
        return this->it;
    }
    //return the end of level_order
    vector<string>::iterator OrgChart::end_level_order(){
        if(this->chart.empty()){
            throw runtime_error("chart is empty..");
        }
        return this->chart.end();
    }

     //iterate reverse level order on the chart
    vector<string>::iterator OrgChart::begin_reverse_order(){
        set_place();
        stack<string> stack;
        queue<string> que;
        vector<string> temp;
        bool same = true;
        for(uint i = 1; i<this->chart1.size();i++){
            if(this->chart1.at(i).data != this->chart1.at(i-1).data){
                same = false;
            }
        }
        if(!same){
            que.push(this->chart.at(0));
            while(!que.empty()){
                string front = que.front();
                que.pop();
                stack.push(front);
                for(uint j = 0; j<this->chart1.size();j++){
                    if(this->chart1.at(j).data == front){
                        if(!this->chart1.at(j).right.empty()){
                            que.push(this->chart1.at(j).right);
                        }
                        if(!this->chart1.at(j).middle.empty()){
                            que.push(this->chart1.at(j).middle);
                        }  
                        if(!this->chart1.at(j).left.empty()){
                            que.push(this->chart1.at(j).left);
                        }
                }
                
            }
        }
            while(!stack.empty()){
                string top = stack.top();
                stack.pop();
                temp.push_back(top);
            }
            this->chart = temp;
        }
        
        
        this->it = this->chart.begin();
        if(this->chart.empty()){
            throw runtime_error("chart is empty..");
        }
        return this->it;
    }
    //return the end of iterator reverse order
    vector<string>::iterator OrgChart::reverse_order(){
        if(this->chart.empty()){
            throw runtime_error("chart is empty..");
        }

        return this->chart.end();
    }

    //iterate pre order on the chart
    vector<string>::iterator OrgChart::begin_preorder(){
        set_place();
        vector<string> temp;
        stack<string> stack;
        bool same = true;
        for(uint i = 1; i<this->chart1.size();i++){
            if(this->chart1.at(i).data != this->chart1.at(i-1).data){
                same = false;
            }
        }
        if(!same){
            stack.push(this->chart1.at(0).data);
            while(!stack.empty()){
                string root = stack.top();
                stack.pop();
                temp.push_back(root);
                for(uint j = 0; j<this->chart1.size();j++){
                    if(this->chart1.at(j).data == root){
                        if(!this->chart1.at(j).right.empty()){
                            stack.push(this->chart1.at(j).right);
                        }
                        if(!this->chart1.at(j).middle.empty()){
                            stack.push(this->chart1.at(j).middle);
                        }
                        if(!this->chart1.at(j).left.empty()){
                            stack.push(this->chart1.at(j).left);
                        }
                    }
                    
                }
            }
            this->chart = temp;
        }
        
        this->it=this->chart.begin();
        if(this->chart.empty()){
            throw runtime_error("chart is empty..");
        }
        return this->it;
    }
    //return the end of iterator
    vector<string>::iterator OrgChart::end_preorder(){
        if(this->chart.empty()){
            throw runtime_error("chart is empty..");
        }
        return this->chart.end();
    }
    // icrement iterator
    vector<string>::iterator OrgChart::operator++(){
        ++this->it;
        return this->it;
    }
    // icrement iterator
    vector<string>::iterator OrgChart::operator++(int){
        vector<string>::iterator tmp = this->it;
        ++this->it;
        return tmp;
    }
    //return the begin of iterator(level order)
    vector<string>::iterator OrgChart::begin(){
        uint place = 0;
        vector<string> temp;
        for (auto it = this->begin_level_order(); it != this->end_level_order(); ++it)
        {
            temp.push_back(*it);
        }
        this->chart = temp;
        this->it = this->chart.begin();
        return this->it;
    }
    //return the end of iterator
    vector<string>::iterator OrgChart::end(){
        return this->chart.end();
    }
    //return pointer to the letter
    string* OrgChart::operator->(){
        return &(*this->it);
    }
    //return pointer to the letter
    string OrgChart::operator*(){
        return *this->it;
    }
    //return the size of the letter
    int OrgChart::size(){
        return this->chart.at(this->place++).size();
    }
    //return the size of the letter
    int OrgChart::length(){
        return this->chart.at(this->place++).size();
    }

    bool operator!=(const OrgChart& lhs,const string& rhs){
        return false;
    }

    bool operator==(OrgChart& lhs, string& rhs){
        return true;
    }

    bool OrgChart::operator!=(const OrgChart& rhs){
        return this->it != rhs.it;
    }

    bool OrgChart::operator==(const OrgChart& rhs){
        return this->it == rhs.it;
    }
    //zero the count for the length and count function
    void OrgChart::set_place(){
        this->place = 0;
    }