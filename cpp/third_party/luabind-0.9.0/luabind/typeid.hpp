// Copyright Daniel Wallin 2008. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef LUABIND_TYPEID_081227_HPP
# define LUABIND_TYPEID_081227_HPP

# include <boost/operators.hpp>
# include <cstdlib>
# include <cstring>
# include <typeinfo>
# include <luabind/detail/primitives.hpp>

// boost/units/detail/utility.hpp
# if defined(__GLIBCXX__) || defined(__GLIBCPP__)
#  define LUABIND_USE_DEMANGLING
#  include <cxxabi.h>
# endif // __GNUC__

namespace luabind {

# ifdef BOOST_MSVC
#  pragma warning(push)
// std::type_info::before() returns int, rather than bool.
// At least on MSVC7.1, this is true for the comparison
// operators as well.
#  pragma warning(disable:4800)
# endif

class type_id
  : public boost::less_than_comparable<type_id>
{
public:
    type_id()
      : id(&typeid(detail::null_type))
    {}

    type_id(std::type_info const& id)
      : id(&id)
    {}

    bool operator!=(type_id const& other) const
    {
        return std::strcmp(id->name(), other.id->name()) != 0;
    }

    bool operator==(type_id const& other) const
    {
        return std::strcmp(id->name(), other.id->name()) == 0;
    }

    bool operator<(type_id const& other) const
    {
        return std::strcmp(id->name(), other.id->name()) < 0;
    }

    std::string name() const
    {
# ifdef LUABIND_USE_DEMANGLING
        int status;
        char* buf = abi::__cxa_demangle(id->name(), 0, 0, &status);
        if (buf != 0) {
            std::string name(buf);
            std::free(buf);
            return name;
        }
# endif
        return id->name();
    }

private:
    std::type_info const* id;
};

# ifdef BOOST_MSVC
#  pragma warning(pop)
# endif

} // namespace luabind

#endif // LUABIND_TYPEID_081227_HPP

