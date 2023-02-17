#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
    ifstream file(filename);
    string L;
    int one,two,three,sum = 0;
    char g,n[27];
    char format[] = "%[^:]: %d %d %d";
    while(getline(file,L)){
        sscanf(L.c_str(),format,n, &one,&two,&three);
        names.push_back(n);
        sum = one+two+three;
        g = score2grade(sum);
        scores.push_back(sum);
        grades.push_back(g);
    }
}

void getCommand(string &command,string &key){
    string A;
    char B[50];
    char N[50];
    cout << "Please input your command: ";
    getline(cin,A);
    sscanf(A.c_str(),"%s %[^]",B,N);
        command = B;
        key = N;
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string &key){
    cout << "---------------------------------";
    bool GG = false;
    for(unsigned int i=0;i<names.size();i++){
        if(toUpperStr(names[i])==key){
            cout << names[i] << "'s score = " << scores[i];
            cout << names[i] << "'s grade = " << grades[i];
            GG=true;
        }
    }
    if(!GG){
        cout << "Cannot found.";
    }
    cout << "---------------------------------";    
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string &key){
    cout << "---------------------------------";
    bool GG = false;
    string s;
    for(unsigned int i=0;i<names.size();i++){
        s=grades[i];
        if(s==key){
            cout << names[i] << " (" << scores[i] << ")";
            GG=true;
        }
    }
    if(!GG){
        cout << "Cannot found.";
    }
    cout << "---------------------------------"; 
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
