using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ServerUDP
{
    public enum DataTypeIdentifier
    {
        Message,
        Login,
        Logout,
        Null
    }

    public class Packet
    {
        /// <summary>
        /// Il tipo di dato contenuto nel pacchetto
        /// </summary>
        public DataTypeIdentifier DataIdentifier { get; set; }

        /// <summary>
        /// Il nome dell'utente della chat che ha generato il messaggio
        /// </summary>
        public string UserName { get; set; }

        /// <summary>
        /// Il messaggio
        /// </summary>
        public string Message { get; set; }

        public Packet(byte[] bytes) {
            FromByteArray(bytes);
        }

        public Packet()
        {
            DataIdentifier = DataTypeIdentifier.Null;
            UserName = "";
            Message = "";
        }

        /// <summary>
        /// Converte l'oggetto in un array di bytes
        /// </summary>
        /// <returns></returns>
        public byte[] ToByteArray()
        {
            List<byte> dataStream = new List<byte>();
            dataStream.AddRange(BitConverter.GetBytes((int)DataIdentifier));
            if (UserName != null)
            {
                dataStream.AddRange(BitConverter.GetBytes(UserName.Length));
            }
            else
            {
                dataStream.AddRange(BitConverter.GetBytes(0));
            }
            if (Message != null)
            {
                dataStream.AddRange(BitConverter.GetBytes(Message.Length));
            }
            else
            {
                dataStream.AddRange(BitConverter.GetBytes(0));
            }

            if (UserName != null)
            {
                dataStream.AddRange(System.Text.Encoding.ASCII.GetBytes(UserName));
            }

            if (Message != null)
            {
                dataStream.AddRange(System.Text.Encoding.ASCII.GetBytes(Message));
            }

            return dataStream.ToArray();
        }

        /// <summary>
        /// Inizializza la struttura da un array di bytes
        /// </summary>
        /// <param name="bytes"></param>
        public void FromByteArray(byte[] bytes)
        {
            DataIdentifier = (DataTypeIdentifier)BitConverter.ToInt32(bytes, 0);
            int nameLength = BitConverter.ToInt32(bytes, 4);
            int msgLength = BitConverter.ToInt32(bytes, 8);
            if (nameLength > 0)
                UserName = Encoding.UTF8.GetString(bytes, 12, nameLength);
            else
                UserName = "";

            if (Message.Length > 0)
                Message = Encoding.UTF8.GetString(bytes, 12+nameLength, msgLength);
            else
                UserName = "";
        }
    }
}
