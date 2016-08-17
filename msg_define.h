#ifndef __MSG_DEFINE__
#define __MSG_DEFINE__

#include "common.h"
#include "cpp_head_writer.h"
#include "cpp_body_writer.h"
#include "js_body_writer.h"
#include "netlib/Xml.h"

typedef std::vector<std::string> TYPENAME;
typedef std::vector<std::string> SUBTYPE1;
typedef std::vector<std::string> SUBTYPE2;
typedef std::vector<std::string> KEYNAME;
typedef std::vector<std::string> VALUENAME;
typedef std::vector<std::string> COMMENT;

class Msg_Define {
public:
	Msg_Define(const char *name);
	~Msg_Define();
	int readAttr(Xml &xml, TiXmlNode *node);
	int setAttr(Xml &xml, TiXmlNode *node);
	inline std::string msgName();
	inline TYPENAME& typeName();
	inline SUBTYPE1& subType1();
	inline SUBTYPE2& subType2();
	inline KEYNAME& keyName();
	inline VALUENAME& valueName();
	inline COMMENT& comment();
	int write_to_h(FILE *fp);
	int write_to_cpp(FILE *fp);
	int write_to_js(FILE *fp);
	void print();
private:
	std::string msgName_;
	TYPENAME typeName_;
	SUBTYPE1 subType1_;
	SUBTYPE2 subType2_;
	KEYNAME keyName_;
	VALUENAME valueName_;
	COMMENT comment_;
	Cpp_Head_Writer *cpp_head_writer_;
	Cpp_Body_Writer *cpp_body_writer_;
	Js_Body_Writer *js_body_writer_;
};

inline std::string Msg_Define::msgName(){
	return msgName_;
}

inline TYPENAME& Msg_Define::typeName(){
	return typeName_;
}

inline VALUENAME& Msg_Define::valueName(){
	return valueName_;
}

inline SUBTYPE1& Msg_Define::subType1(){
	return subType1_;
}

inline SUBTYPE2& Msg_Define::subType2(){
	return subType2_;
}

inline KEYNAME& Msg_Define::keyName(){
	return keyName_;
}

inline COMMENT& Msg_Define::comment(){
	return comment_;
}

#endif
