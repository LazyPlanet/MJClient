#include "stdafx.h"
#include "Reader.h"
#include "Parser.h"
#include <fstream>
#include "AnyLog.h"

namespace Asset {

AssetManager::AssetManager() : _parse_sucess(false)
{

}

bool AssetManager::Load(const std::string assetFilePath)
{
	std::cout << __func__ << ": start load..." << std::endl;
	log_info("%s: Start load...", __func__);

	if (_parse_sucess) return true;

	this->_asset_path = assetFilePath;

	this->_file_descriptor = Parser::Instance().GetFileDescriptor();
	if (!this->_file_descriptor)
	{
		std::cout << __func__ << ": load error, file_descriptor is null." << std::endl;
		log_info("%s: load error, file_descriptor is null.", __func__);
		return false;
	}

	const pb::EnumDescriptor* asset_type = this->_file_descriptor->FindEnumTypeByName("ASSET_TYPE");
	if (!asset_type)
	{
		std::cout << __func__ << ": could not found typename:ASSET_TYPE" << std::endl;	
		log_info("%s: could not found typename:ASSET_TYPE", __func__);
	}

	std::cout << __func__ << ": all messages needed load count is " << this->_file_descriptor->message_type_count() << std::endl;
	log_info("%s: all messages needed load count is :%d", __func__, this->_file_descriptor->message_type_count());

	//加载所有资源结构
	for (int i = 0; i < this->_file_descriptor->message_type_count(); ++i)
	{
		const pb::Descriptor* descriptor = this->_file_descriptor->message_type(i);
		if (!descriptor)
		{
			std::cout << __func__ << ": descriptor is null." << std::endl;
			log_info("%s: descriptor is null.", __func__);
			return false;
		}

		const pb::FieldDescriptor* field = descriptor->FindFieldByNumber(1);	//所有MESSAGE的第一个变量必须是类型
		if (!field || field->enum_type() != asset_type) continue;

		const pb::Message* msg = Parser::Instance().GetDynamicMessageFactory().GetPrototype(descriptor);
		if (!msg)
		{
			std::cout << __func__ << ": msg is null." << std::endl;
			log_info("%s: msg is null.", __func__);
			continue;
		}
		pb::Message* message = msg->New();

		if (_messages.find(field->default_value_enum()->number()) == _messages.end())
		{
			_messages.insert(std::make_pair(field->default_value_enum()->number(), message));	//合法协议，如果已经存在则忽略，即只加载第一个协议
		}
		else
		{
			std::cout << "Load asset error, reduplicate message name：" << msg->GetTypeName() << std::endl;
			log_info("Load asset error, reduplicate message name：%s", msg->GetTypeName().c_str());
		}
	}
	//加载所有资源数据
	fs::path full_path(_asset_path);
	if (!LoadAssets(full_path)) 
	{
		std::cout << "LoadAssets error..." << std::endl;
		log_info("LoadAssets error...");
		return false;
	}
	log_info("%s:Load log start...", __func__);
	std::cout << __func__ << ":Load asset data success，messages total:" << _messages.size() << ", asset total:" << _assets.size() << ", types total:" << _assets_bytypes.size() << std::endl;
	int message_size =_messages.size(), asset_size = _assets.size(), asset_bytypes_size = _assets_bytypes.size();
	log_info("%s:Load asset data success，messages total:%d", __func__, message_size);
	log_info("%s:Load asset data success，asset total:%d", __func__, asset_size);
	log_info("%s:Load asset data success，asset_bytypes total:%d", __func__, asset_bytypes_size);
	log_info("%s:Load finished...", __func__);
	this->_parse_sucess = true;
	return true;
}

bool AssetManager::LoadAssets(fs::path& full_path)
{
	//log_info("LoadAssets Start...");
	if (fs::exists(full_path))
	{
		fs::directory_iterator item_begin(full_path);
		fs::directory_iterator item_end;

		for (; item_begin != item_end; item_begin++)	
		{
			if (fs::is_directory(*item_begin))
			{
				std::string sub_dir_str(item_begin->path().string());
				fs::path sub_dir(sub_dir_str);
				LoadAssets(sub_dir);
			}
			else
			{
				if (item_begin->path().has_extension()) continue;

				const std::string& filename = item_begin->path().string();
				//////打开文件
				std::fstream file(filename.c_str(), std::ios::in | std::ios::binary);
				if (!file) 
				{
					std::cout << __func__ << " open file error, filename:" << filename << std::endl;
					log_info("%s open file error, filename:%s", __func__, filename.c_str());
					return false; 	//如果一个有问题就退出
				}

				int32_t size = 0;

				file >> size;
				if (size == 0 || size > 1024) 
				{
					std::cout << __func__ << " open file error, size:" << size << std::endl;
					log_info("%s open file error, size:%d", __func__, size);
					return false;	//理论上单个文件不会超过1024字节
				}

				char content[1024];
				file.readsome(content, size);
				//////关闭文件
				file.close();

				std::string directory_string = item_begin->path().parent_path().string();
				if (directory_string == "") 
				{
					std::cout << __func__ << ": directory_string is null." << std::endl;
					log_info("%s : directory_string %s is null.", __func__, directory_string.c_str());
					return false;
				}

				int32_t found_pos = directory_string.find_last_of("\\");
				const std::string& message_name = directory_string.substr(found_pos + 1);	//MESSAGE名称即为文件夹名称
				const pb::Descriptor* descriptor = this->_file_descriptor->FindMessageTypeByName(message_name);
				if (!descriptor) 
				{
					std::cout << __func__ << ": descriptor is null." << std::endl;
					log_info("%s : descriptor is null.", __func__);
					return false;
				}

				const pb::Message* msg = Parser::Instance().GetDynamicMessageFactory().GetPrototype(descriptor);
				if (!msg)
				{
					std::cout << __func__ << ": msg is null." << std::endl;
					log_info("%s : msg is null.", __func__);
					return false;
				}

				pb::Message* message = msg->New();
				bool result = message->ParseFromArray(content, size);
				if (!result)
				{
					log_info("%s : parse from array error.", __func__);
					std::cout << __func__ << ": parse from array error." << std::endl;
					return false;
				}

				////////////////////////////////////////////
				const pb::FieldDescriptor* type_field = message->GetDescriptor()->FindFieldByName("type_t");
				if (!type_field) 
				{
					log_info("%s : type_field is null.", __func__);
					return false; //如果一个有问题就退出
				}
				int64_t global_id = 0;

				const pb::FieldDescriptor* prop_field = message->GetDescriptor()->FindFieldByName("common_prop");
				if (prop_field) //普通资源
				{
					const pb::Message& prop_message = message->GetReflection()->GetMessage(*message, prop_field);
					const pb::FieldDescriptor* global_id_field = prop_message.GetDescriptor()->FindFieldByName("global_id");
					if (!global_id_field) 
					{
						log_info("%s: line:%d, global_id not found.", __func__, __LINE__);
						return false;
					}
					global_id = prop_message.GetReflection()->GetInt64(prop_message, global_id_field);
					//log_info("%s: line:%d global_id:%d found.", __func__, __LINE__, global_id);
				}
				else //物品资源
				{
					const pb::FieldDescriptor* item_prop_field = message->GetDescriptor()->FindFieldByName("item_common_prop");
					if (!item_prop_field) return false;

					const pb::Message& item_prop_message = message->GetReflection()->GetMessage(*message, item_prop_field);
					prop_field = item_prop_message.GetDescriptor()->FindFieldByName("common_prop");
					if (!prop_field) return false;

					const pb::Message& prop_message = item_prop_message.GetReflection()->GetMessage(item_prop_message, prop_field);
					const pb::FieldDescriptor* global_id_field = prop_message.GetDescriptor()->FindFieldByName("global_id");
					if (!global_id_field) 
					{
						log_info("%s: line:%d, global_id not found.", __func__, __LINE__);
						return false;
					}
					global_id = prop_message.GetReflection()->GetInt64(prop_message, global_id_field);
					//log_info("%s: line:%d global_id:%d found.", __func__, __LINE__, global_id);
				}
				////////////////////////////////////////////加载到全局唯一表
				_assets.insert(std::make_pair(global_id, message));

				////////////////////////////////////////////加载到类型表
				int32_t type_t = type_field->default_value_enum()->number();
				std::string type_name = type_field->default_value_enum()->name();
				log_info("%s: line:%d type_name:%s loaded success.", __func__, __LINE__, type_name.c_str());
				_assets_bytypes[type_name].insert(message);
				_assets_name[global_id] = type_name;
				_bin_assets[global_id] = message->SerializeAsString();
			}
		}
	}

	return true;
}

pb::Message* AssetManager::GetMessage(int32_t message_type)
{
	auto it = _messages.find(message_type);
	if (it == _messages.end()) return nullptr;
	return it->second;
}

std::unordered_set<pb::Message*>& AssetManager::GetMessagesByType(std::string message_type)
{
	return _assets_bytypes[message_type];
}

pb::Message* AssetManager::Get(int64_t global_id)
{
	auto it = _assets.find(global_id);
	if (it == _assets.end()) return nullptr;
	return it->second;
}

std::string AssetManager::GetTypeName(int64_t global_id)
{
	return _assets_name[global_id];
}

std::string AssetManager::GetBinContent(int64_t global_id)
{
	return _bin_assets[global_id];
}

