using Antmicro.Renode.Peripherals.Sensor;
namespace Antmicro.Renode.Peripherals.Actuator
{

    public interface IHeatingSystem : ISensor
    {
       bool Active{ get; set; }
    }
}