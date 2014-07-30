package com.timmattison.hacking.usbrubberducky.parsers;

import com.google.inject.Guice;
import com.google.inject.Injector;
import com.google.inject.Key;
import com.google.inject.TypeLiteral;
import com.timmattison.hacking.usbrubberducky.UsbRubberDuckyModule;
import com.timmattison.hacking.usbrubberducky.instructions.Instruction;
import com.timmattison.hacking.usbrubberducky.instructions.lists.BasicInstructionList;
import com.timmattison.hacking.usbrubberducky.instructions.lists.InstructionList;
import com.timmattison.hacking.usbrubberducky.instructions.lists.processors.InstructionListProcessor;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;

/**
 * Created by timmattison on 7/21/14.
 */
public class IntegrationTest {
    Injector injector;

    @Before
    public void setup() {
        injector = Guice.createInjector(new UsbRubberDuckyModule());
    }

    @Test
    public void testHelloWorld() throws Exception {
        String filename = "hello-world";

        testFile(filename);
    }

    @Test
    public void testDownloadAndExecute() throws Exception {
        String filename = "download-and-execute";

        testFile(filename);
    }

    @Test
    public void testPayloadNetcatFtpDownloadAndReverseShell() throws Exception {
        String filename = "netcat-ftp-download-and-reverse-shell";

        testFile(filename);
    }

    @Test
    public void testWallpaperPrank() throws Exception {
        String filename = "wallpaper-prank";

        testFile(filename);
    }

    @Test
    public void testHideCmdWindow() throws Exception {
        String filename = "hide-cmd-window-expanded";

        testFile(filename);
    }

    @Test
    public void testYouGotQuacked() throws Exception {
        String filename = "you-got-quacked";

        testFile(filename);
    }

    @Test
    public void testReverseShell() throws Exception {
        String filename = "reverse-shell";

        testFile(filename);
    }

    @Test
    public void testForkBomb() throws Exception {
        String filename = "fork-bomb";

        testFile(filename);
    }

    @Test
    public void testUtilmanExploit() throws Exception {
        String filename = "utilman-exploit";

        testFile(filename);
    }

    @Test
    public void testWifiBackdoor() throws Exception {
        String filename = "wifi-backdoor";

        testFile(filename);
    }

    @Test
    public void testNonMaliciousAutoDefacer() throws Exception {
        String filename = "non-malicious-auto-defacer";

        testFile(filename);
    }

    @Test
    public void testLockYourComputerMessage() throws Exception {
        String filename = "lock-your-computer-message";

        testFile(filename);
    }

    @Test
    public void testDuckyDownloader() throws Exception {
        String filename = "ducky-downloader";

        testFile(filename);
    }

    @Test
    public void testDuckyPhisher() throws Exception {
        String filename = "ducky-phisher";

        testFile(filename);
    }

    @Test
    public void testFtpUploadDownload() throws Exception {
        String filename = "ftp-upload-download";

        testFile(filename);
    }

    @Test
    public void testRestartPrank() throws Exception {
        String filename = "restart-prank";

        testFile(filename);
    }

    @Test
    public void testSillyMouseWindowsIsForKids() throws Exception {
        String filename = "silly-mouse-windows-is-for-kids";

        testFile(filename);
    }

    @Test
    public void testWindowsScreenRotationHack() throws Exception {
        String filename = "windows-screen-rotation-hack";

        testFile(filename);
    }

    @Test
    public void testPowershellWgetAndExecute() throws Exception {
        String filename = "powershell-wget-and-execute";

        testFile(filename);
    }

    @Test
    public void testPowershellWgetAndExecuteHidden() throws Exception {
        String filename = "powershell-wget-and-execute-hidden";

        testFile(filename);
    }

    @Test
    public void testMobileTabs() throws Exception {
        String filename = "mobile-tabs";

        testFile(filename);
    }

    @Test
    public void testCreateWirelessNetworkAssociation() throws Exception {
        String filename = "create-wireless-network-association";

        testFile(filename);
    }

    @Test
    public void testRetrieveSamAndSystemFromALiveFileSystem() throws Exception {
        String filename = "retrieve-sam-and-system-from-a-live-file-system";

        testFile(filename);
    }

    @Test
    public void testRetrieveSamAndSystemFromALiveFileSystem2() throws Exception {
        String filename = "retrieve-sam-and-system-from-a-live-file-system2";

        testFile(filename);
    }

