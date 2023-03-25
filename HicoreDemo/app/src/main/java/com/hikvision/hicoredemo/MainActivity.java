package com.hikvision.hicoredemo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import com.hikvision.Hicore;

public class MainActivity extends AppCompatActivity {
    Hicore hicore;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        hicore = new Hicore();
        hicore.native_helloHicore();

    }
}