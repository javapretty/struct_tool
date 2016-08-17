#include "common.h"

char *get_string_field(char *dst, const char *src, int pos, const char *del){
	char *s;
	assert(dst != NULL);
	strcpy(dst, src);
		s = strtok(dst, del == NULL ? SPLIT : del);
	while(--pos && s != NULL){
		s = strtok(NULL, del == NULL ? SPLIT : del);
	}
	if(s != NULL){
		strcpy(dst, s);
		return dst;
	}
	else 
		return NULL;
}

char *get_string_between(char *dst, const char *src, const char *slip){
	assert(dst != NULL);
	char *temp = (char *)malloc(strlen(src));
	get_string_field(dst, src, 1, slip);
	get_string_field(temp, src, 3, slip);
	strcpy(dst + strlen(dst), temp);
	free(temp);
	return dst;
}

int type_of_int(const char *type){
	if(!strncmp(type, "int8_t", 6)){
		return 1;
	}
	else if(!strncmp(type, "int16_t", 7)){
		return 2;
	}
	else if(!strncmp(type, "int32_t", 7)){
		return 3;
	}
	else if(!strncmp(type, "int64_t", 7)){
		return 4;
	}
	else if(!strncmp(type, "uint8_t", 7)){
		return 5;
	}
	else if(!strncmp(type, "uint16_t", 8)){
		return 6;
	}
	else if(!strncmp(type, "uint32_t", 8)){
		return 7;
	}
	else if(!strncmp(type, "uint64_t", 8)){
		return 8;
	}
	else if(!strncmp(type, "double", 6)){
		return 9;
	}
	else if(!strncmp(type, "bool", 4)){
		return 10;
	}
	else if(!strncmp(type, "std::string", 11)){
		return 11;
	}
	else if(!strncmp(type, "std::vector", 11)){
		return 12;
	}
	else if(!strncmp(type, "std::map", 8)){
		return 13;
	}
	else if(!strncmp(type, "boost::unordered_map", 20)){
		return 14;
	}
	else{
		return 15;
	}
}

FILE_TYPE type_of_file(const char *filename){
	if(!strncmp(filename, "Msg_Struct", 14)){
		return TYPE_MSG_STRUCT;
	}
	else if(!strncmp(filename, "Game_Struct", 11)){
		return TYPE_GAME_STRUCT;
	}
	return TYPE_UNKNOW;
}

std::string trans_to_base_name(std::string type){
	if(type == "int8" || type == "int16" || type == "int32" || type == "int64" ||
		type == "uint8" || type == "uint16" || type == "uint32" || type == "uint64")
		return type + "_t";
	else if(type == "vector" || type == "map" || type == "string")
		return "std::" + type;
	else if(type == "unordered_map")
		return "boost::" + type;
		return type;
}
