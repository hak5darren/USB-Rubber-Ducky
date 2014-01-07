// File:         Encoder.java
// Created:      8/10/2011
// Author:       Jason Appelbaum Jason@Hak5.org	

import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.swing.text.BadLocationException;
import javax.swing.text.Document;
import javax.swing.text.rtf.RTFEditorKit;

public class Encoder {

	public static void main(String[] args) {

		String helpStr = "Hak5 Duck Encoder 1.2\n\n"
				+ "usage: duckencode -i [file ..]\t\t\tencode specified file\n"
				+ "   or: duckencode -i [file ..] -o [file ..]\tencode to specified file\n"
				+ "\nArguments:\n"
				+ "   -i [file ..] \t\tInput File\n"
				+ "   -o [file ..] \t\tOutput File\n"
				+ "\nScript Commands:\n"
				+ "   ALT [END | (ESCAPE | ESC) | F1...F12 | Single Char | SPACE | TAB]\n"
				+ "   BREAK | PAUSE\n"
				+ "   CAPSLOCK\n"
				+ "   CONTROL | CTRL [(BREAK | PAUSE) | F1...F12 | (ESCAPE | ESC) | Single Char]\n"
				+ "   DEFAULT_DELAY | DEFAULTDELAY [Time in millisecond * 10]\n"
				+ "   DELAY [Time in millisecond * 10]\n"
				+ "   DELETE\n"
				+ "   DOWNARROW | DOWN\n"
				+ "   END\n"
				+ "   ESCAPE | ESC\n"
				+ "   F1...F12\n"
				+ "   HOME\n"
				+ "   INSERT\n"
				+ "   LEFTARROW | LEFT\n"
				+ "   MENU | APP\n"
				+ "   NUMLOCK\n"
				+ "   PAGEDOWN\n"
				+ "   PAGEUP\n"
				+ "   PRINTSCREEN\n"
				+ "   REM\n"
				+ "   RIGHTARROW | RIGHT\n"
				+ "   SCROLLLOCK\n"
				+ "   SHIFT [ DELETE | HOME | INSERT | PAGEUP | PAGEDOWN | (WINDOWS | GUI)\n"
				+ "         | (UPARROW | DOWNARROW |LEFTARROW | RIGHTARROW) | TAB]\n"
				+ "   SPACE\n"
				+ "   STRING [a...z A...Z 0..9 !...) `~ += _- \"\' :; <, >. ?/ \\|]\n"
				+ "   TAB\n" + "   UPARROW | UP\n" + "   WINDOWS | GUI\n";

		String inputFile = null;
		String outputFile = null;

		if (args.length == 0) {
			System.out.println(helpStr);
			System.exit(0);
		}

		for (int i = 0; i < args.length; i++) {
			if (args[i].equals("--gui") || args[i].equals("-g")) {
				System.out.println("Launch GUI");
			} else if (args[i].equals("--help") || args[i].equals("-h")) {
				System.out.println(helpStr);
			} else if (args[i].equals("-i")) {
				// encode file
				inputFile = args[++i];
			} else if (args[i].equals("-o")) {
				// output file
				outputFile = args[++i];
			} else {
				System.out.println(helpStr);
				break;
			}
		}

		if (inputFile != null) {
			String scriptStr = null;

			if (inputFile.contains(".rtf")) {
				try {
					FileInputStream stream = new FileInputStream(inputFile);
					RTFEditorKit kit = new RTFEditorKit();
					Document doc = kit.createDefaultDocument();
					kit.read(stream, doc, 0);

					scriptStr = doc.getText(0, doc.getLength());
				} catch (IOException e) {
					System.out.println("Error with input file!");
				} catch (BadLocationException e) {
					System.out.println("Error with input file!");
				}
			} else {
				DataInputStream in = null;
				try {
					File f = new File(inputFile);
					byte[] buffer = new byte[(int) f.length()];
					in = new DataInputStream(new FileInputStream(f));
					in.readFully(buffer);
					scriptStr = new String(buffer);

				} catch (IOException e) {
					System.out.println("Error with input file!");
				} finally {
					try {
						in.close();
					} catch (IOException e) { /* ignore it */
					}
				}
			}

			encodeToFile(scriptStr, (outputFile == null) ? "inject.bin"
					: outputFile);
		}
	}

