#include <iostream>
#include <fstream>
#include <string>

using namespace std;
//this would be so impressive if it could read an html file instead of a txt file

class Dictionary{
	struct NODE{
		int key;
		string word;
		NODE* next;
	};
	NODE* head;
public:
	Dictionary(){
		head = NULL;
	}
	void Load(string word);
	void Display();
	void Search(string word);
	
};

void Dictionary::Search(string word){
	//Next steps:
	//Enter the word and take the key(make a hash function, i guess)
	//compare the key to all the ones in the nodes
	//display all that matches
	//find out next steps from that

	//hash
	int value;
	for(int i=0; i<word.length();i++){
		value += word[i];
	}

	NODE* nodePtr;
	nodePtr = head;
	while(nodePtr){
		if(nodePtr->key==value){
			cout << nodePtr->word;
		}
		nodePtr = nodePtr->next;
	}

}
void Dictionary::Display(){
	//We've done this before
	NODE* nodePtr;
	nodePtr = head;
	while(nodePtr){
		cout << "Word: "<< nodePtr->word <<" Key: "<<nodePtr->key<<"\n";
		nodePtr = nodePtr->next;
	}
}
void Dictionary::Load(string word){
	
	NODE* newNode = new NODE;
	NODE* nodePtr;
	int value = 0;

	//This loads a word in the list into a node;
	newNode->word = word;
	
	// This creates a hash key
	for(int i=0; i<word.length();i++){
		value += word[i];
	}
	// and enters the created key into the node
	newNode->key = value;

	newNode->next = NULL;
	if(!head){
		head = newNode;
	}
	else{
		nodePtr = head;
		while(nodePtr->next!=NULL){
			nodePtr=nodePtr->next;
		}
		nodePtr->next = newNode;
	}
}

int main(){
	Dictionary word;
	string str, unscrambled;

	ifstream file("words.txt");
	while(getline(file, str)){
		word.Load(str);
	}

	cout <<"Enter word: \n";
	cin >> unscrambled;
	word.Search(unscrambled);
	//Current choices

	
	cin.get();
	return 0;
}