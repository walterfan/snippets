#include "WordBank.h"
#include <iostream>
#include <fstream>

using namespace std;




WordBank::WordBank(string_view words_file) {
	ifstream is(words_file.data());
	if (!is) {
		throw invalid_argument("unable open file");
	}
	string word;
	while (is >> word) {
		if (!hasWord(word)) {
			addWord(word);
		}else {
			increaseWordCount(word);
		}
	}
}

int WordBank::getWordRank(std::string_view word) const {
	
	int count = getWordCount(word);
	if (count == 0) {
		return 0;
	}
	
	int rank = 1;
	for (const auto&[key, value] : this->m_mapWords) {
		//std::cout << key << " = " << value << "; ";
		if (value > count) {
			rank++;
		}
	}
	return rank;
}

int WordBank::getWordCount(std::string_view word) const {
	string str = convertString(word.data());
	auto it = m_mapWords.find(str);
	
	if (it != m_mapWords.end()) {
		return it->second;
	}
	return 0;
}

int  WordBank::size() const {
	return m_mapWords.size();
}


bool WordBank::hasWord(string_view word) const {
	string str = convertString(word.data());
	auto it = m_mapWords.find(str);
	
	if (it != m_mapWords.end()) {
		return true;
	}
	return false;
}
void WordBank::increaseWordCount(string_view word) {
	string str = convertString(word.data());
	auto it = m_mapWords.find(str);

	if (it != m_mapWords.end()) {
		it->second++;
	}
}
void WordBank::addWord(string_view word) {
	
	string str = convertString(word);
	if (str.empty()) {
		return;
	}
	//cout << "insert " << word  << " -> " << str << endl;
	m_mapWords.insert(make_pair(str, 1));
}

void WordBank::sortWords() {

	for (auto pair : m_mapWords) {
		m_setWords.insert(pair);
	}

}

void WordBank::printTop(int n) const {
	for (auto pair : m_setWords) {
		cout << pair.first << ": " << pair.second << endl;
		if (--n <= 0) {
			break;
		}
	}

}

string convertString(string_view word) {
	string str("");
	for (size_t i = 0; i < word.length(); ++i) {
		uint8_t ch = word[i];
		if(ch > 0 && ch < 255 && isalpha(ch)) {
			str.push_back(tolower(ch));
		}
	}
	return str;
}