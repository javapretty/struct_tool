#ifndef __FILE_RW__
#define __FILE_RW__

#include "msg_define.h"

class File_RW {
typedef std::vector<Msg_Define *> MSGDEFINES;
public:
	File_RW(char *path, char *srcfile, char *dstfile);
	~File_RW();
	int readFile();
	void print();
	int write_to_h();
	int write_to_cpp();
	int write_to_js();
private:
	int write_to_h_msg(FILE *fp);
	int write_to_h_head(FILE *fp);
	int write_to_h_include(FILE *fp);
	int write_to_h_end(FILE *fp);
	int write_to_h_declare(FILE *fp);
	int write_to_h_struct(FILE *fp);
	int write_to_cpp_head(FILE *fp);
	int write_to_cpp_struct(FILE *fp);
	int write_to_js_head(FILE *fp);
	int write_to_js_struct(FILE *fp);
private:
	char path_[64];
	std::string srcfile_;
	std::string dstfile_;
	MSGDEFINES msgDefines_;
};

#endif
