using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
            int a, b;
            float c, d;

            a = 125;
            b = a / 2;
            string str = string.Format("{0}\n", b);
            Console.Write(str);

            Console.Write("{0}\n", b);      
            Console.Write("{0,3}\n", b);
            Console.Write("{0:D3}\n", b);   //decimale di lunghezza 3, con riempimento di 0
            Console.Write("{0:X}\n", b);
            Console.Write("{0,3:X}\n", b);
            Console.Write("{0:X3}\n", b);

            c = 15.3f;
            d = c / 3;
            Console.Write("{0}\n", b);
            System.Threading.Thread.Sleep(5000);
        }
    }
}
