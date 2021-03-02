#ifndef __WORD_BANK_H__
#define __WORD_BANK_H__

#include <cstdint>
#include <string>
#include <map>
#include <set>
#include <vector>

struct PairComparator {
	template <typename T>
	bool operator()(const T& l, const T& r) const
	{
		if (l.second != r.second) {
			return l.second > r.second;
		}
		return l.first < r.first;
	}
};

class WordBank
{
public:
	WordBank(const std::string& words_file);

	int getWordRank(const std::string& name) const;

	int getWordCount(const std::string& name) const;

	void sortWords();

	void printTop(int n) const;

	int getTotalWordCount() const;

	int getUniqueWordCount() const;

private:

	bool hasWord(const std::string& word) const;

	void increaseWordCount(const std::string& word);

	void addWord(const std::string& word);

	std::map<std::string, int> m_mapWords;

	std::set<std::pair<std::string, int>, PairComparator> m_setWords;;

	std::vector<std::pair<std::string, int>> m_vecWords; 

	uint32_t m_wordCount;

};

std::string convertString(const std::string& word);

#endif