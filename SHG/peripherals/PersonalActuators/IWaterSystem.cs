using Antmicro.Renode.Peripherals.Sensor;
namespace Antmicro.Renode.Peripherals.Actuator
{

    public interface IWaterSystem : ISensor
    {
       bool Active{ get; set; }
    }
}