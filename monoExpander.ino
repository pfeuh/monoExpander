
/*
 * file : monoExpander.ino
 * Copyright (c) pfeuh <ze.pfeuh@gmail>
 * All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <MIDI.h>
#include "monoExpanderMotor.h"
#include "configMode.h"
#include "monoExpander.h"

// let's create configuration
CONFIG_MODE config = CONFIG_MODE();

// let's create midi driver
MIDI_CREATE_DEFAULT_INSTANCE();

// let's create synthetiser
MONO_EXPANDER_MOTOR motor = MONO_EXPANDER_MOTOR();

void ledOn()
{
    digitalWrite(LED_BUILTIN, LED_ON);
}

void ledOff()
{
    digitalWrite(LED_BUILTIN, LED_OFF);
}

void receiveNoteOn(byte channel, byte note, byte velocity)
{
    motor.noteOn(channel, note, velocity);
}

void receiveNoteOff(byte channel, byte note, byte velocity)
{
    motor.noteOff(channel, note, velocity);
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    
    motor.begin(AUDIO_OUTPUT_PIN, GATE_OUTPUT_PIN);
    motor.setGeneratorOn_CB(ledOn);
    motor.setGeneratorOff_CB(ledOff);
    motor.loadParameters();

    config.begin(CALL_CONFIG_KEY, PC_BAUDRATE, &motor);
    // key is only checked at boot
    if(config.keyPressed())
        // no way to get back except reboot
        config.configurationLoop();
    
    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.turnThruOff();
    MIDI.setHandleNoteOn(receiveNoteOn);
    MIDI.setHandleNoteOff(receiveNoteOff);
}

void loop()
{
    MIDI.read();
}

