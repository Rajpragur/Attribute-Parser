#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
using namespace std;
vector<int> spaces(string s){
    vector<int> spaces;
    for (int i = 0 ;i<s.length() ; i++) {
        if(s[i] == ' '){
            spaces.push_back(i);
        } else{
            continue;
        }
    }
    return spaces;
}
vector<int> equals(string s){
    vector<int> spaces;
    for (int i = 0 ;i<s.length() ; i++) {
        if(s[i] == '='){
            spaces.push_back(i);
        } else{
            continue;
        }
    }
    return spaces;
}
string string_upto(string s,int x){
    string l = "";
    for (int i = 0; i<x; i++) {
        char c = s[i];
        l+=c;
    }
    return l;
}
int length_upto(string s, int x){
    int length = 0;
    for (int i = 0; i<x; i++) {
        length+=1;
    }
    length+=1;
    return length;
}
vector<int> length_upto(string s, char c){
    vector<int> length;
    int lengths = 0;
    for (char i:s) {
        if(i!=c){
            lengths+=1;
        }else{
            length.push_back(lengths);
        }
    }
    return length;
}
string space_remove(string s){
    string l = "";
    for (char c:s) {
        if(c==' '){
            continue;
        }else{
            l+=c;
        }
    }
    return l;
}
map<string,string> input_str(string s , vector<int> equal , vector<int> spaces,string tagname){
    map<string, string> m;
    for (int i = 0; i<equal.size(); i++) {
        string value_name = s.substr(0,equal[0]+1);
        vector<int> length_upto_quote = length_upto(s,'\"');
        int length_upto_secondquote = length_upto_quote[1];
        string value_value = s.substr(equal[0]+1,length_upto_secondquote);
        string value_value_opt = space_remove(value_value); 
        string value_name_opt = space_remove(value_name);
        string value_name_optim = tagname+value_name_opt;
        s.erase(0,length_upto_secondquote+1);
        m.insert(value_name_optim,value_value_opt);
    }
    return m;
}
string split_till(string s){
    string k = "";
    int stops = 0;
    vector<int> fullstops;
    for (int i = 0;i<s.length() ; i++) {
        if (s[i]=='.') {
            stops+=1;
            fullstops.push_back(i);
        }
    }
    int laststop = fullstops[fullstops.size()-1];
    k = s.substr(laststop,(s.size()-laststop)+1);
    return k;
}
string remove_char(string s){
    string l = "";
    for (int i = 0; i<s.size(); i++) {
        if (s[i]!='~') {
            l+=s[i];
        }else{
            continue;
        }
    }
    return l;
}
int main() {
    int n,query;
    cin>>n>>query;
    string s;
    getline(cin,s);
    vector<string> answers;
    int total_iterations = n+query;
    for (int i = 0; i<total_iterations; i++) {
        string l; 
        getline(cin,l);
        map<string,string> map_global;
        if(l[0]=='<'){
            //Input Phase
            string y = l.substr(1,l.length()-2);
            if (y[0]!='/') {
                //Taking input phase
                vector<int> space_indexes = spaces(y);
                vector<int> equal_indexes = equals(y);
                int first_space = space_indexes[0];
                string tagnam = y.substr(0,first_space);
                string tagname = space_remove(tagnam);
                string rest = y.substr(first_space+1);
                space_indexes.erase(space_indexes.begin());
                map<string, string> m1 = input_str(rest, equal_indexes, space_indexes,tagname);
                map_global = m1;
            } else{
                //Closing input phase
                continue;
            }
        } else{
            //Query Phase
            string i = split_till(l);
            string mono = remove_char(i);
            auto it = map_global.find(mono);
            if (it==map_global.end()) {
                answers.push_back("Not Found");
            } else{
                answers.push_back(it->second);
            }
        }
    }
    for (int j = 0; j<answers.size(); j++) {
        cout<<answers[j]<<"\n";
    }
    return 0;
}
