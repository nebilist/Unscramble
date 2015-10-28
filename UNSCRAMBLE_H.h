//Martina Almario, Richelle Lacsamana, Reiner Gubio
//CSCI 133 - T/Th 5:45pm
//UNSCRAMBLE_H.H
//Due May 12, 2015

#ifndef UNSCRAMBLE_H
#define UNSCRAMBLE_H

const int TABLELENGTH = 101;

class Dictionary{

	struct NODE{
		int key;
		string word;
		NODE* next;
	};                               
	char inputSearch[50];
	int inputHash;

	NODE* ScrambledHistoryList;
	NODE* UnscrambledHistoryList;
	NODE* HashTable[TABLELENGTH];
	

	public:
	
		Dictionary(){ //constructor

			string str;
			ifstream file("words.txt"); //import dictionary

			ScrambledHistoryList = NULL;
			UnscrambledHistoryList = NULL;
			//int histCount;
			for(int i = 0;i<TABLELENGTH;i++){ //initialize dictionary array to nulls
				HashTable[i] = NULL;
			}

			while(getline(file,str)){ //give hash val to each word in dictionary, places it into the array
				load(str);
			}
		}
		
		/* function declarations start here */
		int hash(string word);
		void load(string word);

		//Search Components
		void Search();
		bool CompareWords(string word1, string word2);
		int ASCII(string word);

		//For displaying items
		void DisplayAll();
		
		//History functions
		void scrambledHistoryLoad(string word);
		void unscrambledHistoryLoad(string word);
		void historyDisplay();

		//Testing purposes, functions are not used in the main program
		
		void Pull(int key);
		void DisplayTable();
};

#endif
