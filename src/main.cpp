#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

#include "lib/avl_tree.h"

#include "index.h"
#include "idea.h"
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
		cout << ") Print word indices" << endl;
		cout << ") Search for related ideas from ideas bank" << endl;
		cout << ") Search for related ideas from indexing tree" << endl;
		cout << ") Related ideas of an idea" << endl;
		cout << "9) Delete an idea" << endl;
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
				
			} break;
			
			case 6: {
				
			} break;
			
			case 7: {
				
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
