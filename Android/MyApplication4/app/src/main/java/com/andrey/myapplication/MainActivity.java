package com.andrey.myapplication;

import android.content.IntentFilter;
import android.graphics.Point;
import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbDeviceConnection;
import android.hardware.usb.UsbManager;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.ViewGroup;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.ImageView;
import android.widget.ScrollView;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.ToggleButton;

import com.felhr.usbserial.UsbSerialDevice;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity implements SerialModule.ViewBound{
    private static final String TAG = "Main Activity";
    private  static final String ACTION_USB_PERMISSION = "com.andrey.arduinousb.USB_PERMISSION";

    private UsbManager mUSBManager;
    private UsbDevice mUsbDevice;
    private UsbSerialDevice mSerialPort;
    private UsbDeviceConnection mConnection;
    private SerialModule mSerial;

    private Logger mLogger;

    private Joystick g;
    private ToggleButton mConnectionButton;
    private Switch mConnectSwitch;
    private TextView mLogTextView;
    private ScrollView mLogScrollView;
    private CheckBox serialSpeedCheckBox;

    private long mSendTimeout;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mLogger = new Logger(MainActivity.this);
        mLogger.write("Hello!");

        mSerial = new SerialModule(this, mLogger);
        mSerial.setUSBManager((UsbManager) getSystemService(this.USB_SERVICE));
        mSerial.setVB(this);

        mSendTimeout = System.currentTimeMillis();

        g = (Joystick)findViewById(R.id.graph);
        g.setOnJoystickChangeListener(new Joystick.OnJoystickChangeListener() {
            @Override
            public void onStartTrackingTouch(Joystick g) {
                Log.d(TAG, " Joystick Start Tracking");
            }

            @Override
            public void onValueChanged(Joystick g, Point value) {
                if(System.currentTimeMillis() - mSendTimeout > -1) {
                mLogger.write("Values - X: " + Float.toString(value.x) + " Y: " + Float.toString(value.y));
                    if(mSerial.write(MessageManager.buildJoystickMessage(value))){
                        mLogger.write("Sent");
                    }else{
                        mLogger.write(new LogItem("Error sending", true));
                    }
                    mSendTimeout = System.currentTimeMillis();
                }
            }

            @Override
            public void onStopTrackingTouch(Joystick g) {
                Log.d(TAG, " Joystick Stop Tracking");
                onValueChanged(g, new Point(0,0));
            }
        });

        mConnectionButton = (ToggleButton) findViewById(R.id.carConnectionStateButten);

        mConnectSwitch = (Switch) findViewById(R.id.connectSwitch);
        mConnectSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                if(b) {
                    boolean result = mSerial.connectSerial(serialSpeedCheckBox.isChecked() ? 115200 : 9600);
                    compoundButton.setChecked(result);
                }else{
                    mSerial.disconnect();
                }
            }
        });

        serialSpeedCheckBox = (CheckBox)findViewById(R.id.speedCheckBox);

        IntentFilter filter = new IntentFilter();
        filter.addAction(ACTION_USB_PERMISSION);
        filter.addAction(UsbManager.ACTION_USB_DEVICE_ATTACHED);
        filter.addAction(UsbManager.ACTION_USB_DEVICE_DETACHED);
        registerReceiver(mSerial.getSerialBroadCastReceiver(), filter);
    }

    @Override
    public void usbDetached() {
        mConnectSwitch.setChecked(false);
        mLogger.write("USB was disconnected");
    }

    @Override
    public void usbAttached() {
        mConnectSwitch.callOnClick();
    }

    @Override
    public void messageReceived(byte[] message) {
        if(MessageManager.isControlData(message)){
            MessageManager.handleMessage(message);
        }else {
            try {
                mLogger.write(new String(message, "UTF-8"));
            }catch (java.io.UnsupportedEncodingException e){
                mLogger.write(new LogItem("UnsupportedEncodingException", true));
            }
        }
    }


}
