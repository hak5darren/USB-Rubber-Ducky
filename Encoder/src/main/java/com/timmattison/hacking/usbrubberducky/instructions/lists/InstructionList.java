package com.timmattison.hacking.usbrubberducky.instructions.lists;

import com.timmattison.hacking.usbrubberducky.instructions.Instruction;

import java.io.IOException;

/**
 * Holds a list of instructions and can convert the list into code suitable for the USB Rubber Ducky
 *
 * Created with IntelliJ IDEA.
 * User: timmattison
 * Date: 11/27/13
 * Time: 6:15 PM
 * To change this template use File | Settings | File Templates.
 */
public interface InstructionList {
    /**
     * Add an instruction to the list
     *
     * @param instruction
     */
    public void addInstruction(Instruction instruction);

    /**
     * Get the binary data for this instruction list
     *
     * @return
     * @throws IOException
     */
    public byte[] getBytes() throws IOException;
}
