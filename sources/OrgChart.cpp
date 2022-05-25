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
    // OrgChart::OrgChart(){
        
    // }
    OrgChart::~OrgChart(){

    }
    //add the head of chart
    OrgChart& OrgChart::add_root(const string root){
        Node temp;
        temp.data = root;
        temp.father = "";
        temp.left = "";
        temp.middle = "";
        temp.right = "";
        if(this->chart.size() == 0){
            this->chart.push_back(temp.data);
            this->chart1.push_back(temp);
        }
        else{
            this->chart.at(0)= temp.data;
            this->chart1.at(0)= temp;
        }
        return *this;
    }

    //add sub to the head of chart
    OrgChart& OrgChart::add_sub(const string root, const string sub){
        Node sun;
        sun.data = sub;
        sun.father = root;
        bool indeed = false;
        for(uint i = 0; i<this->chart1.size();i++){
            string tmp = this->chart1.at(i).data;
            if (tmp == root){
                indeed = true;
                if(this->chart1.at(i).left == ""){
                    this->chart1.at(i).left = sub;
                }
                else if(this->chart1.at(i).middle == ""){
                    this->chart1.at(i).middle = sub;
                }
                else if(this->chart1.at(i).right == ""){
                    this->chart1.at(i).right = sub;
                }
                
            }
        }
        if(!indeed){
            throw runtime_error("can't add sub to non exist root...");
        }
        if(this->chart.size() == 0){
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

    vector<string>::iterator OrgChart::begin_level_order(){
        uint place = 0;
        int k = 0;
        vector<string> temp;
        vector<int> brothers;
        temp.push_back(this->chart.at(0));
        brothers.push_back(0);
        for(uint i = 0; i<this->chart.size();i++){
            for(uint j = i+1; j<this->chart.size();j++){
                string root = this->chart1.at(i).data;
                if(this->chart1.at(j).father == root){
                    k++;
                    temp.push_back(this->chart1.at(j).data);
                }
            }
        }
        this->chart = temp;
        this->it = this->chart.begin();
        if(this->chart.empty()){
            throw runtime_error("chart is empty..");
        }
        return this->it;
    }
    vector<string>::iterator OrgChart::end_level_order(){
        if(this->chart.empty()){
            throw runtime_error("chart is empty..");
        }
        return this->chart.end();
    }
    vector<string>::iterator OrgChart::begin_reverse_order(){
        uint place = 0;
        stack<string> stack;
        queue<string> que;
        vector<string> temp;
        que.push(this->chart.at(0));
        while(!que.empty()){
            string front = que.front();
            que.pop();
            stack.push(front);
            for(uint j = 0; j<this->chart1.size();j++){
                if(this->chart1.at(j).data == front){
                    if(this->chart1.at(j).right != ""){
                        que.push(this->chart1.at(j).right);
                    }
                    if(this->chart1.at(j).middle != ""){
                        que.push(this->chart1.at(j).middle);
                    }
                    if(this->chart1.at(j).left != ""){
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
        
        this->it = this->chart.begin();
        if(this->chart.empty()){
            throw runtime_error("chart is empty..");
        }
        for(uint i = 0; i<this->chart.size();i++){
            // cout<<"------------"<<endl;
            cout<<this->chart.at(i)<<endl;
        }
        return this->it;
    }

    vector<string>::iterator OrgChart::reverse_order(){
        if(this->chart.empty()){
            throw runtime_error("chart is empty..");
        }

        return this->chart.end();
    }
    vector<string>::iterator OrgChart::begin_preorder(){
        uint place = 0;
        vector<string> temp;
        stack<string> stack;
        stack.push(this->chart1.at(0).data);
        while(!stack.empty()){
            string root = stack.top();
            stack.pop();
            temp.push_back(root);
            for(uint j = 0; j<this->chart1.size();j++){
                if(this->chart1.at(j).data == root){
                    if(this->chart1.at(j).right != ""){
                        stack.push(this->chart1.at(j).right);
                    }
                    if(this->chart1.at(j).middle != ""){
                        stack.push(this->chart1.at(j).middle);
                    }
                    if(this->chart1.at(j).left != ""){
                        stack.push(this->chart1.at(j).left);
                    }
                }
                
            }
        }
        // temp.push_back(this->chart1.at(0).data);
        for(uint i = 0; i<temp.size();i++){
            // cout<<"------------"<<endl;
            cout<<temp.at(i)<<endl;
        }
        this->chart = temp;
        this->it=this->chart.begin();
        if(this->chart.empty()){
            throw runtime_error("chart is empty..");
        }
        return this->it;
    }
    vector<string>::iterator OrgChart::end_preorder(){
        if(this->chart.empty()){
            throw runtime_error("chart is empty..");
        }
        return this->chart.end();
    }

    vector<string>::iterator OrgChart::operator++(){
        ++this->it;
        return this->it;
    }
    vector<string>::iterator OrgChart::operator++(int){
        vector<string>::iterator tmp = this->it;
        ++this->it;
        return tmp;
    }
    vector<string>::iterator OrgChart::begin(){
        uint place = 0;
        this->it = this->chart.begin();
        return this->it;
    }

    vector<string>::iterator OrgChart::end(){
        return this->chart.end();
    }
    string* OrgChart::operator->(){
        return &(*this->it);
    }
    string OrgChart::operator*(){
        return *this->it;
    }
    int OrgChart::size(){
        
        return this->chart.at(place++).size();
    }

    int OrgChart::length(){
        return this->chart.at(place++).size();
    }

    bool operator!=(const OrgChart& lhs,const string& rhs){

        // return (*this != comp);
        return false;
    }

    bool operator==(const OrgChart& lhs, const string& rhs){
        return true;
    }

    bool OrgChart::operator!=(const OrgChart& rhs){

        // return (*this != comp);
        return this->it != rhs.it;
    }

    bool OrgChart::operator==(const OrgChart& rhs){
        return this->it == rhs.it;
    }