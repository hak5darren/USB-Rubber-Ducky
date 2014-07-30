package com.timmattison.hacking.usbrubberducky.translation.codes;

/**
 * Created by timmattison on 12/5/13.
 */
public enum KeyboardModifier implements ReturnsKeyboardCode {
    CTRL("CTRL", 0x01),
    CONTROL("CONTROL", 0x01),
    SHIFT("SHIFT", 0x02),
    ALT("ALT", 0xE2),
    GUI("GUI", 0x08),
    WINDOWS("WINDOWS", 0x08),
    COMMAND("COMMAND", 0x08),
    LEFT_CTRL("LEFTCTRL", 0xE0),
    LEFT_SHIFT("LEFTSHIFT", 0xE1),
    LEFT_ALT("LEFTALT", 0xE2),
    LEFT_GUI("LEFTGUI", 0xE3),
    RIGHT_CTRL("RIGHTCTRL", 0xE4),
    RIGHT_SHIFT("RIGHTSHIFT", 0xE5),
    RIGHT_ALT("RIGHTALT", 0xE6),
    RIGHT_GUI("RIGHTGUI", 0xE7);

    private final KeyboardCode value;

    KeyboardModifier(String name, int value) {
        this.value = new KeyboardCode(name, (byte) 0x00, (byte) value);
    }

    public KeyboardCode getValue() {
        return value;
    }
}
