#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int TABLELENGTH = 100;
class Dictionary{
	struct NODE{
		int key;
		string word;
		NODE* next;
	};
	NODE* head;
	int wordHash;
public:
	Dictionary(){
		head = NULL;
		string str;
		ifstream file("words.txt");
		while(getline(file,str)){
			Load(str);
		}
	}
	
	int hash(string word);
	void Load(string word);
	void Display();
	//:)
	//:))
	string removeSpaces(string input);//need to fix this function
	void Search(string word);
	
};

string Dictionary::removeSpaces(string input)
{
  int length = input.length();
  string temp = input;
  for (int i = 0; i < length; i++) {
     if(temp[i] == ' '){
		 temp.erase(i, 1);
	 }
  }
  return temp;
}

int main(){
	Dictionary word;
	string unscrambled;
	while(true){//i know this is illegal, only for testing purposes
		cout <<"~~~~~~\n";
		cout<< "Enter word: \n";
		cin>>unscrambled;
		word.Search(unscrambled);
		cout <<"~~~~~~\n";
	}
	cin.get();
	return 0;
}

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
	wordHash = hash(word);//stores in a temp var in class
	
	NODE* nodePtr;
	nodePtr = head;

	//if wordhash equals key, add word to end of an array, then compare them?
	//char instead of string?
	while(nodePtr){
		if(wordHash==nodePtr->key){
			cout<<"Entry: "<<word<<" Word: "<<nodePtr->word<<"\n";
		}
		nodePtr = nodePtr->next;
		
	}
	

	//maybe, make the unscrambled word into the head node.

	//Next steps:
	//Enter the word and take the key(make a hash function, i guess)
	//compare the key to all the ones in the nodes
	//display all that matches
	//find out next steps from that

	//hash
}