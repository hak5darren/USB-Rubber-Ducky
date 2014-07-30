package com.timmattison.hacking.usbrubberducky.translation;

import com.timmattison.hacking.usbrubberducky.translation.codes.KeyboardCode;

/**
 * Created by timmattison on 12/5/13.
 */
public interface CharacterTranslator {
    /**
     * Translates a character to a keyboard code object.  Throws an exception if the character cannot be translated.
     *
     * @param character
     * @return
     */
    KeyboardCode translate(char character);
}
