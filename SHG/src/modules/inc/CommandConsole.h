#ifndef _COMMAND_CONSOLLE_H
#define _COMMAND_CONSOLLE_H
#define WELCOME_STRING "******Welcome! This is the Smart Hydroponic Greenhouse!******\n\r"
#define PRESENTATION_STRING "This is the Command Console of the SHG, take care of your plants and enjoy!.\n\r"
#define UNKNOWNCOMMAND "Command not recognized, please write an available command.\n\r"
#define RESETMACHINE "The machine is on reset, the default values of the thresholds are set.\n\r"
#define TEMPSTRINGTHS "Please, insert a threshold for the temperature (from 0 to 100), and then confirm (Ok1):\n\r"
#define HUMSTRINGTHS "Please, insert a threshold for the humidity (from 0 to 100), and then confirm (Ok2):\n\r"
#define LIGHTSTRINGTHS "Please, insert a threshold for the light (from 0 to 100), and then confirm (Ok3):\n\r"
#define CONFIRMSTRING "Values accepted!\n\r"
#define COMMANDLENGTH 12

/*****************COMMANDS TODO*****************/
/*
- start         -> to start the SHG (read from sensors and write to actuators);
- status        -> to outupt the values of the environmental variables;
- stop          -> pause the SHG;
- setThs        -> force the three thresholds to a user defined thresholds;
- getThs        -> print the three thresholds to the user;
- reset         -> reset to the default state of the machine;
*/
/***********************************************/
// Shared Variable used to set the command.
enum command {
  wait_pair, pair, start, status, stop, setThs, getThs, reset, error, endThs = 130
}; 

    void CommandConsole(void const * argument);

#endif