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
	int hash(string word);
	void Load(string word);
	void Display();


	void Search(string word);
	
};
int Dictionary::hash(string word){
	int value = 0;
	
	for(int i=0; i<word.length();i++){
		value += word[i];
	}

	return value;
	
}

void Dictionary::Display(){
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
	
	//Separate functions?
		//This loads a word in the list into a node;
		newNode->word = word;
		//create a hash value and loads it too
		newNode->key = hash(word);

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
void Dictionary::Search(string word){
	//maybe, make the unscrambled word into the head node.

	//Next steps:
	//Enter the word and take the key(make a hash function, i guess)
	//compare the key to all the ones in the nodes
	//display all that matches
	//find out next steps from that

	//hash
}
int main(){
	Dictionary word;
	string str, unscrambled;

	ifstream file("words.txt");
	while(getline(file, str)){
		word.Load(str);
	}

	//cout <<"Enter word: \n";
	//cin >> unscrambled;
	//word.Search(unscrambled);

	word.Display();

	cin.get();
	return 0;
}