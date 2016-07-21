#ifndef __CPP_HEAD_WRITER__
#define __CPP_HEAD_WRITER__

#include "common.h"

class Msg_Define;

class Cpp_Head_Writer {
public:
	Cpp_Head_Writer(Msg_Define *msgdef);
	~Cpp_Head_Writer();
	int write_to_file(FILE *fp);
private:
	int write_to_h_begin(FILE *fp);
	int write_to_h_content(FILE *fp);
	int write_to_h_end(FILE *fp);
private:
	Msg_Define *msgdef_;
};

#endif
