package com.hikvision;


public class ThridParty {
    static {
        System.loadLibrary("thridparty");
    }
    public native void native_helloWorld();
}
