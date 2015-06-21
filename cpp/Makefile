# Walter created on 5/1/2012
USER_DEPTH=../../..

CXX = g++
AR  = ar

BASE_DIR=.
BIN_DIR = ./bin
SRC_DIR = ./src
TEST_DIR = ./test
EXAM_DIR = ./exam
INC_DIR = ./inc
LIB_DIR = ../bin

PLATFORM = cygwin

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    PLATFORM = linux
endif

TEST_TOOL_INC=$(BASE_DIR)/third_party
TEST_TOOL_LIB_DIR=$(BASE_DIR)/lib/$(PLATFORM)

LD_FLAGS = -lpthread -lc -lm -lz -ldl
#-L$(TEST_TOOL_LIB_DIR)

ifndef ACE_ROOT
	ACE_ROOT=$(USER_DEPTH)/ACE_wrappers
endif

ifndef BOOST_ROOT
	BOOST_ROOT=$(USER_DEPTH)/boost_1_53_0
endif

ifndef SRTP_DIR
	SRTP_DIR=$(USER_DEPTH)/libsrtp
endif

ifndef GMOCK_DIR
    GMOCK_DIR=$(TEST_TOOL_INC)
    GTEST_DIR=$(TEST_TOOL_INC)
    GMOCK_LIB_DIR=${TEST_TOOL_LIB_DIR}
    GTEST_LIB_DIR=${TEST_TOOL_LIB_DIR}
else
	GTEST_DIR = $(GMOCK_DIR)/gtest
	GMOCK_LIB_DIR=${GMOCK_DIR}/lib/.libs
	GTEST_LIB_DIR=${GTEST_DIR}/lib/.libs
endif

LD_FLAGS += -L$(BOOST_ROOT)/stage/lib -L$(GTEST_LIB_DIR) -L$(GMOCK_LIB_DIR) 
#-lgmock -lgtest

LUA_ROOT=$(TEST_TOOL_INC)/lua
LUA_BIND_ROOT=$(TEST_TOOL_INC)/luabind-0.9.0

C_FLAGS =  -DLINUX -D_XOPEN_SOURCE=500 -D_BSD_SOURCE -Wall -g 

INC_FLAGS = -I$(INC_DIR) -I$(SRC_DIR) -I. \
	-I/usr/include/libxml2 \
	-I../h -I./inc -I./src \
	-I./com \
	-I$(ACE_ROOT) \
	-I$(BOOST_ROOT) \
	-I${GTEST_DIR} \
	-I${GMOCK_DIR}/include \
	-I${GTEST_DIR}/include \
	-I${LUA_ROOT} \
	-I$(LUA_BIND_ROOT) \
	-I$(SRTP_DIR)/include \
	-I$(SRTP_DIR)/crypto/include

CXX_FLAGS = -Wall -g $(INC_FLAGS)
#-Qy -rdynamic


ACE_LD_FLAGS = -L$(ACE_ROOT)/lib -lACE

LUA_STATIC_LIB=${TEST_TOOL_LIB_DIR}/liblua.a
SRTP_STATIC_LIB=${SRTP_DIR}/libsrtp.a
GTEST_STATIC_LIB=${GTEST_LIB_DIR}/libgtest.a
GMOCK_STATIC_LIB=${GMOCK_LIB_DIR}/libgmock.a

# appllication
WF_TEST = $(BIN_DIR)/waltertest.exe
LUA_TEST = $(BIN_DIR)/luatest.exe
LUA_BIND_TEST = $(BIN_DIR)/luabindtest.exe
ECHO_CLIENT = $(BIN_DIR)/EchoClient.exe
ECHO_SERVER = $(BIN_DIR)/EchoServer.exe

# objects
ECHO_CLIENT_OBJS = $(EXAM_DIR)/echo_client_ev.o 
ECHO_SERVER_OBJS = $(EXAM_DIR)/echo_server_ev.o

LUA_TEST_OBJS = $(TEST_DIR)/luatest.o $(SRC_DIR)/LuaUtil.o
LUA_BIND_TEST_OBJS = $(TEST_DIR)/luabindtest.o $(SRC_DIR)/LuaUtil.o

WF_TEST_OBJS = $(TEST_DIR)/waltertest.o \
	$(SRC_DIR)/showbytes.o \
	$(SRC_DIR)/NetworkUtil.o \
	$(SRC_DIR)/FileUtil.o \
	$(SRC_DIR)/StringUtil.o \
	$(SRC_DIR)/Observer.o \
	$(SRC_DIR)/RtpUtil.o
#	$(TEST_DIR)/epolltest.o

UNIT_TEST_OBJS =  \
	$(TEST_DIR)/unittest.o \
	$(TEST_DIR)/stltest.o \
	$(TEST_DIR)/strtest.o \
	$(TEST_DIR)/virtualtest.o \
	$(TEST_DIR)/basictest.o \
	$(TEST_DIR)/functortest.o \
	$(TEST_DIR)/pointertest.o 

