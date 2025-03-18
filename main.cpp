#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
using namespace std;

bool isInt(string& str){
	if (str.size() == 0) {
		return false;
	}
	for (int i = 0; i<str.size(); i++){
		if (!isdigit(str[i]))return false;
	}
	return true;
}

class evFile{
	string* stream;
	int lines;
	stack<double> intStack;
	stack<string> charStack;
	map<string, double> intVars;
public:
	evFile(string s[], int l){
		stream = s;
		lines = l;
	}
	void compRes(){
		for (int pc = 0; pc<lines; pc++){
			stringstream s(stream[pc]);
			string token;
			s >> token;
			if (token == "while") {
				while (s>>token) {
					evExp(token);
				}
				if (intStack.top()) continue;
				else{
					string check = "while";
					while (check != "end") {
						pc++;
						stringstream ss(stream[pc]);
						ss >> check;
					}
				}
			}
			else if(token == "end"){
				string check = "end";
				while (check != "while") {
					pc--;
					stringstream ss(stream[pc]);
					ss >> check;
				}
				pc--;
			}
			if (token == "if") {
				while (s>>token) {
					evExp(token);
				}
				if (intStack.top()) continue;
				else{
					string check = "if";
					while (check != "endif") {
						pc++;
						stringstream ss(stream[pc]);
						ss >> check;
					}
				}
			}
			else if(token == "endif"){
				continue;
			}
			else if(token == "output"){
				while (s>>token) {
					evExp(token);
				}
				cout<<intStack.top()<<endl;
			}
			else{
				auto it = intVars.find(token);
				intStack.push(it->second);
				charStack.push(token);
				string name = token;
				s>>token;
				if(token == "="){
					while (s>>token) {
						evExp(token);
					}
					intVars[name] = intStack.top();
				}
			}
		}
	}
	
	int getTop(){
		return intStack.top();
	}
	void evExp(string str){
		if (isInt(str)) {
			intStack.push(stoi(str));
		}else {
			if (str == "+") {
				int a = intStack.top();
				intStack.pop();
				int b = intStack.top();
				intStack.pop();
				intStack.push(a+b);
			}
			else if (str == "*") {
				double a = intStack.top();
				intStack.pop();
				double b = intStack.top();
				intStack.pop();
				charStack.pop();
				intStack.push(a*b);
			}
			else if (str == "-") {
				int a = intStack.top();
				intStack.pop();
				int b = intStack.top();
				intStack.pop();
				intStack.push(b-a);
			}
			else if (str == "/") {
				int a = intStack.top();
				intStack.pop();
				int b = intStack.top();
				intStack.pop();
				intStack.push((double)b/a);
			}
			else if (str == "%") {
				int a = intStack.top();
				intStack.pop();
				int b = intStack.top();
				intStack.pop();
				intStack.push(b%a);
			}
			else if (str == ">") {
				int a = intStack.top();
				intStack.pop();
				int b = intStack.top();
				intStack.pop();
				b > a ? intStack.push(1) : intStack.push(0);
			}
			else if (str == "<") {
				int a = intStack.top();
				intStack.pop();
				int b = intStack.top();
				intStack.pop();
				b < a ? intStack.push(1) : intStack.push(0);
			}
			else if (str == ">=") {
				int a = intStack.top();
				intStack.pop();
				int b = intStack.top();
				intStack.pop();
				b >= a ? intStack.push(1) : intStack.push(0);
			}
			else if (str == "<=") {
				int a = intStack.top();
				intStack.pop();
				int b = intStack.top();
				intStack.pop();
				b <= a ? intStack.push(1) : intStack.push(0);
			}
			else if (str == "==") {
				int a = intStack.top();
				intStack.pop();
				int b = intStack.top();
				intStack.pop();
				b == a ? intStack.push(1) : intStack.push(0);
			}
			else if (str == "!=") {
				int a = intStack.top();
				intStack.pop();
				int b = intStack.top();
				intStack.pop();
				b != a ? intStack.push(1) : intStack.push(0);
			}
			else if (str == "&&") {
				int a = intStack.top();
				intStack.pop();
				int b = intStack.top();
				intStack.pop();
				b && a ? intStack.push(1) : intStack.push(0);
			}
			else if (str == "||") {
				int a = intStack.top();
				intStack.pop();
				int b = intStack.top();
				intStack.pop();
				b || a ? intStack.push(1) : intStack.push(0);
			}
			else if (str == "!") {
				int a = intStack.top();
				intStack.pop();
				!a ? intStack.push(1) : intStack.push(0);
			}else {
				auto it = intVars.find(str);
				intStack.push(it->second);
				charStack.push(str);
			}
		}
	}
};

int main(int argc, char* argv[]){
	ifstream fin(argv[1]);
	string name = argv[1];

	if (name.substr(name.find('.'), name.size() - name.find('.')) == ".bis") {
		string check;
		getline(fin, check);
		if (check == "Bismillah") {
			int lines = 1;
			string s;
			for (; getline(fin, s); lines++);
			fin.close();
			string file[lines];
			ifstream fSecondIn(argv[1]);
			for (int i = 0; i < lines; i++) {
				getline(fSecondIn, file[i]);
			}
			evFile f(file, lines);
			f.compRes();
		}else cout<<"No Bismillah? You wanna run a marathon in flip-flops?"<<endl;
	}else{
		cout<<"This file is like a bad joke: Doesn’t make sense!"<<endl;
	}
	return 0;
}
