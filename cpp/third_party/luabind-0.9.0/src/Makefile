src = class.cpp \
      class_info.cpp \
      class_registry.cpp \
      class_rep.cpp \
      create_class.cpp \
      error.cpp \
      exception_handler.cpp \
      function.cpp \
      inheritance.cpp \
      link_compatibility.cpp \
      object_rep.cpp \
      open.cpp \
      pcall.cpp \
      scope.cpp \
      stack_content_by_name.cpp \
      weak_ref.cpp \
      wrapper_base.cpp

obj = $(patsubst %.cpp, %.o, $(src))

CFLAGS += -O2 -Wall -I../../lua-5.2.1/src/ -I../ -I../../../boost
RANLIB = ranlib

all: libluabind.a

$(obj): %.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

libluabind.a: $(obj)
	$(AR) $(ARFLAGS) $@ $^
	$(RANLIB) $@

clean:
	-rm -f *.o *.a
