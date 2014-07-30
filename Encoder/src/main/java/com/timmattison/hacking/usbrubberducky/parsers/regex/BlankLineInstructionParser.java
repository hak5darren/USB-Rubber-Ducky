package com.timmattison.hacking.usbrubberducky.parsers.regex;

import com.google.inject.Inject;
import com.timmattison.hacking.usbrubberducky.instructions.NopInstruction;
import com.timmattison.hacking.usbrubberducky.preprocessors.Preprocessor;

import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: timmattison
 * Date: 11/30/13
 * Time: 11:32 AM
 * To change this template use File | Settings | File Templates.
 */
public class BlankLineInstructionParser extends RegexAbstractInstructionParser<NopInstruction> {
    private static final String matchingRegex = "^\\s*$";

    @Inject
    public BlankLineInstructionParser(Preprocessor preprocessor) {
        super(preprocessor);
    }

    @Override
    protected NopInstruction create(List<String> input) {
        // Blank lines are treated as a NOP
        return new NopInstruction();
    }

    @Override
    protected String getMatchingRegex() {
        return matchingRegex;
    }
}
