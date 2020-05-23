#ifndef IDEA_BANK_H_
#define IDEA_BANK_H_

class IdeaBank {
	list<Idea> ideas;
	AvlTree<Index, string> idea_index;
	void parse_idea(string &line);
	void index_list();
	int get_last_id();
	void index_idea(Idea idea);
	void purge_idea_from_tree(Idea idea);
	void to_lower(string s);
	void to_alpha(string s);
	public:
	IdeaBank();
	bool read_from_file();
	bool new_idea();
	void display_idea(int idea_id);
	void display_related_ideas(string query);
	void display_related_indexed_ideas(string query);
	void display_all_ideas();
	bool delete_idea(int idea_id);
	void print_keywords_index();
};

IdeaBank::IdeaBank() {
	
}

bool IdeaBank::read_from_file() {
	// Ask for file path.
	
	ifstream idea_file;
	string line;
	idea_file.open("./ideas.txt");
	
	if (!idea_file) {
		cerr << "Unable to open file ideas.txt";
		return false;
	} else {
		while (getline(idea_file, line)) {
			parse_idea(line);
		}
	}
	
	idea_file.close();
	cout << endl;
	
	return true;
}

void IdeaBank::parse_idea(string &line) {
	// Need to split the string
	int split_counter = 0;
	int id;
	
	istringstream ss(line);
	string proposer, content, val, keyword, split;
	
	list<string> keywords;
	list<string> contents;
	
	while(getline(ss, split, '|')) {
		switch(split_counter) {
			case 0: {
				id = stoi(split);
			} break;
			
			case 1: {
				proposer = split;
			} break;
			
			case 2: {
				istringstream kword_ss(split);
				
				while(getline(kword_ss, keyword, ',')) {
					keywords.push_back(keyword);
				}
			} break;
			
			case 3: {
				istringstream content_ss(split);
				
				while(getline(content_ss, content, ' ')) {
					contents.push_back(content);
				}
			} break;
		}
		
		split_counter++;
	}
	
	Idea idea(id, proposer, keywords, contents);
	index_idea(idea);
	ideas.push_back(idea);
}

bool IdeaBank::new_idea() {
	// @TODO: This could be a whole lot cleaner.
	string proposer;
	string content;
	list<string> keywords, contents;
	
	cin.ignore(); // Make sure cin is ignoring any new lines in the iostream buffer.
	cout << "Proposer Name: ";
	getline(cin, proposer);
	
	cout << "Idea Content: ";
	getline(cin, content);
	
	istringstream contents_ss(content);
	string split_content;
	while (getline(contents_ss, split_content, ' ')) {
		contents.push_back(split_content);
	}
	
	bool keywording = true;
	// Handle comma separation.
	// Need to strip white space at the end.
	cout << "Keywords (separate each keyword with a comma):" << endl;
	string cin_keywords, split_keywords;
	getline(cin, cin_keywords);
	istringstream ss_keywords(cin_keywords);
	
	while(getline(ss_keywords, split_keywords, ',')) {
		keywords.push_back(split_keywords);
	}
	
	int id = get_last_id() + 1;
	
	Idea idea(id, proposer, keywords, contents);
	index_idea(idea);
	ideas.push_back(idea);
	
	return true;
}

void IdeaBank::display_all_ideas() {
	for(list<Idea>::iterator it = ideas.begin(); it != ideas.end(); it++) {
		cout << (*it) << endl;
	}
}

void IdeaBank::display_idea(int idea_id) {
	for (list<Idea>::iterator it = ideas.begin(); it != ideas.end(); it++){
		if ((*it).get_id() == idea_id) {
			cout << (*it) << endl;
		}
	}
}

// Iterates over all ideas in the idea bank and checks if the query string is in the content or keywords.

// Worst Case: O(n)
void IdeaBank::display_related_ideas(string query) {
	if (ideas.size() > 0) {
		for (list<Idea>::iterator it = ideas.begin(); it != ideas.end(); it++) {
			if ((*it).query_in_content(query) || (*it).query_in_keywords(query)) {
				cout << *it;
			}
		}
	} else {
		cout << "There are no ideas to search" << endl;
	}
}


