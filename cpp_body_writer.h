#ifndef __CPP_BODY_WRITER__
#define __CPP_BODY_WRITER__

#include "common.h"

class Msg_Define;

class Cpp_Body_Writer {
public:
	Cpp_Body_Writer(Msg_Define *msgdef);
	~Cpp_Body_Writer();
	int write_to_file(FILE *fp);
private:
	int write_to_cpp_construct(FILE *fp);
	int write_to_cpp_destruct(FILE *fp);
	int write_to_cpp_serialize(FILE *fp);
	int serialize_by_type(char *temp, const char **field);
	int write_to_cpp_deserialize(FILE *fp);
	int deserialize_by_type(char *temp, const char **field);
	int write_to_cpp_reset(FILE *fp);
	int write_to_cpp_print(FILE *fp);
	int print_by_type(char *temp, const char **field);
private:
	Msg_Define *msgdef_;
};

#endif
