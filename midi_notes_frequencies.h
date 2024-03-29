#ifndef midi_notes_frequencies_h
#define midi_notes_frequencies_h

/*
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

#include <Arduino.h>


const int MIDI_NOTES_FREQUENCIES[128] PROGMEM = {
//  freq      note idx float freq
//-------------------------------
    8    , // C-1    0 8.175797
    9    , // Db-1   1 8.661954
    9    , // D-1    2 9.177020
    10   , // Eb-1   3 9.722713
    10   , // E-1    4 10.300855
    11   , // F-1    5 10.913374
    12   , // Gb-1   6 11.562316
    12   , // G-1    7 12.249846
    13   , // Ab-1   8 12.978259
    14   , // A-1    9 13.749985
    15   , // Bb-1  10 14.567601
    15   , // B-1   11 15.433834
    16   , // C0    12 16.351576
    17   , // Db0   13 17.323890
    18   , // D0    14 18.354020
    19   , // Eb0   15 19.445405
    21   , // E0    16 20.601687
    22   , // F0    17 21.826726
    23   , // Gb0   18 23.124608
    24   , // G0    19 24.499667
    26   , // Ab0   20 25.956490
    27   , // A0    21 27.499941
    29   , // Bb0   22 29.135170
    31   , // B0    23 30.867635
    33   , // C1    24 32.703117
    35   , // Db1   25 34.647742
    37   , // D1    26 36.708001
    39   , // Eb1   27 38.890769
    41   , // E1    28 41.203331
    44   , // F1    29 43.653405
    46   , // Gb1   30 46.249167
    49   , // G1    31 48.999281
    52   , // Ab1   32 51.912925
    55   , // A1    33 54.999824
    58   , // Bb1   34 58.270278
    62   , // B1    35 61.735204
    65   , // C2    36 65.406164
    69   , // Db2   37 69.295411
    73   , // D2    38 73.415924
    78   , // Eb2   39 77.781455
    82   , // E2    40 82.406574
    87   , // F2    41 87.306716
    92   , // Gb2   42 92.498235
    98   , // G2    43 97.998458
    104  , // Ab2   44 103.825740
    110  , // A2    45 109.999530
    117  , // Bb2   46 116.540432
    123  , // B2    47 123.470275
    131  , // C3    48 130.812188
    139  , // Db3   49 138.590674
    147  , // D3    50 146.831691
    156  , // Eb3   51 155.562744
    165  , // E3    52 164.812971
    175  , // F3    53 174.613245
    185  , // Gb3   54 184.996272
    196  , // G3    55 195.996706
    208  , // Ab3   56 207.651258
    220  , // A3    57 219.998824
    233  , // Bb3   58 233.080614
    247  , // B3    59 246.940287
    262  , // C4    60 261.624097
    277  , // Db4   61 277.181051
    294  , // D4    62 293.663068
    311  , // Eb4   63 311.125155
    330  , // E4    64 329.625590
    349  , // F4    65 349.226116
    370  , // Gb4   66 369.992149
    392  , // G4    67 391.992992
    415  , // Ab4   68 415.302071
    440  , // A4    69 439.997178
    466  , // Bb4   70 466.160731
    494  , // B4    71 493.880046
    523  , // C5    72 523.247635
    554  , // Db5   73 554.361510
    587  , // D5    74 587.325508
    622  , // Eb5   75 622.249645
    659  , // E5    76 659.250475
    698  , // F5    77 698.451486
    740  , // Gb5   78 739.983507
    784  , // G5    79 783.985146
    831  , // Ab5   80 830.603255
    880  , // A5    81 879.993416
    932  , // Bb5   82 932.320465
    988  , // B5    83 987.759037
    1046 , // C6    84 1046.494152
    1109 , // Db6   85 1108.721834
    1175 , // D6    86 1174.649761
    1244 , // Eb6   87 1244.497959
    1318 , // E6    88 1318.499541
    1397 , // F6    89 1396.901480
    1480 , // Gb6   90 1479.965432
    1568 , // G6    91 1567.968617
    1661 , // Ab6   92 1661.204735
    1760 , // A6    93 1759.984952
    1865 , // Bb6   94 1864.638937
    1976 , // B6    95 1975.515962
    2093 , // C7    96 2092.986068
    2217 , // Db7   97 2217.441298
    2349 , // D7    98 2349.297010
    2489 , // Eb7   99 2488.993259
    2637 , // E7   100 2636.996265
    2794 , // F7   101 2793.799974
    2960 , // Gb7  102 2959.927701
    3136 , // G7   103 3135.933882
    3322 , // Ab7  104 3322.405919
    3520 , // A7   105 3519.966142
    3729 , // Bb7  106 3729.273889
    3951 , // B7   107 3951.027702
    4186 , // C8   108 4185.967662
    4435 , // Db8  109 4434.877857
    4699 , // D8   110 4698.588999
    4978 , // Eb8  111 4977.981197
    5274 , // E8   112 5273.986893
    5588 , // F8   113 5587.593975
    5920 , // Gb8  114 5919.849076
    6272 , // G8   115 6271.861061
    6645 , // Ab8  116 6644.804736
    7040 , // A8   117 7039.924760
    7459 , // Bb8  118 7458.539806
    7902 , // B8   119 7902.046958
    8372 , // C9   120 8371.926376
    8870 , // Db9  121 8869.746235
    9397 , // D9   122 9397.167955
    9956 , // Eb9  123 9955.951753
    10548, // E9   124 10547.962512
    11175, // F9   125 11175.176007
    11840, // Gb9  126 11839.685498
    12544, // G9   127 12543.708717
};

#endif

