#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <unordered_set>

#include <google/protobuf/message.h>
#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/compiler/parser.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/tokenizer.h>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>

namespace Asset {

namespace pb = google::protobuf;
namespace fs = boost::filesystem;

/*
* 类功能：
*
* 自动注册(.proto)文件中的所有合法配置;
*
* */

class AssetManager : public std::enable_shared_from_this<AssetManager>
{
private:
	bool _parse_sucess;
	std::string _asset_path;

	//各个ASSET_TYPE对应的MESSAGE结构
	std::unordered_map<int32_t /*type_t*/, pb::Message*>  _messages;
	//各个ASSET_TYPE对应的所有数据
	std::unordered_map<std::string /*type_t*/, std::unordered_set<pb::Message*> >  _assets_bytypes;
	//各个全局ID对应的数据
	std::unordered_map<int64_t /*global_id*/, pb::Message*>  _assets;
	std::unordered_map<int64_t /*global_id*/, std::string/*二进制数据*/>  _bin_assets;
	std::unordered_map<int64_t /*global_id*/, std::string/*类型枚举*/>  _assets_name;
	const pb::DescriptorPool* _pool = nullptr;
	const pb::FileDescriptor* _file_descriptor = nullptr;
private:
	bool LoadAssets(fs::path& full_path);
public:
	AssetManager();

	static AssetManager& Instance()
	{
		static AssetManager _instance;
		return _instance;
	}
	//获取MESSAGE
	pb::Message* Get(int64_t global_id); //根据ID获取数据：常用
	pb::Message* GetMessage(int32_t message_type); //获取MESSAGE对象实体
	std::unordered_set<pb::Message*>& GetMessagesByType(std::string message_type); //所有类型的资源数据
																				//通过全局ID获取类型ID
	int32_t GetMessageTypeFrom(int64_t global_id)
	{
		int32_t message_type = global_id >> 16;
		return message_type;
	}

	std::string GetTypeName(int64_t global_id);
	std::string GetBinContent(int64_t global_id);
	//加载数据	
	bool Load(const std::string assetFilePath);
};

#define AssetInstance AssetManager::Instance()

}
