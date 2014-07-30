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
        // Create a byte stream for our output
        ByteArrayOutputStream baos = new ByteArrayOutputStream();

        // Store a copy of the delay value
        int tempDelayValue = delayValue;

        // Loop until there's no delay value left
        while (tempDelayValue > 0) {
            // Write the opcode for the delay instruction
            baos.write(DELAY_INSTRUCTION_OPCODE);

            // Is the amount of delay left over too big to fit in a single command?
            if (tempDelayValue > MAX_SINGLE_DELAY) {
                // Yes, write the maximum delay possible
                baos.write(MAX_SINGLE_DELAY);
            } else {
                // No, just write the amount of the delay that's left
                baos.write(tempDelayValue);
            }

            // Subtract out the maximum delay.  This will give us the delay that is left OR a negative number OR zero
            tempDelayValue -= MAX_SINGLE_DELAY;
        }

        // Convert the stream to a byte array and return it
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
