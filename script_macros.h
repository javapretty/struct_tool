#ifndef __SCRIPT_MACROS__
#define __SCRIPT_MACROS__

#define COMMON_FILE_COMMENT  "/** \n" \
	"* This file was auto-generated. Please Do not edit\n" \
	"*\n" \
	"* [Version 1.4]\n" \
	"*/\n"

#define HEAD_FILE_COMMENT \
	COMMON_FILE_COMMENT \
	"\n#ifndef __%s__H\n" \
	"#define __%s__H\n"  

#define MSG_FILE_HEAD \
	"\nstruct MSG { \n" \
	"\tMSG(){}\n"\
	"\tvirtual ~MSG(){}\n"\
	"\tvirtual void serialize(Block_Buffer &buffer) const = 0; \n" \
	"\tvirtual int deserialize(Block_Buffer &buffer) = 0; \n" \
	"\tvirtual void reset(void) = 0; \n" \
	"\tvirtual void print(void) = 0; \n" \
	"};\n"
	

#define BASE_HEAD_INCLUDE "\n#include \"Block_Buffer.h\"\n"\
						"#include \"boost/unordered_map.hpp\"\n"
#define GAME_CLIENT_INCLUDE \
	BASE_HEAD_INCLUDE \
	"#include \"Game_Struct.h\"\n"
#define GAME_SERVER_INCLUDE \
	GAME_CLIENT_INCLUDE 

#define HEAD_FILE_END "\n#endif\n"

#define BASE_TYPE_FLAG "0"

//内存偏移
#define FIELD_2 64
#define FIELD_3 128
#define FIELD_4 192

#define MAP_FIRST "it->first"
#define MAP_SECOND "it->second"
#define MAP_KEY "_key"
#define MAP_V "_v"

#define ENUM_H_HEAD "\nenum %s {\n"
#define ENUM_H_BODY "\t%s = %s, %s\n"
#define ENUM_JS_HEAD "\nif (typeof %s == \"undefined\") {\n" \
					"\tvar %s = {};\n"
#define ENUM_JS_BODY "\t%s.%s = %s; %s\n"

#define EOSTRUCT "};"

#define STRUCT_BEGIN "\nstruct %s : public MSG {\n"

#define STRUCT_END "};\n"
#define JS_STRUCT_END "}\n"

#define FUNCTION_DECLARE \
	"\n\t%s(void);\n" \
	"\t~%s();\n" \
	"\tvoid serialize(Block_Buffer &buffer) const;\n" \
	"\tint deserialize(Block_Buffer &buffer);\n" \
	"\tvoid reset(void);\n" \
	"\tvoid print(void);\n"

#define INCLUDE_FILE "\n#include \"%s.h\"\n"

#define CONSTRUCT_IMPLEMENT "\n%s::%s(void) {\n" \
		"\treset();\n" \
		"}\n"
#define DESTRUCT_IMPLEMENT "\n%s::~%s() {\n" \
		"}\n"

#define SERIALIZE_IMPLEMENT "\nvoid %s::serialize(Block_Buffer &buffer) const {\n"

#define DESERIALIZE_IMPLEMENT "\nint %s::deserialize(Block_Buffer &buffer) {\n"

#define RESET_IMPLEMENT "\nvoid %s::reset(void) {\n"

#define PRINT_IMPLEMENT "\nvoid %s::print(void) {\n"

#define RETURN_ZERO "\treturn 0;\n" \
					"}\n"

#define END_IMPLEMENT "}\n"

#define RESET_ZERO "\t%s = 0;\n"
#define JS_RESET_ZERO "\tthis.%s = 0;\n"

#define JS_RESET_STRING "\tthis.%s = \"\"\n"

#define RESET_CLEAR "\t%s.clear();\n"
#define JS_RESET_CLEAR "\tthis.%s = new Array();\n"

#define RESET_RESET "\t%s.reset();\n"
#define JS_RESET_RESET "\tthis.%s = new %s();\n"

#define JS_RESET_MAP "\tthis.%s = new Map();\n"

#define JS_INIT_IMPLEMENT "\nfunction %s() {\n"
#define JS_SERIALIZE_IMPLEMENT "\n%s.prototype.serialize = function(buffer) {\n"
#define JS_DESERIALIZE_IMPLEMENT "\n%s.prototype.deserialize = function(buffer) {\n"

#define WRITE_INT_8 "\tbuffer.write_int8(%s);\n"
#define WRITE_INT_16 "\tbuffer.write_int16(%s);\n"
#define WRITE_INT_32 "\tbuffer.write_int32(%s);\n"
#define WRITE_INT_64 "\tbuffer.write_int64(%s);\n"
#define WRITE_UINT_8 "\tbuffer.write_uint8(%s);\n"
#define WRITE_UINT_16 "\tbuffer.write_uint16(%s);\n"
#define WRITE_UINT_32 "\tbuffer.write_uint32(%s);\n"
#define WRITE_UINT_64 "\tbuffer.write_uint64(%s);\n"
#define WRITE_DOUBLE "\tbuffer.write_double(%s);\n"
#define WRITE_BOOL "\tbuffer.write_bool(%s);\n"
#define WRITE_STRING "\tbuffer.write_string(%s);\n"
#define WRITE_STRUCT "\t%s.serialize(buffer);\n"
#define WRITE_VECTOR "\tuint16_t %s_size = %s.size();\n" \
	"\tbuffer.write_uint16(%s_size);\n" \
	"\tfor(uint16_t i = 0; i < %s_size; ++i) {\n" \
	"\t%s" \
	"\t}\n"