	private static void encodeToFile(String inStr, String fileDest) {
		inStr = inStr.replaceAll("\\r", ""); // CRLF Fix
		String[] instructions = inStr.split("\n");
		List<Byte> file = new ArrayList<Byte>();
		int defaultDelay = 0;

		for (int i = 0; i < instructions.length; i++) {
			try {
				boolean delayOverride = false;
				String commentCheck = instructions[i].substring(0, 2);
				if (commentCheck.equals("//"))
					continue;

				String instruction[] = instructions[i].split(" ", 2);

				instruction[0].trim();

				if (instruction.length == 2) {
					instruction[1].trim();
				}

				if (instruction[0].equals("DEFAULT_DELAY")
						|| instruction[0].equals("DEFAULTDELAY")) {
					defaultDelay = (byte) Integer.parseInt(instruction[1]
							.trim());
				} else if (instruction[0].equals("DELAY")) {
					int delay = Integer.parseInt(instruction[1].trim());
					while (delay > 0) {
						file.add((byte) 0x00);
						if (delay > 255) {
							file.add((byte) 0xFF);
							delay = delay - 255;
						} else {
							file.add((byte) delay);
							delay = 0;
						}
					}
					delayOverride = true;
				} else if (instruction[0].equals("STRING")) {
					for (int j = 0; j < instruction[1].length(); j++) {
						char c = instruction[1].charAt(j);
						file.add(charToByte(c));

						// Auto shift
						byte shiftByte = 0x00;
						if ((int) c >= 65 && (int) c <= 90) {
							// switch capital letters
							shiftByte = 0x02;
						} else {
							switch (c) {
							case '~':
							case '!':
							case '@':
							case '#':
							case '$':
							case '%':
							case '^':
							case '&':
							case '*':
							case '(':
							case ')':
							case '_':
							case '+':
							case '}':
							case '{':
							case '|':
							case '"':
							case ':':
							case '?':
							case '>':
							case '<':
								// shift
								shiftByte = 0x02;
								break;
							}
						}
						file.add(shiftByte);
					}
				} else if (instruction[0].equals("CONTROL")
						|| instruction[0].equals("CTRL")) {
					if (instruction[1].equals("ESCAPE")
							|| instruction[1].equals("ESC"))
						file.add((byte) 0x29);
					else if (instruction[1].equals("PAUSE")
							|| instruction[1].equals("BREAK"))
						file.add((byte) 0x48);
					else if (instruction.length != 1)
						if (functionKeyCheck(instruction[1]))
							file.add(functionKeyToByte(instruction[1]));
						else
							file.add(charToByte(instruction[1].charAt(0)));
					else
						file.add((byte) 0x00);
					file.add((byte) 0x01);
				} else if (instruction[0].equals("ALT")) {
					if (instruction.length != 1) {
						if (instruction[1].equals("ESCAPE")
								|| instruction[1].equals("ESC"))
							file.add((byte) 0x29);
						else if (instruction[1].equals("SPACE"))
							file.add((byte) 0x2C);
						else if (instruction[1].equals("TAB"))
							file.add((byte) 0x2B);
						else if (instruction.length != 1)
							if (functionKeyCheck(instruction[1]))
								file.add(functionKeyToByte(instruction[1]));
							else
								file.add(charToByte(instruction[1].charAt(0)));
						else
							file.add((byte) 0x00);
					} else {
						file.add((byte) 0x00);
					}
					file.add((byte) 0xE2);

				} else if (instruction[0].equals("ENTER")) {
					file.add((byte) 0x28);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("SHIFT")) {
					if (instruction.length != 1) {
						if (instruction[1].equals("HOME")) {
							file.add((byte) 0x4A);
						} else if (instruction[1].equals("TAB")) {
							file.add((byte) 0x2B);
						} else if (instruction[1].equals("WINDOWS")
								|| instruction[1].equals("GUI")) {
							file.add((byte) 0xE3);
						} else if (instruction[1].equals("INSERT")) {
							file.add((byte) 0x49);
						} else if (instruction[1].equals("PAGEUP")) {
							file.add((byte) 0x4B);
						} else if (instruction[1].equals("PAGEDOWN")) {
							file.add((byte) 0x4E);
						} else if (instruction[1].equals("DELETE")) {
							file.add((byte) 0x4C);
						} else if (instruction[1].equals("END")) {
							file.add((byte) 0x4D);
						} else if (instruction[1].equals("UPARROW")) {
							file.add((byte) 0x52);
						} else if (instruction[1].equals("DOWNARROW")) {
							file.add((byte) 0x51);
						} else if (instruction[1].equals("LEFTARROW")) {
							file.add((byte) 0x50);
						} else if (instruction[1].equals("RIGHTARROW")) {
							file.add((byte) 0x4F);
						}
						file.add((byte) 0xE1);
					} else {
						file.add((byte) 0xE1);
						file.add((byte) 0x00);
					}
				} else if (instruction[0].equals("REM")) {
					continue;
				} else if (instruction[0].equals("MENU")
						|| instruction[0].equals("APP")) {
					file.add((byte) 0x65);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("TAB")) {
					file.add((byte) 0x2B);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("SPACE")) {
					file.add((byte) 0x2C);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("WINDOWS")
						|| instruction[0].equals("GUI")) {
					if (instruction.length == 1) {
						file.add((byte) 0xE3);
						file.add((byte) 0x00);
					} else {
						if (instruction[1].equals("SPACE")) {
							file.add((byte) 0x2C);
						} else {
						    file.add(charToByte(instruction[1].charAt(0)));
						}
						file.add((byte) 0x08);
					}
				} else if (instruction[0].equals("SYSTEMPOWER")) {
					file.add((byte) 0x81);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("SYSTEMSLEEP")) {
					file.add((byte) 0x82);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("SYSTEMWAKE")) {
					file.add((byte) 0x83);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("ESCAPE")
						|| instruction[0].equals("ESC")) {
					file.add((byte) 0x29);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("CAPSLOCK")) {
					file.add((byte) 0x39);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("PRINTSCREEN")) {
					file.add((byte) 0x46);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("SCROLLLOCK")) {
					file.add((byte) 0x47);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("BREAK")
						|| instruction[0].equals("PAUSE")) {
					file.add((byte) 0x48);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("INSERT")) {
					file.add((byte) 0x49);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("HOME")) {
					file.add((byte) 0x4A);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("END")) {
					file.add((byte) 0x4D);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("PAGEUP")) {
					file.add((byte) 0x4B);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("DELETE")) {
					file.add((byte) 0x4C);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("PAGEDOWN")) {
					file.add((byte) 0x4E);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("RIGHTARROW")
						|| instruction[0].equals("RIGHT")) {
					file.add((byte) 0x4F);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("LEFTARROW")
						|| instruction[0].equals("LEFT")) {
					file.add((byte) 0x50);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("DOWNARROW")
						|| instruction[0].equals("DOWN")) {
					file.add((byte) 0x51);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("UPARROW")
						|| instruction[0].equals("UP")) {
					file.add((byte) 0x52);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("NUMLOCK")) {
					file.add((byte) 0x53);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("STOP")) {
					file.add((byte) 0xb5);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("PLAY")
						|| instruction[0].equals("PAUSE")) {
					file.add((byte) 0xCD);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("MUTE")) {
					file.add((byte) 0xE2);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("VOLUMEUP")) {
					file.add((byte) 0xE9);
					file.add((byte) 0x00);
				} else if (instruction[0].equals("VOLUMEDOWN")) {
					file.add((byte) 0xEA);
					file.add((byte) 0x00);
				} else if (functionKeyCheck(instruction[0])) {
					// Function keys
					file.add(functionKeyToByte(instruction[0]));
					file.add((byte) 0x00);
				} else {
					// System.out.print(instruction[0]);
					throw new Exception();
				}

				// Default delay
				if (!delayOverride & defaultDelay != 0x00) {
					while (defaultDelay > 0) {
						file.add((byte) 0x00);
						if (defaultDelay > 255) {
							file.add((byte) 0xFF);
							defaultDelay = defaultDelay - 255;
						} else {
							file.add((byte) defaultDelay);
							defaultDelay = 0;
						}
					}
				}
			} catch (Exception e) {
				System.out.println("Error on Line: " + (i + 1));
				// e.printStackTrace();
			}
		}

		// Write byte array to file
		byte[] data = new byte[file.size()];
		for (int i = 0; i < file.size(); i++) {
			data[i] = file.get(i);
		}
		try {
			File someFile = new File(fileDest);
			FileOutputStream fos = new FileOutputStream(someFile);
			fos.write(data);
			fos.flush();
			fos.close();
		} catch (Exception e) {
			System.out.print("Failed to write hex file!");
		}
	}

