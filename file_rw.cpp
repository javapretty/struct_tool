#include "file_rw.h"

File_RW::File_RW(char *path, char *srcfile, char *dstfile):
	srcfile_(""),
	dstfile_(dstfile),
	path_(),
	msgDefines_()
{
	char temp[128] = {};
	srcfile_ = get_string_field(temp, srcfile, 1);
	memcpy(path_, path, strlen(path));
	memcpy(path_ + strlen(path), srcfile, strlen(srcfile));
}

File_RW::~File_RW(){

}

int File_RW::readFile(){
	Xml xml;
	xml.load_xml(path_);
	TiXmlNode *node = xml.get_root_node();
	std::string key;
	XML_LOOP_BEGIN(node)
		key = xml.get_key(node);
		if(xml.get_attr_str(node, "type") == "mem_only")
			continue;
		Msg_Define *msg_def = new Msg_Define(key.c_str());
		TiXmlNode *sub = xml.enter_node(node, key.c_str());
		if(sub)
			msg_def->readAttr(xml, sub);
		msgDefines_.push_back(msg_def);
	XML_LOOP_END(node)
	return 0;
}

void File_RW::print(){
	for(MSGDEFINES::iterator iter = msgDefines_.begin(); iter != msgDefines_.end(); iter++){
		(*iter)->print();
	}
}

int File_RW::write_to_h(){
	char temp[64] = {};
	sprintf(temp, "CPP/%s.h", dstfile_.c_str());
	FILE *fp = fopen(temp, "rb+");
	if(fp == NULL){
		fp = fopen(temp, "w");
		write_to_h_head(fp);
		write_to_h_include(fp);
		if(type_of_file(dstfile_.c_str()) == TYPE_GAME_STRUCT){
			write_to_h_msg(fp);
		}
	}
	else{
		fseek(fp, -strlen(HEAD_FILE_END), SEEK_END);
	}
	write_to_h_declare(fp);
	write_to_h_struct(fp);
	write_to_h_end(fp);
	fclose(fp);
	return 0;
}

int File_RW::write_to_h_msg(FILE *fp){
	char temp[4096] = {};
	sprintf(temp, MSG_FILE_HEAD);
	fputs(temp, fp);
	return 0;
}

int File_RW::write_to_h_head(FILE *fp){
	char temp[256] = {};
	sprintf(temp, HEAD_FILE_COMMENT, srcfile_.c_str(), srcfile_.c_str());
	fputs(temp, fp);
	return 0;
}

int File_RW::write_to_h_include(FILE *fp){
	char temp[256] = {};
	switch(type_of_file(dstfile_.c_str())){
		case TYPE_MSG_STRUCT:
			sprintf(temp, MSG_STRUCT_INCLUDE);
			fputs(temp, fp);
			break;
		case TYPE_GAME_STRUCT:
			sprintf(temp, BASE_HEAD_INCLUDE);
			fputs(temp, fp);
			break;
		default:
			break;
	}
	return 0;
}

int File_RW::write_to_h_end(FILE *fp){
	char temp[256] = {};
	sprintf(temp, HEAD_FILE_END);
	fputs(temp, fp);
	return 0;
}

int File_RW::write_to_h_declare(FILE *fp){
	char temp[256] = {};
	sprintf(temp, "\n");
	fputs(temp, fp);
	for(MSGDEFINES::iterator iter = msgDefines_.begin(); iter != msgDefines_.end(); iter++){
		sprintf(temp, "struct %s;\n", (*iter)->msgName().c_str());
		fputs(temp, fp);
	}
	return 0;
}

int File_RW::write_to_h_struct(FILE *fp){
	for(MSGDEFINES::iterator iter = msgDefines_.begin(); iter != msgDefines_.end(); iter++){
		(*iter)->write_to_h(fp);
	}
	return 0;
}

int File_RW::write_to_cpp(){
	char temp[64] = {};
	sprintf(temp, "CPP/%s.cpp", dstfile_.c_str());
	FILE *fp = fopen(temp, "rb+");
	if(fp == NULL){
		fp = fopen(temp, "w");
		write_to_cpp_head(fp);
	}
	else{
		fseek(fp, 0, SEEK_END);
	}
	write_to_cpp_struct(fp);
	fclose(fp);
	return 0;
}

int File_RW::write_to_cpp_head(FILE *fp){
	char temp[256] = {};
	sprintf(temp, COMMON_FILE_COMMENT);
	fputs(temp, fp);
	sprintf(temp, INCLUDE_FILE, dstfile_.c_str());
	fputs(temp, fp);
	return 0;
}

int File_RW::write_to_cpp_struct(FILE *fp){
	for(MSGDEFINES::iterator iter = msgDefines_.begin(); iter != msgDefines_.end(); iter++){
		(*iter)->write_to_cpp(fp);
	}
	return 0;
}

int File_RW::write_to_js(){
	char temp[64] = {};
	sprintf(temp, "JS/%s.js", dstfile_.c_str());
	FILE *fp = fopen(temp, "rb+");
	if(fp == NULL){
		fp = fopen(temp, "w");
		write_to_js_head(fp);
	}
	else {
		fseek(fp, 0, SEEK_END);
	}
	write_to_js_struct(fp);
	fclose(fp);
	return 0;
}

int File_RW::write_to_js_head(FILE *fp){
	char temp[256] = {};
	sprintf(temp, COMMON_FILE_COMMENT);
	fputs(temp, fp);
	return 0;
}

int File_RW::write_to_js_struct(FILE *fp){
	for(MSGDEFINES::iterator iter = msgDefines_.begin(); iter != msgDefines_.end(); iter++){
		(*iter)->write_to_js(fp);
	}
	return 0;
}


