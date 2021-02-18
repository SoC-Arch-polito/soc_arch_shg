#ifndef _COMMAND_CONSOLLE_H
#define _COMMAND_CONSOLLE_H
#define WELCOME_STRING "******Welcome! This is the Smart Hydroponic Greenhouse!******\n\r"
#define PRESENTATION_STRING "This is the Command Console of the SHG, write 'help' to have the list of available commands.\n\r"
#define UNKNOWNCOMMAND "Command not recognized, please write an available command, to have the list use the command 'help'.\n\r"
#define COMMANDLENGTH 12

/*****************COMMANDS TODO*****************/
/*
- start         -> to start the SHG (read from sensors and write to actuators);
- status        -> to outupt the values of the environmental variables;
- clear         -> clear the UART command line;
- stop          -> pause the SHG;
- setThs        -> force the three thresholds to a user defined thresholds;
- getThs        -> print the three thresholds to the user;
- reset         -> reset to the default state of the machine;
*/
/***********************************************/
// Shared Variable used to set the command.
enum command {
  wait_pair, pair, start, status, clear, stop, setThs, getThs, reset, error
}; 

    void CommandConsole(void const * argument);
    void CMD_commClear();
    void showCommands();
    void setTresholds(int Temperature, int Humidity, int Light);

#endif