	private static byte charToByte(char c) {
		// System.out.println(c);
		if ((int) c >= 97 && (int) c <= 122)
			// lower case letters
			return (byte) (c - 0x5D);
		else if ((int) c >= 65 && (int) c <= 90)
			// upper case letters
			return (byte) (c - 0x3D);
		else if ((int) c >= 49 && (int) c <= 57)
			// 0 to 9
			return (byte) (c - 0x13);
		else
			switch (c) {
			case ' ':
				return 0x2C;
			case '!':
				return 0x1e;
			case '@':
				return 0x1f;
			case '#':
				return 0x20;
			case '$':
				return 0x21;
			case '%':
				return 0x22;
			case '^':
				return 0x23;
			case '&':
				return 0x24;
			case '*':
				return 0x25;
			case '(':
				return 0x26;
			case ')':
			case '0':
				return 0x27;
			case '-':
			case '_':
				return 0x2D;
			case '=':
			case '+':
				return 0x2E;
			case '[':
			case '{':
				return 0x2F;
			case ']':
			case '}':
				return 0x30;
			case '\\':
			case '|':
				return 0x31;
			case ':':
			case ';':
				return 0x33;
			case '\'':
			case '"':
				return 0x34;
			case '`':
			case '~':
				return 0x35;
			case ',':
			case '<':
				return 0x36;
			case '.':
			case '>':
				return 0x37;
			case '/':
			case '?':
				return 0x38;
			}

		return (byte) 0x99;
	}

