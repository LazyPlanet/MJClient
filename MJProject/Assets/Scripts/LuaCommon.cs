using XLua;
using UnityEngine;

using System.Collections.Generic;
using System;
using FairyGUI;
public class LuaEnvSingleton
{

    static private LuaEnv _instance = null;
    static public LuaEnv Instance
    {
        get
        {
            if (_instance == null)
            {
                _instance = new LuaEnv();
            }

            return _instance;
        }
    }
}

[LuaCallCSharp]
public class LuaCommon
{
#if     UNITY_IOS || UNITY_IPHONE
    public static string resultPath = Application.streamingAssetsPath + "/";
#elif   UNITY_ANDROID
    public static string resultPath = "jar:file://" + Application.dataPath + "!/assets/";
#elif   UNITY_EDITOR
    public static string resultPath = Application.streamingAssetsPath + "/";
    //public static string xxxtdrfilepath = Application.dataPath + "/StreamingAssets" + "/testxxx.tdr";
    //public static string xxxtdr2filepath = Application.dataPath + "/StreamingAssets" + "/testxxx2.tdr";
    //public static bool android_platform = false;
#elif   UNITY_STANDALONE_OSX
    public static string resultPath = Application.streamingAssetsPath + "/";
#else
    public static string resultPath = Application.streamingAssetsPath + "/";
#endif

    public static bool IsMacPlatform()
    {
#if UNITY_EDITOR
        string os = System.Environment.OSVersion.ToString();
        if (os.Contains("Unix"))
        {
            return true;
        }
        else
        {
            return false;
        }
#else
        return false;
#endif
    }

    public static bool IsIOSPlatform()
    {
#if UNITY_IOS || UNITY_IPHONE 
		return true;
#else
        return false;
#endif
    }
}

//注意：用户自己代码不建议在这里配置，建议通过标签来声明!!
public class TestCaseGenConfig : XLua.GenConfig
{

    //lua中要使用到C#库的配置，比如C#标准库，或者Unity API，第三方库等。
    public List<Type> LuaCallCSharp
    {
        get
        {
            return new List<Type>()
            {
                typeof(UnityEngine.TextAsset),
                typeof(UIPanel),
                typeof(EventContext),
                typeof(EventDispatcher),
                typeof(EventListener),
                typeof(InputEvent),
                typeof(DisplayObject),
                typeof(Container),
                typeof(Stage),
                typeof(Controller),
                typeof(GObject),
                typeof(GGraph),
                typeof(GGroup),
                typeof(GImage),
                typeof(GLoader),
                typeof(PlayState),
                typeof(GMovieClip),
                typeof(TextFormat),
                typeof(GTextField),
                typeof(GRichTextField),
                typeof(GTextInput),
                typeof(GComponent),
                typeof(GList),
                typeof(GRoot),
                typeof(GLabel),
                typeof(GButton),
                typeof(GComboBox),
                typeof(GProgressBar),
                typeof(GSlider),
                typeof(PopupMenu),
                typeof(ScrollPane),
                typeof(Transition),
                typeof(UIPackage),
                typeof(Window),
                typeof(GObjectPool),
                typeof(Relations),
                typeof(RelationType),
                typeof(UIConfig),
                typeof(GoWrapper),
            };
        }
    }

    //C#静态调用Lua的配置（包括事件的原型），仅可以配delegate，interface
    public List<Type> CSharpCallLua
    {
        get
        {
            return new List<Type>()
            {
                typeof(EventCallback1),
                typeof(EventCallback0),
            };
        }
    }

    //黑名单
    public List<List<string>> BlackList
    {
        get
        {
            return null;
        }
    }
}

