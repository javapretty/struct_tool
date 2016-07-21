#include "common.h"
#include "file_rw.h"
#include "msgid_rw.h"
using namespace std;

int main(int argc, char *argv[]){
	if(argc != 5){
		cout<<"please input the correct args"<<endl;
		exit(0);
	}
	else if(!strcmp("cpp", argv[1])){
		File_RW filerw(argv[2], argv[3], argv[4]);
		if(!mkdir("CPP", 0777)){
			cout<<"create dir CPP"<<endl;
		}
		cout<<"proc file "<<argv[3]<<endl;
		filerw.readFile();
		filerw.write_to_h();
		filerw.write_to_cpp();
	}
	else if(!strcmp("js", argv[1])){
		File_RW filerw(argv[2], argv[3], argv[4]);
		if(!mkdir("JS", 0777)){
			cout<<"create dir JS"<<endl;
		}
		cout<<"proc file "<<argv[3]<<endl;
		filerw.readFile();
		filerw.write_to_js();
	}
	else if(!strcmp("msg", argv[1])){
		MsgId_RW msgidrw(argv[2], argv[3], argv[4]);
		msgidrw.readFile();
		msgidrw.write_to_h();
		msgidrw.write_to_js();
	}
	else{
		cout<<"Mode match error"<<endl;
	}
	return 0;
}
