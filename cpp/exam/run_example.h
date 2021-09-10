#ifndef RUN_EXAMPLE_H_
#define RUN_EXAMPLE_H_

#include <stdio.h>
#include <stdint.h>

#include <string>
#include <map>
#include <iostream>
#include <memory>

#include <unordered_map>
#include <boost/log/trivial.hpp>
#include <boost/program_options.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/assert.hpp>

//old function pointer
typedef int (*exam_func_ptr)(int argc, char** argv);
//new function object
typedef std::function<int(int, char**)> exam_func_t;


template<typename T, typename... Ts>
std::unique_ptr<T> my_make_unique(Ts&&... params) {
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}


class Command
{
public:
    Command();
    Command(std::string name);

    Command(const Command& other);
    Command& operator=(const Command& other);

    Command(Command&& other);
    Command& operator=(Command&& other);

    virtual ~Command();

    void setName(const std::string& name);
    void setParameter(const std::string& name, const std::string& value);
    void setData(const uint8_t* pData, size_t length);

    friend std::ostream& operator<<(std::ostream&, const Command& obj);

private:
    std::string m_name = "";
    std::map<std::string, std::string> m_parameters;
    size_t m_length = 0;
    uint8_t* m_data = nullptr;
};

class ExampleRunner: boost::noncopyable {
public:
    ExampleRunner();
    //no need by noncopyable
    //ExampleRunner(const ExampleRunner& rhs);
    //ExampleRunner& operator=(const ExampleRunner& rhs);

    virtual ~ExampleRunner();

    void init();

    size_t size() const;

    void register_example(const std::string& name, const exam_func_t &exam);

    int execute_example(const std::string& name, int argc, char** argv) const;
private:
    volatile uint32_t m_example_count = 0;
    std::unordered_map<std::string, exam_func_t> m_func_examples;        
};


#endif