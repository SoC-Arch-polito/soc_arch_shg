# Smart Hydroponic Greenhouse

Authors: Mauro Perra, Luca Marongiu, Simone Peraccini


## Contents


  - [Intro](#intro)
  - [How to run the project](#how-to-run-the-project)
  - [Structure and behavior of the firmware](#structure-and-behavior-of-the-firmware)
    - [SHG_runner](#shg_runner)
    - [OutputConsole](#outputconsole)
    - [CommandConsole](#commandconsole)
  - [Command List](#command-list)
    - [Pair](#pair)
  - [Start](#start)
    - [GetThs](#getths)
    - [SetThs](#setths)
    - [Status](#status)
    - [Reset](#reset)
    - [Stop](#stop)





## Intro

The Smart Hydroponic Greenhouse is a firmware for the *STM32F4DISCOVERY* board, it main goal is to control that the environmental parameters (temperature, humidity and light) stay into certain thresholds defined by the user or by the machine itself, reading the values by specific sensors and activating the  actuators that drive the Heating, the Water and the Light systems. The user can interact with the SHG through the *CommandConsole* (UART2) and the Renode terminal in order to insert the various commands and seeing the results of them. The *OutputConsole* (UART1) is instead used in order to debug the firmware during the development phase or by the maintainer because it shows time by time the actual state of the SHG.

## How to run the project

One important point of the SHG is that it is very easy to be launched thanks to its adaptation capability to VSCode, Platform IO and Renode.

[Platform IO integration in VSCode](https://docs.platformio.org/en/latest/integration/ide/vscode.html#ide-vscode)

[Renode](https://renode.io/)

After installing the developements tools the system can be run following
the steps listed below:

1) Clone the repository.
2) Build the project.
3) Open Renode and write `include @./stm32f4_discovery_modified.resc`.
4) Launch the firmware writing the `start` command in the Renode console.
5) Interact with the SHG writing the commands of the machine in the Renode console and looking to the result in the *CommandConsole* (UART2) and in *OutputConsole* to check the instantaneous status of the machine.

## Structure and behavior of the firmware

The source file of the SHG is inside the folder *SHG/src* of the project, here we can find the *main.c* file, and the source file of the operating system installed (FreeRTOS), but the main functionalities of the firmware (the three parallel tasks that are activated in *freertos.c*) are inside the folder *SHG/src/modules/src* with their respective header files in *SHG/src/modules/inc*.
If we give a look inside the folder *SHG/peripherals* we have two folders that contain the models of the sensors and of the actuators written in some *.cs* files, those external modules are connected throug I2C interfaces correctly defined in the file *peripheral_definition.repl*, their connection with the serial interfaces is instead done through the file *ext_peripheral.repl*.
Further examples of peripherals model provided by the Renode infrastructure can be found [here](https://github.com/renode/renode-infrastructure/tree/3f1abde88ac5a2dae326b77ab91892f335e78f80/src/Emulator/Peripherals/Peripherals).

In order to make the entire project executable by everyone in a very low number of steps is important to correctly define the *stm32f4_discovery.resc* file that has to be included through the Renode console as soon as the simulation program is launched. Inside this file the set of sensors and actuators are included to the enviroment loading also the platform description and the connections with the external modules through the *.repl* files.
In the *.resc* files the alias for the environmental variables (Temperature, Humidity and Light) are created, and also the set of commands to be received by the BluetoothRX module are properly associated to a specific code to be sent through the I2C protocol (this last concept is very important because it is the key to make the program easy to be used from the Renode console).



### SHG_runner

SHG runner is the firmware module that performs the checkof the sensors  compared with the thresholds and set on or off the corresponding actuators. It implements all functions tointeract with i2c sensor and actuators and keep  track of themachine status. In particular the SHG runner keep track if thedevice is paired with bluetooth, if the machine is powered on oroff and store all the three thresholds.

### OutputConsole

The Output console is a module that aims to show thestate of the machine writing it on the UART interface. In order to do this it periodically interrogates the SHG Runner to acquire the state of the machine and after this it defines how the data are shown to a possible user. 

### CommandConsole

The Command Console is the module that has the role of interfacing the user with the machine and start an interaction with it, the module in fact uses a Bluetooth peripheral in order to receive commands from the user and do a corresponding action.

## Command List

In order to have an effective experience with the SHG is important to have a look to the list of the commands that are supported by the firmware, to send a data through the I2C connected to the BluetoothRX module (and so to communicate with the SHG) is possible to write in the Renode console:
> **Command** *data_to_be_sent*

Or in an easyer way is possible to write directly the desired command, for example if we want to simulate the pairing process of the bluetooth module with the user is possible to write only the command:
>**Pair**

And the BluetoothRX will communicate throgh I2C to the STM32 board that it is correctly paired witht the user.
In the following section a list of the available commands and a short description of usage is explained.

### Pair

In order to start the interaction with the SHG is important to simulate the pairing process between the BluetoothRX module and the user, this can be performed with the command **Pair** that communicates to the board that the user is connected to the external bluetooth module and it is ready to start the communication.

## Start

**Start** is the command sent by the BluetoothRX module in order to communicate that the user want to start the SHG  monitoring process, from that point on the SHG will check the values of the environmental variables and will activate the control systems if those values are under the default thresholds (already defined by the machine).

### GetThs

**GetThs** is the command used to print the values of the thresholds currently in use.

### SetThs

**SetThs** is a command used to define a set of thresholds that the machine has to use in order to evaluate the values of the environmental parameters, the BluetoothRX module has to communicate the value of a threshold through the I2C channel and an acknowledge value used to confirm the last data, for example if the user want to set the thresholds of Temperature, Humidity and Light respectively at 35°C, 60% and 70% the BluetoothRX has to send to the board the following values:
> **Command** 35 <br />
**Ok1** <br />
**Command** 60 <br />
**Ok2** <br />
**Command** 70 <br />
**Ok3** <br />

In this way a user defined set of thresholds is set (the result can be checked by the *OutputConsole* or by the command **GetThs** prevously described).

### Status

The **Status** command can be used to monitor time by time the state of the machine simulating the experience that a maintainer (but obviously with less information) has with the *OutputConsole*.

### Reset

**Reset** is a command used to set the thresholds to the original machine defined values.

### Stop

In order to stop the monitoring process of the SHG and to shut off all the control systems is possible to write the command **Stop**.