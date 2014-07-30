package com.timmattison.hacking.usbrubberducky.instructions;

import java.io.ByteArrayOutputStream;

/**
 * Created by timmattison on 12/11/13.
 */
public class DefaultDelayInstruction extends VirtualInstruction implements Instruction {
    private final int delayValue;

    public DefaultDelayInstruction(int delayValue) {
        this.delayValue = delayValue;
    }

    public int getDelayValue() {
        return delayValue;
    }
}