	private static boolean functionKeyCheck(String possibleFKey) {
		if (possibleFKey.equals("F1") || possibleFKey.equals("F2")
				|| possibleFKey.equals("F3") || possibleFKey.equals("F4")
				|| possibleFKey.equals("F5") || possibleFKey.equals("F6")
				|| possibleFKey.equals("F7") || possibleFKey.equals("F8")
				|| possibleFKey.equals("F9") || possibleFKey.equals("F10")
				|| possibleFKey.equals("F11") || possibleFKey.equals("F12")) {
			return true;
		} else
			return false;
	}

	private static byte functionKeyToByte(String fKey) {
		if (fKey.equals("F1"))
			return (byte) 0x3a;
		else if (fKey.equals("F2"))
			return (byte) 0x3b;
		else if (fKey.equals("F3"))
			return (byte) 0x3c;
		else if (fKey.equals("F4"))
			return (byte) 0x3d;
		else if (fKey.equals("F5"))
			return (byte) 0x3e;
		else if (fKey.equals("F6"))
			return (byte) 0x3f;
		else if (fKey.equals("F7"))
			return (byte) 0x40;
		else if (fKey.equals("F8"))
			return (byte) 0x41;
		else if (fKey.equals("F9"))
			return (byte) 0x42;
		else if (fKey.equals("F10"))
			return (byte) 0x43;
		else if (fKey.equals("F11"))
			return (byte) 0x44;
		else if (fKey.equals("F12"))
			return (byte) 0x45;
		else
			return (byte) 0x99;
	}
}
