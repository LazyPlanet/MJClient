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
    public static TouchCT currentTouchCT;
    // Use this for initialization
    void Start () {
        myRenderer = gameObject.GetComponent<Renderer>();
    }
	
	// Update is called once per frame
	void Update () {
        if(Application.platform == RuntimePlatform.IPhonePlayer || Application.platform == RuntimePlatform.Android)
        {
            if (Input.touchCount > 0)
            {
                Touch touchPoint = Input.touches[0];
                if (touchPoint.phase == TouchPhase.Canceled || touchPoint.phase == TouchPhase.Ended)
                {
                    movePos = touchPoint.position;
                    movePos.z = CameraPosZ;
                    if (inArea(Camera.main.ScreenToWorldPoint(movePos)) && downPos == movePos && TouchCT.currentTouchCT != null)
                    {
                        if (onClick != null && TouchCT.currentTouchCT == this)
                            onClick(gameObject);
                    }
                }
                else if (touchPoint.phase == TouchPhase.Began)
                {
                    movePos = touchPoint.position;
                    movePos.z = CameraPosZ;
                    downPos = movePos;
                    if (inArea(Camera.main.ScreenToWorldPoint(movePos)))
                    {
                        TouchCT.currentTouchCT = this;
                    }
                }
                else if (touchPoint.phase == TouchPhase.Moved)
                {
                    movePos = touchPoint.position;
                    movePos.z = CameraPosZ;
                }
            }
        }
        else
        {
            if (Input.GetMouseButtonDown(0))
            {
                movePos = Input.mousePosition;
                movePos.z = CameraPosZ;
                downPos = movePos;
                if (inArea(Camera.main.ScreenToWorldPoint(movePos)))
                {
                    TouchCT.currentTouchCT = this;
                }
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
                if (inArea(Camera.main.ScreenToWorldPoint(movePos)) && downPos == movePos && TouchCT.currentTouchCT != null)
                {
                    if (onClick != null && TouchCT.currentTouchCT == this)
                        onClick(gameObject);
                }
            }
        }
    }

    bool inArea(Vector3 position) {
        return (Mathf.Abs(transform.position.x - position.x) < myRenderer.bounds.size.x/2
                && Mathf.Abs(transform.position.y - position.y) < myRenderer.bounds.size.y/ 2
                && Mathf.Abs(transform.position.z - position.z) < myRenderer.bounds.size.z / 2);
    }
}