#define WRITE_STD_MAP_STRUCT "\n\tbuffer.write_uint16(%s.size());\n" \
	"\tfor(std::map<%s,%s>::const_iterator it = %s.begin();\n"\
			"\t\tit != %s.end(); ++it) {\n"\
		"\t\tit->second.serialize(buffer);\n"\
	"\t}\n"
#define WRITE_STD_MAP_BASE "\n\tbuffer.write_uint16(%s.size());\n" \
	"\tfor(std::map<%s,%s>::const_iterator it = %s.begin();\n"\
			"\t\tit != %s.end(); ++it) {\n"\
		"\t%s\t%s"\
	"\t}\n"

#define WRITE_BOOST_MAP_STRUCT "\n\tbuffer.write_uint16(%s.size());\n" \
	"\tfor(boost::unordered_map<%s,%s>::const_iterator it = %s.begin();\n"\
			"\t\tit != %s.end(); ++it) {\n"\
		"\t\tit->second.serialize(buffer);\n"\
	"\t}\n"
#define WRITE_BOOST_MAP_BASE "\n\tbuffer.write_uint16(%s.size());\n" \
	"\tfor(boost::unordered_map<%s,%s>::const_iterator it = %s.begin();\n"\
		"\t\tit != %s.end(); ++it) {\n"\
		"\t%s\t%s"\
	"\t}\n"

#define READ_INT_8 "\t%s = buffer.read_int8();\n"
#define READ_INT_16 "\t%s = buffer.read_int16();\n"
#define READ_INT_32 "\t%s = buffer.read_int32();\n"
#define READ_INT_64 "\t%s = buffer.read_int64();\n"
#define READ_UINT_8 "\t%s = buffer.read_uint8();\n"
#define READ_UINT_16 "\t%s = buffer.read_uint16();\n"
#define READ_UINT_32 "\t%s = buffer.read_uint32();\n"
#define READ_UINT_64 "\t%s = buffer.read_uint64();\n"
#define READ_DOUBLE "\t%s = buffer.read_double();\n"
#define READ_BOOL "\t%s = buffer.read_bool();\n"
#define READ_STRING "\t%s = buffer.read_string();\n"
#define READ_STRUCT "\t%s.deserialize(buffer);\n"
#define READ_VECTOR "\tuint16_t %s_size = buffer.read_uint16();\n" \
	"\t%s %s;\n" \
	"\tfor(uint16_t i = 0; i < %s_size; ++i) {\n" \
	"\t%s" \
	"\t\t%s.push_back(%s);\n" \
	"\t}\n"
#define READ_STD_MAP_STRUCT "\tuint16_t %s_size = buffer.read_uint16();\n" \
		"\tfor (int16_t i = 0; i < %s_size; ++i) {\n" \
		"\t\t%s _v;\n" \
		"\t\t_v.deserialize(buffer);\n" \
		"\t\t%s.insert(std::make_pair(_v.%s, _v));\n" \
		"\t}\n"
#define READ_STD_MAP_BASE "\tuint16_t %s_size = buffer.read_uint16();\n" \
		"\tfor (int16_t i = 0; i < %s_size; ++i) {\n" \
		"\t\t%s _key;\n" \
		"\t\t%s _v;\n" \
		"\t%s\t%s" \
		"\t\t%s.insert(std::make_pair(_key, _v));\n" \
		"\t}\n"

#define READ_BOOST_MAP_STRUCT "\tuint16_t %s_size = buffer.read_uint16();\n" \
		"\tfor (int16_t i = 0; i < %s_size; ++i) {\n" \
		"\t\t%s _v;\n" \
		"\t\t_v.deserialize(buffer);\n" \
		"\t\t%s[_v.%s] =  _v;\n" \
		"\t}\n"
#define READ_BOOST_MAP_BASE "\tuint16_t %s_size = buffer.read_uint16();\n" \
		"\tfor (int16_t i = 0; i < %s_size; ++i) {\n" \
		"\t\t%s _key;\n" \
		"\t\t%s _v;\n" \
		"\t%s\t%s" \
		"\t\t%s[_key] =  _v;\n" \
		"\t}\n"

