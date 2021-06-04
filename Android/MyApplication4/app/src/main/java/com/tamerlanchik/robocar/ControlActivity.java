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
import android.view.KeyEvent;
import android.view.View;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.ScrollView;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.ToggleButton;

import androidx.appcompat.app.AppCompatActivity;

import com.tamerlanchik.robocar.transport.Communicator;
import com.tamerlanchik.robocar.transport.UICallback;
import com.tamerlanchik.robocar.transport.bluetooth.BluetoothController;
import com.tamerlanchik.robocar.transport.bluetooth.SerialListener;
import com.tamerlanchik.robocar.transport.bluetooth.SerialService;

import java.util.Date;
import java.util.Timer;
import java.util.TimerTask;

public class ControlActivity extends AppCompatActivity implements UICallback, SerialListener, MessageManager.Listener {
    private static final String TAG = "Main Activity";
    private  static final String ACTION_USB_PERMISSION = "com.andrey.arduinousb.USB_PERMISSION";

    @Override
    public void handleStatus(Event event, String data) {
        LogItem logitem = new LogItem();
        if (event == Event.ERROR) {

        }

    }

    private enum Connected { False, Pending, True }

    private Logger mLogger;

    private Joystick g;
    private ToggleButton mConnectionButton;
    private Switch mConnectSwitch;
    private TextView mLogTextView;
    private ScrollView mLogScrollView;
    private CheckBox serialSpeedCheckBox;

    private TextView[] mGyroTextViews;
    private TextView[] mAccelTextViews;
    private EditText mDifferentialKTestView;

    private String deviceAddress;

    private Communicator mSerial;
    private Connected connected = Connected.False;
    private boolean initialStart = true;
    private boolean hexEnabled = false;
    private boolean pendingNewline = false;
    private String newline = TextUtil.newline_crlf;

    private Timer mSendControlTimer;

    private MessageManager mMessagemanager;
    Date lastSent = new Date();

    private long mSendTimeout;

    @Override
    public void onSerialConnect(boolean connected) {
        if (connected) {
            mLogger.write("Serial connected");
            mSendControlTimer = new Timer();
            setTimerTask();
        } else {
            mSendControlTimer.cancel();
            mSendControlTimer = null;
            mLogger.write("Serial disconnected");
        }
        mConnectSwitch.setChecked(connected);
    }

    @Override
    public void onSerialConnectError(Exception e) {
        mLogger.write("Connecton failed: " + e.getMessage());
        Log.e(TAG, "Connecton failed: " + e.getMessage());
    }

    @Override
    public void onSerialRead(byte[] data) {
        receive(data);
    }

    @Override
    public void onSerialIoError(Exception e) {
        mLogger.write("Connecion lost: "+ e.getMessage());
        Log.e(TAG, "Connecion lost: "+ e.getMessage());
    }

    private void send(String str) {
        if (!mSerial.isConnected()) {
//        if(connected != Connected.True) {
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
//            mLogger.write("Gonna send: " + spn.toString());
            mSerial.send(data);
//            service.write(data);
//            mLogger.write(spn.toString());
        } catch (Exception e) {
            onSerialIoError(e);
        }
    }

