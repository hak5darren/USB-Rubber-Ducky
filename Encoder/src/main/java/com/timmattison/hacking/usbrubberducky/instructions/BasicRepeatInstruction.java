package com.timmattison.hacking.usbrubberducky.instructions;

import com.google.inject.Inject;
import com.google.inject.assistedinject.Assisted;
import com.timmattison.hacking.usbrubberducky.instructions.interfaces.RepeatInstruction;

/**
 * Created with IntelliJ IDEA.
 * User: timmattison
 * Date: 12/3/13
 * Time: 8:00 PM
 * To change this template use File | Settings | File Templates.
 */
public class BasicRepeatInstruction extends VirtualInstruction implements RepeatInstruction {
    private final int repeatCount;
    private final int instructionCount = 1;

    @Inject
    public BasicRepeatInstruction(@Assisted("repeatCount") int repeatCount) {
        this.repeatCount = repeatCount;
    }

    public int getRepeatCount() {
        return repeatCount;
    }

    public int getInstructionCount() {
        return instructionCount;
    }
}
