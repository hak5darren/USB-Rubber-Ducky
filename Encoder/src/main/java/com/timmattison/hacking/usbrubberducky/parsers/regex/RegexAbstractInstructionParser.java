package com.timmattison.hacking.usbrubberducky.parsers.regex;

import com.google.inject.Inject;
import com.timmattison.hacking.usbrubberducky.instructions.Instruction;
import com.timmattison.hacking.usbrubberducky.parsers.InstructionParser;
import com.timmattison.hacking.usbrubberducky.preprocessors.Preprocessor;

import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Parses an instruction that is described by a regular expression
 *
 * Created with IntelliJ IDEA.
 * User: timmattison
 * Date: 11/27/13
 * Time: 6:15 PM
 * To change this template use File | Settings | File Templates.
 */
public abstract class RegexAbstractInstructionParser<T extends Instruction> implements InstructionParser<T> {
    protected final Preprocessor preprocessor;
    private Pattern pattern;

    @Inject
    public RegexAbstractInstructionParser(Preprocessor preprocessor) {
        this.preprocessor = preprocessor;
    }

    private Pattern getPattern() {
        // Did we already create a pattern object?
        if(pattern == null) {
            // No, create one with the matching regex
            pattern = Pattern.compile(getMatchingRegex());
        }

        // Return the pattern to the caller
        return pattern;
    }

    private Matcher getMatcher(String input) {
        return getPattern().matcher(input);
    }

    @Override
    public T parse(String input) {
        // Preprocess the input
        input = preprocessor.preprocess(input);

        // Get the matcher
        Matcher matcher = getMatcher(input);

        // Does this input match what we're expecting for this instruction?
        if (!matcher.find()) {
            // No, just return NULL
            return null;
        }

        // The input matches

        // Create an array to hold the fields for this instruction
        List<String> fields = new ArrayList<String>();

        // Loop through each group
        for(int loop = 0; loop < matcher.groupCount(); loop++) {
            // Add the group to the fields (+1 skips the first group which is the instruction itself)
            fields.add(matcher.group(loop + 1));
        }

        // Create the instruction with the extracted fields
        return create(fields);
    }

    /**
     * Creates an instruction once we know that the input matches the regex
     *
     * @param input
     * @return
     */
    protected abstract T create(List<String> input);

    /**
     * Returns the regex that an input must match for this instruction
     *
     * @return
     */
    protected abstract String getMatchingRegex();
}
