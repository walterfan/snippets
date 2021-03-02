#include "WordBank.h"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <boost/timer/timer.hpp>


using namespace std;
using namespace boost::timer;

int main(int argc, char *argv[])
{
	string word_search = "rtp";
	string word_file = "rfc3550.txt";
	int topN = 10;
	if (argc > 1) {
		word_search = argv[1];
		cout << "Make statistics for word count and rank: " <<convertString(word_search) << endl;
	} else {
		cout << "usage: " << argv[0] << " <search_word> <input_file> <topN>" << endl;
		cout << "example: " << argv[0] << " " << word_search << " " << word_file << " " << topN <<endl;
	}
	if (argc > 2) {
		word_file = argv[2];
		cout << "Read file: " << word_file << endl;
	}
	if (argc > 3) {
		topN = atoi(argv[3]);
	}
	//cpu_timer timer;
	try {
		boost::timer::auto_cpu_timer timer;
		
        WordBank wordbank(word_file);
        wordbank.sortWords();
        std::cout << "wordbank total word count: " << wordbank.getTotalWordCount() << endl;
        std::cout << "wordbank unique word count: " << wordbank.getUniqueWordCount() << endl;
        cout << word_search << "'s count=" << wordbank.getWordCount(word_search) << endl;
        cout << word_search  << "'s rank=" << wordbank.getWordRank(word_search) << endl;
        cout << "--- top "  << topN << " ---" << endl;
        wordbank.printTop(topN);

	} catch(const invalid_argument& e) {
        cerr << "Caught exeption: " <<e.what() <<endl;

    }
    return 0;

}
