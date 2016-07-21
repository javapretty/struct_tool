#include "js_body_writer.h"
#include "msg_define.h"

#define FIELD1 (tmp)
#define FIELD2 (tmp + FIELD_2)
#define FIELD3 (tmp + FIELD_3)
#define FIELD4 (tmp + FIELD_4)

Js_Body_Writer::Js_Body_Writer(Msg_Define *msgdef):
		msgdef_(msgdef)
{}

Js_Body_Writer::~Js_Body_Writer()
{}

int Js_Body_Writer::write_to_file(FILE *fp){
	write_to_js_init(fp);
	write_to_js_serialize(fp);
	return write_to_js_deserialize(fp);
}

int Js_Body_Writer::write_to_js_init(FILE *fp){
	char temp[256] = {};
	sprintf(temp, JS_INIT_IMPLEMENT, msgdef_->msgName().c_str());
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
				sprintf(temp, JS_RESET_ZERO, msgdef_->valueName()[i].c_str());
				break;
			case 11:
				sprintf(temp, JS_RESET_STRING, msgdef_->valueName()[i].c_str());
				break;
			case 12:
				sprintf(temp, JS_RESET_CLEAR, msgdef_->valueName()[i].c_str());
				break;
			case 13:
			case 14:
				sprintf(temp, JS_RESET_MAP, msgdef_->valueName()[i].c_str());
				break;
			default:
				sprintf(temp, JS_RESET_RESET, msgdef_->valueName()[i].c_str(), msgdef_->typeName()[i].c_str());
				break;
		}
		fputs(temp, fp);
	}
	sprintf(temp, END_IMPLEMENT);
	fputs(temp, fp);
	return 0;
}

