#ifndef IDEA_BANK_H_
#define IDEA_BANK_H_

class IdeaBank {
	list<Idea> ideas;
	void parse_line(string &line);
	int get_last_id();
	public:
	IdeaBank();
	bool read_from_file();
	bool new_idea();
	void display_idea(int idea_id);
	void display_all_ideas();
	bool delete_idea(int idea_id);
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
			parse_line(line);
		}
	}
	
	idea_file.close();
	return true;
}

void IdeaBank::parse_line(string &line) {
	// Need to split the string
	int split_counter = 0;
	int id;
	string proposer, content;
	list<string> keywords;
	
	string val, keyword;
	for (char &c: line) {
		val += c;
		keyword += c;
		if (c == ',' && split_counter == 2) {
			keyword.pop_back();
			keywords.push_back(keyword);
			keyword = "";
		}
		if (c == '|') {
			val.pop_back();
			switch (split_counter) {
				case 0: {
					id = stoi(val);
				} break;
				
				case 1: {
					proposer = val;
				} break;
				
				case 2: {
					// Need to catch the last keyword in the list.
					keyword.pop_back();
					keywords.push_back(keyword);
				} break;
				
				case 3 : {
					content = val;
				} break;
			}
			val = "";
			keyword = "";
			split_counter++;
		}
	}
	
	Idea idea(id, proposer, keywords, content);
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
	string proposer;
	string content;
	list<string> keywords;
	
	cin.ignore(); // Make sure cin is ignoring any new lines in the iostream buffer.
	cout << "Proposer Name: ";
	getline(cin, proposer);
	
	cout << "Idea Content: ";
	getline(cin, content);
	
	bool keywording = true;
	cout << "Keywords (to stop type -1):" << endl;
	while(keywording) {
		string keyword;
		getline(cin, keyword);
		
		if (keyword != "") {
			keywords.push_back(keyword);
		} else {
			keywording = false;
		}
	}
	
	int id = get_last_id() + 1;
	
	Idea idea(id, proposer, keywords, content);
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

#endif