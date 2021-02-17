//
// Copyright (c) 2010-2018 Antmicro
//
// This file is licensed under the MIT License.
// Full license text is available in 'licenses/MIT.txt'.






using Antmicro.Renode.Peripherals.I2C;
using Antmicro.Renode.Utilities;
using Antmicro.Renode.EmulationEnvironment;
using System;
using System.Collections.Generic;
using System.Linq;
using Antmicro.Migrant;
using Antmicro.Migrant.Hooks;
using Antmicro.Renode.Core;
using Antmicro.Renode.Exceptions;
using Antmicro.Renode.Logging;
using Antmicro.Renode.Peripherals.Sensor;
using Antmicro.Renode.UserInterface;

namespace Antmicro.Renode.Peripherals.Sensors
{
    public class BluetoothRx : II2CPeripheral, IBluetoothRx,IExternal
    {
        public BluetoothRx()
        {
            commandos = new I2CCommandManager<Action<byte[]>>();
            outputBuffer = new Queue<byte>();
            commandos.RegisterCommand(ReadCommand, 0xE5);
            Reset();
        }

        public byte[] Read(int count = 1)
        {
            outputBuffer.Clear();
            outputBuffer.Enqueue((byte)command);
            var result = outputBuffer.ToArray();
            this.Log(LogLevel.Info, "Reading {0} bytes from the device (asked for {1} bytes): {2}", result.Length, count,result[0]);
            outputBuffer.Clear();
            return result;
        }

        public void Write(byte[] data)
        {
            this.Log(LogLevel.Noisy, "Received {0} bytes: [{1}]", data.Length, string.Join(", ", data.Select(x => x.ToString())));
        }

        public void Reset()
        {
            Command = 0;
            outputBuffer.Clear();
        }

        public uint Command
        {
            get
            {
                return command;
            }
            set
            {
                command = value;
            }
        }

        private void ReadCommand(byte[] commando)
        {
            outputBuffer.Enqueue((byte)((uint)command >> 8));
            outputBuffer.Enqueue((byte)((uint)command & 0xFF));
        }



        private uint command;

        private readonly I2CCommandManager<Action<byte[]>> commandos;
        private readonly Queue<byte> outputBuffer;
    }
}