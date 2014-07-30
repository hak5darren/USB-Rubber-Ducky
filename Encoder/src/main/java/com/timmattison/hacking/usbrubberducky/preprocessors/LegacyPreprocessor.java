package com.timmattison.hacking.usbrubberducky.preprocessors;

/**
 * This preprocessor converts some legacy script syntax to the standard syntax
 * <p/>
 * Created by timmattison on 7/30/14.
 */
public class LegacyPreprocessor implements Preprocessor {
    @Override
    public String preprocess(String input) {
        /**
         * "CTRL-SHIFT" needs to be translated to "CTRL SHIFT" because we stack up the modifiers automatically rather
         * than directly supporting a new code that is both values combined
         */
        input = input.replaceAll("^CTRL-SHIFT", "CTRL SHIFT");
        input = input.replaceAll("^CONTROL-SHIFT", "CONTROL SHIFT");

        /**
         * We always treat "DEFAULTDELAY" as "DEFAULT_DELAY".  No reason to have another code for that.
         */
        input = input.replaceAll("^DEFAULTDELAY", "DEFAULT_DELAY");

        return input;
    }
}
