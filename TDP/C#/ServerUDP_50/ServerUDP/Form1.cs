using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Windows.Forms;

namespace ServerUDP
{
    public partial class Form1 : Form
    {
        private struct Client
        {
            public EndPoint EndPoint;
            public string Name;
        }

        /*Dichiaro la funzione delegata e il puntatore alla funzione. Scrive del testo nella TextBox*/
        private delegate void SetTextDelegate(string message);
        private SetTextDelegate _setText;


        private List<Client> _clientList;

        private Socket _serverSocket;

        /// <summary>
        /// Il vettore di bytes per la comunicazione
        /// </summary>
        private byte[] _dataStream;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            _setText = AppendTextLong;
            _clientList = new List<Client>();
            _dataStream = new byte[Properties.Settings.Default.MAX_PACKET_LENGTH];
            _serverSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
            IPEndPoint server = new IPEndPoint(IPAddress.Any, Properties.Settings.Default.DEFAULT_SERVER_PORT); 
            _serverSocket.Bind(server);

            EndPoint epSender = new IPEndPoint(IPAddress.Any, 0);
            _serverSocket.BeginReceiveFrom(_dataStream, 0, _dataStream.Length, SocketFlags.None, ref epSender, ReceiveData, epSender);
        }

        private void AppendTextLong(string message)
        {
            txtLog.Text += message;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Close();
        }

        public void ReceiveData(IAsyncResult asyncResult)
        {
            Packet receivedData = new Packet(_dataStream);

            // e uno per i dati da spedire
            Packet sendDataPacket = new Packet();

            // di nuovo il polimorfismo!!!! Sempre per lo stesso motivo
            EndPoint epSender = new IPEndPoint(IPAddress.Any, 0);;

            // Ricevo i dati
            _serverSocket.EndReceiveFrom(asyncResult, ref epSender);

            // Inizio a popolare il pacchetto da spedire
            sendDataPacket.DataIdentifier = receivedData.DataIdentifier;
            sendDataPacket.UserName = receivedData.UserName;

            switch (receivedData.DataIdentifier)
            {
                case DataTypeIdentifier.Message:
                    sendDataPacket.Message = string.Format("{0}: {1}", receivedData.UserName, receivedData.Message);
                    break;

                case DataTypeIdentifier.Login:
                    // Richiesta di join alla chat

                    // Creo l'oggetto client
                    // qui un esempio di ObjectInitializer al posto di scrivere:
                    //Client client = new Client();
                    //client.EndPoint = epSender;
                    //client.Name = receivedData.UserName;

                    Client client = new Client { EndPoint = epSender, Name = receivedData.UserName };

                    // Aggiungo il client alla lista
                    _clientList.Add(client);

                    sendDataPacket.Message = string.Format("-- {0} adesso è online --", receivedData.UserName);
                    break;

                case DataTypeIdentifier.Logout:
                    // Richiesta di uscita dalla chat (cerco il client da rimuovere)
                    foreach (Client c in _clientList.Where(c => c.EndPoint.Equals(epSender)))
                    {
                        _clientList.Remove(c);
                        break;
                    }

                    sendDataPacket.Message = string.Format("-- {0} è andato offline --", receivedData.UserName);
                    break;
            }

            /*Invio a tutti i client un messaggio di notifica di ciò che è accaduto*/
            byte[] data = sendDataPacket.ToByteArray();
            foreach (Client client in _clientList)
            {
                if (!client.EndPoint.Equals(epSender))
                {
                    _serverSocket.BeginSendTo(data, 0, data.Length, SocketFlags.None, client.EndPoint, SendData, client.EndPoint);
                }
            }

            _serverSocket.BeginReceiveFrom(_dataStream, 0, _dataStream.Length, SocketFlags.None, ref epSender, ReceiveData, epSender);
            Invoke(_setText, sendDataPacket.Message);
        }

        void SendData(IAsyncResult result)
        {
            _serverSocket.EndSendTo(result);

            
        }
    }
}
