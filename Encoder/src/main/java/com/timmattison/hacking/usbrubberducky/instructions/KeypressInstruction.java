package com.timmattison.hacking.usbrubberducky.instructions;

import com.google.gson.Gson;
import com.google.inject.assistedinject.Assisted;
import com.timmattison.hacking.usbrubberducky.translation.codes.KeyboardCode;
import com.timmattison.hacking.usbrubberducky.translation.codes.KeyboardModifier;

import javax.inject.Inject;
import java.util.HashSet;
import java.util.Set;
import java.util.Stack;

/**
 * Created with IntelliJ IDEA.
 * User: timmattison
 * Date: 12/3/13
 * Time: 7:52 PM
 * To change this template use File | Settings | File Templates.
 */
public class KeypressInstruction implements Instruction {
    private final Stack<KeyboardCode> keyboardCodeStack;

    @Inject
    public KeypressInstruction(@Assisted("keyboardCodeStack") Stack<KeyboardCode> keyboardCodeStack) {
        this.keyboardCodeStack = keyboardCodeStack;
    }

    @Override
    public byte[] getEncodedInstruction() {
        // The final output value
        KeyboardCode output = null;

        // The keyboard codes we've used already
        HashSet<KeyboardCode> usedKeyboardCodes = new HashSet<KeyboardCode>();

        // Clone the stack that we're working with so that we can re-run this instruction if necessary
        Stack<KeyboardCode> tempKeyboardCodeStack = (Stack<KeyboardCode>) keyboardCodeStack.clone();

        // Loop while there are still codes on the stack
        while (!tempKeyboardCodeStack.empty()) {
            // Pop off the top element
            KeyboardCode keyboardCode = tempKeyboardCodeStack.pop();

            // Make sure there are no duplicates
            forceNoDuplicates(usedKeyboardCodes, keyboardCode);

            // TODO: Check to make sure that we don't have codes whose bit pattern clashes

            // Do we have any keys yet?
            if (output == null) {
                // No, just copy this code
                output = keyboardCode;
            } else {
                // Yes, it with the previous keys
                output = output.combine(keyboardCode);
            }
        }

        // Return the bytes to the caller
        return output.getBytes();
    }

    private void forceNoDuplicates(Set<KeyboardCode> usedKeyboardCodes, KeyboardCode keyboardCode) {
        // TODO: This could be done with less code if we use contains()

        // Determine how big our set was before we added this element
        int sizeBeforeAdding = usedKeyboardCodes.size();

        // Add the code to the set
        usedKeyboardCodes.add(keyboardCode);

        // Determine how big our set is now
        int sizeAfterAdding = usedKeyboardCodes.size();

        // Did the set increase in size?
        if (sizeAfterAdding == sizeBeforeAdding) {
            // No, this means we have a duplicate code
            throw new UnsupportedOperationException("Duplicate keyboard code in a single line [" + keyboardCode + "]");
        }
    }

    @Override
    public String toString() {
        return new Gson().toJson(this);
    }
}
