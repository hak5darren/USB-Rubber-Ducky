package com.timmattison.hacking.usbrubberducky.instructions.lists;

import com.timmattison.hacking.usbrubberducky.instructions.Instruction;
import com.timmattison.hacking.usbrubberducky.instructions.interfaces.RepeatInstruction;
import com.timmattison.hacking.usbrubberducky.instructions.lists.processors.InstructionListProcessor;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;

/**
 * Created with IntelliJ IDEA.
 * User: timmattison
 * Date: 11/30/13
 * Time: 11:29 AM
 * To change this template use File | Settings | File Templates.
 */
public class BasicInstructionList implements InstructionList {
    private final Set<InstructionListProcessor> instructionListProcessors;

    protected List<Instruction> instructionList = new ArrayList<Instruction>();

    public BasicInstructionList(Set<InstructionListProcessor> instructionListProcessors) {
        this.instructionListProcessors = instructionListProcessors;
    }

    @Override
    public void addInstruction(Instruction instruction) {
        instructionList.add(instruction);
    }

    @Override
    public byte[] getBytes() throws IOException {
        // Create our output byte stream
        ByteArrayOutputStream baos = new ByteArrayOutputStream();

        // Create a new instruction list to hold our final instruction list (leave our existing instruction list in place)
        List<Instruction> finalInstructionList = new ArrayList<Instruction>();

        // Add all of the instructions to our new list
        finalInstructionList.addAll(instructionList);

        // Loop through all of the processors
        for (InstructionListProcessor instructionListProcessor : instructionListProcessors) {
            // For each processor loop as many times as it needs to
            while (true) {
                // TODO: There is a possibility of an infinite loop here.  We should have a sane upper bound.

                // Run each instruction list processor until it makes no more changes
                List<Instruction> tempInstructionList = instructionListProcessor.process(finalInstructionList);

                // Is this the same as the final instruction list?
                if (tempInstructionList.equals(finalInstructionList)) {
                    // Yes, break from the loop
                    break;
                }

                // The lists were different.  Update our final list and try again
                finalInstructionList = tempInstructionList;
            }
        }

        // Loop through all of the instructions
        for (Instruction instruction : finalInstructionList) {
            // Get the encoded instruction
            byte[] encodedInstruction = instruction.getEncodedInstruction();

            // Add the encoded instruction to the byte stream
            baos.write(encodedInstruction);
        }

        // Return the byte stream as a byte array
        return baos.toByteArray();
    }

    public List<Instruction> getInstructions() {
        return instructionList;
    }
}
