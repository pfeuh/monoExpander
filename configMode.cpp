
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

#include "configMode.h"

#define NO_COMMAND_RECEIVED 0
#define COMMAND_RECEIVED 1

/*******************/
/* private methods */
/*******************/

#ifdef CONFIG_MODE_DEBUG
void CONFIG_MODE::displayUserCommand()
{
    Serial.print(F("userCommand    "));
    if(userCommand)
        Serial.write(userCommand);
    else
        Serial.print(F("none"));
    Serial.write('\n');
}

void CONFIG_MODE::displayUserCommandAux()
{
    Serial.print(F("userCommandAux "));
    if(userCommandAux)
        Serial.write(userCommandAux);
    else
        Serial.print(F("none"));
    Serial.write('\n');
}

void CONFIG_MODE::displayUserNegative()
{
    Serial.print(F("userNegative   "));
    Serial.println(userNegative);
}

void CONFIG_MODE::displayUserValue()
{
    Serial.print(F("userValue      "));
    Serial.println(userValue);
}
#endif

bool CONFIG_MODE::sequencer()
{
    bool retval = NO_COMMAND_RECEIVED;
    char car = Serial.read();
    switch(car)
    {
        case '-':
            userNegative = true;
            break;
        case '?':
        case 'f':
        case 'g':
        case 'i':
        case 'l':
        case 'o':
        case 'p':
        case 'q':
        case 't':
        case 's':
            if(userCommand)
                userCommandAux = car;
            else
                userCommand = car;
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            userValue = userValue * 10 + car - '0';
            break;
        case '\n':
            if(userNegative)
                userValue = 0 - userValue;
            retval = COMMAND_RECEIVED;
            break;
        default:
            if(userCommand)
                userCommandAux = car;
            break;
    }
    return retval;
}

void CONFIG_MODE::initUserInput()
{
    userValue = 0;
    userCommand = 0;
    userCommandAux = 0;
    userNegative = false;
}

void CONFIG_MODE::displayChannel()
{
    Serial.print(F("Input channel "));
    Serial.println(motor->getChannel());
}

void CONFIG_MODE::displayOmni()
{
    Serial.print(F("Omni          "));
    Serial.println(motor->getOmni());
}

void CONFIG_MODE::displayTransposition()
{
    Serial.print(F("Transposition "));
    Serial.println((signed char)motor->getTransposition());
}

void CONFIG_MODE::displayPriority()
{
    Serial.print(F("Priority :    "));
    switch(motor->getPriority())
    {
        case MONO_EXPANDER_PRIORITY_LOWEST:
            Serial.println(F("lowest"));
            break;
        case MONO_EXPANDER_PRIORITY_HIGHEST:
            Serial.println(F("highest"));
            break;
        default:
            Serial.println(F("???"));
            break;
    }
}

void CONFIG_MODE::displayGateLogic()
{
    Serial.print(F("Gate Logic    "));
    if(motor->getGateLogic() == MONO_EXPANDER_GATE_LOGIC_POSITIVE)
        Serial.println(F("positive"));
    else
        Serial.println(F("negative"));
}

void CONFIG_MODE::displayMenu()
{
    Serial.write('\n');

    displayChannel();
    displayOmni();
    displayTransposition();
    displayPriority();
    displayGateLogic();
    
    Serial.write('\n');

    Serial.println(F("i[1:16]       Input channel"));
    Serial.println(F("o[0:1]        Omni mode"));
    Serial.println(F("t[-128:127]   Transposition (in semi-tones)"));
    Serial.println(F("p[l:h]        Priority (lowest/highest note)"));
    Serial.println(F("g[n:p]        Gate Logic (negative/positive)"));
    Serial.println(F("?             Menu"));
    Serial.println(F("l             Load Parameters"));
    Serial.println(F("q             Quit Parameters"));
    Serial.println(F("s             Save Parameters"));
    Serial.println(F("f             Restore Factory Parameters"));
    Serial.println(F("?             Invoke this menu"));
}

/******************/
/* public methods */
/******************/

CONFIG_MODE::CONFIG_MODE()
{
}

void CONFIG_MODE::begin(int button_pin_num, unsigned long int baudrate, MONO_EXPANDER_MOTOR* _motor)
{
    buttonPinNum = button_pin_num;
    motor = _motor;
    pinMode(buttonPinNum, INPUT_PULLUP);
    Serial.flush();
    Serial.begin(baudrate);
    Serial.println(F("\n\n\n\n" __DATE__ " " __TIME__ " " APP_NAME " v." VERSION " configurator\n"));
}

bool CONFIG_MODE::keyPressed()
{
    return digitalRead(buttonPinNum) == 0;
}

void CONFIG_MODE::configurationLoop()
{
    displayMenu();
    initUserInput();
    
    while(1)
    {
        if(Serial.available())
            if(sequencer() == COMMAND_RECEIVED)
            {
                #ifdef CONFIG_MODE_DEBUG
                displayUserCommand();
                displayUserCommandAux();
                displayUserNegative();
                displayUserValue();
                #endif
                switch(userCommand)
                {
                    case '?':
                        displayMenu();
                        break;
                    case 'f':
                        motor->restoreFactoryParameters();
                        Serial.println(F("Factory Parameters restored."));
                        break;
                    case 'g':
                        switch(userCommandAux)
                        {
                            case 'p':
                                motor->setGateLogic(MONO_EXPANDER_GATE_LOGIC_POSITIVE);
                                break;
                            case 'n':
                                motor->setGateLogic(MONO_EXPANDER_GATE_LOGIC_NEGATIVE);
                                break;
                            default:
                                break;
                        }
                        displayGateLogic();
                        break;
                    case 'i':
                        motor->setChannel(userValue);
                        displayChannel();
                        break;
                    case 'l':
                        motor->loadParameters();
                        Serial.println(F("Parameters loaded."));
                        break;
                    case 'o':
                        motor->setOmni(userValue);
                        displayOmni();
                        break;
                    case 'p':
                        switch(userCommandAux)
                        {
                            case 'l':
                                motor->setPriority(MONO_EXPANDER_PRIORITY_LOWEST);
                                break;
                            case 'h':
                                motor->setPriority(MONO_EXPANDER_PRIORITY_HIGHEST);
                                break;
                            default:
                                break;
                        }
                        displayPriority();
                        break;
                    case 'q':
                        Serial.println(F("Waiting for reboot... Bye bye."));
                        while(1);
                        break;
                    case 's':
                        motor->saveParameters();
                        Serial.println(F("Parameters saved."));
                        break;
                    case 't':
                        motor->setTransposition(userValue);
                        displayTransposition();
                        break;
                    default:
                        break;
                }
                initUserInput();
            }
    }
}

