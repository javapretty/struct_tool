#include "msgid_define.h"

MsgId_Define::MsgId_Define(char *name):
	msgidName_(name),
	msgName_(),
	msgId_(),
	comment_(),
	buff_()
{
}

MsgId_Define::~MsgId_Define()
{
}
	
int MsgId_Define::readAttr(FILE *fp){
	fgets(buff_, 256, fp);
	while(strncmp(EOSTRUCT, buff_, 2)){
		setAttr();
		memset(buff_, 0, 256);
		fgets(buff_, 256, fp);
	}
	return 0;
}

int MsgId_Define::setAttr(){
	char temp[128] = {};
	char slip[8] = "\x20\t\n,={";
	char *str;
	if((str = get_string_field(temp, buff_, 1, slip)) == NULL)
		return -1;
	std::string msgname = str;
	std::string msgid = get_string_field(temp, buff_, 2, slip);
	std::string comt = "";
	if((str = get_string_field(temp, buff_, 3, slip)) != NULL)
		comt = str;
	msgName_.push_back(msgname);
	msgId_.push_back(msgid);
	comment_.push_back(comt);
	return 0;
}

int MsgId_Define::write_to_h(FILE *fp){
	char temp[256] = {};
	sprintf(temp, ENUM_H_HEAD, msgidName_.c_str());
	fputs(temp, fp);
	write_to_h_msg(temp, fp);
	sprintf(temp, STRUCT_END);
	fputs(temp, fp);
	return 0;
}

int MsgId_Define::write_to_h_msg(char *temp, FILE *fp){
	for(uint i = 0; i < msgName_.size(); i++){
		sprintf(temp, ENUM_H_BODY, msgName_[i].c_str(), msgId_[i].c_str(), comment_[i].c_str());
		fputs(temp, fp);
	}
	return 0;
}

int MsgId_Define::write_to_js(FILE *fp){
	std::string js_name = get_js_enum_name(msgidName_);
	if(js_name == ""){
		return -1;
	}
	char temp[256] = {};
	sprintf(temp, ENUM_JS_HEAD, js_name.c_str(), js_name.c_str());
	fputs(temp, fp);
	write_to_js_msg(temp, js_name, fp);
	sprintf(temp, JS_STRUCT_END);
	fputs(temp, fp);
	return 0;
}

int MsgId_Define::write_to_js_msg(char *temp, std::string js_name, FILE *fp){
	for(uint i = 0; i < msgName_.size(); i++){
		sprintf(temp, ENUM_JS_BODY, js_name.c_str(), msgName_[i].c_str(), msgId_[i].c_str(), comment_[i].c_str());
		fputs(temp, fp);
	}
	return 0;
}

