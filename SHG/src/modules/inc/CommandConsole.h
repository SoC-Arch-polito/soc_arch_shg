#ifndef _COMMAND_CONSOLLE_H
#define _COMMAND_CONSOLLE_H

/*****************COMMANDS TODO*****************/
/*
- start         -> to start the SHG (read from sensors and write to actuators);
- log           -> to output info messages about the recent history of the machine;
- status        -> to outupt the values of the environmental variables;
- clear         -> clear the UART command line;
- help          -> to show the available commands;
- stop          -> pause the SHG;
- setTresholds  -> force the three thresholds to a user defined thresholds;
- reset         -> reset to the default state of the machine;
*/
/***********************************************/
// Shared Variable used to set the command.
enum command {
  start, log, status, clear, help, stop, setThs, reset
}; 

    void CommandConsole(void const * argument);
    void CMD_commClear();
    void showCommands();
    void setTresholds(int Temperature, int Humidity, int Light);

#endif