#define JS_WRITE_INT_8 "\tbuffer.write_int8(%s);\n"
#define JS_WRITE_INT_16 "\tbuffer.write_int16(%s);\n"
#define JS_WRITE_INT_32 "\tbuffer.write_int32(%s);\n"
#define JS_WRITE_INT_64 "\tbuffer.write_int64(%s);\n"
#define JS_WRITE_UINT_8 "\tbuffer.write_uint8(%s);\n"
#define JS_WRITE_UINT_16 "\tbuffer.write_uint16(%s);\n"
#define JS_WRITE_UINT_32 "\tbuffer.write_uint32(%s);\n"
#define JS_WRITE_UINT_64 "\tbuffer.write_uint64(%s);\n"
#define JS_WRITE_DOUBLE "\tbuffer.write_double(%s);\n"
#define JS_WRITE_BOOL "\tbuffer.write_bool(%s);\n"
#define JS_WRITE_STRING "\tbuffer.write_string(%s);\n"
#define JS_WRITE_STRUCT "\t%s.serialize(buffer);\n"
#define JS_WRITE_VECTOR "\tvar len = %s.length;\n" \
	"\tbuffer.write_uint16(len);\n" \
	"\tfor(var i = 0; i < len; ++i) {\n" \
	"\t%s" \
	"\t}\n"

#define JS_WRITE_MAP_STRUCT "\tbuffer.write_uint16(%s.size());\n" \
		"\t%s.each(function(_key,_v,index) {\n" \
			"\t\t_v.serialize(buffer);\n" \
     	"\t});\n"
#define JS_WRITE_MAP_BASE "\tbuffer.write_uint16(this.%s.size());\n" \
		"\t%s.each(function(_key,_v,index) {\n" \
			"\t%s\t%s" \
     	"\t});\n"

#define JS_READ_INT_8 "\t%s = buffer.read_int8();\n"
#define JS_READ_INT_16 "\t%s = buffer.read_int16();\n"
#define JS_READ_INT_32 "\t%s = buffer.read_int32();\n"
#define JS_READ_INT_64 "\t%s = buffer.read_int64();\n"
#define JS_READ_UINT_8 "\t%s = buffer.read_uint8();\n"
#define JS_READ_UINT_16 "\t%s = buffer.read_uint16();\n"
#define JS_READ_UINT_32 "\t%s = buffer.read_uint32();\n"
#define JS_READ_UINT_64 "\t%s = buffer.read_uint64();\n"
#define JS_READ_DOUBLE "\t%s = buffer.read_double();\n"
#define JS_READ_BOOL "\t%s = buffer.read_bool();\n"
#define JS_READ_STRING "\t%s = buffer.read_string();\n"
#define JS_READ_STRUCT "\t%s.deserialize(buffer);\n"

#define JS_READ_VECTOR_STRUCT "\tvar len = buffer.read_uint16();\n" \
	"\tfor(var i = 0; i < len; ++i) {\n" \
	"\t\tvar %s = new %s();\n" \
	"\t%s" \
	"\t\t%s.push(%s);\n" \
	"\t}\n"
#define JS_READ_VECTOR_BASE "\tvar len = buffer.read_uint16();\n" \
	"\tfor(var i = 0; i < len; ++i) {\n" \
	"\t\tvar %s;\n" \
	"\t%s" \
	"\t\t%s.push(%s);\n" \
	"\t}\n"

#define JS_READ_MAP_STRUCT "\tvar len = buffer.read_uint16();\n" \
		"\tfor (var i = 0; i < len; ++i) {\n" \
			"\t\tvar _v = new %s();\n" \
			"\t\t_v.deserialize(buffer);\n" \
			"\t\t%s.insert(_v.%s, _v);\n" \
		"\t}\n"
#define JS_READ_MAP_BASE "\tvar len = buffer.read_uint16();\n" \
		"\tfor (var i = 0; i < len; ++i) {\n" \
			"\t\tvar _key;\n" \
			"\t\tvar _v;\n" \
			"\t%s\t%s" \
			"\t\t%s.insert(_key, _v);\n" \
		"\t}\n"

#define JS_THIS_HEAD "this.%s"

#define JS_THIS_SIZE 7

#define NUMBER_PRINT \
	"\tprintf(\"%s: %%d, \", %s);\n"
#define LONG_NUMBER_PRINT \
	"\tprintf(\"%s: %%ld, \", %s);\n"
#define STRING_PRINT \
	"\tprintf(\"%s: %%s, \", %s.c_str());\n"
#define STRUCT_PRINT \
	"\t%s.print();\n"
#define VECTOR_PRINT "\tuint16_t %s_size = (%s.size() > 5 ? 5 : %s.size());\n" \
	"\tprintf(\"%s.size: %%ld [\", %s.size());\n" \
	"\tfor(uint16_t i = 0; i < %s_size; ++i) {\n" \
	"\t%s" \
	"\t}\n"\
	"\tprintf(\"], \");\n"
#define MAP_PRINT "\tprintf(\"%s.size: %%ld {}, \", %s.size());\n" \

#define END_PRINT \
	"\tprintf(\"\\n\");\n" \
	"}\n"

#endif
