package com.tamerlanchik.robocar.transport.bluetooth;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;

import androidx.lifecycle.Lifecycle;

import com.tamerlanchik.robocar.ControlActivity;
import com.tamerlanchik.robocar.transport.Communicator;

public class BluetoothController implements Communicator, ServiceConnection, SerialListener {
    private enum Connected { False, Pending, True }


    private Activity mContext;
    private SerialService mService;
    private boolean initialStart = true;
    private Connected isConnected = Connected.False;
    private String deviceAddress;

    public BluetoothController(Activity context) {
        mContext = context;
        context.bindService(new Intent(context, SerialService.class), this, Context.BIND_AUTO_CREATE);
    }

    @Override
    public void onStart() {
        if(mService != null) {
            mService.attach(this);
        } else {
            mContext.startService(new Intent(mContext, SerialService.class));
        }
    }

    @Override
    public void onStop() {
        if(mService != null && !mContext.isChangingConfigurations())
            mService.detach();
    }

    @Override
    public void onDestroy() {
        if (isConnected != Connected.False)
            disconnect();
        mContext.stopService(new Intent(mContext, SerialService.class));
    }

    @Override
    public void onResume() {
        if(initialStart && mService != null) {
            initialStart = false;
            mContext.runOnUiThread(this::connect);
        }
    }

    private boolean connect() {
        try {
            BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
            BluetoothDevice device = bluetoothAdapter.getRemoteDevice(deviceAddress);
//            status("connecting...");
//            mLogger.write("Connecting...");
            isConnected = Connected.Pending;
            SerialSocket socket = new SerialSocket(mContext, device);
            mService.connect(socket);
            return true;
        } catch (Exception e) {
            onSerialConnectError(e);
            return false;
        }
    }

    private void disconnect() {
        isConnected = Connected.False;
        mService.disconnect();
    }



    @Override
    public boolean send(String string) {
        return send(string.getBytes());
    }

    @Override
    public boolean send(byte[] message) {

        return false;
    }


    @Override
    public void onServiceConnected(ComponentName name, IBinder service) {

    }

    @Override
    public void onServiceDisconnected(ComponentName name) {

    }

    @Override
    public void onSerialConnect() {

    }

    @Override
    public void onSerialConnectError(Exception e) {

    }

    @Override
    public void onSerialRead(byte[] data) {

    }

    @Override
    public void onSerialIoError(Exception e) {

    }
}
