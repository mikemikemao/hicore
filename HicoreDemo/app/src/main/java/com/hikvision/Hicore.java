package com.hikvision;

import android.view.Surface;

public class Hicore {
    static {
        System.loadLibrary("hicore");
    }
    /**
     * description startPreview
     * param surface
     * @return
     */
    public native void native_helloHicore();
}
