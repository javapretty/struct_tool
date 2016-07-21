#include "cpp_body_writer.h"
#include "msg_define.h"

Cpp_Body_Writer::Cpp_Body_Writer(Msg_Define *msgdef):
		msgdef_(msgdef)
{}

Cpp_Body_Writer::~Cpp_Body_Writer(){}

int Cpp_Body_Writer::write_to_file(FILE *fp){
	write_to_cpp_construct(fp);
	write_to_cpp_destruct(fp);
	write_to_cpp_serialize(fp);
	write_to_cpp_deserialize(fp);
	write_to_cpp_reset(fp);
	return write_to_cpp_print(fp);
}

int Cpp_Body_Writer::write_to_cpp_construct(FILE *fp){
	char temp[256] = {};
	sprintf(temp, CONSTRUCT_IMPLEMENT, msgdef_->msgName().c_str(), msgdef_->msgName().c_str());
	fputs(temp, fp);
	return 0;
}

int Cpp_Body_Writer::write_to_cpp_destruct(FILE *fp){
	char temp[256] = {};
	sprintf(temp, DESTRUCT_IMPLEMENT, msgdef_->msgName().c_str(), msgdef_->msgName().c_str());
	fputs(temp, fp);
	return 0;
}

int Cpp_Body_Writer::write_to_cpp_serialize(FILE *fp){
	char temp[256] = {};
	const char *field[5] = {};
	sprintf(temp, SERIALIZE_IMPLEMENT, msgdef_->msgName().c_str());
	fputs(temp, fp);
	for(uint i = 0; i < msgdef_->typeName().size(); i++){
		field[0] = msgdef_->typeName()[i].c_str();
		field[1] = msgdef_->subType1()[i].c_str();
		field[2] = msgdef_->subType2()[i].c_str();
		field[3] = msgdef_->keyName()[i].c_str();
		field[4] = msgdef_->valueName()[i].c_str();
		serialize_by_type(temp, field);
		fputs(temp, fp);
	}
	sprintf(temp, END_IMPLEMENT);
	fputs(temp, fp);
	return 0;
}

int Cpp_Body_Writer::serialize_by_type(char *temp, const char **field){
	char tmp[256] = {};
	char subvalue[64] = {};
	const char *subfield[5] = {};
	switch(type_of_int(field[0])){
		case 1:
			sprintf(temp, WRITE_INT_8, field[4]);
			break;
		case 2:
			sprintf(temp, WRITE_INT_16, field[4]);
			break;
		case 3:
			sprintf(temp, WRITE_INT_32, field[4]);
			break;
		case 4:
			sprintf(temp, WRITE_INT_64, field[4]);
			break;
		case 5:
			sprintf(temp, WRITE_UINT_8, field[4]);
			break;
		case 6:
			sprintf(temp, WRITE_UINT_16, field[4]);
			break;
		case 7:
			sprintf(temp, WRITE_UINT_32, field[4]);
			break;
		case 8:
			sprintf(temp, WRITE_UINT_64, field[4]);
			break;
		case 9:
			sprintf(temp, WRITE_DOUBLE, field[4]);
			break;
		case 10:
			sprintf(temp, WRITE_BOOL, field[4]);
			break;
		case 11:
			sprintf(temp, WRITE_STRING, field[4]);
			break;
		case 12:
			sprintf(subvalue, "%s[i]", field[4]);
			subfield[0] = field[1];
			subfield[4] = subvalue;
			serialize_by_type(tmp, subfield);
			sprintf(temp, WRITE_VECTOR, field[4], field[4], field[4], field[4], tmp);
			break;
		case 13:
			if(is_struct_type(field[2])){
				sprintf(temp, WRITE_STD_MAP_STRUCT, field[4], field[1], field[2], field[4], field[4]);
			}
			else {
				subfield[0] = field[1];
				subfield[4] = MAP_FIRST;
				serialize_by_type(tmp, subfield);
				subfield[0] = field[2];
				subfield[4] = MAP_SECOND;
				serialize_by_type(tmp + 128, subfield);
				sprintf(temp, WRITE_STD_MAP_BASE, field[4], field[1], field[2], field[4], field[4], tmp, tmp + 128);
			}
			break;
		case 14:
			if(is_struct_type(field[2])){
				sprintf(temp, WRITE_BOOST_MAP_STRUCT, field[4], field[1], field[2], field[4], field[4]);
			}
			else {
				subfield[0] = field[1];
				subfield[4] = MAP_FIRST;
				serialize_by_type(tmp, subfield);
				subfield[0] = field[2];
				subfield[4] = MAP_SECOND;
				serialize_by_type(tmp + 128, subfield);
				sprintf(temp, WRITE_BOOST_MAP_BASE, field[4], field[1], field[2], field[4], field[4], tmp, tmp + 128);
			}
			break;
		default:
			sprintf(temp, WRITE_STRUCT, field[4]);
			break;
	}
	return 0;
}

