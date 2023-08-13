package com.hikvision;


public class ThridParty {
    static {
        System.loadLibrary("thridparty");
    }
    public native void native_helloWorld();
    public native void native_startSipServer(String strIp,int port);
}
