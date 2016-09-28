/*
 *
 * 功能: 测试使用protocol buffer生成的cpp文件
 *
 */

#include <iostream>
#include <fstream>

#include "dataguru.class.pb.h"

int main(int argc,char* argv[]){
	dataguru::Class msg;
	
	std::cout<<"print default parameter"<<std::endl;
	std::cout<<msg.id()<<" "<<msg.name()<<std::endl;
	
	msg.set_id(18);
	// msg.set_name("peter");
	msg.set_name(dataguru::DATAMINING);

	std::cout<<"print setting parameter"<<std::endl;
	std::cout<<msg.id()<<" "<<msg.name()<<std::endl;

	// Write the new address book back to disk.
	std::fstream output("./log",std::ios::out | std::ios::trunc | std::ios::binary);

	if(!msg.SerializeToOstream(&output)){
		std::cerr<< "Failed to write msg."<< std::endl;
		return 1;
	}
	return 0;
}
