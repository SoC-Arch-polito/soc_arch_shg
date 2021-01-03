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
    public class LightSensor : II2CPeripheral, ILightSensor,IExternal
    {
        public LightSensor()
        {
            commands = new I2CCommandManager<Action<byte[]>>();
            outputBuffer = new Queue<byte>();
            commands.RegisterCommand(MeasureLight, 0xE5);
            Reset();
        }

        public byte[] Read(int count = 1)
        {
            var result = outputBuffer.ToArray();
            this.Log(LogLevel.Noisy, "Reading {0} bytes from the device (asked for {1} bytes).", result.Length, count);
            outputBuffer.Clear();
            return result;
        }

        public void Write(byte[] data)
        {
            this.Log(LogLevel.Noisy, "Received {0} bytes: [{1}]", data.Length, string.Join(", ", data.Select(x => x.ToString())));
            if(!commands.TryGetCommand(data, out var command))
            {
                this.Log(LogLevel.Warning, "Unknown command: [{0}]. Ignoring the data.", string.Join(", ", data.Select(x => string.Format("0x{0:X}", x))));
                return;
            }
            command(data);
        }

        public void Reset()
        {
            Light = 0;
            outputBuffer.Clear();
        }

        public decimal Light
        {
            get
            {
                return light;
            }
            set
            {
                if(MinLight > value || value > MaxLight)
                {
                    throw new RecoverableException("The temperature value must be between {0} and {1}.".FormatWith(MinLight, MaxLight));
                }
                light = value;
            }
        }

        private void MeasureLight(byte[] command)
        {
            outputBuffer.Enqueue((byte)((uint)light >> 8));
            outputBuffer.Enqueue((byte)((uint)light & 0xFF));
        }



        private decimal light;

        private readonly I2CCommandManager<Action<byte[]>> commands;
        private readonly Queue<byte> outputBuffer;

        private const decimal MaxLight = 100;
        private const decimal MinLight = 0;
    }
}