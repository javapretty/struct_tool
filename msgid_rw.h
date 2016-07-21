#ifndef __MSGID_RW__
#define __MSGID_RW__

#include "msgid_define.h"

class MsgId_RW {
typedef std::vector<MsgId_Define *> MSGIDDEFINES;
public:
	MsgId_RW(char *path, char *srcfile, char *dstfile);
	~MsgId_RW();
	int readFile();
	int write_to_h();
	int write_to_js();
private:
	int get_enum(FILE *fp);
	int write_to_h_head(FILE *fp);
	int write_to_h_end(FILE *fp);
	int write_to_h_enum(FILE *fp);
	int write_to_js_head(FILE *fp);
	int write_to_js_enum(FILE *fp);
private:
	char path_[64];
	std::string srcfile_;
	std::string dstfile_;
	MSGIDDEFINES msgIdDefines_;
};

#endif
