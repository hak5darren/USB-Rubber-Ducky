package com.timmattison.hacking.usbrubberducky.translation.string;

import com.timmattison.hacking.usbrubberducky.translation.codes.KeyboardCode;
import com.timmattison.hacking.usbrubberducky.translation.codes.ReturnsKeyboardCode;

/**
 * Created by timmattison on 12/5/13.
 */
public enum KeyboardUSShiftedCodes implements ReturnsKeyboardCode {
    KeyboardA(4, 'A'),
    KeyboardB(5, 'B'),
    KeyboardC(6, 'C'),
    KeyboardD(7, 'D'),
    KeyboardE(8, 'E'),
    KeyboardF(9, 'F'),
    KeyboardG(10, 'G'),
    KeyboardH(11, 'H'),
    KeyboardI(12, 'I'),
    KeyboardJ(13, 'J'),
    KeyboardK(14, 'K'),
    KeyboardL(15, 'L'),
    KeyboardM(16, 'M'),
    KeyboardN(17, 'N'),
    KeyboardO(18, 'O'),
    KeyboardP(19, 'P'),
    KeyboardQ(20, 'Q'),
    KeyboardR(21, 'R'),
    KeyboardS(22, 'S'),
    KeyboardT(23, 'T'),
    KeyboardU(24, 'U'),
    KeyboardV(25, 'V'),
    KeyboardW(26, 'W'),
    KeyboardX(27, 'X'),
    KeyboardY(28, 'Y'),
    KeyboardZ(29, 'Z'),
    Keyboard1(30, '!'),
    Keyboard2(31, '@'),
    Keyboard3(32, '#'),
    Keyboard4(33, '$'),
    Keyboard5(34, '%'),
    Keyboard6(35, '^'),
    Keyboard7(36, '&'),
    Keyboard8(37, '*'),
    Keyboard9(38, '('),
    Keyboard0(39, ')'),
    KeyboardUnderscore(45, '_'),
    KeyboardPlus(46, '+'),
    KeyboardLeftCurlyBracket(47, '{'),
    KeyboardRightCurlyBracket(48, '}'),
    KeyboardPipe(49, '|'),
    KeyboardColon(51, ':'),
    KeyboardDoubleQuotes(52, '"'),
    KeyboardTilde(53, '~'),
    KeyboardLessThan(54, '<'),
    KeyboardGreaterThan(55, '>'),
    KeyboardQuestionMark(56, '?');

    private final KeyboardCode value;

    KeyboardUSShiftedCodes(int value, Character character) {
        this.value = new KeyboardCode(String.valueOf(character), (byte) value, KeyboardCode.SHIFT);
    }

    public KeyboardCode getValue() {
        return value;
    }
}
