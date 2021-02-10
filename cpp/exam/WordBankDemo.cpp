#include "WordBank.h"
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	string word_search = "the";
	string word_file = "quote.txt";
	int topN = 10;
	if (argc > 1) {
		word_search = argv[1];
		cout << "Make statistics for word count and rank: " <<convertString(word_search) << endl;
	}
	if (argc > 2) {
		word_file = argv[2];
		cout << "Read file: " << word_file << endl;
	}
	if (argc > 3) {
		topN = atoi(argv[3]);
	}
	
	try {
        WordBank wordbank(word_file);
        wordbank.sortWords();

        std::cout << "wordbank size: " << wordbank.size() << endl;
        cout << word_search << "'s count=" << wordbank.getWordCount(word_search) << endl;
        cout << word_search  << "'s rank=" << wordbank.getWordRank(word_search) << endl;
        cout << "--- top "  << topN << " ---" << endl;
        wordbank.printTop(topN);
	} catch(const invalid_argument& e) {
        cerr << "Caught exeption: " <<e.what() <<endl;

    }
    return 0;

}

