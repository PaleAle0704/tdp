Imports System.Net.Sockets
Imports System.Net
Imports System.Text
Imports System.Threading


Public Class frmPrincipale
    Dim UDPClient As New UdpClient
    Dim thrRicevente As Thread

    Private Sub frmPrincipale_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Load
        thrRicevente = New Thread(AddressOf ThreadTask)
        thrRicevente.IsBackground = False
        thrRicevente.Start()
    End Sub

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnInvia.Click
        Dim ip As IPAddress
        Dim port As Integer
        Dim messaggioByte As Byte()
        Dim lung As Integer

        ip = IPAddress.Parse("127.0.0.10")
        port = 9998

        UDPClient.Connect(ip, port)
        messaggioByte = Encoding.ASCII.GetBytes(txtInvia.Text)
        lung = messaggioByte.Length
        UDPClient.Send(messaggioByte, lung)

    End Sub

    Private Sub ThreadTask()
        Dim recUDP As New UdpClient(9998)
        Dim RemoteIpEndPoint As New System.Net.IPEndPoint(System.Net.IPAddress.Any, 0)
        While (True)
            Dim bytesRicevuti As [Byte]() = recUDP.Receive(RemoteIpEndPoint)
            MessageBox.Show(Encoding.ASCII.GetString(bytesRicevuti))
            'txtRicevi.Text = txtRicevi.Text & " " & Encoding.ASCII.GetString(bytesRicevuti)
        End While
    End Sub
End Class


