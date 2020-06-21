#include "gmock/gmock.h"
#include <string>
#include <iostream>
#include <memory>

using namespace std;
using namespace testing;

using ::testing::Return;
using ::testing::Mock;

typedef enum {
    STR = 0,
    SIP,
    SOAP,
    PDU,
    DSA,
    HTTP
} test_message_type;

typedef enum {
    test_err_status_ok = 0,
    test_err_status_error = 1,
    test_err_status_ignore = 2,
    test_err_status_retry = 3

} test_status_t;

typedef test_status_t (*message_handler)(test_message_type msg_type, void * test_msg);

struct MessageHandler {
    MessageHandler() {

    }
    MessageHandler(test_message_type msgType, message_handler pHandler) {
        msg_type = msgType;
        msg_handler = pHandler;

    }

    void handle(void* pMsg) {
        msg_result =  (*msg_handler)(msg_type, pMsg);
    }
    test_message_type msg_type;
    test_status_t msg_result;
    message_handler msg_handler;
};

test_status_t str_message_handler(test_message_type msg_type, void* test_msg) {
    if(msg_type != STR) {
        return test_err_status_ignore;
    }
    string* pMsg = static_cast<string*>(test_msg);
    cout << *pMsg << endl;

    return test_err_status_ok;
}

struct st_node
{
	struct st_node * pNext;
	int nValue;
};


typedef void (*func_t)(int);

void foreach(struct st_node* pList, func_t func)
{
	while(pList){
		func(pList->nValue);
		pList =pList->pNext;

	}
}

void f(int n)
{
	printf("node(?)=%d\n", n);
}

class Rectangle {
public:
    Rectangle(std::string name):m_name(name) {}
    virtual int draw(int x1, int y1, int x2, int y2) {
        printf("--> draw rectangle (%d, %d) to (%d, %d)", x1, y1, x2, y2);
        return (x2 - x1) * (y2 - y1);

    }  
    std::string m_name; 
};

class Square: public Rectangle {
public:
    Square(std::string name):Rectangle(name) {}
     virtual int draw(int x1, int y1, int x2, int y2) {
        printf("--> draw square (%d, %d) to (%d, %d)\n", x1, y1, x2, y2);
        return (x2 - x1) * (y2 - y1);
    } 
};

typedef int (Square::*DRAW_FN_PTR)(int x1, int y1, int x2, int y2);

TEST(functorTest, testcase1)
{
    cout<<"--- functorTest.testcase1 --"<<endl;
	
    struct st_node *pList = NULL;
    struct st_node *pNode = NULL;

    int i = 0;

    for(; i<4; i++)
    {
    	pNode = (struct st_node *)malloc(sizeof(struct st_node));
    	pNode->nValue = i;
    	pNode->pNext = pList;
    	pList = pNode;
    }

    i = 0;
    pNode = pList;
    while(pNode)
    {
    	printf("node(%d)=%d\n", i++, pNode->nValue);
    	pNode = pNode->pNext;

    }
    foreach(pList,f);
}

TEST(functorTest, testcase2)
{
    cout<<"--- functorTest.testcase2 --"<<endl;
    
    MessageHandler*  pHandler = new MessageHandler(STR, &str_message_handler);

    string test_msg = "hello baby, come on";

    pHandler->handle(&test_msg);
    
    EXPECT_EQ(pHandler->msg_result, test_err_status_ok);

    delete pHandler;

}

TEST(functorTest, testcase3)
{
    cout<<"--- functorTest.testcase3 --"<<endl;
    shared_ptr<Rectangle> p1 = std::make_shared<Rectangle>("box");
    std::cout << "Created a shared Rectangle\n"
              << "  p1.get() = " << p1.get()
              << ", p1.use_count() = " << p1.use_count() << '\n';
    p1->draw(10, 10, 50, 50);

    shared_ptr<Square> p2 = std::make_shared<Square>("box");
    std::cout << "Created a shared Square\n"
              << "  p2.get() = " << p2.get()
              << ", p2.use_count() = " << p2.use_count() << '\n';
    p2->draw(10, 10, 50, 50);

    DRAW_FN_PTR fnPtr = &Square::draw; 
    Square* thePtr = p2.get();
    (thePtr->*fnPtr)(20, 20, 40, 40);

}
