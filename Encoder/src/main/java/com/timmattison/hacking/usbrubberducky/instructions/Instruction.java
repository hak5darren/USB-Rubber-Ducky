package com.timmattison.hacking.usbrubberducky.instructions;

/**
 * A single instruction
 *
 * Created with IntelliJ IDEA.
 * User: timmattison
 * Date: 11/27/13
 * Time: 6:15 PM
 * To change this template use File | Settings | File Templates.
 */
public interface Instruction {
    /**
     * Gets the raw bytes of the instruction after it has been encoded
     * @return
     */
    public byte[] getEncodedInstruction();
}
