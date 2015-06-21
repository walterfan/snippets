#include "gmock/gmock.h"
#include <string>
#include <iostream>

using namespace std;
using namespace testing;

using ::testing::Return;
using ::testing::Mock;

typedef struct person {
    int age;
    char sex;
} person_t;

person_t walter = {38, 'm'};
person_t alice = {35, 'f'};

int update_person(person** ppPerson, int* pAge)
{
    if(*pAge > 26)
        *ppPerson = &walter;
    else
        *ppPerson = &alice;
    *pAge = (*ppPerson)->age;
    return *pAge;
}

TEST(PointerTest, pointponter)
{
    cout<<"--- PointerTest, pointponter --"<<endl;

    person_t* pPerson = NULL;
    int age = 36;
    update_person(&pPerson, &age);

    cout<<"person="<<pPerson->sex<<endl;
    cout<<"age="<<age<<endl;



}
