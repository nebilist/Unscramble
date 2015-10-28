//Martina Almario, Richelle Lacsamana, Reiner Gubio
//CSCI 133 - T/Th 5:45pm
//Unscramble.cpp
//Due May 12, 2015

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "UNSCRAMBLE_H.h"


int main()
{
	Dictionary word; //instantly calls the constructor
	char ans = '0';
	bool running = true;
	while(running){

		system("CLS");
		cout << "\nPlease enter a number to select a menu option: \n\n";
		cout << "[1] - Enter a word to be unscrambled" << endl;
		cout << "[2] - Display the dictionary" << endl;
		cout << "[3] - Display words that have been unscrambled" << endl;
		cout << "[4] - Exit the program\n\n";
		cout << "Selection: ";
		cin.get(ans);
		cin.ignore();
		cout << endl;
	
	
		switch(ans)
		{
		case '1':
			word.Search();
			break;
		case '2': //display dictionary
			word.DisplayAll();
			break;
		case '3': //display unscrambled word bank
			word.historyDisplay();
			break;
		case '4': //quit
			running = false;
			break;
		case '5':
			word.DisplayTable();
			break;
		default: 
			cout << "Selection not valid.\n\n";
			system("pause");
			break;
		}
	}

	return 0;
}

//input: string word
//creates a hash val based on ASCII value sum and some other math
int Dictionary::hash(string word){
	
	int value = (ASCII(word)/3) % TABLELENGTH;

	return value;
}

//input: string word
//converts the words into ASCII values
int Dictionary::ASCII(string word){
	int value = 0;
	char temp;
	for(int i=0; i<word.length();i++){
		temp = word[i];
		value += temp;
	}
	return value;
}

//input: string input
//loads each word from the text file into the hash table
void Dictionary::load(string input){

	NODE* newNode = new NODE;
	NODE* nodePtr;

	newNode->word = input;
	newNode->key = hash(input);
	newNode->next = NULL;
	
	if(!HashTable[newNode->key]){ //if there's no head at the linked list
		HashTable[newNode->key]= newNode; //place it at the head
	}
	else{
		nodePtr = HashTable[newNode->key]; 
		while(nodePtr->next){ //go down the linked list
			nodePtr = nodePtr->next;
		}
		nodePtr->next = newNode; //place the word in the last available node
	}
	
}

//input: void
//takes user input from scrambled word, finds unscrambled word
void Dictionary::Search(){

	int match=0;
	cout << "Enter Scrambled word: ";
	cin.getline(inputSearch, sizeof(inputSearch)); //take in the given word as an array of chars

	scrambledHistoryLoad(inputSearch); //load into scrambled history

	NODE* nodePtr = HashTable[hash(inputSearch)]; //Hashes Scrambled word, and points to array location 

	if(!nodePtr){//if nothing is entered yet
		cout << "No matches!\n";
	}
	else{
		while(nodePtr){
			if(CompareWords(nodePtr->word, inputSearch)){ //if the two words are the same
				cout <<"\nUnscrambled word: "<< nodePtr->word<< "\n\n";		 //displays Unscrambled word
				unscrambledHistoryLoad(nodePtr->word);	         //load into unscrambled history    
				match++;
			}
			nodePtr= nodePtr->next; //continue down the linked list
		}
		if(match == 0){ //if no matches
			cout << "No matches found!\n";
			unscrambledHistoryLoad("No match found!");
		}
	}
	cout << endl;
	system("pause");
}

//input: string word 1, string word 2
//returns true if the words match by word length & each letter
bool Dictionary::CompareWords(string word1, string word2){
	int length = 0;
	int matches = 0;

	if(word1.length() != word2.length()){
		return false;//the words aren't even the same length
	}
	else{
		//at this point, the words have the same length
	
		length = word1.length();
	
		//finding matches for char values
		for(int i = 0; i<length;i++){
			for(int j=0;j<length;j++){
				if(word1[i]==word2[j]){
					matches++;
				}
			}
		}

		//comparing ASCII vals and lengths
		if(matches >= length && ASCII(word1)==ASCII(word2)){
			return true;
		}
		else{
			return false;
		}
	}
}