    @Test
    public void testUglyRolledPrank() throws Exception {
        String filename = "ugly-rolled-prank";

        testFile(filename);
    }

    @Test
    public void testXmas() throws Exception {
        String filename = "xmas";

        testFile(filename);
    }

    @Test
    public void testPineappleAssociationVeryFast() throws Exception {
        String filename = "pineapple-association-very-fast";

        testFile(filename);
    }

    @Test
    public void testOsxRootBackdoor() throws Exception {
        String filename = "osx-root-backdoor";

        testFile(filename);
    }

    @Test
    public void testOsxLocalDnsPoisoning() throws Exception {
        String filename = "osx-local-dns-poisoning";

        testFile(filename);
    }

    @Test
    public void testMrGrayRubberHacksEncode() throws Exception {
        String filename = "mrgray-rubber-hacks-encode";

        testFile(filename);
    }

    @Test
    public void testOsxUserBackdoor() throws Exception {
        String filename = "osx-user-backdoor";

        testFile(filename);
    }

    @Test
    public void testYoutubeBlaster() throws Exception {
        String filename = "osx-youtube-blaster";

        testFile(filename);
    }

    @Test
    public void testOsxAsciiPrank() throws Exception {
        String filename = "osx-ascii-prank";

        testFile(filename);
    }

    @Test
    public void testOsxGrabMinecraftAccountPasswordAndUploadToFtp() throws Exception {
        String filename = "osx-grab-minecraft-account-password-and-upload-to-ftp";

        testFile(filename);
    }

    @Test
    public void testOsxWgetAndExecute() throws Exception {
        String filename = "osx-wget-and-execute";

        testFile(filename);
    }

    @Test
    public void testOsxPasswordlessSshAccess() throws Exception {
        String filename = "osx-passwordless-ssh-access";

        testFile(filename);
    }

    @Test
    public void testOsxPasswordlessSshAccessTwinDuck() throws Exception {
        String filename = "osx-passwordless-ssh-access-twin-duck";

        testFile(filename);
    }

    @Test
    public void testBatchWiperDriveEraser() throws Exception {
        String filename = "batch-wiper-drive-eraser";

        testFile(filename);
    }

    @Test
    public void testGenericBatch() throws Exception {
        String filename = "generic-batch";

        testFile(filename);
    }

    @Test
    public void testPaintHack() throws Exception {
        String filename = "paint-hack";

        testFile(filename);
    }

    @Test
    public void testLocalDnsPoisoning() throws Exception {
        String filename = "local-dns-poisoning";

        testFile(filename);
    }

    @Test
    public void testDenyNetAccess() throws Exception {
        String filename = "deny-net-access";

        testFile(filename);
    }

    @Test
    public void testRunexeFromSd() throws Exception {
        String filename = "runexe-from-sd";

        testFile(filename);
    }

    @Test
    public void testRunexeFromSd2() throws Exception {
        String filename = "runexe-from-sd-2";

        testFile(filename);
    }

    @Test
    public void testRunJavaFromSd() throws Exception {
        String filename = "run-java-from-sd";

        testFile(filename);
    }

    @Test
    public void testMimikatz1() throws Exception {
        String filename = "mimikatz-1";

        testFile(filename);
    }

    @Test
    public void testMimikatz2() throws Exception {
        String filename = "mimikatz-2";

        testFile(filename);
    }

    @Test
    public void testWifunV1_1() throws Exception {
        String filename = "wifun-v1-1";

        testFile(filename);
    }

    @Test
    public void testMissDirection() throws Exception {
        String filename = "miss-direction";

        testFile(filename);
    }

    @Test
    public void testRemotelyPossible() throws Exception {
        String filename = "remotely-possible";

        testFile(filename);
    }

    @Test
    public void testCopyFileToDesktop() throws Exception {
        String filename = "copy-file-to-desktop";

        testFile(filename);
    }

    @Test
    public void testYoutubeRoll() throws Exception {
        String filename = "youtube-roll";

        testFile(filename);
    }

    @Test
    public void testDisableAvg2012() throws Exception {
        String filename = "disable-avg-2012";

        testFile(filename);
    }

    @Test
    public void testDisableAvg2013() throws Exception {
        String filename = "disable-avg-2013";

        testFile(filename);
    }

    @Test
    public void testEicarAvTest() throws Exception {
        String filename = "eicar-av-test";

        testFile(filename);
    }

