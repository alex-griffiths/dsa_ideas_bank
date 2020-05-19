#ifndef IDEA_H_
#define IDEA_H_

class Idea {
	int id;
	string proposer;
	list<string> keywords, contents;
	
	public:
	Idea(int id, string proposer, list<string> keywords, list<string> contents);
	~Idea();
	int get_id();
	bool query_in_content(string word);
	bool query_in_keywords(string word);
	friend ostream& operator<<(ostream& os, const Idea& idea);
};

Idea::Idea(int _id, string _proposer, list<string> _keywords, list<string> _contents) {
	// Constructor
	id       = _id;
	proposer = _proposer;
	keywords = _keywords;
	contents = _contents;
}

Idea::~Idea() {
	// Destructor
}

ostream& operator<<(ostream& os, const Idea& idea) {
	os << "ID: " << idea.id << endl;
	os << "Proposer: " << idea.proposer << endl;
	os << "Keywords:" << endl;
	
	list<string> _keywords = idea.keywords;
	for (list<string>::iterator it = _keywords.begin(); it != _keywords.end(); it++) {
		os << "\t" << *it << endl;
	}
	
	os << "Content: " << endl;
	list<string> _contents = idea.contents;
	for (list<string>::iterator it = _contents.begin(); it != _contents.end(); it++) {
		os << *it << ' ';
	}
	os <<  endl;
	
	return os;
}


bool Idea::query_in_keywords(string word) {
	// If the word is in the keywords, return true;
	for (list<string>::iterator it = keywords.begin(); it != keywords.end(); it++) {
		if (*it == word) {
			cout << "Word found in keywords" << endl;
			return true;
		}
	}
	return false;
}

bool Idea::query_in_content(string word) {
	for (list<string>::iterator it = contents.begin(); it != contents.end(); it++) {
		if (*it == word) {
			cout << "Word found in content" << endl;
			return true;
		}
	}
	return false;
}


int Idea::get_id() {
	return id;
}


#endif