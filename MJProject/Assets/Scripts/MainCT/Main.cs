using UnityEngine;
using System.Collections;
using XLua;

public class Main : MonoBehaviour {

	private LuaEnv _luaenv;
    
	public void Start () {
        _luaenv = LuaEnvSingleton.Instance;
        _luaenv.DoString ("require 'Main'");
	}

    public void Update () {
        _luaenv.GC ();
	}
}
