package com.timmattison.hacking.usbrubberducky.instructions.factories;

import com.google.inject.assistedinject.Assisted;
import com.timmattison.hacking.usbrubberducky.instructions.KeypressInstruction;
import com.timmattison.hacking.usbrubberducky.translation.codes.KeyboardCode;

import java.util.Stack;

/**
 * Created by timmattison on 12/16/13.
 */
public interface KeypressInstructionFactory {
    KeypressInstruction create(@Assisted("keyboardCodeStack") Stack<KeyboardCode> keyboardCodeStack);
}
