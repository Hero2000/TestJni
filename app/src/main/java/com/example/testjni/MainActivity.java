package com.example.testjni;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Looper;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Button btn = (Button) findViewById(R.id.button);
        //使用匿名内部类
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(MainActivity.this, "Clicked", Toast.LENGTH_SHORT).show();
                test5();
            }
        });


        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);

        String str = getPerson().toString();
        tv.setText(str);

        /** 1. Java 数据传递给 native */
        test1(false,
                (byte) 1,
                ',',
                (short) 3,
                4,
                3.3f,
                2.2d,
                "DevYK",
                28,
                new int[]{1, 2, 3, 4, 5, 6, 7},
                new String[]{"1", "2", "4"},
                new Person("阳坤"),
                new boolean[]{false, true}
        );

        dynamicRegister("我是动态注册的");

        float result = printInfo(33.120f);
        Log.d("native-lib", " result ==  " + result);

    }

    // AndroidUI操作，让C++线程里面来调用
    public void updateUI() {

        if (Looper.getMainLooper() == Looper.myLooper()) {
            new AlertDialog.Builder(MainActivity.this)
                    .setTitle("UI")
                    .setMessage("native 运行在主线程，直接更新 UI ...")
                    .setPositiveButton("确认", null)
                    .show();
        } else {
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    new AlertDialog.Builder(MainActivity.this)
                            .setTitle("UI")
                            .setMessage("native运行在子线程切换为主线程更新 UI ...")
                            .setPositiveButton("确认", null)
                            .show();
                }
            });
        }
    }

    public void test5() {
        testThread();
    }





    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native String stringFromJNI2();
    /**
     * Java 将数据传递到 native 中
     */
    public native void test1(
            boolean b,
            byte b1,
            char c,
            short s,
            long l,
            float f,
            double d,
            String name,
            int age,
            int[] i,
            String[] strs,
            Person person,
            boolean[] bArray
    );

    public native Person getPerson();


    /**
     * 动态注册
     */
    public native void dynamicRegister(String name);
    public native float printInfo(float info);
    public native void testThread();
    public native void unThread();
}
