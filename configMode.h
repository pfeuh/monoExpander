#ifndef configMode_h
#define configMode_h

/*
 * file : configMode.h
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
#include "monoExpander.h"
#include "monoExpanderMotor.h"

#define CONFIG_MODE_FACTORY_CHANNEL 1
#define CONFIG_MODE_FACTORY_OMNI 1
#define CONFIG_MODE_FACTORY_TRANSPOSITION 0

//~ #define CONFIG_MODE_DEBUG

class CONFIG_MODE
{
    public:
        CONFIG_MODE();
        void begin(int button_pin_num, unsigned long int baudrate, MONO_EXPANDER_MOTOR* _motor);
        bool keyPressed();
        void configurationLoop();
    
    private:
        int  buttonPinNum;
        MONO_EXPANDER_MOTOR* motor;
    
        // dedicated to the user's input
        byte userValue;
        //~ unsigned long int userValue;
        char userCommand;
        char userCommandAux;
        bool userNegative;
    
        bool sequencer();
        void initUserInput();
        void displayChannel();
        void displayOmni();
        void displayTransposition();
        void displayPriority();
        void displayGateLogic();
        void displayMenu();

        #ifdef CONFIG_MODE_DEBUG
        void displayUserCommand();
        void displayUserCommandAux();
        void displayUserNegative();
        void displayUserValue();
        #endif
};

#endif
