#ifndef IDEA_H_
#define IDEA_H_

class Idea {
	int id;
	string proposer, content;
	list<string> keywords;
	
	public:
	Idea(int id, string proposer, list<string> keywords, string content);
	~Idea();
	int get_id();
	bool in_content(string word);
	bool in_keywords(string word);
	friend ostream& operator<<(ostream& os, const Idea& idea);
};

Idea::Idea(int _id, string _proposer, list<string> _keywords, string _content) {
	// Constructor
	id       = _id;
	proposer = _proposer;
	keywords = _keywords;
	content  = _content;
}

Idea::~Idea() {
	// Destructor
}

ostream& operator<<(ostream& os, const Idea& idea) {
	os << "ID: " << idea.id << endl;
	os << "Proposer: " << idea.proposer << endl;
	os << "Content: " << idea.content << endl;
	
	return os;
}


bool Idea::in_keywords(string word) {
	// If the word is in the keywords, return true;
	return true;
}

bool Idea::in_content(string word) {
	// If the word is in the content return true;
	return true;
}

int Idea::get_id() {
	return id;
}


#endif