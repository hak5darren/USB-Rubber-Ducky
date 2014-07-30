package com.timmattison.hacking.usbrubberducky.translation.keyboards;

import com.timmattison.hacking.usbrubberducky.translation.codes.KeyboardCode;
import com.timmattison.hacking.usbrubberducky.translation.codes.ReturnsKeyboardCode;

import java.util.Map;

/**
 * Created by timmattison on 12/9/13.
 */
public abstract class AbstractKeyboardCodes {
    /**
     * Adds keyboard codes to a map
     *
     * @param keyboardCodeValues the codes to add to the map
     * @param keyboardCodes      the map to which the codes are added
     */
    protected void addKeyboardValues(ReturnsKeyboardCode[] keyboardCodeValues, Map<String, KeyboardCode> keyboardCodes) {
        for (ReturnsKeyboardCode keyboardCodeValue : keyboardCodeValues) {
            keyboardCodes.put(keyboardCodeValue.getValue().getStringToMatch(), keyboardCodeValue.getValue());
        }
    }
}
