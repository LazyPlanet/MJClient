#pragma once

#include <string>
#include "Parser.h"
#include "Reader.h"
#include "AnyLog.h"

#if defined(__cplusplus)
extern "C" {
#endif

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#if defined(__cplusplus)
}
#endif

namespace Asset {
	
namespace pb = google::protobuf;

class LuaReader 
{
public:
	~LuaReader() { }
	LuaReader() { 
		
	}

	static LuaReader& Instance() {
		static LuaReader _instance;
		return _instance;
	}

public:
	void Message2Lua(const pb::Message* pMsg, lua_State* L);

	void Get(const int64_t global_id, lua_State* L);
	void GetMessage(const int32_t message_type, lua_State* L);
	void GetMessagesByType(const std::string message_type, lua_State* L);
	int32_t GetMessageTypeFrom(const int64_t global_id, lua_State* L);
	std::string GetTypeName(int64_t global_id, lua_State* L);
	std::string GetBinContent(int64_t global_id, lua_State* L);
};
}
