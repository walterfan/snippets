#include "run_example.h"

using namespace std;
namespace po = boost::program_options;

extern int std_function_test(int argc, char** argv);
extern int function_demo(int argc, char** argv);
extern int lambda_demo(int argc, char* argv[]);
extern int rvalue_demo(int argc, char* argv[]);
extern int smart_ptr_demo(int argc, char** argv);

const int CASE_COUNT = 5;

const char* usage = R"name(please specify example name:
    function_demo
    or lambda_demo
    or rvalue_demo
    or smart_ptr_demo
    or std_function_test
)name";


//C++11: delegate constructor
Command::Command():Command("") {
    BOOST_LOG_TRIVIAL(trace) << "line " <<__LINE__<< ". construct: " << m_name << "@" <<this;    
}

Command::Command(string name):m_name(name) {
    BOOST_LOG_TRIVIAL(trace) << "line " <<__LINE__<< ". construct: " << m_name << "@" <<this;    
}

Command::Command(const Command& other) {
    BOOST_LOG_TRIVIAL(trace) << "line " <<__LINE__<< ". copy construct: " << m_name << "@" <<this;
    m_name = other.m_name;
    for (const auto& kv : other.m_parameters) {
        BOOST_LOG_TRIVIAL(trace) << kv.first << " has value " << kv.second;
        m_parameters.insert(kv);
    }
    std::copy(other.m_data, other.m_data + m_length, m_data);
}

Command& Command::operator=(const Command& other) {
	BOOST_LOG_TRIVIAL(trace) << "line " <<__LINE__<< ". operator =: " << other.m_name;
    if (this != &other)
    {
        this->m_name = other.m_name;
        for (const auto& kv : other.m_parameters) {
            std::cout << kv.first << " has value " << kv.second << std::endl;
            m_parameters.insert(kv);
        }
        // Free the existing resource.
        if(m_data) {
            delete[] m_data;
        }
        m_length = other.m_length;
        m_data = new uint8_t[m_length];
        std::copy(other.m_data, other.m_data + m_length, m_data);
    }
    return *this;
}

Command::Command(Command&& other) {
    BOOST_LOG_TRIVIAL(trace) << "line " <<__LINE__<< " move copy construct: " << other.m_name << "@" <<this;
    m_name = std::move(other.m_name);
    m_parameters = std::move(other.m_parameters);

    // Copy the data pointer and its length from the source object.
    m_data = other.m_data;
    m_length = other.m_length;

    // Release the data pointer from the source object so that
    // the destructor does not free the memory multiple times.
    other.m_data = nullptr;
    other.m_length = 0;

}

Command& Command::operator=(Command&& other) 
{
	BOOST_LOG_TRIVIAL(trace) << "line " <<__LINE__<< " move operator ==" << other.m_name;
   if (this != &other)
   {
      m_name = std::move(other.m_name);
      m_parameters = std::move(other.m_parameters);
      // Free the existing resource.
      delete[] m_data;

      // Copy the data pointer and its length from the
      // source object.
      m_data = other.m_data;
      m_length = other.m_length;

      // Release the data pointer from the source object so that
      // the destructor does not free the memory multiple times.
      other.m_data = nullptr;
      other.m_length = 0;
   }
   return *this;
}

Command::~Command() {
    BOOST_LOG_TRIVIAL(trace) << "line " <<__LINE__<< ". destruct: " << m_name ;
}


void Command::setName(const string& name) {
    m_name = name;
}
void Command::setParameter(const string& name, const string& value) {
    m_parameters[name] = value;
}

void Command::setData(const uint8_t* pData, size_t length) {
    BOOST_LOG_TRIVIAL(trace) << "line " <<__LINE__<< ". setData: " << m_name;
	if(nullptr != m_data) {
        delete[] m_data;
    }
	
    m_length = length;
	m_data = new uint8_t[length];
    std::copy(pData, pData + length, m_data);
}

ostream& operator<<(ostream& os, const Command& obj)
{
    os << obj.m_name;
    os << ": ";
    //for (map<string, string>::iterator it = obj.m_parameters.begin(); it != obj.m_parameters.end(); ++it)
    for (const auto& kv : obj.m_parameters)
    {
        os << kv.first << "=" << kv.second << endl;
    }
    for(size_t i=0; i< obj.m_length; ++i) {
        os << *(obj.m_data + i);
    }
    return os;
}


ExampleRunner::ExampleRunner(): m_example_count(0),m_func_examples() {
    BOOST_LOG_TRIVIAL(trace)<<"* ExampleRunner construct: " ;    
}

ExampleRunner::~ExampleRunner() {
    BOOST_LOG_TRIVIAL(trace)<<"* ExampleRunner destruct: ";
}

void ExampleRunner::init() {
    register_example("function_demo", function_demo);
    register_example("smart_ptr_demo", smart_ptr_demo);
    register_example("lambda_demo", lambda_demo);
	register_example("rvalue_demo", rvalue_demo);
    register_example("std_function_test", std_function_test);
}

void ExampleRunner::register_example(const string& name, const exam_func_t &exam)
{
    m_example_count++;
    m_func_examples[name] = exam;
}

int ExampleRunner::execute_example(const string& name, int argc, char** argv) const
{
    auto it = m_func_examples.find(name);
    if(it != m_func_examples.end()) {
        BOOST_LOG_TRIVIAL(trace) << "execute "<< it->first;
        exam_func_t func = it->second;
        return func(argc, argv);
    }
    BOOST_LOG_TRIVIAL(trace) << "not registered "<< name;
    return -1;
}


size_t ExampleRunner::size() const {
    return m_func_examples.size();
}

int main(int argc, char** argv)
{
    unique_ptr<ExampleRunner> runner = my_make_unique<ExampleRunner>();
    runner->init();
    BOOST_ASSERT_MSG(runner->size()==CASE_COUNT, "example count should be 2");
    //c++11 R"raw string"
    po::options_description desc("Allowed options:");
    
    desc.add_options()
        ("help,h", "produce help message")
        ("name,n", po::value<string>(), usage)
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);    

    if (vm.count("help")) {
        BOOST_LOG_TRIVIAL(trace) << desc << "\n";
        return 1;
    }

    if (vm.count("name")) {
        BOOST_LOG_TRIVIAL(trace) << "* example name is "<< vm["name"].as<string>() << ".";
        runner->execute_example(vm["name"].as<string>(), argc, argv);
    } else {
        BOOST_LOG_TRIVIAL(trace) << "example name was not set.";
        BOOST_LOG_TRIVIAL(trace) << desc ;
    }

    return 0;
}
