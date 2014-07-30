package com.timmattison.hacking.usbrubberducky.parsers.regex;

import com.google.inject.Inject;
import com.timmattison.hacking.usbrubberducky.constants.Whitespace;
import com.timmattison.hacking.usbrubberducky.instructions.StringInstruction;
import com.timmattison.hacking.usbrubberducky.instructions.factories.StringInstructionFactory;
import com.timmattison.hacking.usbrubberducky.preprocessors.Preprocessor;

import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: timmattison
 * Date: 11/27/13
 * Time: 6:17 PM
 * To change this template use File | Settings | File Templates.
 */
public class StringInstructionParser extends RegexAbstractInstructionParser<StringInstruction> {
    private static final String name = "STRING";
    private static final String matchingRegex = "^" + name + Whitespace.getWhitespaceCharClass() + "{1}" + "(.+)$";
    private final StringInstructionFactory stringInstructionFactory;

    @Inject
    public StringInstructionParser(Preprocessor preprocessor, StringInstructionFactory stringInstructionFactory) {
        super(preprocessor);
        this.stringInstructionFactory = stringInstructionFactory;
    }

    @Override
    protected StringInstruction create(List<String> input) {
        // The first (and only) input parameter is the string we need to be encoding, create the instruction using that data via the factory
        return stringInstructionFactory.create(input.get(0));
    }

    @Override
    protected String getMatchingRegex() {
        return matchingRegex;
    }
}
