using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace Threads
{
    class MyApp
    {
        private int _vectorSize;
        private int _maxNumber;
        private int[] _sharedVector;
        private bool _done;
        private Mutex _mutex;

        public MyApp(string[] args)
        {
            if (args.Length != 2) {
               throw new Exception("Usage: ... N M");
            }

            _vectorSize = int.Parse(args[0]);
            _maxNumber = int.Parse(args[1]);
            _sharedVector = new int[_vectorSize];
            _done = false;
            _mutex = new Mutex();
        }

        public void Run() {
            Thread prod = new Thread(ProdThreadProc);
            prod.Start();

            for (int i = 0; i < 5; i++)
            {
                Thread cons = new Thread(ConsThreadProc);
                cons.Start(i+1);
            }

            while (!_done)
            {
                Thread.Sleep(100);
            }
        }

        private void ProdThreadProc() {
            Random rnd = new Random(Guid.NewGuid().GetHashCode());
            while (!_done)
            {
                if (_mutex.WaitOne(200)) { 
                    // Sono riuscito ad acquisire l'accesso al vettore condiviso
                    for (int i = 0; i < _sharedVector.Length; i++)
                    {
                        if (_sharedVector[i] == 0) {
                            _sharedVector[i] = rnd.Next(1, _maxNumber);
                        }
                    }
                    _mutex.ReleaseMutex();
                }
                Thread.Sleep(10);
            }
        }

        private void ConsThreadProc(object param) {
            int consID = (int)param;
            int sum = 0;
            Random rnd = new Random(Guid.NewGuid().GetHashCode());
            while (!_done)
            {
                if (_mutex.WaitOne(200))
                {
                    // Sono riuscito ad acquisire l'accesso al vettore condiviso
                    int i = rnd.Next(0, _vectorSize - 1);
                    
                    if (_sharedVector[i] != 0)
                    {
                        sum += _sharedVector[i];
                        Console.WriteLine("Produttore{0}: {1}", consID, sum);
                        _sharedVector[i] = 0;
                    }

                    if (sum >= 1000) {
                        _done = true;
                    }
                    _mutex.ReleaseMutex();
                }
                Thread.Sleep(10);
            }
        }
    }
}
