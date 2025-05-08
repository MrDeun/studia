using System;
using System.Threading;
using System.Threading.Tasks;



class HorseRace
{
    public static void EmulateRace()
    {
        var rand = new Random();
        int count = 0;
        Barrier barrier = new Barrier(6);
        Action action = () =>
        {
            barrier.SignalAndWait();
            int timeout = (int)(rand.NextDouble() * 5.0 * 1000);
            Thread.Sleep(timeout);
            Console.WriteLine("Finished the race after {0}!", timeout);
            barrier.SignalAndWait();
        };

        Parallel.Invoke(action, action, action, action, action, action);
    }
};
