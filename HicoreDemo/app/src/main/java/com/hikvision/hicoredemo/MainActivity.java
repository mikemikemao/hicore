package com.hikvision.hicoredemo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import com.hikvision.Hicore;
import com.hikvision.ThridParty;

public class MainActivity extends AppCompatActivity {
    Hicore hicore;
    ThridParty thridParty;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        hicore = new Hicore();
        hicore.native_helloHicore();
        thridParty = new ThridParty();
        thridParty.native_helloWorld();

    }
}