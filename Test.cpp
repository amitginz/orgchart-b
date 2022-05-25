/**
 *
 * AUTHORS: amit ginzberg
 * 
 * Date: 2021-05
 */
#include "doctest.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;
#include <vector>
#include "OrgChart.hpp"
using namespace ariel;

TEST_CASE("checkthrow-goodinput"){
    OrgChart org;
    OrgChart org1;
        CHECK_NOTHROW(org.add_root("mark zukerberg"));
        CHECK_NOTHROW(org.add_sub("mark zukerberg","amit"));
        CHECK_NOTHROW(org1.add_root("bill gatizs"));
        CHECK_NOTHROW(org.add_sub("mark zukerberg","mayan"));
        CHECK_NOTHROW(bool temp = (org!=org1));
        CHECK_NOTHROW(bool temp = (org1!=org));
        CHECK_NOTHROW(org.add_sub("mark zukerberg","amit"));//we dont have node as aylon mask in org1
        CHECK_NOTHROW(org.add_sub("mark zukerberg","amit"));
        CHECK_NOTHROW(org1.add_sub("bill gatiz","YONI"));//wehave node as bill gatiz in org
        CHECK_NOTHROW(org1.add_sub("bill gatizs","arik"));
        CHECK_NOTHROW(org1.add_sub("bill gatizs","amit"));//add to ufind root
        CHECK_NOTHROW(org1.add_sub("bill gatizs","may"));
}

TEST_CASE("checkthrow-badinput"){
    OrgChart org;
    OrgChart org1;
        CHECK_NOTHROW(org.add_root("mark zukerberg"));
        CHECK_NOTHROW(org1.add_root("bill gatizs"));
        CHECK_THROWS(org.add_sub("aylon mask","amit"));//we dont have node as aylon mask in org1
        CHECK_THROWS(org.add_sub("alylon mask","amit"));
        CHECK_THROWS(org1.add_sub("alylon mask","amit"));//we dont have node as aylon mask in org1
        CHECK_NOTHROW(org1.add_sub("bill gatizs","haim"));
        CHECK_THROWS(org1.add_sub("aviv","amit"));//add to ufind root
        CHECK_THROWS(org1.add_sub("aviv","arik"));
        CHECK_THROWS(org1.add_sub("haim","arik"));
        CHECK_THROWS(org1.add_sub("shalom","amit"));//add to ufind root
        CHECK_THROWS(org1.add_sub("shlomo","arik"));
        CHECK_THROWS(org1.add_sub("rik","amit"));//add to ufind root
        CHECK_THROWS(org1.add_sub("morty","arik"));
}

TEST_CASE("checknothrow-comperators"){
    OrgChart org;
    OrgChart org1;
        org.add_root("mark zukerberg");
        org1.add_root("bill gatizs");
        CHECK_NOTHROW(bool temp = (org!=org1));
        CHECK_NOTHROW(bool temp = (org1!=org));
    OrgChart org2;
    OrgChart org3;
        org2.add_root("mark zukerberg");
        org3.add_root("mark zukerberg");
        CHECK_NOTHROW(bool temp = (org2!=org3));
        CHECK_NOTHROW(bool temp = (org1!=org2));
        CHECK_NOTHROW(bool temp = (org1!=org3));
}


TEST_CASE("check ->size()"){
    OrgChart organization;
    organization.add_root("CEO")
      .add_sub("CEO", "CTO")         // Now the CTO is subordinate to the CEO
      .add_sub("CEO", "CFO")         // Now the CFO is subordinate to the CEO
      .add_sub("CEO", "COO")         // Now the COO is subordinate to the CEO
      .add_sub("CTO", "VP_SW") // Now the VP Software is subordinate to the CTO
      .add_sub("COO", "VP_BI");      // Now the VP_BI is subordinate to the COO
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK_NOTHROW( cout << it->size() << " " );
        // CHECK(it->size() == 3);
        // CHECK(it->size() != 5);
    } // prints: 3 3 3 3 5 5
    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it)
    {
        CHECK_NOTHROW( cout << it->size() << " " );
        // CHECK(it->size() == 3);
        // CHECK(it->size() != 5);
    }
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
    {
        CHECK_NOTHROW( cout << it->size() << " " );
        // CHECK(it->size() == 3);
        // CHECK(it->size() != 5);
    }
}







