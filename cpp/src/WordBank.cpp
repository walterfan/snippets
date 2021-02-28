#include "WordBank.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

bool comparePair(pair<string, int>& a, 
         pair<string, int>& b) 
{ 
    return a.second > b.second; 
} 

WordBank::WordBank(const string & words_file): m_wordCount(0) {
	ifstream is(words_file.data());
	if (!is) {
		throw invalid_argument("unable open file");
	}
	string word;
	while (is >> word) {
		m_wordCount ++;
		if (!hasWord(word)) {
			addWord(word);
		}else {
			increaseWordCount(word);
		}
	}
}

int WordBank::getWordRank(const std::string& word) const {
	
	int count = getWordCount(word);
	if (count == 0) {
		return 0;
	}
	
	int rank = 1;
	for (const auto&[key, value] : this->m_mapWords) {
		if (value > count) {
			rank++;
		}
	}
	return rank;
}

int WordBank::getWordCount(const std::string& word) const {
	string str = convertString(word.data());
	auto it = m_mapWords.find(str);
	
	if (it != m_mapWords.end()) {
		return it->second;
	}
	return 0;
}


int WordBank::getTotalWordCount() const {
	return m_wordCount;
}

int WordBank::getUniqueWordCount() const {
	return m_mapWords.size();
}

bool WordBank::hasWord(const string & word) const {
	string str = convertString(word.data());
	auto it = m_mapWords.find(str);
	
	if (it != m_mapWords.end()) {
		return true;
	}
	return false;
}
void WordBank::increaseWordCount(const string & word) {
	string str = convertString(word.data());
	auto it = m_mapWords.find(str);

	if (it != m_mapWords.end()) {
		it->second++;
	}
}
void WordBank::addWord(const string & word) {
	
	string str = convertString(word);
	if (str.empty()) {
		return;
	}
	//cout << "insert " << word  << " -> " << str << endl;
	m_mapWords.insert(make_pair(str, 1));
}

void WordBank::sortWords() {
/*
	for (auto& pair : m_mapWords) {
		m_setWords.insert(pair);
	}
*/
   
    for (auto& pair : m_mapWords ) { 
        m_vecWords.push_back(pair); 
    } 
  
    // Sort using comparator function 
    sort(m_vecWords.begin(), m_vecWords.end(), comparePair); 
  

} 

void WordBank::printTop(int n) const {
	for (auto pair : m_vecWords) {
		cout << pair.first << ": " << pair.second << endl;
		if (--n <= 0) {
			break;
		}
	}

}

string convertString(const string & word) {
	string str("");
	for (size_t i = 0; i < word.length(); ++i) {
		uint8_t ch = word[i];
		if(ch > 0 && ch < 255 && isalpha(ch)) {
			str.push_back(tolower(ch));
		}
	}
	return str;
}