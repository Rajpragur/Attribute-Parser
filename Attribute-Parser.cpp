#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <iterator>
using namespace std;
//To count the spaces indexes
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
//To get the equal indexes and we can also know how many values will be there
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
//To get the length upto a char for ex:- "
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
//Remove spaces in string
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
//Map storing tagname+name+value
map<string,string> input_str(string s,string tagname){
    map<string, string> m;
    vector<int> equal = equals(s);
    vector<int> space = spaces(s);
    for (int i = 0; i<equal.size(); i++) {
        string value_name = s.substr(0,equal[0]+1);
        vector<int> length_upto_quote = length_upto(s,'"');
        int length_upto_secondquote = length_upto_quote[1];
        string value_value = s.substr(equal[0]+1,length_upto_secondquote);
        string value_value_opt = space_remove(value_value); 
        value_value_opt = value_value_opt.substr(1,value_value_opt.length()-2);
        string value_name_opt = space_remove(value_name);
        value_name_opt.erase(value_name_opt.begin()+value_name_opt.length()-1);
        string value_name_optim = tagname+value_name_opt;
        s.erase(0,length_upto_secondquote+1);
        m.insert(pair<string,string>(value_name_optim,value_value_opt));
    }
    return m;
}
//Split the query from the last fullstop
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
    if(stops!=0){
    int laststop = fullstops[fullstops.size()-1];
    k = s.substr(laststop+1,s.length()-laststop);
    } else{
        k = s;
    }
    return k;
}
//Remove tilde
string remove_tilde(string s){
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
    //Take the remaining line to prevent other input taking it
    string s;
    getline(cin,s);
    //Answers container
    vector<string> answers;
    //Total iterations which will take place
    int total_iterations = n+query;
    for (int i = 0; i<total_iterations; i++) {
        //Take the whole line
        string l; 
        getline(cin,l);
        //MAP STORING values
        map<string,string> map_global;
        //If starting is with this then it's a line because order is not guaranteed that after lines query phase will come
        if(l[0]=='<'){
            //Input Phase
            string y = l.substr(1,l.length()-2);
            if (y[0]!='/') {
                //Taking input phase
                vector<int> space_indexes = spaces(y);
                vector<int> equal_indexes = equals(y);
                int first_space = space_indexes[0];
                string tagnam = y.substr(0,first_space+1);
                string tagname = space_remove(tagnam);
                string rest = y.substr(first_space+1);
                space_indexes.erase(space_indexes.begin());
                map<string, string> m1 = input_str(rest,tagname);
                map_global = m1;
            } else{
                //Closing input phase
                continue;
            }
        } else{
            //Query Phase
            string i = split_till(l);
            string mono = remove_tilde(i);
            try {
                string value = map_global.at(mono);
                answers.push_back(value);
            } catch (const out_of_range&) {
                answers.push_back("Not Found!");
            }
        }
    }
    for (int j = 0; j<answers.size(); j++) {
        cout<<answers[j]<<"\n";
    }
    return 0;
}
