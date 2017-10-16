/*
refer to 
* http://www.geeksforgeeks.org/greedy-algorithms-set-3-huffman-coding/
* http://www.cplusplus.com/forum/general/112141/
*/
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <string>
#include <map>
#include <vector>
#include <iostream>   
#include <functional>
#include <queue>



using namespace std;       



struct BitsChar{
    unsigned char* c;
    int shift_count;
    std::string BITS;

    BitsChar():shift_count(0) {
        c = (unsigned char*)calloc(1, sizeof(char));
    }
    ~BitsChar();

    int insertBits(ostream& os) {
        int total = 0;

        while(BITS.length())
        {
            if(BITS[0] == '1')
                *c |= 1;
            *c <<= 1;
            ++shift_count;
            ++total;
            BITS.erase(0, 1);

            if(shift_count == 7)
            {
                writeBits(os);
                shift_count = 0;
                free(c);
                c = (unsigned char*)calloc(1, sizeof(char));
            }
        }

        //Account for any trailing bits and push them over
        if(shift_count > 0)
        {
            *c <<= (8 - shift_count);
            writeBits(os);
            free(c);
            c = (unsigned char*)calloc(1, sizeof(char));
        }

        return total;
    }
    void writeBits(ostream& os) {
        os << *c;
    }
    
};

struct HCNode {
    char data;
    int freq;
    HCNode* left;
    HCNode* right;

    HCNode(char data, unsigned freq):left(NULL), right(NULL)
    {
        this->data = data;
        this->freq = freq;
    }

    ostream& encode(ostream& os) {
        os << "data=" << this->data << ", freq=" << this->freq <<endl;
        if(this->left)
            this->left->encode(os);
        if(this->right)
            this->right->encode(os);

        return os;
    }
 
};

struct HCNodeComparator
{
    bool operator()(HCNode* l, HCNode* r)
    {
        return (l->freq > r->freq);
    }
};

class HCTree {
public:


    HCTree(map<char, int>& datamap):m_dataFreqMap(datamap) {

    }

    void Build()
    {
        struct HCNode *left, *right, *top;
     
        // Create a min heap & inserts all characters of data[]
        
     
        map<char, int>::const_iterator it = m_dataFreqMap.begin();
        for(; it != m_dataFreqMap.end(); ++it )
        {
            m_minHeap.push(new HCNode(it->first, it->second));
        }

        // Iterate while size of heap doesn't become 1
        while (m_minHeap.size() > 1)
        {
            // Extract the two minimum freq items from min heap
            left = m_minHeap.top();
            m_minHeap.pop();
     
            right = m_minHeap.top();
            m_minHeap.pop();
     
            // Create a new internal node with frequency equal to the
            // sum of the two nodes frequencies. Make the two extracted
            // node as left and right children of this new node. Add
            // this node to the min heap
            // '$' is a special value for internal nodes, not used
            top = new HCNode('$', left->freq + right->freq);
            top->left = left;
            top->right = right;
            m_minHeap.push(top);
        }
        Traverse(m_minHeap.top(), "");
     
    }


    void Traverse(HCNode* pNode, string str) {
        if (!pNode)
            return;
 
        if (pNode->data != '$') {
            cout << pNode->data << ": " << str << endl;
            m_huffmanCodeMap[pNode->data] = str;
        }
 
        Traverse(pNode->left, str + "0");
        Traverse(pNode->right, str + "1");
    }


private:
    priority_queue<HCNode*, vector<HCNode*>, HCNodeComparator> m_minHeap;
    map<char, int>& m_dataFreqMap;
    map<char, string> m_huffmanCodeMap;
};

#endif