using Antmicro.Renode.Peripherals.Sensor;
namespace Antmicro.Renode.Peripherals.Actuator
{

    public interface ILightSystem : ISensor
    {
       bool Active{ get; set; }
    }
}