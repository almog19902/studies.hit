using System.Net.Sockets;
using System.Net;

namespace ChatClient
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("client start");
            Client client = new Client();
            client.ConnectToServer();
            client.StartChating();
        }
    }
}
