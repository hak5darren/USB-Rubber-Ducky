package com.timmattison.hacking.usbrubberducky.instructions.lists.processors;

import com.timmattison.hacking.usbrubberducky.instructions.Instruction;
import com.timmattison.hacking.usbrubberducky.instructions.lists.InstructionList;

import java.util.List;

/**
 * Created by timmattison on 7/29/14.
 */
public interface InstructionListProcessor {
    /**
     * Takes a list of instructions and returns a new list of instructions with some processing done to it (removal of
     * NOPs, REPEAT instructions expanded, DELAYs added for DEFAULT_DELAY)
     * @param instructionList
     * @return
     */
    List<Instruction> process(List<Instruction> instructionList);
}