int Cpp_Body_Writer::write_to_cpp_deserialize(FILE *fp){
	char temp[256] = {};
	const char *field[5] = {};
	sprintf(temp, DESERIALIZE_IMPLEMENT, msgdef_->msgName().c_str());
	fputs(temp, fp);
	for(uint i = 0; i < msgdef_->typeName().size(); i++){
		field[0] = str_2_pchar(msgdef_->typeName()[i]);
		field[1] = str_2_pchar(msgdef_->subType1()[i]);
		field[2] = str_2_pchar(msgdef_->subType2()[i]);
		field[3] = str_2_pchar(msgdef_->keyName()[i]);
		field[4] = str_2_pchar(msgdef_->valueName()[i]);
		deserialize_by_type(temp, field);
		fputs(temp, fp);
	}
	sprintf(temp, RETURN_ZERO);
	fputs(temp, fp);
	return 0;
}

int Cpp_Body_Writer::deserialize_by_type(char *temp, const char **field){
	char tmp[256] = {};
	char subvalue[64] = {};
	const char *subfield[5] = {};
	switch(type_of_int(field[0])){
		case 1:
			sprintf(temp, READ_INT_8, field[4]);
			break;
		case 2:
			sprintf(temp, READ_INT_16, field[4]);
			break;
		case 3:
			sprintf(temp, READ_INT_32, field[4]);
			break;
		case 4:
			sprintf(temp, READ_INT_64, field[4]);
			break;
		case 5:
			sprintf(temp, READ_UINT_8, field[4]);
			break;
		case 6:
			sprintf(temp, READ_UINT_16, field[4]);
			break;
		case 7:
			sprintf(temp, READ_UINT_32, field[4]);
			break;
		case 8:
			sprintf(temp, READ_UINT_64, field[4]);
			break;
		case 9:
			sprintf(temp, READ_DOUBLE, field[4]);
			break;
		case 10:
			sprintf(temp, READ_BOOL, field[4]);
			break;
		case 11:
			sprintf(temp, READ_STRING, field[4]);
			break;
		case 12:
			sprintf(subvalue, "%s_v", field[4]);
			subfield[0] = field[1];
			subfield[4] = subvalue;
			deserialize_by_type(tmp, subfield);
			sprintf(temp, READ_VECTOR, field[4], field[1], subvalue, field[4], tmp, field[4], subvalue);
			break;
		case 13:
			if(is_struct_type(field[2])){
				sprintf(temp, READ_STD_MAP_STRUCT, field[4], field[4], field[2], field[4], field[3]);
			}
			else {
				subfield[0] = field[1];
				subfield[4] = MAP_KEY;
				deserialize_by_type(tmp, subfield);
				subfield[0] = field[2];
				subfield[4] = MAP_V;
				deserialize_by_type(tmp + 128, subfield);
				sprintf(temp, READ_STD_MAP_BASE, field[4], field[4], field[1], field[2], tmp, tmp + 128, field[4]);
			}
			break;
		case 14:
			if(is_struct_type(field[2])){
				sprintf(temp, READ_BOOST_MAP_STRUCT, field[4], field[4], field[2], field[4], field[3]);
			}
			else {
				subfield[0] = field[1];
				subfield[4] = MAP_KEY;
				deserialize_by_type(tmp, subfield);
				subfield[0] = field[2];
				subfield[4] = MAP_V;
				deserialize_by_type(tmp + 128, subfield);
				sprintf(temp, READ_BOOST_MAP_BASE, field[4], field[4], field[1], field[2], tmp, tmp + 128, field[4]);
			}
			break;
		default:
			sprintf(temp, READ_STRUCT, field[4]);
			break;
	}
	return 0;
}

