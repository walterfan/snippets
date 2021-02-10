#ifndef __WORD_BANK_H__
#define __WORD_BANK_H__

#pragma once

#include <string_view>
#include <string>
#include <map>
#include <set>


struct comp {
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
	WordBank(std::string_view words_file);

	int getWordRank(std::string_view name) const;

	int getWordCount(std::string_view name) const;

	void sortWords();

	void printTop(int n) const;

	int size() const;

private:

	bool hasWord(std::string_view word) const;

	void increaseWordCount(std::string_view word);

	void addWord(std::string_view word);

	std::map < std::string, int> m_mapWords;

	std::set<std::pair<std::string, int>, comp> m_setWords;;

};

std::string convertString(std::string_view word);

#endif