package com.tamerlanchik.robocar;

import android.graphics.Point;
import android.graphics.PointF;
import android.util.Log;

import java.lang.reflect.Array;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;

public class MessageManager {
    public enum Mode {CHECK_CONN, MOTOR_COMM, SIGNAL_COMM, SENSOR_REQUEST, ALL};
    public static char[] mCode = {'#', '@'};
    public enum MessCode {EMPTY, CHKCONN, ANDR_CHK_CONN, CHASSIS_COMM, DEF1};

    public static byte[] buildJoystickMessage(Point data){
        List<Byte> l = new ArrayList<>();

        //l.add((byte)'#');
        l.add((byte)MessCode.CHASSIS_COMM.ordinal());
        copyArrayToList(l, intToByte(-data.y));
        copyArrayToList(l, intToByte(-data.x));
        l.add((byte)';');

        byte a[] = new byte[l.size()];
        for(int i=0; i<l.size(); i++){
            a[i] = l.get(i);
        }
        return a;
    }
    public static void handleMessage(byte[] mess){

    }

    private static void copyArrayToList(List<Byte> l, byte[] d){
        for(byte b : d){
            l.add(b);
        }
    }

    private static byte[] floatToByte(float a){
        return ByteBuffer.allocate(Float.SIZE/8).putFloat(a).array();
    }

    private static byte[] intToByte(int a){
        return ByteBuffer.allocate(Integer.SIZE/8).putInt(a).array();
    }

    private static float byteToFloat(byte[] b){
        return ByteBuffer.wrap(b).getFloat();
    }

    private static int byteToInt(byte[] b){
        return ByteBuffer.wrap(b).getInt();
    }

    public static boolean isControlData(byte [] message){
        /*if(findInArray(code, message[0]) >= 0){
            return true;
        }else{
            return false;
        }*/
        return true;
    }

    private static int findInArray(char [] a, byte c){
        for(int i=0; i<a.length; i++){
            if(a[i] == c){
                return i;
            }
        }
        return -1;
    }
}