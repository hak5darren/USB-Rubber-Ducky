package com.timmattison.hacking.usbrubberducky;

import com.google.inject.AbstractModule;
import com.google.inject.assistedinject.FactoryModuleBuilder;
import com.google.inject.multibindings.Multibinder;
import com.timmattison.hacking.usbrubberducky.instructions.BasicRepeatInstruction;
import com.timmattison.hacking.usbrubberducky.instructions.DelayInstruction;
import com.timmattison.hacking.usbrubberducky.instructions.KeypressInstruction;
import com.timmattison.hacking.usbrubberducky.instructions.factories.DelayInstructionFactory;
import com.timmattison.hacking.usbrubberducky.instructions.interfaces.RepeatInstruction;
import com.timmattison.hacking.usbrubberducky.instructions.StringInstruction;
import com.timmattison.hacking.usbrubberducky.instructions.factories.KeypressInstructionFactory;
import com.timmattison.hacking.usbrubberducky.instructions.factories.RepeatInstructionFactory;
import com.timmattison.hacking.usbrubberducky.instructions.factories.StringInstructionFactory;
import com.timmattison.hacking.usbrubberducky.instructions.lists.processors.DefaultDelayInstructionListProcessor;
import com.timmattison.hacking.usbrubberducky.instructions.lists.processors.InstructionListProcessor;
import com.timmattison.hacking.usbrubberducky.instructions.lists.processors.NopInstructionListProcessor;
import com.timmattison.hacking.usbrubberducky.instructions.lists.processors.RepeatInstructionListProcessor;
import com.timmattison.hacking.usbrubberducky.parsers.*;
import com.timmattison.hacking.usbrubberducky.parsers.advanced.KeypressInstructionParser;
import com.timmattison.hacking.usbrubberducky.parsers.regex.*;
import com.timmattison.hacking.usbrubberducky.preprocessors.LegacyPreprocessor;
import com.timmattison.hacking.usbrubberducky.preprocessors.Preprocessor;
import com.timmattison.hacking.usbrubberducky.translation.BasicCharacterTranslator;
import com.timmattison.hacking.usbrubberducky.translation.CharacterTranslator;
import com.timmattison.hacking.usbrubberducky.translation.keyboards.KeyboardCodes;
import com.timmattison.hacking.usbrubberducky.translation.keyboards.USKeyboardCodes;

/**
 * Created with IntelliJ IDEA.
 * User: timmattison
 * Date: 10/25/13
 * Time: 10:47 AM
 * To change this template use File | Settings | File Templates.
 */
public class UsbRubberDuckyModule extends AbstractModule {
    @Override
    protected void configure() {
        // Create a multi-binder that holds all of the instruction parsers
        createInstructionParsingMultibinder();

        // Create a multi-binder that does instruction list processing
        createListProcessingMultibinder();

        // Bind the concrete implementations
        bindConcreteImplementations();

        // Create factories from the factory interfaces
        createFactoriesFromInterfaces();
    }

    private void createInstructionParsingMultibinder() {
        Multibinder<InstructionParser> instructionParserMultibinder = Multibinder.newSetBinder(binder(), InstructionParser.class);

        // Support "STRING"
        instructionParserMultibinder.addBinding().to(StringInstructionParser.class);
        // Support "DELAY"
        instructionParserMultibinder.addBinding().to(DelayInstructionParser.class);
        // Support keypresses
        instructionParserMultibinder.addBinding().to(KeypressInstructionParser.class);
        // Support "REPEAT"
        instructionParserMultibinder.addBinding().to(RepeatInstructionParser.class);
        // Support "REM"
        instructionParserMultibinder.addBinding().to(NopInstructionParser.class);
        // Support "DEFAULT_DELAY"
        instructionParserMultibinder.addBinding().to(DefaultDelayInstructionParser.class);
        // Support blank lines
        instructionParserMultibinder.addBinding().to(BlankLineInstructionParser.class);
    }

    private void createListProcessingMultibinder() {
        Multibinder<InstructionListProcessor> instructionListProcessorMultibinder = Multibinder.newSetBinder(binder(), InstructionListProcessor.class);

        // NOTE: The order of this list is important!

        // Step 1 - Prune NOP instructions
        instructionListProcessorMultibinder.addBinding().to(NopInstructionListProcessor.class);
        // Step 2 - Repeat instructions
        instructionListProcessorMultibinder.addBinding().to(RepeatInstructionListProcessor.class);
        // Step 3 - Add default delays
        instructionListProcessorMultibinder.addBinding().to(DefaultDelayInstructionListProcessor.class);
    }

    private void bindConcreteImplementations() {
        // TODO: Add more keyboards and make it configurable at runtime

        // Use the US keyboard
        bind(KeyboardCodes.class).to(USKeyboardCodes.class);

        // Use the basic character translator
        bind(CharacterTranslator.class).to(BasicCharacterTranslator.class);

        // Use the pre-processor that cleans up some legacy instructions
        bind(Preprocessor.class).to(LegacyPreprocessor.class);
    }

    private void createFactoriesFromInterfaces() {
        install(new FactoryModuleBuilder().implement(StringInstruction.class, StringInstruction.class).build(StringInstructionFactory.class));
        install(new FactoryModuleBuilder().implement(RepeatInstruction.class, BasicRepeatInstruction.class).build(RepeatInstructionFactory.class));
        install(new FactoryModuleBuilder().implement(KeypressInstruction.class, KeypressInstruction.class).build(KeypressInstructionFactory.class));
        install(new FactoryModuleBuilder().implement(DelayInstruction.class, DelayInstruction.class).build(DelayInstructionFactory.class));
    }
}
