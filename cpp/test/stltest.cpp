#include "gmock/gmock.h"
#include <string>
#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>

using namespace std;
using namespace testing;

using ::testing::Return;
using ::testing::Mock;

// timestamp returns the current time as a string
std::string timestamp();

class LogStatement;
ostream& operator<<(ostream& ost, const LogStatement& ls);

class LogStatement
{
public:
        LogStatement(std::string s): data(s), time_string( timestamp() )
        { };

        //This method handles all the outputs.
        friend ostream& operator<<(ostream&, const LogStatement&);
private:
        std::string data;
        std::string time_string;

};

ostream& operator<<(ostream& ost, const LogStatement& ls)
{
        ost<<"["<<ls.time_string<<"] "<<ls.data;
        return ost;
}

std::string timestamp()
{
        //Notice the use of a stringstream, yet another useful stream medium!
        ostringstream stream;
        time_t rawtime;
        tm * timeinfo;

        time(&rawtime);
        timeinfo = localtime( &rawtime );

        stream << (timeinfo->tm_year)+1900<<"-"<<timeinfo->tm_mon
        <<"-"<<timeinfo->tm_mday<<" "<<timeinfo->tm_hour
        <<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec;

        return stream.str();
}

TEST(StlTest, StringTest)
{
    cout<<"--- StringTest.find --"<<endl;
    string strTransaction = "APP|APP_AUTHENTICATE_RESPONSE|0|3";
    ASSERT_TRUE(strTransaction.find("APP|APP_AUTHENTICATE_RESPONSE|0|") != string::npos);
}


TEST(StlTest, IostreamTest)
{
	ostringstream log_data;

	log_data<<"waltertest"<<endl;

	LogStatement log_entry(log_data.str());

	cout << log_entry << endl;

	ofstream logfile("logfile", ios::app);

	// check for errors opening the file
	if (logfile) {
		logfile << log_entry << endl;
		logfile.close();
	}

}

