
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

#include <EEPROM.h>
#include "monoExpanderMotor.h"
#include "midi_notes_frequencies.h"

#define CHANNEL_INDEX 0
#define TRANSPOSITION_INDEX 1
#define OMNI_INDEX 2
#define PRIORITY_INDEX 3
#define GATE_LOGIC_INDEX 4

#define MONO_EXPANDER_PRIORITY_MAX MONO_EXPANDER_PRIORITY_HIGHEST
#define MONO_EXPANDER_GATE_LOGIC_MAX MONO_EXPANDER_GATE_LOGIC_NEGATIVE

#define inputChannel  configData[CHANNEL_INDEX]
#define transposition configData[TRANSPOSITION_INDEX]
#define omni          configData[OMNI_INDEX]
#define priority      configData[PRIORITY_INDEX]
#define gateLogic      configData[GATE_LOGIC_INDEX]

#define MONO_EXPANDER_MOTOR_NOTHING_PLAYING 255

/*******************/
/* Private methods */
/*******************/

bool MONO_EXPANDER_MOTOR::messageReceived(byte channel)
{
    return (getOmni() || (getChannel() == channel));
}

void MONO_EXPANDER_MOTOR::startGenerate(byte note)
{
    tone(audioPin, pgm_read_word(MIDI_NOTES_FREQUENCIES + note));
    digitalWrite(gatePin, MONO_EXPANDER_MOTOR_GATE_ON ^ gateLogic);
    if(generatorOn_CB)
        generatorOn_CB();
}

void MONO_EXPANDER_MOTOR::stopGenerate()
{
    digitalWrite(gatePin, MONO_EXPANDER_MOTOR_GATE_OFF ^ gateLogic);
    noTone(audioPin);
    if(generatorOff_CB)
        generatorOff_CB();
}

