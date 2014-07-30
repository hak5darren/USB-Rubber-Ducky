package com.timmattison.hacking.usbrubberducky.instructions.factories;

import com.google.inject.assistedinject.Assisted;
import com.timmattison.hacking.usbrubberducky.instructions.StringInstruction;

/**
 * Created by timmattison on 12/16/13.
 */
public interface StringInstructionFactory {
    StringInstruction create(@Assisted("input") String input);
}
