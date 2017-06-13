#include "stdafx.h"
#include "LuaReader.h"
#include "Reader.h"
#include "Parser.h"
#include "AnyLog.h"

namespace Asset
{

void LuaReader::Get(const int64_t global_id, lua_State* L)
{
	pb::Message* message = AssetInstance.Get(global_id);
	if (!message) return;
	//Message2Lua(message, L);
	lua_newtable(L);
	lua_pushlstring(L, message->SerializeAsString().c_str(),message->SerializeAsString().size());
}

void LuaReader::GetMessage(const int32_t message_type, lua_State* L)
{
	pb::Message* message = AssetInstance.GetMessage(message_type);
	if (!message) return;
	Message2Lua(message, L);
}

void LuaReader::GetMessagesByType(const std::string message_type, lua_State* L)
{
	log_info("%s: line:%d message_type:\n%s", __func__, __LINE__, message_type.c_str());

	std::unordered_set<pb::Message*>& messages = AssetInstance.GetMessagesByType(message_type);

	int32_t i = 0;
	lua_newtable(L);
	for (auto it = messages.begin(); it != messages.end(); ++it, ++i) 
	{
		//Message2Lua(*it, L);
		//lua_settable(L, -2);
		std::string content = (*it)->DebugString();
		log_info("%s: line:%d contet:\n%s", __func__, __LINE__, content.c_str());

		lua_pushlstring(L, (*it)->SerializeAsString().c_str(),(*it)->SerializeAsString().size());
		lua_rawseti(L, -2, i + 1);
	}
}

int32_t LuaReader::GetMessageTypeFrom(const int64_t global_id, lua_State* L)
{
	int32_t message_type = AssetInstance.GetMessageTypeFrom(global_id);
	lua_pushnumber(L, message_type);
	return message_type;
}

std::string LuaReader::GetTypeName(int64_t global_id, lua_State* L)
{
	std::string message_type = AssetInstance.GetTypeName(global_id);
	lua_pushlstring(L, message_type.c_str(), message_type.size());
	return message_type;
}

std::string LuaReader::GetBinContent(int64_t global_id, lua_State* L)
{
	std::string message_content = AssetInstance.GetBinContent(global_id);
	lua_pushlstring(L, message_content.c_str(), message_content.size());
	return message_content;
}

static void PushValue(const pb::Message* pMsg, const pb::FieldDescriptor* fd, lua_State* L);
static void SetField(const int key, const pb::Message* pMsg, const pb::FieldDescriptor* fd, lua_State* L);
static void SetField(const std::string& key, const pb::Message* pMsg, const pb::FieldDescriptor* fd, lua_State* L);
static void PushArray(const pb::Message* pMsg, const pb::FieldDescriptor* fd, lua_State* L);
static void PushArrayValue(const pb::Message* pMsg, const pb::FieldDescriptor* fd, int idx, lua_State* L);

void LuaReader::Message2Lua(const pb::Message* pMsg, lua_State* L)
{
	if (!pMsg) 
	{
		std::cout << __func__ << ": message is null." << std::endl;
		log_info("%s: message is null.", __func__);
		return;
	}

	const pb::Descriptor* descriptor = pMsg->GetDescriptor();
	if (!descriptor) 
	{
		std::cout << __func__ << ": descriptor is null." << std::endl;
		return;
	}

	lua_newtable(L);

	for (int i = 0; i < descriptor->field_count(); ++i) 
	{
		const pb::FieldDescriptor* fd = descriptor->field(i);
		const pb::FieldDescriptor::Type type = fd->type();
		if (!fd->is_repeated() && type != pb::FieldDescriptor::Type::TYPE_MESSAGE) {
			SetField(fd->name(), pMsg, fd, L);
		}
		else if (fd->is_repeated() && type != pb::FieldDescriptor::Type::TYPE_MESSAGE) {
			lua_pushstring(L, fd->name().c_str());
			lua_newtable(L);
			PushArray(pMsg, fd, L);
			lua_settable(L, -3);
		}
		else if (!fd->is_repeated() && type == pb::FieldDescriptor::Type::TYPE_MESSAGE) {
			const pb::Message& msg = pMsg->GetReflection()->GetMessage(*pMsg, fd);
			lua_pushstring(L, fd->name().c_str());
			Message2Lua(&msg, L);
			lua_settable(L, -3);
		}
		else {
			lua_pushstring(L, fd->name().c_str());
			lua_newtable(L);
			int size = pMsg->GetReflection()->FieldSize(*pMsg, fd);
			for (int idx = 0; idx < size; ++idx) {
				const pb::Message& msg = pMsg->GetReflection()->GetRepeatedMessage(*pMsg, fd, idx);
				lua_pushnumber(L, idx + 1);
				Message2Lua(&msg, L);
				lua_settable(L, -3);
			}
			lua_settable(L, -3);
		}
	}
}

static void PushArray(const pb::Message* pMsg, const pb::FieldDescriptor* fd, lua_State* L)
{
	int size = pMsg->GetReflection()->FieldSize(*pMsg, fd);
	for (int i = 0; i < size; ++i)
	{
		PushArrayValue(pMsg, fd, i, L);
		lua_settable(L, -3);
	}
}

static void PushValue(const pb::Message* pMsg, const pb::FieldDescriptor* fd, lua_State* L)
{
	const pb::FieldDescriptor::Type type = fd->type();
	switch (type) {
	case pb::FieldDescriptor::Type::TYPE_DOUBLE:
	{
		const double v = pMsg->GetReflection()->GetDouble(*pMsg, fd);
		lua_pushnumber(L, v);
	}
	break;
	case pb::FieldDescriptor::Type::TYPE_FLOAT:
	{
		const float v = pMsg->GetReflection()->GetFloat(*pMsg, fd);
		lua_pushnumber(L, v);
	}
	break;

	case pb::FieldDescriptor::Type::TYPE_INT64:
	case pb::FieldDescriptor::Type::TYPE_SFIXED64:
	case pb::FieldDescriptor::Type::TYPE_SINT64:
	{
		const int64_t v = pMsg->GetReflection()->GetInt64(*pMsg, fd);
		lua_pushinteger(L, v);
	}
	break;

	case pb::FieldDescriptor::Type::TYPE_UINT64:
	case pb::FieldDescriptor::Type::TYPE_FIXED64:
	{
		const uint64_t v = pMsg->GetReflection()->GetUInt64(*pMsg, fd);
		lua_pushinteger(L, v);
	}
	break;

	case pb::FieldDescriptor::Type::TYPE_INT32:
	case pb::FieldDescriptor::Type::TYPE_SINT32:
	case pb::FieldDescriptor::Type::TYPE_SFIXED32:
	{
		const int v = pMsg->GetReflection()->GetInt32(*pMsg, fd);
		lua_pushinteger(L, v);
	}
	break;

	case pb::FieldDescriptor::Type::TYPE_UINT32:
	case pb::FieldDescriptor::Type::TYPE_FIXED32:
	{
		const unsigned int v = pMsg->GetReflection()->GetUInt32(*pMsg, fd);
		lua_pushinteger(L, v);
	}
	break;

	case pb::FieldDescriptor::Type::TYPE_ENUM:
	{
		const pb::EnumValueDescriptor* e_v = pMsg->GetReflection()->GetEnum((*pMsg), fd);
		const std::string &v = e_v->name();
		lua_pushstring(L, v.c_str());
	}
	break;
	case pb::FieldDescriptor::Type::TYPE_STRING:
	case pb::FieldDescriptor::Type::TYPE_BYTES:
	{
		const std::string &v = pMsg->GetReflection()->GetString(*pMsg, fd);
		lua_pushstring(L, v.c_str());
	}
	break;

	case pb::FieldDescriptor::Type::TYPE_BOOL:
	{
		const bool v = pMsg->GetReflection()->GetBool(*pMsg, fd);
		lua_pushboolean(L, v);
	}
	break;

	default:
		lua_pushnil(L);
		break;
	}
}

static void SetField(const int key, const pb::Message* pMsg, const pb::FieldDescriptor* fd, lua_State* L)
{
	lua_pushnumber(L, key);
	PushValue(pMsg, fd, L);
	lua_settable(L, -3);
}

static void SetField(const std::string& key, const pb::Message* pMsg, const pb::FieldDescriptor* fd, lua_State* L)
{
	lua_pushstring(L, key.c_str());
	PushValue(pMsg, fd, L);
	lua_settable(L, -3);
}

static void PushArrayValue(const pb::Message* pMsg, const pb::FieldDescriptor* fd, int idx, lua_State* L)
{
	const pb::FieldDescriptor::Type type = fd->type();
	lua_pushnumber(L, idx + 1);
	switch (type) {
	case pb::FieldDescriptor::Type::TYPE_DOUBLE:
	{
		const double v = pMsg->GetReflection()->GetRepeatedDouble(*pMsg, fd, idx);
		lua_pushnumber(L, v);
	}
	break;
	case pb::FieldDescriptor::Type::TYPE_FLOAT:
	{
		const float v = pMsg->GetReflection()->GetRepeatedFloat(*pMsg, fd, idx);
		lua_pushnumber(L, v);
	}
	break;

	case pb::FieldDescriptor::Type::TYPE_INT64:
	case pb::FieldDescriptor::Type::TYPE_SFIXED64:
	case pb::FieldDescriptor::Type::TYPE_SINT64:
	{
		const long long v = pMsg->GetReflection()->GetRepeatedInt64(*pMsg, fd, idx);
		lua_pushinteger(L, v);
	}
	break;

	case pb::FieldDescriptor::Type::TYPE_UINT64:
	case pb::FieldDescriptor::Type::TYPE_FIXED64:
	{
		const unsigned long long v = pMsg->GetReflection()->GetRepeatedUInt64(*pMsg, fd, idx);
		lua_pushinteger(L, v);
	}
	break;

	case pb::FieldDescriptor::Type::TYPE_INT32:
	case pb::FieldDescriptor::Type::TYPE_SINT32:
	case pb::FieldDescriptor::Type::TYPE_SFIXED32:
	{
		const int v = pMsg->GetReflection()->GetRepeatedInt32(*pMsg, fd, idx);
		lua_pushinteger(L, v);
	}
	break;

	case pb::FieldDescriptor::Type::TYPE_UINT32:
	case pb::FieldDescriptor::Type::TYPE_FIXED32:
	{
		const unsigned int v = pMsg->GetReflection()->GetRepeatedUInt32(*pMsg, fd, idx);
		lua_pushinteger(L, v);
	}
	break;

	case pb::FieldDescriptor::Type::TYPE_ENUM:
	{
		const pb::EnumValueDescriptor *e_v = pMsg->GetReflection()->GetRepeatedEnum(*pMsg, fd, idx);
		const std::string &v = e_v->name();
		lua_pushstring(L, v.c_str());
	}
	break;
	case pb::FieldDescriptor::Type::TYPE_STRING:
	case pb::FieldDescriptor::Type::TYPE_BYTES:
	{
		const std::string &v = pMsg->GetReflection()->GetRepeatedString(*pMsg, fd, idx);
		lua_pushstring(L, v.c_str());
	}
	break;

	case pb::FieldDescriptor::Type::TYPE_BOOL:
	{
		const bool v = pMsg->GetReflection()->GetRepeatedBool(*pMsg, fd, idx);
		lua_pushboolean(L, v);
	}
	break;

	default:
		lua_pushnil(L);
		break;
	}
}

}