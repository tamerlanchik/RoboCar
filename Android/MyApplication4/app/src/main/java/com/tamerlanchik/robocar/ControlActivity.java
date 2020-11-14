package com.tamerlanchik.robocar;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.graphics.Point;
import android.os.Bundle;
import android.os.IBinder;
import android.text.Spannable;
import android.text.SpannableStringBuilder;
import android.text.style.ForegroundColorSpan;
import android.util.Log;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.ScrollView;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.ToggleButton;

import androidx.appcompat.app.AppCompatActivity;

import com.tamerlanchik.robocar.transport.Communicator;
import com.tamerlanchik.robocar.transport.UICallback;
import com.tamerlanchik.robocar.transport.bluetooth.BluetoothController;

public class ControlActivity extends AppCompatActivity implements UICallback {
    private static final String TAG = "Main Activity";
    private  static final String ACTION_USB_PERMISSION = "com.andrey.arduinousb.USB_PERMISSION";

    @Override
    public void handleStatus(Event event, String data) {
        LogItem logitem = new LogItem();
        if (event == Event.ERROR) {

    }

    private enum Connected { False, Pending, True }

    private Logger mLogger;

    private Joystick g;
    private ToggleButton mConnectionButton;
    private Switch mConnectSwitch;
    private TextView mLogTextView;
    private ScrollView mLogScrollView;
    private CheckBox serialSpeedCheckBox;

    private String deviceAddress;
//    private SerialService service;

    private Communicator mSerial;
    private Connected connected = Connected.False;
    private boolean initialStart = true;
    private boolean hexEnabled = false;
    private boolean pendingNewline = false;
    private String newline = TextUtil.newline_crlf;

    private long mSendTimeout;

    @Override
    public void onServiceConnected(ComponentName name, IBinder binder) {
        mLogger.write("onServiceConnected. connecting...");
        service = ((SerialService.SerialBinder) binder).getService();
        service.attach(this);
        if(initialStart) {
            initialStart = false;
            runOnUiThread(this::connect);
        }
    }

    @Override
    public void onServiceDisconnected(ComponentName name) {
        mLogger.write("onServiceDisconected");
    }

    @Override
    public void onSerialConnect() {
        mLogger.write("Connected");
//        status("connected");
        connected = Connected.True;
    }

    @Override
    public void onSerialConnectError(Exception e) {
        mLogger.write("Connecton failed: " + e.getMessage());
        Log.e(TAG, "Connecton failed: " + e.getMessage());
        disconnect();
    }

    @Override
    public void onSerialRead(byte[] data) {
        receive(data);
    }

    @Override
    public void onSerialIoError(Exception e) {
        mLogger.write("Connecion lost: "+ e.getMessage());
        Log.e(TAG, "Connecion lost: "+ e.getMessage());
        disconnect();
    }

//    private void connect() {
//        try {
//            BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
//            BluetoothDevice device = bluetoothAdapter.getRemoteDevice(deviceAddress);
//            status("connecting...");
//            mLogger.write("Connecting...");
//            connected = Connected.Pending;
//            SerialSocket socket = new SerialSocket(getApplicationContext(), device);
//            service.connect(socket);
//        } catch (Exception e) {
//            onSerialConnectError(e);
//        }
//    }

//    private void disconnect() {
//        connected = Connected.False;
//        service.disconnect();
//    }

    private void send(String str) {
        if(connected != Connected.True) {
            mLogger.write(new LogItem("Not connected", true));
//            Toast.makeText(ControlActivity.this, "not connected", Toast.LENGTH_SHORT).show();
            return;
        }
        try {
            String msg;
            byte[] data;
            if(hexEnabled) {
                StringBuilder sb = new StringBuilder();
                TextUtil.toHexString(sb, TextUtil.fromHexString(str));
                TextUtil.toHexString(sb, newline.getBytes());
                msg = sb.toString();
                data = TextUtil.fromHexString(msg);
            } else {
                msg = str;
                data = (str + newline).getBytes();
            }
            SpannableStringBuilder spn = new SpannableStringBuilder(msg+'\n');
            spn.setSpan(new ForegroundColorSpan(getResources().getColor(R.color.colorSendText)), 0, spn.length(), Spannable.SPAN_EXCLUSIVE_EXCLUSIVE);
//            receiveText.append(spn);
            mLogger.write("Gonna send: " + spn.toString());
            service.write(data);
            mLogger.write(spn.toString());
        } catch (Exception e) {
            onSerialIoError(e);
        }
    }

    private void receive(byte[] data) {
//        if(hexEnabled) {
//            receiveText.append(TextUtil.toHexString(data) + '\n');
//        } else {
//            String msg = new String(data);
//            if(newline.equals(TextUtil.newline_crlf) && msg.length() > 0) {
//                // don't show CR as ^M if directly before LF
//                msg = msg.replace(TextUtil.newline_crlf, TextUtil.newline_lf);
//                // special handling if CR and LF come in separate fragments
//                if (pendingNewline && msg.charAt(0) == '\n') {
//                    Editable edt = receiveText.getEditableText();
//                    if (edt != null && edt.length() > 1)
//                        edt.replace(edt.length() - 2, edt.length(), "");
//                }
//                pendingNewline = msg.charAt(msg.length() - 1) == '\r';
//            }
//            receiveText.append(TextUtil.toCaretString(msg, newline.length() != 0));
//        }
    }

    private void status(String str) {
//        SpannableStringBuilder spn = new SpannableStringBuilder(str+'\n');
//        spn.setSpan(new ForegroundColorSpan(getResources().getColor(R.color.colorStatusText)), 0, spn.length(), Spannable.SPAN_EXCLUSIVE_EXCLUSIVE);
//        receiveText.append(spn);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_control);

        mLogger = new Logger(ControlActivity.this);
        mLogger.write("Hello!");

        Intent intent = getIntent();
        if (intent != null) {
            deviceAddress = intent.getStringExtra("device");
        } else {
            mLogger.write("No device selected");
        }

        mSerial = new BluetoothController(this);

//        bindService(new Intent(this, SerialService.class), this, Context.BIND_AUTO_CREATE);

//        mSerial = new SerialModule(this, mLogger);
//        mSerial.setUSBManager((UsbManager) getSystemService(this.USB_SERVICE));
//        mSerial.setVB(this);

        mSendTimeout = System.currentTimeMillis();

        g = (Joystick)findViewById(R.id.graph);
        g.setOnJoystickChangeListener(new Joystick.OnJoystickChangeListener() {
            @Override
            public void onStartTrackingTouch(Joystick g) {
                Log.d(TAG, " Joystick Start Tracking");
            }

            @Override
            public void onValueChanged(Joystick g, Point value) {
                mLogger.write("Values - X: " + Integer.toString(value.x) + " Y: " + Integer.toString(value.y));
                send(MessageManager.buildJoystickTextMessage(value));
//                if(mSerial.write(MessageManager.buildJoystickMessage(value))){
//                    mLogger.write("Sent");
//                }else{
//                    mLogger.write(new LogItem("Error sending", true));
//                }
                mSendTimeout = System.currentTimeMillis();
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
                if (b) {
                    connect();
                }
//                if(b) {
//                    boolean result = mSerial.connectSerial(serialSpeedCheckBox.isChecked() ? 115200 : 9600);
//                    compoundButton.setChecked(result);
//                }else{
//                    mSerial.disconnect();
//                }
            }
        });

//        serialSpeedCheckBox = (CheckBox)findViewById(R.id.speedCheckBox);
//
//        IntentFilter filter = new IntentFilter();
//        filter.addAction(ACTION_USB_PERMISSION);
//        filter.addAction(UsbManager.ACTION_USB_DEVICE_ATTACHED);
//        filter.addAction(UsbManager.ACTION_USB_DEVICE_DETACHED);
//        registerReceiver(mSerial.getSerialBroadCastReceiver(), filter);
    }

//    @Override
//    public void usbDetached() {
//        mConnectSwitch.setChecked(false);
//        mLogger.write("USB was disconnected");
//    }
//
//    @Override
//    public void usbAttached() {
//        mConnectSwitch.callOnClick();
//    }
//
//    @Override
//    public void messageReceived(byte[] message) {
//        if(MessageManager.isControlData(message)){
//            MessageManager.handleMessage(message);
//        }else {
//            try {
//                mLogger.write(new String(message, "UTF-8"));
//            }catch (java.io.UnsupportedEncodingException e){
//                mLogger.write(new LogItem("UnsupportedEncodingException", true));
//            }
//        }
//    }

    @Override
    public void onDestroy() {
        mLogger.write("onDEstroy");
        mSerial.onDestroy();
//        if (connected != Connected.False)
//            disconnect();
//        stopService(new Intent(ControlActivity.this, SerialService.class));
        super.onDestroy();
    }

    @Override
    public void onStart() {
        mLogger.write("onStart");
        super.onStart();
        mSerial.onStart();
//        if(service != null) {
//            service.attach(this);
//            mLogger.write("service.attach()");
//        }
//
//        else {
//            startService(new Intent(ControlActivity.this, SerialService.class)); // prevents service destroy on unbind from recreated activity caused by orientation change
//            mLogger.write("startService()");
//        }
    }

    @Override
    public void onStop() {
        mLogger.write("onStop");
//        if(service != null && !ControlActivity.this.isChangingConfigurations())
//            service.detach();
        super.onStop();
    }

    @Override
    public void onResume() {
        super.onResume();
        mLogger.write("onResume");
        mSerial.onResume();
//        if(initialStart && service != null) {
//            initialStart = false;
//            runOnUiThread(this::connect);
//        }
    }


}
