#ifndef __MSGID_DEFINE__
#define __MSGID_DEFINE__

#include "common.h"

typedef std::vector<std::string> MSGNAME;
typedef std::vector<std::string> MSGID;
typedef std::vector<std::string> COMMENT;

class MsgId_Define {
public:
	MsgId_Define(char *name);
	~MsgId_Define();
	int readAttr(FILE *fp);
	int setAttr();
	int write_to_h(FILE *fp);
	int write_to_js(FILE *fp);
private:
	int write_to_h_msg(char *temp, FILE *fp);
	int write_to_js_msg(char *temp, std::string js_name, FILE *fp);
private:
	std::string msgidName_;
	MSGNAME msgName_;
	MSGID msgId_;
	COMMENT comment_;
	char buff_[256];
};

#endif
