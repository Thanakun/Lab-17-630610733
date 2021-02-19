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

void importDataFromFile(string filename,vector<string> &names,vector<int> &score,vector<char> &grades){
    ifstream source;
    source.open(filename.c_str());
    string textline;
    int score1,score2,score3,sumscore = 0;
    char name1[100];
    char grade1;
    while(getline(source,textline)){
        char format[] = "%[^:]: %d %d %d";
        sscanf(textline.c_str(),format,name1,&score1,&score2,&score3);
        sumscore = score1 + score2 + score3;
        grade1 = score2grade(sumscore);
        names.push_back(name1);
        score.push_back(sumscore);
        grades.push_back(grade1);
    }

}

void getCommand(string &command, string &key){
    string temp = "";
    int start = 0;
    cout << "Please input your command: ";
    getline(cin,temp);
    start = temp.find_first_of(" ");
    command = temp.substr(0,start);
    key = temp.substr(start+1 ,temp.size());

}

void searchName(vector<string> &names,vector<int> &score,vector<char> &grades,string &key){
    bool flag = false;
    cout << "---------------------------------" << endl;
    for(unsigned int i = 0; i < names.size();i++){
        if(toUpperStr(key) == toUpperStr(names[i])){
            cout << names[i] <<"'s score = " << score[i] << endl;
            cout << names[i] <<"'s grade = " << grades[i] << endl;
            flag = true;
        }
    }
    if(!flag)
    {
        cout << "Cannot found." << endl;
    } 
    cout << "---------------------------------" << endl;
}

void searchGrade(vector<string> &names,vector<int> &score,vector<char> &grades, string &key ){
    bool flag = false;
    char keyCh = key[0];
    cout << "---------------------------------" << endl;
    for(unsigned int i = 0; i < names.size(); i++){
        if(keyCh == grades[i]){
            cout << names[i] << " " << "(" << score[i] << ")" << endl;
            flag =true;
        }
    }
    if(!flag)
    {
        cout << "Cannot found." << endl;
    }
    cout << "---------------------------------" << endl;
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
