package com.timmattison.hacking.usbrubberducky.preprocessors;

/**
 * This preprocessor does nothing and can be used for testing or to remove legacy support
 * <p/>
 * Created by timmattison on 7/30/14.
 */
public class NopPreprocessor implements Preprocessor {
    @Override
    public String preprocess(String input) {
        // Do nothing, just return the unmodified input
        return input;
    }
}
