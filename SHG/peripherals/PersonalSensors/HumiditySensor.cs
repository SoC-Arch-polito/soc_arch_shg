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
    public class HumiditySensor : II2CPeripheral, IHumidityMODSensor,IExternal
    {
        public HumiditySensor()
        {
            commands = new I2CCommandManager<Action<byte[]>>();
            outputBuffer = new Queue<byte>();
            commands.RegisterCommand(MeasureHumidity, 0xE5);
            Reset();
        }

        public byte[] Read(int count = 1)
        {
            outputBuffer.Clear();
            outputBuffer.Enqueue((byte)humidity);
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
            Humidity = 0;
            outputBuffer.Clear();
        }

        public uint Humidity
        {
            get
            {
                return humidity;
            }
            set
            {

                if(MinHumidity > value || value > MaxHumidity)
                {
                    throw new RecoverableException("The humidity value must be between {0} and {1}.".FormatWith(MinHumidity, MaxHumidity));
                }

                humidity = value;

            }
        }

        private void MeasureHumidity(byte[] command)
        {
            outputBuffer.Enqueue((byte)((uint)humidity >> 8));
            outputBuffer.Enqueue((byte)((uint)humidity & 0xFF));
        }



        private uint humidity;

        private readonly I2CCommandManager<Action<byte[]>> commands;
        private readonly Queue<byte> outputBuffer;

        private const decimal MaxHumidity = 100;
        private const decimal MinHumidity = 0;
    }
}