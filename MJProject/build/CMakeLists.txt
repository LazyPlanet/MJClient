# Tencent is pleased to support the open source community by making xLua available.
# Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.
# Licensed under the MIT License (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
# http://opensource.org/licenses/MIT
# Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.

cmake_minimum_required(VERSION 2.8)

if ( WIN32 AND NOT CYGWIN )
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT" CACHE STRING "")
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd" CACHE STRING "")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT" CACHE STRING "")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd" CACHE STRING "")
endif ()

set(CMAKE_CXX_STANDARD 11)
	
project(XLua)

option ( UINT_ESPECIALLY "using custom ulong" OFF )
option ( USING_LUAJIT "using luajit" OFF )

find_path(XLUA_PROJECT_DIR NAMES SConstruct
    PATHS 
    ${CMAKE_SOURCE_DIR}
    NO_DEFAULT_PATH
    )

MARK_AS_ADVANCED(XLUA_PROJECT_DIR)

#

#数据读取
set (READER_SRC 
	lua-reader/source/LUAMain.cpp
	lua-reader/source/LUAReader.cpp
	lua-reader/source/AnyLog.cpp
	lua-reader/source/Parser.cpp
	lua-reader/source/Reader.cpp
	lua-reader/source/stdafx.cpp
)
set_property(
	SOURCE ${READER_SRC}
	APPEND
	PROPERTY COMPILE_DEFINITIONS
	LUA_LIB
)

set(SYSTEM_DIR
	lua-reader/source/boost-1.60.0/system/src/error_code.cpp
)

