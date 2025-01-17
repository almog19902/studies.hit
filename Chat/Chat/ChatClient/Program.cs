//using System.Net.Sockets;
//using System.Net;

//namespace ChatClient
//{
//    internal class Program
//    {
//        static void Main(string[] args)
//        {
//            Console.WriteLine("client start");
//            Client client = new Client();
//            client.ConnectToServer();
//            client.StartChating();
//        }
//    }
//}

using System;
using System.Net.Sockets;
using System.Text;
using System.Threading;

class Program
{
    private const int port = 5000;

    static void Main(string[] args)
    {
        Console.Write("Enter server IP: ");
        string serverIP = Console.ReadLine();

        Console.Write("Enter your name: ");
        string clientName = Console.ReadLine();

        try
        {
            Socket clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            clientSocket.Connect(serverIP, port);

            // Send client name to server
            clientSocket.Send(Encoding.UTF8.GetBytes(clientName));

            byte[] buffer = new byte[1024];
            int receivedBytes = clientSocket.Receive(buffer);
            string response = Encoding.UTF8.GetString(buffer, 0, receivedBytes);
            Console.WriteLine(response);

            if (response == "Name already taken.")
            {
                clientSocket.Close();
                return;
            }

            // Start a thread to listen for incoming messages
            Thread receiveThread = new Thread(() => ReceiveMessages(clientSocket));
            receiveThread.Start();

            // Send messages to server
            while (true)
            {
                string message = Console.ReadLine();
                clientSocket.Send(Encoding.UTF8.GetBytes(message));
            }
        }
        catch (SocketException ex)
        {
            Console.WriteLine($"Connection error: {ex.Message}");
        }
    }

    private static void ReceiveMessages(Socket clientSocket)
    {
        try
        {
            byte[] buffer = new byte[1024];
            while (true)
            {
                int receivedBytes = clientSocket.Receive(buffer);
                string message = Encoding.UTF8.GetString(buffer, 0, receivedBytes);
                Console.WriteLine(message);
            }
        }
        catch (SocketException)
        {
            Console.WriteLine("Disconnected from server.");
        }
        finally
        {
            clientSocket.Close();
        }
    }
}
