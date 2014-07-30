package com.timmattison.hacking.usbrubberducky.translation.string;

import com.timmattison.hacking.usbrubberducky.translation.codes.KeyboardCode;
import com.timmattison.hacking.usbrubberducky.translation.codes.ReturnsKeyboardCode;

/**
 * Created by timmattison on 12/5/13.
 */
public enum KeyboardUSNonShiftedCodes implements ReturnsKeyboardCode {
    KeyboardA(4, 'a'),
    KeyboardB(5, 'b'),
    KeyboardC(6, 'c'),
    KeyboardD(7, 'd'),
    KeyboardE(8, 'e'),
    KeyboardF(9, 'f'),
    KeyboardG(10, 'g'),
    KeyboardH(11, 'h'),
    KeyboardI(12, 'i'),
    KeyboardJ(13, 'j'),
    KeyboardK(14, 'k'),
    KeyboardL(15, 'l'),
    KeyboardM(16, 'm'),
    KeyboardN(17, 'n'),
    KeyboardO(18, 'o'),
    KeyboardP(19, 'p'),
    KeyboardQ(20, 'q'),
    KeyboardR(21, 'r'),
    KeyboardS(22, 's'),
    KeyboardT(23, 't'),
    KeyboardU(24, 'u'),
    KeyboardV(25, 'v'),
    KeyboardW(26, 'w'),
    KeyboardX(27, 'x'),
    KeyboardY(28, 'y'),
    KeyboardZ(29, 'z'),
    Keyboard1(30, '1'),
    Keyboard2(31, '2'),
    Keyboard3(32, '3'),
    Keyboard4(33, '4'),
    Keyboard5(34, '5'),
    Keyboard6(35, '6'),
    Keyboard7(36, '7'),
    Keyboard8(37, '8'),
    Keyboard9(38, '9'),
    Keyboard0(39, '0'),
    KeyboardSpace(44, ' '),
    KeyboardMinus(45, '-'),
    KeyboardEquals(46, '='),
    KeyboardLeftBracket(47, '['),
    KeyboardRightBracket(48, ']'),
    KeyboardBackslash(49, '\\'),
    KeyboardSemicolon(51, ';'),
    KeyboardApostrophe(52, '\''),
    KeyboardGraveAccent(53, '`'),
    KeyboardComma(54, ','),
    KeyboardPeriod(55, '.'),
    KeyboardForwardSlash(56, '/');

    private final KeyboardCode value;

    KeyboardUSNonShiftedCodes(int value, Character character) {
        this.value = new KeyboardCode(String.valueOf(character), (byte) value, KeyboardCode.NO_SHIFT);
    }

    public KeyboardCode getValue() {
        return value;
    }
}