void MONO_EXPANDER_MOTOR::restartPreviousNote(byte note)
{
    if(note == currentlyPlayingNote)
    {
        if(!busyMapIsEMpty())
        {
            // if currently playing note is stopping,
            // we have to check for starting a waiting one
            switch(priority)
            {
                case MONO_EXPANDER_PRIORITY_HIGHEST:
                    // highest note priority
                    for(byte note_num = MONO_EXPANDER_NB_MIDI_NOTES - 1; note_num != MONO_EXPANDER_MOTOR_NOTHING_PLAYING; note_num--)
                    {
                        if(busyMap[note_num])
                        {
                            startGenerate(note_num);
                            currentlyPlayingNote = note_num;
                            break;
                        }
                    }
                    break;
                case MONO_EXPANDER_PRIORITY_LOWEST:
                    // lowest note priority
                    for(byte note_num = 0; note_num < MONO_EXPANDER_NB_MIDI_NOTES; note_num++)
                    {
                        if(busyMap[note_num])
                        {
                            startGenerate(note_num);
                            currentlyPlayingNote = note_num;
                            break;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

void MONO_EXPANDER_MOTOR::registerNote(byte note)
{
    busyMap[note] = true;
    currentlyPlayingNote = note;
}

void MONO_EXPANDER_MOTOR::unregisterNote(byte note)
{
    busyMap[note] = false;
}

void MONO_EXPANDER_MOTOR::clearBusyMap()
{
    stopGenerate();
    for(byte note_num = 0; note_num < MONO_EXPANDER_NB_MIDI_NOTES; note_num++)
        busyMap[note_num] = false;
}

bool MONO_EXPANDER_MOTOR::busyMapIsEMpty()
{
    for(byte note_num = 0; note_num < MONO_EXPANDER_NB_MIDI_NOTES; note_num++)
        if(busyMap[note_num])
            return false;
    return true;
}

byte MONO_EXPANDER_MOTOR::transpose(byte note)
{
    return (note + getTransposition()) & MONO_EXPANDER_NB_MIDI_NOTE_MASK;
}

/******************/
/* Public methods */
/******************/

void MONO_EXPANDER_MOTOR::begin(int audio_pin, int gate_pin)
{
    generatorOn_CB = NULL;
    generatorOff_CB = NULL;
    audioPin = audio_pin;
    pinMode(audioPin, OUTPUT);
    gatePin = gate_pin;
    pinMode(gatePin, OUTPUT);
    stopGenerate();
    clearBusyMap();
    currentlyPlayingNote = MONO_EXPANDER_MOTOR_NOTHING_PLAYING;
}

void MONO_EXPANDER_MOTOR::noteOn(byte channel, byte note, byte velocity)
{
    if(messageReceived(channel))
    {
        note = transpose(note);
        startGenerate(note);
        registerNote(note);
    }
    velocity++; // avoiding compiler warning "unused parameter"
}

void MONO_EXPANDER_MOTOR::noteOff(byte channel, byte note, byte velocity)
{
    if(messageReceived(channel))
    {
        note = transpose(note);
        if(currentlyPlayingNote == note)
            stopGenerate();
        unregisterNote(note);
        restartPreviousNote(note);
    }
    velocity++; // avoiding compiler warning "unused parameter"
}

void MONO_EXPANDER_MOTOR::setGeneratorOn_CB(void (*generator_on_CB)())
{
    generatorOn_CB = generator_on_CB;
}

void MONO_EXPANDER_MOTOR::setGeneratorOff_CB(void (*generator_off_CB)())
{
    generatorOff_CB = generator_off_CB;
}

byte MONO_EXPANDER_MOTOR::getChannel()
{
    return inputChannel;
}

void MONO_EXPANDER_MOTOR::setChannel(byte _channel)
{
    if(_channel > 0)
        if(_channel <= 16)
            inputChannel = _channel;
}

byte MONO_EXPANDER_MOTOR::getTransposition()
{
    return transposition;
}

void MONO_EXPANDER_MOTOR::setTransposition(byte _transposition)
{
    transposition = _transposition;
}

bool MONO_EXPANDER_MOTOR::getOmni()
{
    return omni;
}

void MONO_EXPANDER_MOTOR::setOmni(bool _omni)
{
    omni = _omni != 0;
}
byte MONO_EXPANDER_MOTOR::getPriority()
{
    return priority;
}

void MONO_EXPANDER_MOTOR::setPriority(byte _priority)
{
    if(_priority <= MONO_EXPANDER_PRIORITY_MAX)
        priority = _priority != 0;
}

byte MONO_EXPANDER_MOTOR::getGateLogic()
{
    return gateLogic;
}

void MONO_EXPANDER_MOTOR::setGateLogic(byte gate_logic)
{
    if(gate_logic <= MONO_EXPANDER_PRIORITY_MAX)
        gateLogic = gate_logic;
}

void MONO_EXPANDER_MOTOR::loadParameters()
{
    byte* target = configData;
    word nb_bytes = MONO_EXPANDER_MOTOR_NB_BYTES;
    word base = MONO_EXPANDER_MOTOR_EEPROM_BASE;
    
    while(nb_bytes--)
         *target++ = EEPROM.read(base++);
}

void MONO_EXPANDER_MOTOR::saveParameters()
{
    byte* source = configData;
    word nb_bytes = MONO_EXPANDER_MOTOR_NB_BYTES;
    word base = MONO_EXPANDER_MOTOR_EEPROM_BASE;
    
    while(nb_bytes--)
        EEPROM.update(base++, *source++);
}

void MONO_EXPANDER_MOTOR::restoreFactoryParameters()
{
    setChannel(MONO_EXPANDER_MOTOR_FACTORY_CHANNEL);
    setTransposition(MONO_EXPANDER_MOTOR_FACTORY_TRANSPOSITION);
    setOmni(MONO_EXPANDER_MOTOR_FACTORY_OMNI);
    setPriority(MONO_EXPANDER_MOTOR_FACTORY_PRIORITY);
}




