package com.timmattison.hacking.usbrubberducky.translation.codes;

/**
 * Created by timmattison on 12/5/13.
 */
public enum KeyboardSpecialCodes {
    ReservedNoEventIndicated(0),
    ErrorRollOver(1),
    POSTFail(2),
    ErrorUndefined(3);

    public int getValue() {
        return value;
    }

    private final int value;

    KeyboardSpecialCodes(int value) {
        this.value = value;
    }
}
