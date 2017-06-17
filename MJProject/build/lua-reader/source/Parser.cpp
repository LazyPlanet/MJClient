#include "stdafx.h"
#include "Parser.h"
#include "AnyLog.h"
#include <iostream>
#include <strstream>
#include <sstream>
#include <fstream>

bool Parser::GenerateDescriptorPool(const std::string filePath)
{
	log_info("%s: descriptor_file is %s.", __func__, filePath.c_str());

	if (_loader) 
	{
		log_info("%s: descriptor_file is %s who has been loaded success.", __func__, filePath.c_str());
		return true;
	}

	const int descriptor_cout = 1;
	const string tempPath = filePath + "P_Asset.proto";
	const string descriptor[descriptor_cout] = {tempPath};

	for (int i = 0; i < descriptor_cout; ++i)
	{
		const string& descriptor_file = descriptor[i];

		if (descriptor_file == "")
		{
			std::cout << __func__ << ": descriptor_file is empty." << std::endl;
			log_info("%s: descriptor_file is empty.", __func__);
			continue;
		}

		std::fstream file(descriptor_file.c_str(), std::ios::in | std::ios::binary);
		if (!file)
		{
			std::cout << __func__ << " open file error, filename:" << descriptor_file << std::endl;
			log_info("%s open file error, filename:%s", __func__, descriptor_file.c_str());
			return false; 	//如果一个有问题就退出
		}

		io::ZeroCopyInputStream* zero_copy_input_stream = new io::IstreamInputStream(&file);
		io::Tokenizer* tokenizer = new io::Tokenizer(zero_copy_input_stream, NULL);

		compiler::Parser parser;
		FileDescriptorProto file_descriptor_proto;
		if (!parser.Parse(tokenizer, &file_descriptor_proto))
		{
			file.close();
			std::cout << __func__ << " line:" << __LINE__ << ": file descriptor parse error, file name:" << descriptor_file << std::endl;
			log_info("%s: line:%d file_descriptor parse error, file name is:%s", __func__, __LINE__, descriptor_file.c_str());
			return false;
		}
		file.close();

		if (!file_descriptor_proto.has_name())
			file_descriptor_proto.set_name(descriptor_file);

		const FileDescriptor* file_desc = _descriptor_pool.BuildFile(file_descriptor_proto);
		if (!file_desc)
		{
			std::cout << __func__ << " line:" << __LINE__ << ": file_descriptor parse error, file name is:" << descriptor_file << std::endl;
			log_info("%s: line:%d file_descriptor parse error, file name is:%s", __func__, __LINE__, descriptor_file.c_str());
			return false;
		}
		_file_descriptor = (FileDescriptor*)file_desc;
	}

	std::cout << __func__ << ": file_descriptor parse success." << std::endl;
	log_info("%s: file_descriptor parse success.", __func__);
	_loader = true;
	return true;
}
