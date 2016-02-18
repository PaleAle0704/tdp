using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Chat;
using System.Net.Sockets;
using System.Net;


namespace Client_TCP
{
    public partial class Form1 : Form
    {
        private string _userName;
        private Socket _clientSocket;
        private byte[] _dataStream;

        public Form1()
        {
            InitializeComponent();
        }

        private void btnConnetti_Click(object sender, EventArgs e)
        {
            _userName = txtNome.Text.Trim();

            Packet sendData = new Packet();
            sendData.DataIdentifier = DataTypeIdentifier.Login;
            sendData.UserName = _userName;

            _clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);

            IPAddress serverIP = IPAddress.Parse(txtIp.Text.Trim());
            int serverPort = int.Parse(txtPort.Text.Trim());

            IPEndPoint epServer = new IPEndPoint(serverIP, serverPort);

            byte[] data = sendData.ToByteArray();
            _clientSocket.BeginSendTo(data, 0, data.Length, SocketFlags.None, epServer, SendData, null);
            _dataStream = new byte[1024];
            _clientSocket.BeginReceiveFrom(_dataStream);
        }

        void SendData(IAsyncResult result)
        {
            _clientSocket.EndSend(result);
        }


    }
}
