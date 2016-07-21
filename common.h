#ifndef __COMMON__
#define __COMMON__

#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include "script_macros.h"

#define SPLIT "\x09\x20.;\n"

enum FILE_TYPE {
	TYPE_SERVER = 0,
	TYPE_CLIENT = 1,
	TYPE_MSG_STRUCT = 2,
	TYPE_GAME_STRUCT = 3,
	TYPE_UNKNOW = 4
};

char *get_string_field(char *dst, const char *src, int pos, const char *del = NULL);

char *get_string_between(char *dst, const char *src, const char *slip);

int type_of_int(const char *type);

FILE_TYPE type_of_file(const char *filename);

std::string get_js_enum_name(std::string msgName);

std::string trans_to_base_name(std::string type);

inline char *str_2_pchar(std::string str){
	return (char *)str.data();
}

inline bool is_struct_type(const char *type){
	return type_of_int(type) > 11;
}

inline bool is_struct_member(std::string key){
	if(key == "arg" || key == "vector" || key == "struct"
		|| key == "map" || key == "unordered_map")
		return true;
	return false;
}

#endif
