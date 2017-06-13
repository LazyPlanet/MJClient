using UnityEditor;
using System.IO;
using System.Collections;
using UnityEngine;
using System.Collections.Generic;

class Rename {
    [UnityEditor.MenuItem("Tools/Rename")]
    static void RenameFile()
    {
        Object[] selects = Selection.GetFiltered(typeof(Object), SelectionMode.DeepAssets);
        //foreach (string path in Directory.GetFiles(Application.streamingAssetsPath))
        //{
        //    //获取所有文件夹中包含后缀为 .prefab 的路径  
        //    if (System.IO.Path.GetExtension(path) == ".prefab")
        //    {
        //        Debug.Log(path.Substring(path.IndexOf("Assets")));
        //    }
        //}
        int sum = 0;
        foreach (Object item in selects)
        {
            if (File.Exists(AssetDatabase.GetAssetPath(item)))
            {
                string assetName = item.name;
                string numberName = System.Text.RegularExpressions.Regex.Replace(assetName, @"[^0-9]+", "");
                string path = AssetDatabase.GetAssetPath(item);
                AssetDatabase.RenameAsset(path, numberName + "");
            }
            sum++;
        }
        AssetDatabase.SaveAssets();
        AssetDatabase.Refresh();
    }
}
