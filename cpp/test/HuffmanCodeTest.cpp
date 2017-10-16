#include "gmock/gmock.h"
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <map>

#include "HuffmanCode.h"
using namespace std;
using namespace testing;

using ::testing::Return;
using ::testing::Mock;

int read_file(string strFileName, map<char, int>& charFreqMap) {
    ifstream txt_file(strFileName.c_str());  

    if(!txt_file)  {
        cerr << strFileName << " read failed" << endl;
        return -1;
    }
    int i = 0;
    char c;
    while(txt_file.get(c)) {
        map<char, int>::const_iterator it = charFreqMap.find(c);
        if(it == charFreqMap.end()) {
            charFreqMap[c] = 1;
        } else {
            charFreqMap[c] = it->second + 1;
        }
        i++;
    }
    cout << "total count: " << i << endl;
    map<char, int>::const_iterator it = charFreqMap.begin();
    for(; it != charFreqMap.end(); ++it )
    {
        cout << it->first << "=" << it->second << endl;

    }

    return i;

}

TEST(HuffmanCodesTest, buildTest)
{
    map<char, int> charFreqMap;
    int nSize0 = read_file("./dat/declaration_of_independence.txt", charFreqMap);
    ASSERT_FALSE(charFreqMap.empty());
    cout << "original size is " << nSize0 << endl;

    HCTree hcTree(charFreqMap);
    hcTree.Build();

    
 
}