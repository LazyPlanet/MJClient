using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using XLua;
using System;
using UnityEngine.EventSystems;

[LuaCallCSharp]
public class TouchCT : MonoBehaviour {
    [CSharpCallLua]
    public delegate void VoidDelegate(GameObject go);
    public VoidDelegate onClick;
    //public static GameObject currentPai;
    private Renderer myRenderer;
    private Vector3 downPos;
    private Vector3 movePos;
    private float CameraPosZ = 0.35f;
    // Use this for initialization
    void Start () {
        myRenderer = gameObject.GetComponent<Renderer>();
    }
	
	// Update is called once per frame
	void Update () {
        if (Input.GetMouseButtonDown(0))
        {
            movePos = Input.mousePosition;
            movePos.z = CameraPosZ;
            downPos = movePos;
        }
        else if (Input.GetMouseButton(0))
        {
            movePos = Input.mousePosition;
            movePos.z = CameraPosZ;
        }
        else if (Input.GetMouseButtonUp(0))
        {
            movePos = Input.mousePosition;
            movePos.z = CameraPosZ;
            if (inArea(Camera.main.ScreenToWorldPoint(movePos)) && downPos == movePos)
            {
                if (onClick != null)
                    onClick(gameObject);
            }
        }
    }

    bool inArea(Vector3 position) {
        return (Mathf.Abs(transform.position.x - position.x) < myRenderer.bounds.size.x/2
                && Mathf.Abs(transform.position.y - position.y) < myRenderer.bounds.size.y/ 2
                && Mathf.Abs(transform.position.z - position.z) < myRenderer.bounds.size.z / 2);
    }
}
