package com.timmattison.hacking.usbrubberducky.translation.codes;

import java.io.ByteArrayOutputStream;

/**
 * Created by timmattison on 12/9/13.
 */
public class KeyboardCode {
    public static final byte SHIFT = 0x02;
    public static final byte NO_SHIFT = 0x00;

    private final String stringToMatch;
    private final byte firstByte;
    private final byte secondByte;

    public KeyboardCode(String stringToMatch, byte firstByte, byte secondByte) {
        this.stringToMatch = stringToMatch;
        this.firstByte = firstByte;
        this.secondByte = secondByte;
    }

    public String getStringToMatch() {
        return stringToMatch;
    }

    public KeyboardCode combine(KeyboardCode keyboardCode) {
        KeyboardCode newKeyboardCode = new KeyboardCode(stringToMatch, (byte) (firstByte | keyboardCode.getFirstByte()), (byte) (secondByte | keyboardCode.getSecondByte()));

        return newKeyboardCode;
    }

    public void write(ByteArrayOutputStream baos) {
        baos.write(firstByte);
        baos.write(secondByte);
    }

    public byte[] getBytes() {
        byte[] output = new byte[2];

        output[0] = firstByte;
        output[1] = secondByte;

        return output;
    }

    public byte getFirstByte() {
        return firstByte;
    }

    public byte getSecondByte() {
        return secondByte;
    }
}
