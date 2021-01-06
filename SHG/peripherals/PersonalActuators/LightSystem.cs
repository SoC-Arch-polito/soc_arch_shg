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
using Antmicro.Renode.UserInterface;

namespace Antmicro.Renode.Peripherals.Actuator
{
    public class LightSystem : II2CPeripheral, ILightSystem,IExternal
    {
        public LightSystem()
        {
            outputBuffer = new Queue<byte>();
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
            byte[] b=data.ToArray();
            byte off=0x00;
            this.Log(LogLevel.Noisy, "Received {0} bytes: [{1}]", data.Length, string.Join(", ", data.Select(x => x.ToString())));
            if(data.Length>1){
            if(b[1].Equals(off)){
                outputBuffer.Clear();
                outputBuffer.Enqueue(b[1]);
                active=false;
            }else {
                outputBuffer.Clear();
                outputBuffer.Enqueue(b[1]);
                active=true;
            } 
            }
            return;
        }

        public void Reset()
        {
            Active = false;
            outputBuffer.Clear();
            outputBuffer.Enqueue(0x00);
        }

        public bool Active
        {
            get
            {
                return active;
            }
            set
            {
                active = value;
            }        }


        private bool active;


        private readonly Queue<byte> outputBuffer;
    }
}