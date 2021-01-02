using System;
using Antmicro.Renode.Core;
using Antmicro.Renode.Exceptions;
using Antmicro.Renode.Peripherals.I2C;
using Antmicro.Renode.Utilities;
using Antmicro.Renode.Peripherals.Sensor;

namespace Antmicro.Renode.Peripherals.Sensors
{
    public class LightSensor  
    {
        public LightSensor()
        {
            Reset();
        }

        public void FinishTransmission()
        {
            Reset();
        }

        public void Reset()
        {
            isFirstByte = true;
            currentReadOut = 0;
        }

        public byte Transmit(byte data)
        {
            byte value = 0;
            if(isFirstByte)
            {
                //The 3 LSB are set to 1. 0x1000 = 0.0625C. Decimal->Int->UInt conversion to handle negative values.
                currentReadOut = (((uint)(int)(Light * 10000 / 625) << 3) | 0x7);
                value = (byte)(currentReadOut >> 8);
            }
            else
            {
                value = (byte)(currentReadOut & 0xFF);
            }
            isFirstByte = !isFirstByte;
            return value;
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
                    throw new RecoverableException("The light value must be between {0} and {1}.".FormatWith(MinLight, MaxLight));
                }
                light = value;
            }
        }

        private decimal light;
        private uint currentReadOut;
        private bool isFirstByte;

        private const decimal MaxLight = 100;
        private const decimal MinLight = 0;
    }
}