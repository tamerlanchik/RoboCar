package com.tamerlanchik.robocar.transport;

public interface Communicator {
    void onStart();
    void onStop();
    void onDestroy();
    void onResume();

    boolean send(String string);
    boolean send(byte[] message);
    
}

