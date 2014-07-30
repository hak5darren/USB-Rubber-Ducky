package com.timmattison.hacking.usbrubberducky.instructions;

import com.google.inject.Inject;
import com.google.inject.assistedinject.Assisted;

import java.io.ByteArrayOutputStream;

/**
 * Created by timmattison on 12/11/13.
 */
public class DelayInstruction implements Instruction {
    private static final int DELAY_INSTRUCTION_OPCODE = 0x00;
    private static final int MAX_SINGLE_DELAY = 0xFF;
    private final int delayValue;

    @Inject
    public DelayInstruction(@Assisted("delayInMilliseconds") int delayValue) {
        this.delayValue = delayValue;
    }

    @Override
    public byte[] getEncodedInstruction() {
        ByteArrayOutputStream baos = new ByteArrayOutputStream();

        int tempDelayValue = delayValue;

        while (tempDelayValue > 0) {
            baos.write(DELAY_INSTRUCTION_OPCODE);

            if (tempDelayValue > MAX_SINGLE_DELAY) {
                baos.write(MAX_SINGLE_DELAY);
            } else {
                baos.write(tempDelayValue);
            }

            tempDelayValue -= MAX_SINGLE_DELAY;
        }

        return baos.toByteArray();
    }

    public int getDelayValue() {
        return delayValue;
    }

    @Override
    public String toString() {
        return "DELAY " + delayValue;
    }
}