//input: void
//displays all words from the text file
void Dictionary::DisplayAll(){
	int count = 0;
	string str;

	ifstream file("words.txt");

	while(getline(file,str)){
		count ++;
		if ((count%2) == 0){ //put words into two columns
			cout << str << endl;
		}else{
			if(str.length() <= 7){ //fix tabbing because we have really long words LOL
				cout << str << "\t\t\t\t\t";
			}else if(str.length() > 7 && str.length() <= 15){
				cout << str << "\t\t\t\t";
			}else if(str.length() > 15 && str.length() < 24){
				cout << str << "\t\t\t";
			}else{
				cout << str << "\t\t";
			}
		}
	}
	cout << endl;
	system("pause");
	
}

//input: string input
//loads unscrambled words into linked list
void Dictionary::unscrambledHistoryLoad(string input){
	NODE* nodePtr; //slider
	NODE* newNode = new NODE;
	
	newNode->word = input; //put the unscrambled word into a variable in the node (word)
	newNode->next = NULL;

	
	if(!UnscrambledHistoryList){                 //if there's no head
		newNode->key = 1;             //make this the head
		UnscrambledHistoryList = newNode;        //plug this word into the head
		
	}
	else{
		nodePtr = UnscrambledHistoryList;

		while(nodePtr->next){
			nodePtr = nodePtr->next; //move down the list to the very last node that isn't null
		}

		newNode->key = (nodePtr->key) + 1; //add to the count
		nodePtr->next = newNode; //put the word into this node
	}
}

//input: string input
//loads scrambled words into linked list
void Dictionary::scrambledHistoryLoad(string input){
	NODE* nodePtr; //slider
	NODE* newNode = new NODE;
	
	newNode->word = input; //put the unscrambled word into a variable in the node (word)
	newNode->next = NULL;

	
	if(!ScrambledHistoryList){ //if there's no head
		newNode->key = 1; //make this the head
		ScrambledHistoryList = newNode; //plug this word into the head
		
	}
	else{
		nodePtr = ScrambledHistoryList;

		while(nodePtr->next){
			nodePtr = nodePtr->next; //move down the list to the very last node that isn't null
		}
		newNode->key = (nodePtr->key) + 1; //add to the count
		nodePtr->next = newNode; //put the word into this node
	}
}

//input: void
//displays scrambled and unscrambled linked lists
void Dictionary::historyDisplay(){
	
	NODE* nodePtr1;
	NODE* nodePtr2;
	nodePtr1 = UnscrambledHistoryList;
	nodePtr2 = ScrambledHistoryList;

	if(!nodePtr2){
		cout<<"No words have been entered.\n\n";
	}
	else{
			cout<<"History\n\n";
			while(nodePtr2){
				cout << nodePtr2->key <<" "<< nodePtr2->word << " -> " << nodePtr1->word <<"\n";
				nodePtr1=nodePtr1->next;
				nodePtr2=nodePtr2->next;
			}
	}
	
	cout << endl;
	system("pause");

}

//input: int key
//TESTING PURPOSES! (prints out the hash value of each word)
void Dictionary::Pull(int key){
	NODE* nodePtr;
	nodePtr = HashTable[key];
	if(!nodePtr){
		cout <<"["<< key<<"]=\tNULL\n";
	}
	else{
		nodePtr = HashTable[key];
		cout <<"["<< nodePtr->key<<"]=\t";
		while(nodePtr){
			cout << nodePtr->word;
			if(!nodePtr->next==NULL){
				cout << " => ";
			}
			
			nodePtr = nodePtr->next;
		}
		cout <<"\n";
	}
}



//input: void
//TESTING PURPOSES! (calls Pull)
void Dictionary::DisplayTable(){
	for (int i = 0;i<TABLELENGTH;i++){
		Pull(i);
	}
	cin.get();
}