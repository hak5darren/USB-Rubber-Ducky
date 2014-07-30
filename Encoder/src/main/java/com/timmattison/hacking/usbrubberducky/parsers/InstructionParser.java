package com.timmattison.hacking.usbrubberducky.parsers;

import com.timmattison.hacking.usbrubberducky.instructions.Instruction;

/**
 * Created with IntelliJ IDEA.
 * User: timmattison
 * Date: 11/27/13
 * Time: 6:15 PM
 * To change this template use File | Settings | File Templates.
 */
public interface InstructionParser<T extends Instruction> {
    /**
     * Returns an instruction if the input can be parsed as a particular instruction.  Returns NULL if not.
     *
     * @param input
     * @return
     */
    public T parse(String input);
}