add_library(libboost_system-vc140-mt-s-1_60 STATIC ${SYSTEM_DIR})
	target_include_directories(libboost_system-vc140-mt-s-1_60
PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

list (APPEND THIRDPART_LIB libboost_system-vc140-mt-s-1_60)

set(FILE_SYSTEM_DIR
	lua-reader/source/boost-1.60.0/filesystem/src/windows_file_codecvt.cpp
	lua-reader/source/boost-1.60.0/filesystem/src/utf8_codecvt_facet.cpp
	lua-reader/source/boost-1.60.0/filesystem/src/unique_path.cpp
	lua-reader/source/boost-1.60.0/filesystem/src/portability.cpp
	lua-reader/source/boost-1.60.0/filesystem/src/path_traits.cpp
	lua-reader/source/boost-1.60.0/filesystem/src/path.cpp
	lua-reader/source/boost-1.60.0/filesystem/src/operations.cpp
	lua-reader/source/boost-1.60.0/filesystem/src/codecvt_error_category.cpp
)

add_library(libboost_filesystem-vc140-mt-s-1_60 STATIC ${FILE_SYSTEM_DIR})
	target_include_directories(libboost_filesystem-vc140-mt-s-1_60
PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)


list (APPEND THIRDPART_LIB libboost_filesystem-vc140-mt-s-1_60)

#########BOOST库目录
list(APPEND THIRDPART_INC lua-reader/include/boost-1.60.0)

set(protobuf_STAT_SRCS
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/compiler/importer.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/compiler/parser.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/descriptor.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/descriptor.pb.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/descriptor_database.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/dynamic_message.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/extension_set.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/extension_set_heavy.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/generated_message_reflection.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/generated_message_util.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/io/coded_stream.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/io/gzip_stream.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/io/printer.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/io/strtod.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/io/tokenizer.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/io/zero_copy_stream.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/io/zero_copy_stream_impl.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/io/zero_copy_stream_impl_lite.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/message.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/message_lite.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/reflection_ops.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/repeated_field.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/service.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/stubs/common.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/stubs/once.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/stubs/stringprintf.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/stubs/structurally_valid.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/stubs/strutil.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/stubs/substitute.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/text_format.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/unknown_field_set.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/wire_format.cc
  lua-reader/source/protobuf-2.6.1/src/google/protobuf/wire_format_lite.cc
)

if (MSVC)
  set(protobuf_STAT_SRCS
    ${protobuf_STAT_SRCS}
    lua-reader/source/protobuf-2.6.1/src/google/protobuf/stubs/atomicops_internals_x86_msvc.cc
  )
  add_compile_options(/wd4800)
else()
  set(protobuf_STAT_SRCS
    ${protobuf_STAT_SRCS}
    lua-reader/source/protobuf-2.6.1/src/google/protobuf/stubs/atomicops_internals_x86_gcc.cc
  )
endif()

add_library(protobuf STATIC ${protobuf_STAT_SRCS})

target_include_directories(protobuf
  PUBLIC
    lua-reader/source/protobuf-2.6.1/src
  PRIVATE
    lua-reader/source/protobuf-2.6.1/tc_custom
)

list(APPEND THIRDPART_INC lua-reader/include/protobuf-2.6.1)
list (APPEND THIRDPART_LIB protobuf)

set (THIRDPART_SRC ${THIRDPART_SRC} ${READER_SRC})
#数据读取

#Protobuff
#set (PROTOCOL_BUFF_SRC lua-pb/source/pb.c)
#set_property(
#	SOURCE ${PROTOCOL_BUFF_SRC}
#	APPEND
#	PROPERTY COMPILE_DEFINITIONS
#	LUA_LIB
#)
#list(APPEND THIRDPART_INC  lua-pb/include)
#set (THIRDPART_SRC ${THIRDPART_SRC} ${PROTOCOL_BUFF_SRC})
#Protobuff

#Pbc
  set (PBC_SRC
    pbc/src/source/alloc.c
    pbc/src/source/array.c
    pbc/src/source/bootstrap.c
    pbc/src/source/context.c
    pbc/src/source/decode.c
    pbc/src/source/map.c
    pbc/src/source/pattern.c
    pbc/src/source/proto.c
    pbc/src/source/register.c
    pbc/src/source/rmessage.c
    pbc/src/source/stringpool.c
    pbc/src/source/varint.c
    pbc/src/source/wmessage.c
    pbc/src/source/pbc-lua53.c
    )
  set_property(
    SOURCE ${PBC_SRC}
    APPEND
    PROPERTY COMPILE_DEFINITIONS
    LUA_LIB
  )
  list(APPEND THIRDPART_INC pbc/src/include)
  set (THIRDPART_SRC ${THIRDPART_SRC} ${PBC_SRC})
#Pbc

#Gbk
  set (GBK_SRC 
    lua-gbk/source/lgbk.c
    lua-gbk/source/lpinyin.c
    )
  set_property(
      SOURCE ${GBK_SRC}
      APPEND
      PROPERTY COMPILE_DEFINITIONS
      LUA_LIB 
    )
    list(APPEND THIRDPART_INC lua-gbk/include)
    set (THIRDPART_SRC ${THIRDPART_SRC} ${GBK_SRC})
#Gbk

#JSON
set (RAPIDJSON_SRC lua-rapidjson/source/rapidjson.cpp)
set_property(
	SOURCE ${RAPIDJSON_SRC}
	APPEND
	PROPERTY COMPILE_DEFINITIONS
	LUA_LIB
)
list(APPEND THIRDPART_INC  lua-rapidjson/include)
set (THIRDPART_SRC ${THIRDPART_SRC} ${RAPIDJSON_SRC})
#JSON

if (USING_LUAJIT)
	
    if (APPLE AND NOT IOS)
	    include_directories(
		  ${CMAKE_SOURCE_DIR}
		  lua-5.1.5/src
		  lua-5.1.5/etc
		  ${CMAKE_CURRENT_BINARY_DIR}
		  ${THIRDPART_INC}
	    )
	    set ( LUA_CORE lua-5.1.5/src/lapi.c lua-5.1.5/src/lcode.c lua-5.1.5/src/ldebug.c lua-5.1.5/src/ldo.c lua-5.1.5/src/ldump.c lua-5.1.5/src/lfunc.c 
          lua-5.1.5/src/lgc.c lua-5.1.5/src/llex.c lua-5.1.5/src/lmem.c lua-5.1.5/src/lobject.c lua-5.1.5/src/lopcodes.c lua-5.1.5/src/lparser.c lua-5.1.5/src/lstate.c 
          lua-5.1.5/src/lstring.c lua-5.1.5/src/ltable.c lua-5.1.5/src/ltm.c lua-5.1.5/src/lundump.c lua-5.1.5/src/lvm.c lua-5.1.5/src/lzio.c lua-5.1.5/src/lauxlib.c 
          lua-5.1.5/src/lbaselib.c lua-5.1.5/src/ldblib.c lua-5.1.5/src/liolib.c lua-5.1.5/src/lmathlib.c lua-5.1.5/src/loslib.c lua-5.1.5/src/ltablib.c 
          lua-5.1.5/src/lstrlib.c lua-5.1.5/src/linit.c lua-5.1.5/src/loadlib.c)
	else ()
	    include_directories(
		  ${CMAKE_SOURCE_DIR}
		  luajit-2.1.0b2/src
		  ${CMAKE_CURRENT_BINARY_DIR}
		  ${THIRDPART_INC}
	    )

	    set ( LUA_CORE )
    endif ()
	set ( LUA_LIB )
else ()
	set ( LUA_IDSIZE 120 CACHE NUMBER "gives the maximum size for the description of the source." )

	configure_file ( lua-5.3.3/src/luaconf.h.in ${CMAKE_CURRENT_BINARY_DIR}/luaconf.h )

	include_directories(
	    ${CMAKE_SOURCE_DIR}
		lua-5.3.3/src
		${CMAKE_CURRENT_BINARY_DIR}
		${THIRDPART_INC}
	)

	set ( LUA_CORE lua-5.3.3/src/lapi.c lua-5.3.3/src/lcode.c lua-5.3.3/src/lctype.c lua-5.3.3/src/ldebug.c lua-5.3.3/src/ldo.c lua-5.3.3/src/ldump.c
	  lua-5.3.3/src/lfunc.c lua-5.3.3/src/lgc.c lua-5.3.3/src/llex.c lua-5.3.3/src/lmem.c lua-5.3.3/src/lobject.c lua-5.3.3/src/lopcodes.c lua-5.3.3/src/lparser.c
	  lua-5.3.3/src/lstate.c lua-5.3.3/src/lstring.c lua-5.3.3/src/ltable.c lua-5.3.3/src/ltm.c lua-5.3.3/src/lundump.c lua-5.3.3/src/lvm.c lua-5.3.3/src/lzio.c )
	set ( LUA_LIB lua-5.3.3/src/lauxlib.c lua-5.3.3/src/lbaselib.c lua-5.3.3/src/lbitlib.c lua-5.3.3/src/lcorolib.c lua-5.3.3/src/ldblib.c
	  lua-5.3.3/src/liolib.c lua-5.3.3/src/lmathlib.c lua-5.3.3/src/loslib.c lua-5.3.3/src/lstrlib.c lua-5.3.3/src/ltablib.c lua-5.3.3/src/linit.c
	  lua-5.3.3/src/lutf8lib.c lua-5.3.3/src/loadlib.c )
endif ()

set ( LUA_SOCKET
    luasocket/auxiliar.c
    luasocket/buffer.c
    luasocket/except.c
    luasocket/inet.c
    luasocket/io.c
    luasocket/luasocket.c
    luasocket/mime.c
    luasocket/options.c
    luasocket/select.c
    luasocket/tcp.c
    luasocket/timeout.c
    luasocket/udp.c 
)

if ( WIN32 AND NOT CYGWIN )
    list (APPEND LUA_SOCKET luasocket/wsocket.c)
else ( )
    list (APPEND LUA_SOCKET luasocket/usocket.c)
endif ( )

set ( XLUA_CORE
    i64lib.c
    perflib.c
    xlua.c
)

if (APPLE)
    if (IOS)
        set(CMAKE_OSX_ARCHITECTURES "$(ARCHS_STANDARD)")
        add_library(xlua STATIC
           ${LUA_CORE}
           ${LUA_LIB}
           ${LUA_SOCKET}
           ${XLUA_CORE}
           ${THIRDPART_SRC}
        )
    else ()
        set(CMAKE_OSX_ARCHITECTURES "$(ARCHS_STANDARD_32_64_BIT)")
        add_library(xlua MODULE
            ${LUA_CORE}
            ${LUA_LIB}
            ${LUA_SOCKET}
            ${XLUA_CORE}
            ${THIRDPART_SRC}
        )
        set_target_properties ( xlua PROPERTIES BUNDLE TRUE )
        #set_target_properties ( xlua PROPERTIES FRAMEWORK TRUE )
        #set_target_properties ( xlua PROPERTIES MACOSX_RPATH TRUE )
    endif ()
else ( )
    add_library(xlua SHARED
        ${LUA_CORE}
        ${LUA_LIB}
        ${LUA_SOCKET}
        ${XLUA_CORE}
        ${THIRDPART_SRC}
    )
endif ( )

if ( WIN32 AND NOT CYGWIN )
    target_compile_definitions (xlua PRIVATE LUA_BUILD_AS_DLL)
endif ( )

set_property(
	SOURCE ${LUA_SOCKET}
	APPEND
	PROPERTY COMPILE_DEFINITIONS
	LUA_COMPAT_APIINTCASTS LUA_LIB
)

if(UINT_ESPECIALLY)
    ADD_DEFINITIONS(-DUINT_ESPECIALLY)
endif()

if ( WIN32 AND NOT CYGWIN )
    if (USING_LUAJIT)
        target_link_libraries(xlua
            ${CMAKE_SOURCE_DIR}/luajit-2.1.0b2/src/lua51.lib
            ws2_32
            ${THIRDPART_LIB} 
        )
    else ()
        target_link_libraries(xlua
            ws2_32
            ${THIRDPART_LIB} 
        )
    endif()
else ( )
    if (USING_LUAJIT AND NOT APPLE)
		target_link_libraries(xlua
			${CMAKE_SOURCE_DIR}/luajit-2.1.0b2/src/libluajit.a
			m
            ${THIRDPART_LIB} 
		)
    else ()
        target_link_libraries(xlua
            m
            ${THIRDPART_LIB} 
        )
    endif()
endif ( )