ACE_TEST_OBJS = $(TEST_DIR)/unittest.o \
	$(TEST_DIR)/message_block_test.o 

all: unittest

waltertest:$(WF_TEST)

luatest:$(LUA_TEST)

luabindtest:$(LUA_BIND_TEST)

timeserver:  $(TEST_DIR)/timeserver.o
	@if [ ! -d $(BIN_DIR) ]; then mkdir -p $(BIN_DIR); fi
	$(CXX) $(CXX_FLAGS) -o $(BIN_DIR)/timeserver $^ $(LD_FLAGS)
	
unittest:$(UNIT_TEST_OBJS) $(SRTP_STATIC_LIB) $(GMOCK_STATIC_LIB) $(GTEST_STATIC_LIB) 
	@if [ ! -d $(BIN_DIR) ]; then mkdir -p $(BIN_DIR); fi
	$(CXX) $(CXX_FLAGS) -o $@ $^ $(LD_FLAGS) -lboost_system -lboost_thread

$(WF_TEST):$(WF_TEST_OBJS) 
	@if [ ! -d $(BIN_DIR) ]; then mkdir -p $(BIN_DIR); fi
	$(CXX) $(CXX_FLAGS) -o $@ $^ $(LD_FLAGS)

$(LUA_TEST):$(LUA_TEST_OBJS) $(LUA_STATIC_LIB)
	@if [ ! -d $(BIN_DIR) ]; then mkdir -p $(BIN_DIR); fi
	$(CXX) $(CXX_FLAGS) -o $@ $^ $(LD_FLAGS) -llua -lluabind

$(LUA_BIND_TEST):$(LUA_BIND_TEST_OBJS) 
	@if [ ! -d $(BIN_DIR) ]; then mkdir -p $(BIN_DIR); fi
	$(CXX) $(CXX_FLAGS) -o $@ $^ $(LD_FLAGS) -llua -lluabind


acetest:$(ACE_TEST_OBJS) $(GMOCK_STATIC_LIB) 
	@if [ ! -d $(BIN_DIR) ]; then mkdir -p $(BIN_DIR); fi
	$(CXX) $(CXX_FLAGS) -o $(BIN_DIR)/ace_test $^ $(LD_FLAGS) $(ACE_LD_FLAGS)
boosttest: $(TEST_DIR)/boosttest.o
	@if [ ! -d $(BIN_DIR) ]; then mkdir -p $(BIN_DIR); fi
	$(CXX) $(CXX_FLAGS) -o $(BIN_DIR)/boosttest $^ $(LD_FLAGS) 
	
$(SRC_DIR)/%.o:$(SRC_DIR)/%.cpp
	@if [ ! -d $(BIN_DIR) ]; then mkdir -p $(BIN_DIR); fi
	$(CXX) $(CXX_FLAGS) -c $< -o $@
	
$(TEST_DIR)/%.o:$(TEST_DIR)/%.cpp
	@if [ ! -d $(BIN_DIR) ]; then mkdir -p $(BIN_DIR); fi
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(EXAM_DIR)/%.o:$(EXAM_DIR)/%.cpp
	@if [ ! -d $(BIN_DIR) ]; then mkdir -p $(BIN_DIR); fi
	$(CXX) $(CXX_FLAGS) -c $< -o $@ -I$(USER_DEPTH)/libev

echoclient: $(ECHO_CLIENT_OBJS)
	$(CXX) $(CXX_FLAGS) -o $@ $^ $(LD_FLAGS) -L$(USER_DEPTH)/libev/.libs -lev
	
echoserver: $(ECHO_SERVER_OBJS)
	$(CXX) $(CXX_FLAGS) -o $@ $^ $(LD_FLAGS) -L$(USER_DEPTH)/libev/.libs -lev
	
rtptest: 
	g++ -g $(INC_FLAGS) test/rtptest.cpp -o bin/rtptest ${LD_FLAGS}
	
examples:
	$(CXX) $(CXX_FLAGS) -o ./bin/udpclient ./exam/udpclient.cpp
	$(CXX) $(CXX_FLAGS) -o ./bin/udpserver ./exam/udpserver.cpp
	$(CXX) $(CXX_FLAGS) -o ./bin/tcpclient ./exam/tcpclient.cpp
	$(CXX) $(CXX_FLAGS) -o ./bin/tcpserver ./exam/tcpserver.cpp
#	$(CXX) $(CXX_FLAGS) -o ./bin/sniffer   ./test/sniffer.cpp -lpcap

clean:
	rm -f bin/* src/*.o test/*.o exam/*.o ./unittest ./*.exe ./logfile
