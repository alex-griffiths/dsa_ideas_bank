#ifndef IDEA_BANK_H_
#define IDEA_BANK_H_

class IdeaBank {
	list<Idea> ideas;
	AVLTree<Index, string> keyword_index;
	void parse_idea(string &line);
	void index_list();
	int get_last_id();
	void index_keywords(list<string> keywords, int idea_id);
	public:
	IdeaBank();
	bool read_from_file();
	bool new_idea();
	void display_idea(int idea_id);
	void display_all_ideas();
	bool delete_idea(int idea_id);
	void print_indicies();
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
		cout << split;
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
	
	index_keywords(keywords, id);
	ideas.push_back(idea);
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

bool IdeaBank::delete_idea(int idea_id) {
	for (list<Idea>::iterator it = ideas.begin(); it != ideas.end(); it++){
		if ((*it).get_id() == idea_id) {
			list<Idea>::iterator next = it++;
			ideas.erase(it);
			it = next;
			return true;
		}
	}
	
	return false;
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
	cout << "Keywords (to stop type -1):" << endl;
	while(keywording) {
		string keyword;
		getline(cin, keyword);
		
		if (keyword != "-1") {
			keywords.push_back(keyword);
		} else {
			keywording = false;
		}
	}
	
	int id = get_last_id() + 1;
	
	Idea idea(id, proposer, keywords, contents);
	ideas.push_back(idea);
	
	return true;
}

int IdeaBank::get_last_id() {
	if (ideas.size() > 0) {
		Idea last_idea = ideas.back();
		return last_idea.get_id();
	} else {
		return 0;
	}
}


void IdeaBank::index_keywords(list<string> keywords, int idea_id) {
	Index kword_index;
	
	keyword_index.AVLTree_print();
	//for(list<string>::iterator it = keywords.begin(); it != keywords.end(); it++) {
	//index.AVLTree_retrieve(*it, &kword_index);
	//}
	
}
#endif