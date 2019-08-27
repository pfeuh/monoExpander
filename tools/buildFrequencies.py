#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys

openSourceText = """/*
 * file : midi_notes_frequencies.h
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

"""
    
RDDD = 1.059463 # racine douzieme de deux
A4Freq = 440.0

NOTE_LABELS = ["C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"]

STAVE_SIZE = 12
STAVE_LAST_NOTE = STAVE_SIZE - 1

def getMidiNoteLabels():
    midi_notes_labels = []
    for x in range(128):
        if x % STAVE_SIZE == 0:
            line = "    "
            
        stave_num = (x / STAVE_SIZE) - 1
        note_num = x % STAVE_SIZE

        label = "%-4s"%(NOTE_LABELS[note_num] + str(stave_num))
        assert len(label) == 4
        midi_notes_labels.append(label)
    return midi_notes_labels

def getMidiNotesFrequencies():
    # First midi note is 6 staves lower and 3 halftones higher than A4
    current_frequency = A4Freq / 2.0**6.0 * RDDD**3.0
    frequencies = []
    fltFrequencies = []
    for x in range(128):
        frequencies.append(int(current_frequency + 0.5))
        fltFrequencies.append(current_frequency)
        current_frequency = current_frequency * RDDD
    return frequencies, fltFrequencies

if __name__ == "__main__":

    frequencies, fltFrequencies = getMidiNotesFrequencies()
    noteLabels = getMidiNoteLabels()
    
    #~ with open(sys.stdout, "w") as fp:
    #~ with open("midi_notes_frequencies.h", "w") as fp:
    fp = sys.stdout
    fp.write("#ifndef midi_notes_frequencies_h\n")
    fp.write("#define midi_notes_frequencies_h\n\n")
    fp.write(openSourceText)
    fp.write("#include <Arduino.h>\n\n")
    fp.write("\nconst int MIDI_NOTES_FREQUENCIES[128] PROGMEM = {\n")
    fp.write("//  freq      note idx float freq\n")
    fp.write("//-------------------------------\n")

    for note_num, frequency in enumerate(frequencies):
        #~ fp.write("    /* midi note %03u */ %u,\n"%(note_num, frequency + 0.5))
        fp.write("    %-5u, // %s %3u %f\n"%( frequency + 0.5, noteLabels[note_num], note_num, fltFrequencies[note_num]))
    fp.write("};\n\n")
    fp.write("#endif\n\n")

