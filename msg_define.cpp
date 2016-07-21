#include "msg_define.h"

Msg_Define::Msg_Define(const char *name):
	msgName_(name),
	typeName_(),
	subType1_(),
	subType2_(),
	keyName_(),
	valueName_(),
	comment_(),
	cpp_head_writer_(new Cpp_Head_Writer(this)),
	cpp_body_writer_(new Cpp_Body_Writer(this)),
	js_body_writer_(new Js_Body_Writer(this))
{
}

Msg_Define::~Msg_Define()
{
}
	
int Msg_Define::readAttr(Xml &xml, TiXmlNode *node){
	std::string key;
	XML_LOOP_BEGIN(node)
		key = xml.get_key(node);
		if(is_struct_member(key))
			setAttr(xml, node);
	XML_LOOP_END(node)
	return 0;
}

int Msg_Define::setAttr(Xml &xml, TiXmlNode *node){
	std::string type, value, comt, sub1, sub2, key;
	std::string label = xml.get_key(node);
	if(label == "arg"){
		type = trans_to_base_name(xml.get_attr_str(node, "type"));
	}
	else if(label == "struct"){
		type = trans_to_base_name(xml.get_attr_str(node, "type"));
	}
	else if(label == "vector"){
		type = trans_to_base_name(label);
		sub1 = trans_to_base_name(xml.get_attr_str(node, "type"));
	}
	else if(label == "map"){
		type = trans_to_base_name(label);
		sub1 = trans_to_base_name(xml.get_attr_str(node, "key_type"));
		sub2 = trans_to_base_name(xml.get_attr_str(node, "type"));
		key = xml.get_attr_str(node, "key_name");
		
	}
	else if(label == "unordered_map"){
		type = trans_to_base_name(label);
		sub1 = trans_to_base_name(xml.get_attr_str(node, "key_type"));
		sub2 = trans_to_base_name(xml.get_attr_str(node, "type"));
		key = xml.get_attr_str(node, "key_name");
	}
	value = xml.get_attr_str(node, "name");
	if((comt = xml.get_attr_str(node, "desc")) != "" )
		comt = "//" + comt;
	typeName_.push_back(type);
	subType1_.push_back(sub1);
	subType2_.push_back(sub2);
	keyName_.push_back(key);
	valueName_.push_back(value);
	comment_.push_back(comt);
	return 0;
}

int Msg_Define::write_to_h(FILE *fp){
	return cpp_head_writer_->write_to_file(fp);
}

int Msg_Define::write_to_cpp(FILE *fp){
	return cpp_body_writer_->write_to_file(fp);
}

int Msg_Define::write_to_js(FILE *fp){
	return js_body_writer_->write_to_file(fp);
}

void Msg_Define::print(){
	for(TYPENAME::iterator iter = typeName_.begin(); iter != typeName_.end(); iter ++){
		std::cout<<(*iter)<<std::endl;
	}
	for(VALUENAME::iterator iter = valueName_.begin(); iter != valueName_.end(); iter ++){
		std::cout<<(*iter)<<std::endl;
	}
}

