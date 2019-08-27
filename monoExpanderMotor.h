#ifndef monoExpanderMotor_H
#define monoExpanderMotor_H

/*
 * file : monoExpanderMotor.h
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

#include <Arduino.h>

#define MONO_EXPANDER_MOTOR_VERSION "1.00"
#define MONO_EXPANDER_NB_MIDI_NOTES 128
#define MONO_EXPANDER_NB_MIDI_NOTE_MASK 127
#define MONO_EXPANDER_NOTHING_PLAYING 255
#define MONO_EXPANDER_MOTOR_NB_BYTES (sizeof(byte) * 5)
#define MONO_EXPANDER_MOTOR_EEPROM_BASE 0

#define MONO_EXPANDER_PRIORITY_LOWEST 0
#define MONO_EXPANDER_PRIORITY_HIGHEST 1

#define MONO_EXPANDER_GATE_LOGIC_POSITIVE 0
#define MONO_EXPANDER_GATE_LOGIC_NEGATIVE 1
#define MONO_EXPANDER_MOTOR_GATE_ON 1
#define MONO_EXPANDER_MOTOR_GATE_OFF 0


// factory default parameter
#define MONO_EXPANDER_MOTOR_FACTORY_CHANNEL 1
#define MONO_EXPANDER_MOTOR_FACTORY_OMNI 1
#define MONO_EXPANDER_MOTOR_FACTORY_TRANSPOSITION 0
#define MONO_EXPANDER_MOTOR_FACTORY_PRIORITY MONO_EXPANDER_PRIORITY_HIGHEST
#define MONO_EXPANDER_MOTOR_FACTORY_GATE_MODE MONO_EXPANDER_PRIORITY_HIGHEST

class MONO_EXPANDER_MOTOR
{
    public:
        void begin(int audio_pin, int gate_pin);

        // motor itself
        void noteOn(byte channel, byte note, byte velocity);
        void noteOff(byte channel, byte note, byte velocity);
        void setGeneratorOn_CB(void (*generator_on_CB)());
        void setGeneratorOff_CB(void (*generator_off_CB)());

        // parameters getters & setters
        byte getChannel();
        void setChannel(byte _channel);
        byte getTransposition();
        void setTransposition(byte _tranposition);
        bool getOmni();
        void setOmni(bool _omni);
        byte getPriority();
        void setPriority(byte _priority);    
        byte getGateLogic();
        void setGateLogic(byte gate_logic);
    
        // parameters storage
        void loadParameters();
        void saveParameters();
        void restoreFactoryParameters();

    private:
        int audioPin;
        int gatePin;
        byte currentlyPlayingNote;
        bool busyMap[MONO_EXPANDER_NB_MIDI_NOTES];
        void (*generatorOn_CB)();
        void (*generatorOff_CB)();

        // this bytes should be saved in EEPROM
        byte configData[MONO_EXPANDER_MOTOR_NB_BYTES];

        bool messageReceived(byte channel);
        void startGenerate(byte note);
        void stopGenerate();
        void restartPreviousNote(byte note);
        void registerNote(byte note);
        void unregisterNote(byte note);
        void clearBusyMap();
        bool busyMapIsEMpty();
        byte transpose(byte note);
};

#endif