    @Test
    public void testDownloadMimikatzGrabPasswordsAndEmailThemViaGmail() throws Exception {
        String filename = "download-mimikatz-grab-passwords-and-email-them-via-gmail";

        testFile(filename);
    }

    private void testFile(String filename) throws Exception {
        // Get the instruction list processors
        Set<InstructionListProcessor> instructionListProcessors = getInstructionListProcessors();

        // Get the instruction list
        InstructionList instructionList = new BasicInstructionList(instructionListProcessors);

        // Test the file against the legacy encoder
        testAgainstLegacyEncoder(instructionList, filename);
    }

    private Set<InstructionListProcessor> getInstructionListProcessors() {
        // Create a type literal implementation that is for Set<InstructionListProcessor>
        TypeLiteral<Set<InstructionListProcessor>> instructionListProcessorTypeLiteral = new TypeLiteral<Set<InstructionListProcessor>>() {
        };

        // Get the multibinding from Guice for Set<InstructionListProcessor>
        return injector.getInstance(Key.get(instructionListProcessorTypeLiteral));
    }

    private void testAgainstLegacyEncoder(InstructionList instructionList, String filename) throws Exception {
        String[] inputFile;
        byte[] outputFile;

        // Get the input file data
        try {
            inputFile = TestAgainstFiles.getInputFile(filename);
        } catch (NullPointerException e) {
            throw new UnsupportedOperationException("Input file [" + filename + ".txt] not found");
        }

        // Get the output file from the legacy encoder
        outputFile = getOutputFileFromLegacyEncoder(filename);

        // Get the output from the current encoder
        byte[] generatedData = getOutputFromCurrentEncoder(instructionList, inputFile);

        // Make sure the output matches
        Assert.assertArrayEquals("There was an issue with " + filename, outputFile, generatedData);
    }

    private byte[] getOutputFromCurrentEncoder(InstructionList instructionList, String[] inputFile) throws IOException {
        // Get the set of instruction parsers
        Set<InstructionParser> instructionParserSet = getInstructionParserSet();

        // Loop through each input line
        for (String line : inputFile) {
            // Start out with a null instruction
            Instruction instruction = null;

            // Loop through each parser
            for (InstructionParser instructionParser : instructionParserSet) {
                // Run the parser on this line
                instruction = instructionParser.parse(line);

                // Was the parser successful?
                if (instruction != null) {
                    // Yes, exit the for loop
                    break;
                }
            }

            // Did we find a parser that could handle this line?
            if (instruction == null) {
                // No, throw an exception
                throw new UnsupportedOperationException("Couldn't process instruction [" + line + "]");
            }

            // Add the instruction to the list
            instructionList.addInstruction(instruction);
        }

        // Get the byte array from this instruction list
        return instructionList.getBytes();
    }

    /**
     * Gets the set of instruction parser from Guice
     *
     * @return
     */
    private Set<InstructionParser> getInstructionParserSet() {
        // Create a type literal implementation that is for Set<InstructionParser>
        TypeLiteral<Set<InstructionParser>> instructionParserTypeLiteral = new TypeLiteral<Set<InstructionParser>>() {
        };

        // Get the multibinding from Guice for Set<InstructionParser>
        return injector.getInstance(Key.get(instructionParserTypeLiteral));
    }

    private byte[] getOutputFileFromLegacyEncoder(String filename) throws Exception {
        byte[] outputFile;

        // Create a stream to hold the output
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        PrintStream printStream = new PrintStream(baos);

        // Save the original System.out
        PrintStream old = System.out;

        // Use the printStream
        System.setOut(printStream);

        // Build the arguments for the encoder
        List<String> args = buildEncoderArgs(filename);

        // Run the encoder and capture the output
        com.hak5.usbrubberducky.Encoder.main(args.toArray(new String[args.size()]));

        // Flush the output
        System.out.flush();

        // Go back to the original System.out
        System.setOut(old);

        // Get the output from the Encoder
        outputFile = baos.toByteArray();
        return outputFile;
    }

    private List<String> buildEncoderArgs(String filename) {
        List<String> args = new ArrayList<String>();

        // Input file arguments
        args.add("-i");
        args.add(TestAgainstFiles.getInputFileName(filename));

        // Output file arguments
        args.add("-o");
        args.add("-");

        // Test mode argument
        args.add("-t");

        return args;
    }
}

