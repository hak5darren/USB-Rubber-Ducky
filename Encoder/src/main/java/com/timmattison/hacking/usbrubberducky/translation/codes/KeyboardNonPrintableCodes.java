package com.timmattison.hacking.usbrubberducky.translation.codes;

/**
 * Created by timmattison on 12/5/13.
 *
 * Built from http://www.usb.org/developers/devclass_docs/Hut1_11.pdf
 *
 * The original USB Rubber Ducky application defines MENU and APP as code 101.  USB HID defines MENU as 118.
 * To maintain backwards compatibility USB HID's MENU was renamed MENU2
 */
public enum KeyboardNonPrintableCodes implements ReturnsKeyboardCode {
    KeyboardEnter(40, "ENTER"),
    KeyboardEscape(41, "ESCAPE"),
    KeyboardEscape2(41, "ESC"),
    KeyboardSpace(44, "SPACE"),
    KeyboardCapsLock(57, "CAPSLOCK"),
    KeyboardF1(58, "F1"),
    KeyboardF2(59, "F2"),
    KeyboardF3(60, "F3"),
    KeyboardF4(61, "F4"),
    KeyboardF5(62, "F5"),
    KeyboardF6(63, "F6"),
    KeyboardF7(64, "F7"),
    KeyboardF8(65, "F8"),
    KeyboardF9(66, "F9"),
    KeyboardF10(67, "F10"),
    KeyboardF11(68, "F11"),
    KeyboardF12(69, "F12"),
    KeyboardPrintScreen(70, "PRINTSCREEN"),
    KeyboardScrollLock(71, "SCROLLLOCK"),
    KeyboardPause(72, "PAUSE"),
    KeyboardInsert(73, "INSERT"),
    KeyboardHome(74, "HOME"),
    KeyboardPageUp(75, "PAGEUP"),
    KeyboardDeleteForward(76, "DELETE"),
    KeyboardEnd(77, "END"),
    KeyboardPageDown(78, "PAGEDOWN"),
    KeyboardRightArrow(79, "RIGHTARROW"),
    KeyboardRightArrow2(79, "RIGHT"),
    KeyboardLeftArrow(80, "LEFTARROW"),
    KeyboardLeftArrow2(80, "LEFT"),
    KeyboardDownArrow(81, "DOWNARROW"),
    KeyboardDownArrow2(81, "DOWN"),
    KeyboardUpArrow(82, "UPARROW"),
    KeyboardUpArrow2(82, "UP"),
    KeyboardMenu(101, "MENU"),
    KeyboardApplication(101, "APPLICATION"),
    KeyboardPower(102, "POWER"),
    KeyboardF13(104, "F13"),
    KeyboardF14(105, "F14"),
    KeyboardF15(106, "F15"),
    KeyboardF16(107, "F16"),
    KeyboardF17(108, "F17"),
    KeyboardF18(109, "F18"),
    KeyboardF19(110, "F19"),
    KeyboardF20(111, "F20"),
    KeyboardF21(112, "F21"),
    KeyboardF22(113, "F22"),
    KeyboardF23(114, "F23"),
    KeyboardF24(115, "F24"),
    KeyboardExecute(116, "EXECUTE"),
    KeyboardHelp(117, "HELP"),
    KeyboardMenu2(118, "MENU2"), // Renamed from MENU for backwards compatibility
    KeyboardSelect(119, "SELECT"),
    KeyboardStop(120, "STOP"),
    KeyboardAgain(121, "AGAIN"),
    KeyboardUndo(122, "UNDO"),
    KeyboardCut(123, "CUT"),
    KeyboardCopy(124, "COPY"),
    KeyboardPaste(125, "PASTE"),
    KeyboardFind(126, "FIND"),
    KeyboardMute(127, "MUTE"),
    KeyboardVolumeUp(128, "VOLUMEUP"),
    KeyboardVolumeDown(129, "VOLUMEDOWN"),
    KeyboardLockingCapsLock(130, "LOCKINGCAPSLOCK"),
    KeyboardLockingNumLock(131, "LOCKINGNUMLOCK"),
    KeyboardLockingScrollLock(132, "LOCKINGSCROLLLOCK"),
    KeyboardInternational1(135, "INTERNATIONAL1"),
    KeyboardInternational2(136, "INTERNATIONAL2"),
    KeyboardInternational3(137, "INTERNATIONAL3"),
    KeyboardInternational4(138, "INTERNATIONAL4"),
    KeyboardInternational5(139, "INTERNATIONAL5"),
    KeyboardInternational6(140, "INTERNATIONAL6"),
    KeyboardInternational7(141, "INTERNATIONAL7"),
    KeyboardInternational8(142, "INTERNATIONAL8"),
    KeyboardInternational9(143, "INwallpaper-prankTERNATIONAL9"),
    KeyboardLang1(144, "LANG1"),
    KeyboardLang2(145, "LANG2"),
    KeyboardLang3(146, "LANG3"),
    KeyboardLang4(147, "LANG4"),
    KeyboardLang5(148, "LANG5"),
    KeyboardLang6(149, "LANG6"),
    KeyboardLang7(150, "LANG7"),
    KeyboardLang8(151, "LANG8"),
    KeyboardLang9(152, "LANG9"),
    KeyboardAlternateErase(153, "ALTERNATEERASE"),
    KeyboardSysReqAttention(154, "SYSREQ_ATTENTION"),
    KeyboardCancel(155, "CANCEL"),
    KeyboardClear(156, "CLEAR"),
    KeyboardPrior(157, "PRIOR"),
    KeyboardReturn(158, "RETURN"),
    KeyboardSeparator(159, "SEPARATOR"),
    KeyboardOut(160, "OUT"),
    KeyboardOper(161, "OPER"),
    KeyboardClearAgain(162, "CLEAR_AGAIN"),
    KeyboardCrSelProps(163, "CRSEL_PROPS"),
    KeyboardExSel(164, "EXSEL"),
    KeyboardWindows(0xE3, "WINDOWS"),
    KeyboardGui(0xE3, "GUI"),
    KeyboardTab(0x2B, "TAB");

    private final KeyboardCode value;

    public KeyboardCode getValue() {
        return value;
    }

    KeyboardNonPrintableCodes(int value, String name) {
        this.value = new KeyboardCode(name, (byte) value, KeyboardCode.NO_SHIFT);
    }
}