int Js_Body_Writer::write_to_js_serialize(FILE *fp){
	char temp[256] = {};
	const char *field[5] = {};
	sprintf(temp, JS_SERIALIZE_IMPLEMENT, msgdef_->msgName().c_str());
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

int Js_Body_Writer::serialize_by_type(char *temp, const char **field, bool is_sub){
	char tmp[256] = {};
	const char *subfield[5] = {};
	if(!is_sub){
		sprintf(tmp + FIELD_3, JS_THIS_HEAD, field[4]);
	}
	else {
		sprintf(tmp + FIELD_3, field[4]);
	}
	switch(type_of_int(field[0])){
		case 1:
			sprintf(temp, JS_WRITE_INT_8, tmp + FIELD_3);
			break;
		case 2:
			sprintf(temp, JS_WRITE_INT_16, tmp + FIELD_3);
			break;
		case 3:
			sprintf(temp, JS_WRITE_INT_32, tmp + FIELD_3);
			break;
		case 4:
			sprintf(temp, JS_WRITE_INT_64, tmp + FIELD_3);
			break;
		case 5:
			sprintf(temp, JS_WRITE_UINT_8, tmp + FIELD_3);
			break;
		case 6:
			sprintf(temp, JS_WRITE_UINT_16, tmp + FIELD_3);
			break;
		case 7:
			sprintf(temp, JS_WRITE_UINT_32, tmp + FIELD_3);
			break;
		case 8:
			sprintf(temp, JS_WRITE_UINT_64, tmp + FIELD_3);
			break;
		case 9:
			sprintf(temp, JS_WRITE_DOUBLE, tmp + FIELD_3);
			break;
		case 10:
			sprintf(temp, JS_WRITE_BOOL, tmp + FIELD_3);
			break;
		case 11:
			sprintf(temp, JS_WRITE_STRING, tmp + FIELD_3);
			break;
		case 12:
			sprintf(tmp + FIELD_2, "%s[i]", tmp + FIELD_3);
			subfield[0] = field[1];
			subfield[4] = tmp + FIELD_2;
			serialize_by_type(tmp, subfield, true);
			sprintf(temp, JS_WRITE_VECTOR, tmp + FIELD_3, tmp);
			break;
		case 13:
		case 14:
			if(is_struct_type(field[2])){
				sprintf(temp, JS_WRITE_MAP_STRUCT, tmp + FIELD_3, tmp + FIELD_3);
			}
			else {
				subfield[0] = field[1];
				subfield[4] = MAP_KEY;
				serialize_by_type(tmp, subfield, true);
				subfield[0] = field[2];
				subfield[4] = MAP_V;
				serialize_by_type(FIELD4, subfield, true);
				sprintf(temp, JS_WRITE_MAP_BASE, FIELD3, FIELD3, FIELD1, FIELD4);
			}
			break;
		default:
			sprintf(temp, JS_WRITE_STRUCT, tmp + FIELD_3);
			break;
	}
	return 0;
}

int Js_Body_Writer::write_to_js_deserialize(FILE *fp){
	char temp[256] = {};
	const char *field[5] = {};
	sprintf(temp, JS_DESERIALIZE_IMPLEMENT, msgdef_->msgName().c_str());
	fputs(temp, fp);
	for(uint i = 0; i < msgdef_->typeName().size(); i++){
		field[0] = msgdef_->typeName()[i].c_str();
		field[1] = msgdef_->subType1()[i].c_str();
		field[2] = msgdef_->subType2()[i].c_str();
		field[3] = msgdef_->keyName()[i].c_str();
		field[4] = msgdef_->valueName()[i].c_str();
		deserialize_by_type(temp, field);
		fputs(temp, fp);
	}
	sprintf(temp, END_IMPLEMENT);
	fputs(temp, fp);
	return 0;
}

int Js_Body_Writer::deserialize_by_type(char *temp, const char **field, bool is_sub){
	char tmp[256] = {};
	const char *subfield[5] = {};
	if(!is_sub){
		sprintf(FIELD4, JS_THIS_HEAD, field[4]);
	}
	else {
		sprintf(FIELD4, field[4]);
	}
	switch(type_of_int(field[0])){
		case 1:
			sprintf(temp, JS_READ_INT_8, FIELD4);
			break;
		case 2:
			sprintf(temp, JS_READ_INT_16, FIELD4);
			break;
		case 3:
			sprintf(temp, JS_READ_INT_32, FIELD4);
			break;
		case 4:
			sprintf(temp, JS_READ_INT_64, FIELD4);
			break;
		case 5:
			sprintf(temp, JS_READ_UINT_8, FIELD4);
			break;
		case 6:
			sprintf(temp, JS_READ_UINT_16, FIELD4);
			break;
		case 7:
			sprintf(temp, JS_READ_UINT_32, FIELD4);
			break;
		case 8:
			sprintf(temp, JS_READ_UINT_64, FIELD4);
			break;
		case 9:
			sprintf(temp, JS_READ_DOUBLE, FIELD4);
			break;
		case 10:
			sprintf(temp, JS_READ_BOOL, FIELD4);
			break;
		case 11:
			sprintf(temp, JS_READ_STRING, FIELD4);
			break;
		case 12:
			sprintf(FIELD2, "%s_v", field[4]);
			subfield[0] = field[1];
			subfield[4] = FIELD2;
			deserialize_by_type(tmp, subfield, true);
			if(is_struct_type(field[1])){
				sprintf(temp, JS_READ_VECTOR_STRUCT, FIELD2, field[1], tmp, FIELD4, FIELD2);
			}
			else {
				sprintf(temp, JS_READ_VECTOR_BASE, FIELD2, tmp, FIELD4, FIELD2);
			}
			break;
		case 13:
		case 14:
			if(is_struct_type(field[2])){
				sprintf(temp, JS_READ_MAP_STRUCT, field[2], FIELD4, field[3]);
			}
			else {
				subfield[0] = field[1];
				subfield[4] = MAP_KEY;
				deserialize_by_type(FIELD2, subfield, true);
				subfield[0] = field[2];
				subfield[4] = MAP_V;
				deserialize_by_type(FIELD3, subfield, true);
				sprintf(temp, JS_READ_MAP_BASE, FIELD2, FIELD3, FIELD4);
			}
			break;
		default:
			sprintf(temp, JS_READ_STRUCT, FIELD4, field[0], FIELD4);
			break;
	}
	return 0;
}

