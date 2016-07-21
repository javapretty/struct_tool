#include "msgid_rw.h"

MsgId_RW::MsgId_RW(char *path, char *srcfile, char *dstfile):
	srcfile_(""),
	dstfile_(dstfile),
	path_(),
	msgIdDefines_()
{
	char temp[128] = {};
	srcfile_ = get_string_field(temp, srcfile, 1);
	memcpy(path_, path, strlen(path));
	memcpy(path_ + strlen(path), srcfile, strlen(srcfile));
}

MsgId_RW::~MsgId_RW(){

}

int MsgId_RW::readFile(){
	FILE *fp = fopen(path_, "rb+");
	if(fp == NULL){
		std::cout<<"Can not open the file "<<srcfile_<<std::endl;
		exit(0);
	}
	get_enum(fp);
	fclose(fp);
	return 0;
}

int MsgId_RW::get_enum(FILE *fp){
	char temp[128] = {};
	char dst[128] = {};
	char slip[8] = "\x20\t\n,={";
	while(fgets(temp, 128, fp)){
		if(strncmp("enum", temp, 4)){
			continue;
		}
		MsgId_Define *msgid_def = new MsgId_Define(get_string_field(dst, temp, 2, slip));
		msgid_def->readAttr(fp);
		msgIdDefines_.push_back(msgid_def);
	}
	return 0;
}

int MsgId_RW::write_to_h(){
	FILE *fp = fopen("CPP/Message.h", "w+");
	if(fp == NULL){
		std::cout<<"Can not open the .h file "<<dstfile_<<std::endl;
		exit(0);
	}
	write_to_h_head(fp);
	write_to_h_enum(fp);
	write_to_h_end(fp);
	fclose(fp);
	return 0;
}

int MsgId_RW::write_to_h_head(FILE *fp){
	char temp[256] = {};
	sprintf(temp, HEAD_FILE_COMMENT, srcfile_.c_str(), srcfile_.c_str(), srcfile_.c_str());
	fputs(temp, fp);
	return 0;
}

int MsgId_RW::write_to_h_end(FILE *fp){
	char temp[256] = {};
	sprintf(temp, HEAD_FILE_END);
	fputs(temp, fp);
	return 0;
}

int MsgId_RW::write_to_h_enum(FILE *fp){
	for(MSGIDDEFINES::iterator iter = msgIdDefines_.begin(); iter != msgIdDefines_.end(); iter++){
		(*iter)->write_to_h(fp);
	}
	return 0;
}

int MsgId_RW::write_to_js(){
	FILE *fp = fopen("JS/message.js", "w+");
	if(fp == NULL){
		std::cout<<"Can not open the js file "<<dstfile_<<std::endl;
		exit(0);
	}
	long pos = ftell(fp);
	if(pos == 0)
		write_to_js_head(fp);
	write_to_js_enum(fp);
	fclose(fp);
	return 0;
}

int MsgId_RW::write_to_js_head(FILE *fp){
	char temp[256] = {};
	sprintf(temp, COMMON_FILE_COMMENT, "JS file");
	fputs(temp, fp);
	return 0;
}

int MsgId_RW::write_to_js_enum(FILE *fp){
	for(MSGIDDEFINES::iterator iter = msgIdDefines_.begin(); iter != msgIdDefines_.end(); iter++){
		(*iter)->write_to_js(fp);
	}
	return 0;
}