// Iterates over each indexed word in the AVL Tree, 
// Worst Case: O(log2n)
// Best Case: O(1)
void IdeaBank::display_related_indexed_ideas(string query) {
	Index word_index;
	if (ideas.size() > 0 && idea_index.AVL_Retrieve(query, word_index)) {
		// Output the index.
		vector<int> ids = word_index.id_list;
		cout << "Keyword: " << word_index.key << " | Idea Ids: { ";
		for (vector<int>::iterator it = ids.begin(); it != ids.end(); it++) {
			if (it != ids.begin()) {
				cout << ", ";
			}
			cout << *it;
		}
		
		cout << " }" << endl;
		
		for (vector<int>::iterator it = ids.begin(); it != ids.end(); it++) {
			display_idea(*it);
		}
	} else {
		cout << "Could not find an idea related to this query string: " << query << endl;
	}
	
}

void IdeaBank::purge_idea_from_tree(Idea idea) {
	// Loop over words and retrieve each index of each word. Then we remove the idea from index.
	int id = idea.get_id();
	list<string> contents = idea.get_contents();
	for(list<string>::iterator it = contents.begin(); it != contents.end(); it++) {
		string word = *it;
		Index index;
		idea_index.AVL_Retrieve(word, index);
		
		vector<int> id_list = index.id_list;
		
		if (id_list.size() == 1) {
			if (id != id_list[0]) {
				// This should never happen.
				cout << "Error in delete";
				exit(100);
			}
			// Delete the word from the index.
			idea_index.AVL_Delete(word);
		} else {
			// Iterate over id list and delete id.
			// Not efficient.
			for (vector<int>::iterator it = id_list.begin(); it != id_list.end(); it++) {
				if (*it == id) {
					vector<int>::iterator del_it = it;
					it++;
					
					id_list.erase(del_it);
				}
			}
		}
	}
}


// This isn't particularly efficient. I couldn't get a nicer solution working.
bool IdeaBank::delete_idea(int idea_id) {
	if (ideas.size() > 0) {
		int purge_id;
		for (list<Idea>::iterator it = ideas.begin(); it != ideas.end(); it++){
			cout << (*it).get_id() << endl;
			if ((*it).get_id() == idea_id) {
				purge_id = (*it).get_id();
				list<Idea>::iterator del_it = it;
				it++;
				
				//purge_idea_from_tree(*del_it);
				
				ideas.erase(del_it);
				
				return true;
			}
		}
		
	} else {
		cout << "There are no ideas to delete" << endl;
	}
	return false;
}

int IdeaBank::get_last_id() {
	if (ideas.size() > 0) {
		Idea last_idea = ideas.back();
		return last_idea.get_id();
	} else {
		return 0;
	}
}


void IdeaBank::index_idea(Idea idea) {
	Index kword_index, new_index;
	
	NODE<Index> new_node;
	
	list<string> keywords = idea.get_keywords();
	list<string> contents = idea.get_contents();
	int idea_id = idea.get_id();
	
	// Index keywords.
	for(list<string>::iterator it = keywords.begin(); it != keywords.end(); it++) {
		string keyword = *it;
		
		transform(keyword.begin(), keyword.end(), keyword.begin(), [](unsigned char c){return tolower(c);});
		
		new_index.key = keyword;
		new_index.id_list = {idea_id};
		
		new_node.data = new_index;
		new_node.left = NULL;
		new_node.right = NULL;
		new_node.bal = EH;
		
		idea_index.AVL_Insert(new_index);
	}
	
	for(list<string>::iterator it = contents.begin(); it != contents.end(); it++) {
		string word = *it;
		
		transform(word.begin(), word.end(), word.begin(), [](unsigned char c){return tolower(c);});
		word.erase(remove_if(word.begin(), word.end(), [](char c) {
																							return !(isalpha(c) || c == ' ');
																							}), word.end());
		
		new_index.key = word;
		new_index.id_list = {idea_id};
		
		new_node.data = new_index;
		new_node.left = NULL;
		new_node.right = NULL;
		new_node.bal = EH;
		
		idea_index.AVL_Insert(new_index);
	}
}


void IdeaBank::print_keywords_index() {
	cout << "Keywords index count: " << idea_index.AVL_Count() << endl;
	idea_index.AVL_Print();
}


#endif