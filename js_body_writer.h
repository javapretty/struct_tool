#ifndef __JS_BODY_WRITER__
#define __JS_BODY_WRITER__

#include "common.h"

class Msg_Define;

class Js_Body_Writer {
public:
	Js_Body_Writer(Msg_Define *msgdef);
	~Js_Body_Writer();
	int write_to_file(FILE *fp);
private:
	int write_to_js_init(FILE *fp);
	int write_to_js_serialize(FILE *fp);
	int serialize_by_type(char *temp, const char **field, bool is_sub = false);
	int write_to_js_deserialize(FILE *fp);
	int deserialize_by_type(char *temp, const char **field, bool is_sub = false);
private:
	Msg_Define *msgdef_;
};

#endif
