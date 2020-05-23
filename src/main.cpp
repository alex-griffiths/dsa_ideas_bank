#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace std;

#include "lib/AVLTree.h"

#include "idea.h"
#include "index.h"
#include "idea_bank.h"

int main() {
	IdeaBank ideas_bank;
	
	while(true) {
		int choice;
		cout << "Menu:" << endl;
		cout << "1) Import ideas from a file" << endl;
		cout << "2) Print the ideas bank" << endl;
		cout << "3) Show a single idea" << endl;
		cout << "4) Add an idea" << endl;
		cout << "5) Print word indices" << endl;
		cout << "6) Search for related ideas from ideas bank" << endl;
		cout << "7) Search for related ideas from indexing tree" << endl;
		cout << "8) Delete an idea" << endl;
		cout << "0) Quit" << endl;
		
		cin >> choice;
		
		switch (choice) {
			case 1: {
				ideas_bank.read_from_file();
			} break;
			
			case 2: {
				ideas_bank.display_all_ideas();
			} break;
			
			case 3: {
				int idea_id;
				cout << "Please input the id of the Idea you would like to display: ";
				cin >> idea_id;
				
				ideas_bank.display_idea(idea_id);
			} break;
			
			case 4: {
				bool inserting = true;
				while(inserting) {
					ideas_bank.new_idea();
					
					cout << "Continue Inserting Ideas(Y/N)" << endl;
					char cont;
					cin >> cont;
					if (cont == 'N' || cont == 'n') {
						inserting = false;
					}
				}
			} break;
			
			case 5: {
				ideas_bank.print_keywords_index();
			} break;
			
			case 6: {
				string query;
				cout << "Enter query word: ";
				cin >> query;
				
				ideas_bank.display_related_ideas(query);
			} break;
			
			case 7: {
				string query;
				cout << "Enter query word: ";
				cin >> query;
				
				ideas_bank.display_related_indexed_ideas(query);
			} break;
			
			case 8: {
				int d_id;
				cout << "Please input the id of the Idea you would like to delete: ";
				cin >> d_id;
				
				if(!ideas_bank.delete_idea(d_id)) {
					cout << "There was a problem deleting this idea. It may not exist, or another error may have occured." << endl;
				}
			} break;
			
			
			case 0: {
				cout << "Exiting..." << endl;
				return false;
			} break;
			
			default: {
				cout << "Please input a valid choice" << endl;
			}
		}
	}
	
	return 0;
}
