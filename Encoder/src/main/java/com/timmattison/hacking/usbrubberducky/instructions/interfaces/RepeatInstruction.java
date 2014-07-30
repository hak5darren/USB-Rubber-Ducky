package com.timmattison.hacking.usbrubberducky.instructions.interfaces;

import com.timmattison.hacking.usbrubberducky.instructions.Instruction;

/**
 * Created with IntelliJ IDEA.
 * User: timmattison
 * Date: 12/3/13
 * Time: 8:00 PM
 * To change this template use File | Settings | File Templates.
 */
public interface RepeatInstruction extends Instruction {
    /**
     * Get the number of times to repeat
     *
     * @return
     */
    public int getRepeatCount();

    /**
     * Get the number of instructions to repeat
     *
     * @return
     */
    public int getInstructionCount();
}
