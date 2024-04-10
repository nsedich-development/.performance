using System.Runtime.ConstrainedExecution;

namespace PerformanceC_
{
    internal class Program
    {
        static void Main(string[] args)
        {
            var watch = System.Diagnostics.Stopwatch.StartNew(); 

            double sum = 0;
            double sum2 = 0;
            double sum3 = 0;

            for (double i = 0; i < 1500000000; i++)
            {
                sum += i;
                for (int k = 0; k < 5; k++)
                {
                    sum2 += k;
                    for (int n = 0; n < k; n++)
                    {
                        sum3 += n;
                    }
                }
            }

            watch.Stop();
            var elapsedMs = watch.ElapsedMilliseconds;

            Console.WriteLine("{0} {1} {2} {3}", sum, sum2, sum3, elapsedMs);

            System.Threading.Thread.Sleep(10000);
        }
    }
}
