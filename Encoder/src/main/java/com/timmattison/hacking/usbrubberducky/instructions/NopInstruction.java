package com.timmattison.hacking.usbrubberducky.instructions;

import java.io.ByteArrayOutputStream;

/**
 * Created by timmattison on 12/11/13.
 */
public class NopInstruction implements Instruction {
    @Override
    public byte[] getEncodedInstruction() {
        // Return an empty array to indicate that this instruction does nothing
        return new byte[0];
    }
}
