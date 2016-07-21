#include "cpp_head_writer.h"
#include "msg_define.h"

Cpp_Head_Writer::Cpp_Head_Writer(Msg_Define *msgdef):
		msgdef_(msgdef)
{}

Cpp_Head_Writer::~Cpp_Head_Writer(){}

int Cpp_Head_Writer::write_to_file(FILE *fp){
	write_to_h_begin(fp);
	write_to_h_content(fp);
	return write_to_h_end(fp);
}

int Cpp_Head_Writer::write_to_h_begin(FILE *fp){
	char temp[128] = {};
	sprintf(temp, STRUCT_BEGIN, msgdef_->msgName().c_str());
	fputs(temp, fp);
	return 0;
}

int Cpp_Head_Writer::write_to_h_content(FILE *fp){
	for(uint i = 0; i < msgdef_->typeName().size(); i++){
		char tmp[128] = {};
		switch(type_of_int(msgdef_->typeName()[i].c_str())){
		case 12:
			sprintf(tmp, "\t%s<%s> %s;\t%s\n", msgdef_->typeName()[i].c_str(), msgdef_->subType1()[i].c_str(),
				msgdef_->valueName()[i].c_str(), msgdef_->comment()[i].c_str());
			break;
		case 13:
		case 14:
			sprintf(tmp, "\t%s<%s, %s> %s;\t%s\n", msgdef_->typeName()[i].c_str(), msgdef_->subType1()[i].c_str(),
				msgdef_->subType2()[i].c_str(), msgdef_->valueName()[i].c_str(), msgdef_->comment()[i].c_str());
			break;
		default:
			sprintf(tmp, "\t%s %s;\t%s\n", msgdef_->typeName()[i].c_str(), msgdef_->valueName()[i].c_str(), msgdef_->comment()[i].c_str());
			break;
		}
		fputs(tmp, fp);
	}
	return 0;
}

int Cpp_Head_Writer::write_to_h_end(FILE *fp){
	char temp[256] = {};
	sprintf(temp, FUNCTION_DECLARE, msgdef_->msgName().c_str(), msgdef_->msgName().c_str());
	fputs(temp, fp);
	sprintf(temp, STRUCT_END);
	fputs(temp, fp);
	return 0;
}

