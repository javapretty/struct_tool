CC = g++
FLAG = -g 
INCLUDE = 
TARGET = serialize_tool
LIB_DIR = -L./xml
LIB = -lxml
SRCS = main.cpp file_rw.cpp msg_define.cpp cpp_head_writer.cpp cpp_body_writer.cpp \
		js_body_writer.cpp msgid_rw.cpp msgid_define.cpp common.cpp

$(TARGET):$(SRCS:.cpp=.o)
	$(CC) $(FLAG)-o $@ $^ $(LIB_DIR) $(LIB)
	-rm -f *.o *.d

%.o:%.cpp
	$(CC) $(FLAG) $(INCLUDE) -c -o $@ $<

clean:
	-rm -f *.o *.d