    private void receive(byte[] data) {
//        onReceive(new MessageManager.Message(){MessageManager.});
        mLogger.write(new String(data));
//        return;
//        mMessagemanager.handleMessage(data);

//        MessageManager.Message msg = MessageManager.handleMessage(data);
//        if (msg == null || msg.cmd == null || msg.cmd == MessageManager.Command.VOID) {
//            mLogger.write(new String(data));
//            return;
//        }
//        switch (msg.cmd) {
//            case TELEMETRY:
//                String payload = msg.stringData();
//                mAccelTextViews[1].setText(payload);
//                break;
//            default:
//                mLogger.write(new String(data));
//        }
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

    @Override
    public void onReceive(MessageManager.Message msg) {
        if (msg == null) {
            return;
        }
        if (msg.cmd == null || msg.cmd == MessageManager.Command.VOID) {
            mLogger.write(new String(msg.data));
            return;
        }
        switch (msg.cmd) {
            case TELEMETRY:
                String payload = msg.stringData();
                int i = 0;
                for(String data : payload.split(" ")) {
                    if (data == "" || data == " ") {
                        continue;
                    }
                    try {
                        int d = Integer.parseInt(data);
                        if (i < 3) {
                            mAccelTextViews[i].setText(data);
                        } else {
                            mGyroTextViews[i+2].setText(data);
                        }
                        ++i;
                    } catch (NumberFormatException e) {
                        Log.e("Robocar", e.toString());
                        return;
                    }


                }
//                mAccelTextViews[1].setText(payload);
                break;
            default:
                mLogger.write(new String(msg.data));
        }
    }

    private void setTimerTask() {
        if (mSendControlTimer == null) {
            return;
        }
        TimerTask task = new TimerTask() {
            @Override
            public void run() {
                sendMovement(g.getValue());
                setTimerTask();
            }
        };
        mSendControlTimer.schedule(task, 50);  // 50ms
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

        mSerial = new BluetoothController(this, deviceAddress);

        mSendTimeout = System.currentTimeMillis();

        g = (Joystick)findViewById(R.id.graph);
        g.setOnJoystickChangeListener(new Joystick.OnJoystickChangeListener() {
            @Override
            public void onStartTrackingTouch(Joystick g) {
                Log.d(TAG, " Joystick Start Tracking");
            }

            @Override
            public void onValueChanged(Joystick g, Point value) {
//                sendMovement(value);
//                if (Math.abs(value.x) < 50) {
//                    value.x = 0;
//                }
//                if (Math.abs(value.y) < 50) {
//                    value.y = 0;
//                }
//                if ((new Date()).getTime() - lastSent.getTime() < 50 ) {
//                    return;
//                }
//                value.x = (int)(value.x * 1.4);
//                value.y = (int)(value.y * 1.4);
//                lastSent = new Date();
////                value.x = (int)Math.signum(value.x)*(Math.abs(value.x) + 80);
////                value.y = (int)Math.signum(value.y)*(Math.abs(value.y) + 80);
//                mLogger.write("Values - X: " + Integer.toString(value.x) + " Y: " + Integer.toString(value.y));
//                send(MessageManager.buildJoystickTextMessage(value));
////                if(mSerial.write(MessageManager.buildJoystickMessage(value))){
////                    mLogger.write("Sent");
////                }else{
////                    mLogger.write(new LogItem("Error sending", true));
////                }
//                mSendTimeout = System.currentTimeMillis();
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
                    mLogger.write("Trying to reconnect...");
                    mSerial.onResume();
                } else {
                    mLogger.write("Disconnecting...");
                    mSerial.onPause();
                }
            }
        });

        mGyroTextViews = new TextView[]{
            (TextView)findViewById(R.id.gyroXTextView),
            (TextView)findViewById(R.id.gyroYTextView),
            (TextView)findViewById(R.id.gyroZTextView),
        };
        mAccelTextViews = new TextView[]{
            (TextView)findViewById(R.id.accelXTextView),
            (TextView)findViewById(R.id.accelYTextView),
            (TextView)findViewById(R.id.accelZTextView),
        };

        mMessagemanager = new MessageManager(this);

        mDifferentialKTestView = (EditText) findViewById(R.id.rotationK);
        mDifferentialKTestView.setText(Double.toString(MessageManager.mDiffK));
        mDifferentialKTestView.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
                MessageManager.mDiffK = Double.parseDouble(v.getText().toString());
//                if (event.getAction() == KeyEvent.ACTION_DOWN) {
//                    MessageManager.mDiffK = Integer.parseInt(v.getText().toString());
//                }
                return false;
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

    private void sendMovement(Point value) {
//        value.x = (int)(Math.signum(value.x) * Math.max(0, Math.abs(value.x) - 70));
        if (Math.abs(value.y) < 70) {
            value.y = 0;
        }
        if (Math.abs(value.y) < 40) {
            value.y = 0;
        }
//        value.x = (int)(value.x * 1.2);
        value.y = (int)(value.y * 1.4);
//        mLogger.write("Values - X: " + Integer.toString(value.x) + " Y: " + Integer.toString(value.y));
        send(MessageManager.buildJoystickTextMessage(value));
    }

    @Override
    public void onDestroy() {
        mLogger.write("onDestroy");
        mSerial.onDestroy();
        super.onDestroy();
    }

    @Override
    public void onStart() {
        mLogger.write("onStart");
        super.onStart();
        mConnectSwitch.setChecked(true);
    }

    @Override
    public void onStop() {
        mLogger.write("onStop");
        mConnectSwitch.setChecked(false);
        super.onStop();
    }

    @Override
    public void onResume() {
        super.onResume();
        mLogger.write("onResume");
        mConnectSwitch.setChecked(true);
    }


}
