/*
 * Tencent is pleased to support the open source community by making xLua available.
 * Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.
 * Licensed under the MIT License (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
 * http://opensource.org/licenses/MIT
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
*/

using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using XLua;
using XLua.LuaDLL;
using System;
using UnityEngine.UI;
using System.IO;

[System.Serializable]
//public class Injection
//{
//    public string name;
//    public GameObject value;
//}

[LuaCallCSharp]
public class LuaBehaviour : MonoBehaviour {
    public TextAsset luaScript;
    //public Injection[] injections;
    internal static float lastGCTime = 0;
    internal const float GCInterval = 1;//1 second 

    private Action luaAwake;
    private Action luaStart;
    private Action luaUpdate;
    private Action luaOnDestroy;

    private LuaTable scriptEnv;

    private string luaChunkName = "LuaBehaviour";


    void Awake()
    {
        LuaEnvSingleton.Instance.AddBuildin("rapidjson", XLua.LuaDLL.Lua.LoadRapidJson);
        LuaEnvSingleton.Instance.AddBuildin("protobuf_c", XLua.LuaDLL.Lua.LoadlProtobufC);
        LuaEnvSingleton.Instance.AddBuildin("LuaReader", XLua.LuaDLL.Lua.LoadlLuaReader);
        LuaEnvSingleton.Instance.AddBuildin("gbk", XLua.LuaDLL.Lua.LoadlGbk);
        XLua.LuaDLL.Lua.InitXLuaAnyLog();
        //Toggle mytoggle;
        scriptEnv = LuaEnvSingleton.Instance.NewTable();
        LuaTable meta = LuaEnvSingleton.Instance.NewTable();
        meta.Set("__index", LuaEnvSingleton.Instance.Global);
        scriptEnv.SetMetaTable(meta);
        meta.Dispose();
        
        scriptEnv.Set("self", this);
        //foreach (var injection in injections)
        //{
        //    scriptEnv.Set(injection.name, injection.value);
        //}


        LuaEnvSingleton.Instance.DoString(luaScript.text, luaChunkName, scriptEnv);
        
        luaAwake = scriptEnv.Get<Action>("awake");
        scriptEnv.Get("start", out luaStart);
        scriptEnv.Get("update", out luaUpdate);
        scriptEnv.Get("ondestroy", out luaOnDestroy);

        if (luaAwake != null)
        {
            luaAwake();
        }

    }

	// Use this for initialization
	void Start ()
    {
        if (luaStart != null)
        {
            luaStart();
        }
	}
	
	// Update is called once per frame
	void Update ()
    {
        //lock (mainThreadDelegate)
        //{
        //    if (mainThreadDelegate != empty)
        //    {
        //        mainThreadDelegate();
        //        mainThreadDelegate = empty;
        //    }

        //}
        if (luaUpdate != null)
        {
            luaUpdate();
        }
        if (Time.time - LuaBehaviour.lastGCTime > GCInterval)
        {
            LuaEnvSingleton.Instance.Tick();
            LuaBehaviour.lastGCTime = Time.time;
        }
    }
    void LateUpdate()
    {

    }

    public void YieldAndCallback(object to_yield, Action callback)
    {
        StartCoroutine(CoBody(to_yield, callback));
    }

    private IEnumerator CoBody(object to_yield, Action callback)
    {
        if (to_yield is IEnumerator)
            yield return StartCoroutine((IEnumerator)to_yield);
        else
            yield return to_yield;
        callback();
    }
    //private static void empty() { }
    //protected static Action mainThreadDelegate = empty;
    //public void Attach(Action callback){
    //    if (callback != null) {
    //        lock (mainThreadDelegate)
    //        {
    //            mainThreadDelegate += callback;
    //        }
    //    }
    //}
    void OnDestroy()
    {
        if (luaOnDestroy != null)
        {
            luaOnDestroy();
        }
        luaOnDestroy = null;
        luaUpdate = null;
        luaStart = null;
        scriptEnv.Dispose();
        //injections = null;
    }
}
