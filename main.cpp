#include <iostream>
#include <fstream>
#include <string>

using namespace std;
const int tableSize = 100;
//this would be so impressive if it could read an html file instead of a txt file

class Unscramble{
	struct NODE{
		char word[10];
		NODE* next;
	};

public:
	void EnterWord();
	int hash(string key);
};

int Unscramble::hash(string key){
	int value = 0;
	for(int i=0; i<key.length();i++){
		value += key[i];
	}
	return value%tableSize;
}
int main(){
	//hash the entered word
	//use the number to look up place in array
	cout <<"1. Enter Word\n2. Exit\n";
	Unscramble word;
	int count = 1;
	ifstream file("words.txt");
	string str;
	while(getline(file, str)){
		cout << count <<". "<<str << " " << word.hash(str)<< "\n";
		count++;
	}
	cin.get();
	return 0;
}