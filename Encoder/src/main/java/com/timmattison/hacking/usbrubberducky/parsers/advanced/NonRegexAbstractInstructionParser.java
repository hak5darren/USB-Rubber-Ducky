package com.timmattison.hacking.usbrubberducky.parsers.advanced;

import com.google.inject.Inject;
import com.timmattison.hacking.usbrubberducky.instructions.Instruction;
import com.timmattison.hacking.usbrubberducky.parsers.InstructionParser;
import com.timmattison.hacking.usbrubberducky.preprocessors.Preprocessor;

/**
 * Parses an instruction that is not described by a regular expression
 * <p/>
 * Created with IntelliJ IDEA.
 * User: timmattison
 * Date: 11/27/13
 * Time: 6:15 PM
 * To change this template use File | Settings | File Templates.
 */
public abstract class NonRegexAbstractInstructionParser<T extends Instruction> implements InstructionParser {
    private final Preprocessor preprocessor;

    @Inject
    public NonRegexAbstractInstructionParser(Preprocessor preprocessor) {
        this.preprocessor = preprocessor;
    }

    @Override
    public T parse(String input) {
        // Preprocess the input
        input = preprocessor.preprocess(input);

        // Let the concrete implementation do its job
        return innerParse(input);
    }

    /**
     * Runs the non-regex parser
     *
     * @param input
     * @return
     */
    protected abstract T innerParse(String input);
}
