package com.timmattison.hacking.usbrubberducky.parsers;

import com.google.common.io.ByteStreams;
import org.apache.commons.io.FileUtils;
import org.apache.commons.io.IOUtils;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

/**
 * Created by timmattison on 12/10/13.
 */
public class TestAgainstFiles {
    private static final String inputPath = "/inputs/";
    private static final String numberedInputPath = inputPath + "test-input-";
    private static final String inputSuffix = ".txt";
    private static final String outputPath = "/outputs/";
    private static final String numberedOutputPath = outputPath + "test-output-";
    private static final String outputSuffix = ".bin";

    public static String[] getInputFile(int fileNumber) throws IOException {
        return readFileAsStringArray(inputPath + fileNumber + inputSuffix);
    }

    public static String[] getInputFile(String filename) throws IOException {
        return readFileAsStringArray(inputPath + filename + inputSuffix);
    }

    public static String getInputFileName(String filename) {
        return inputPath + filename + inputSuffix;
    }

    public static byte[] getOutputFile(int fileNumber) throws IOException {
        return readFileAsByteArray(outputPath + fileNumber + outputSuffix);
    }

    public static byte[] getOutputFile(String filename) throws IOException {
        return readFileAsByteArray(outputPath + filename + outputSuffix);
    }

    private static String[] readFileAsStringArray(String inputFile) throws IOException {
        String string = IOUtils.toString(new InputStreamReader(inputFile.getClass().getResourceAsStream(inputFile)));
        string = string.replaceAll("\r", "");
        String[] lines = string.split("\n");

        return lines;
    }

    private static byte[] readFileAsByteArray(String inputFile) throws IOException {
        //return IOUtils.toByteArray(new InputStreamReader(inputFile.getClass().getResourceAsStream(inputFile)), "ISO-8859-1");
        return ByteStreams.toByteArray(inputFile.getClass().getResourceAsStream(inputFile));
    }
}
