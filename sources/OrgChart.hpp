#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "Node.cpp"
using namespace std;
#include <iterator>
namespace ariel{
    class OrgChart{
    private:
        vector<string> chart;
        vector<Node> chart1;
        vector<string>::iterator it;
        uint place = 0;
    public:
        OrgChart(){

        }
        OrgChart(const OrgChart&) =delete;
        OrgChart& operator =(const OrgChart&)=delete;
        OrgChart(OrgChart&&) = delete;
        OrgChart& operator=(OrgChart&&) = delete;
        ~OrgChart();
        int size();
        int length();
        OrgChart& add_root(const string& root);
        OrgChart& add_sub(const string& root, const string& sub);
        vector<string>::iterator begin();
        vector<string>::iterator end();
        vector<string>::iterator begin_level_order();
        vector<string>::iterator end_level_order();
        vector<string>::iterator begin_reverse_order();
        vector<string>::iterator reverse_order();
        vector<string>::iterator begin_preorder();
        vector<string>::iterator end_preorder();
        vector<string>::iterator operator++();
        vector<string>::iterator operator++(int);
        string operator*();
        friend bool operator!=(OrgChart lhs,string& rhs);
        friend bool operator==(OrgChart lhs,string& rhs);
        bool operator!=(const OrgChart& rhs);
        bool operator==(const OrgChart& rhs);
        string* operator->();
        void set_place();
        friend ostream& operator<< (ostream& output, const OrgChart& chart);
        
    };

}
