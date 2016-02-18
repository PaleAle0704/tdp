using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Threads
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                MyApp app = new MyApp(args);
                app.Run();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
    }
}
