package com.timmattison.hacking.usbrubberducky.parsers;

import com.google.inject.assistedinject.Assisted;
import com.timmattison.hacking.usbrubberducky.instructions.BasicRepeatInstruction;
import com.timmattison.hacking.usbrubberducky.instructions.DelayInstruction;
import com.timmattison.hacking.usbrubberducky.instructions.Instruction;
import com.timmattison.hacking.usbrubberducky.instructions.factories.RepeatInstructionFactory;
import com.timmattison.hacking.usbrubberducky.instructions.interfaces.RepeatInstruction;
import com.timmattison.hacking.usbrubberducky.instructions.lists.processors.RepeatInstructionListProcessor;
import junit.framework.Assert;
import org.junit.Before;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: timmattison
 * Date: 12/4/13
 * Time: 6:59 AM
 * To change this template use File | Settings | File Templates.
 */
public class TestRepeatInstructionListProcessor {
    private RepeatInstructionListProcessor repeatInstructionListProcessor;
    private RepeatInstructionFactory repeatInstructionFactory;

    @Before
    public void setup() {
        repeatInstructionFactory = new RepeatInstructionFactory() {
            @Override
            public RepeatInstruction create(@Assisted("repeatCount") int repeatCount) {
                return new BasicRepeatInstruction(repeatCount);
            }
        };

        repeatInstructionListProcessor = new RepeatInstructionListProcessor();
    }

    private DelayInstruction getDelayInstruction(int delayInMilliseconds) {
        return new DelayInstruction(delayInMilliseconds);
    }

    @Test
    public void testSingleRepeatRepeatsOnce() {
        List<Instruction> instructionList = new ArrayList<Instruction>();
        testSimpleRepeat(instructionList, 100, 1);
    }

    @Test
    public void testSingleRepeatRepeatsTenTimes() {
        List<Instruction> instructionList = new ArrayList<Instruction>();
        testSimpleRepeat(instructionList, 100, 10);
    }

    private void testSimpleRepeat(List<Instruction> instructionList, int delayInMilliseconds, int repeatCount) {
        instructionList.add(getDelayInstruction(delayInMilliseconds));
        instructionList.add(repeatInstructionFactory.create(repeatCount));

        instructionList = repeatInstructionListProcessor.process(instructionList);

        int totalInstructionCount = repeatCount + 1;
        Assert.assertEquals(totalInstructionCount, instructionList.size());

        for (int loop = 0; loop < totalInstructionCount; loop++) {
            Instruction instruction = instructionList.get(loop);
            Assert.assertTrue(instruction instanceof DelayInstruction);

            DelayInstruction delayInstruction = (DelayInstruction) instruction;
            Assert.assertEquals(delayInMilliseconds, delayInstruction.getDelayValue());
        }
    }
}