int Cpp_Body_Writer::write_to_cpp_reset(FILE *fp){
	char temp[256] = {};
	sprintf(temp, RESET_IMPLEMENT, msgdef_->msgName().c_str());
	fputs(temp, fp);
	for(uint i = 0; i < msgdef_->typeName().size(); i++){
		switch(type_of_int(msgdef_->typeName()[i].c_str())){
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
				sprintf(temp, RESET_ZERO, msgdef_->valueName()[i].c_str());
				break;
			case 11:
			case 12:
			case 13:
			case 14:
				sprintf(temp, RESET_CLEAR, msgdef_->valueName()[i].c_str());
				break;
			default:
				sprintf(temp, RESET_RESET, msgdef_->valueName()[i].c_str());
				break;
		}
		fputs(temp, fp);
	}
	sprintf(temp, END_IMPLEMENT);
	fputs(temp, fp);
	return 0;
}

int Cpp_Body_Writer::write_to_cpp_print(FILE *fp){
	char temp[256] = {};
	const char *field[5] = {};
	sprintf(temp, PRINT_IMPLEMENT, msgdef_->msgName().c_str());
	fputs(temp, fp);
	for(uint i = 0; i < msgdef_->typeName().size(); i++){
		field[0] = str_2_pchar(msgdef_->typeName()[i]);
		field[1] = str_2_pchar(msgdef_->subType1()[i]);
		field[2] = str_2_pchar(msgdef_->subType2()[i]);
		field[3] = str_2_pchar(msgdef_->keyName()[i]);
		field[4] = str_2_pchar(msgdef_->valueName()[i]);
		print_by_type(temp, field);
		fputs(temp, fp);
	}
	sprintf(temp, END_PRINT);
	fputs(temp, fp);
	return 0;
}

int Cpp_Body_Writer::print_by_type(char *temp, const char **field){
	char tmp[256] = {};
	char subvalue[64] = {};
	const char *subfield[5] = {};
	switch(type_of_int(field[0])){
		case 1:
			sprintf(temp, NUMBER_PRINT, field[4], field[4]);
			break;
		case 2:
			sprintf(temp, NUMBER_PRINT, field[4], field[4]);
			break;
		case 3:
			sprintf(temp, NUMBER_PRINT, field[4], field[4]);
			break;
		case 4:
			sprintf(temp, LONG_NUMBER_PRINT, field[4], field[4]);
			break;
		case 5:
			sprintf(temp, NUMBER_PRINT, field[4], field[4]);
			break;
		case 6:
			sprintf(temp, NUMBER_PRINT, field[4], field[4]);
			break;
		case 7:
			sprintf(temp, NUMBER_PRINT, field[4], field[4]);
			break;
		case 8:
			sprintf(temp, LONG_NUMBER_PRINT, field[4], field[4]);
			break;
		case 9:
			sprintf(temp, LONG_NUMBER_PRINT, field[4], field[4]);
			break;
		case 10:
			sprintf(temp, NUMBER_PRINT, field[4], field[4]);
			break;
		case 11:
			sprintf(temp, STRING_PRINT, field[4], field[4]);
			break;
		case 12:
			sprintf(subvalue, "%s[i]", field[4]);
			subfield[0] = field[1];
			subfield[4] = subvalue;
			print_by_type(tmp, subfield);
			sprintf(temp, VECTOR_PRINT, field[4], field[4], field[4], field[4], field[4], field[4], tmp);
			break;
		case 13:
		case 14:
			sprintf(temp, MAP_PRINT, field[4], field[4]);
			break;
		default:
			sprintf(temp, STRUCT_PRINT, field[4]);
			break;
	}
	return 0;
}
