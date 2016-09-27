/*
 *
 * 功能: 测试使用protocol buffer生成的cpp文件
 *
 */

#include <iostream>
#include <fstream>

#include "ly.helloworld.pb.h"

int main(int argc,char* argv[]){
	ly::helloworld msg;
	msg.set_id(10);
	msg.set_str("hello");

	std::cout<<msg.id()<<" "<<msg.str()<<std::endl;

	// Write the new address book back to disk.
	std::fstream output("./log",std::ios::out | std::ios::trunc | std::ios::binary);

	if(!msg.SerializeToOstream(&output)){
		std::cerr<< "Failed to write msg."<< std::endl;
		return 1;
	}
	return 0;
}
