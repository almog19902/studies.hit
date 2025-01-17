using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;

namespace ChatClient
{
    public class Client
    {
        private ClientDetails? _details;
        private IPEndPoint _host;
        private Socket _socket;

        public Client() 
        {
            _details = null;
            _host = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 5740); //define
            _socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        }

        public void ConnectToServer()
        {
            try
            {
                CreateClientDetailsFromUserInput();
                _socket.Connect(_host);
                Console.WriteLine($"Connect to server in {_host.Address}:{_host.Port}");

                string detailsAsJson = JsonSerializer.Serialize(_details);
                byte[] detailsInBytes = Encoding.UTF8.GetBytes(detailsAsJson);

                _socket.Send(detailsInBytes);
                Console.WriteLine($"Send Connect message to server");

                Task.Run(ListenToServerMessages);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Failed to connect to server\n {ex.Message}");
                _socket.Close();
            }
        }

        public void StartChating()
        {
            Console.WriteLine("Enter message (write exit for exit):");
            string currentMessage = Console.ReadLine();

            while(currentMessage != "exit")
            {
                if (string.IsNullOrEmpty(currentMessage))
                {
                    Console.WriteLine("Cant send empty message...");
                }
                else
                {
                    _socket.Send(Encoding.UTF8.GetBytes(currentMessage));
                    Console.WriteLine($"{_details._username} : {currentMessage}");
                }
                Console.Write($"{_details._username}:");
                currentMessage = Console.ReadLine();
            }
        }

        private Task ListenToServerMessages()
        {
            byte[] buffer = new byte[1024];

            while (true)
            {
                _socket.Receive(buffer);
                Console.WriteLine(Encoding.UTF8.GetString(buffer));
            }
        }

        private void CreateClientDetailsFromUserInput()
        {
            _details = new ClientDetails();
            Console.WriteLine("welcome to chat service");
            Console.WriteLine("Enter user name:");
            _details._username = Console.ReadLine();
            while (string.IsNullOrEmpty(_details._username))
            {
                Console.WriteLine("Incorrect user name, please enter user name again:");
                _details._username = Console.ReadLine();
            }

            Console.WriteLine("Enter user name to chat with:");
            _details._reqUserToChatWith = Console.ReadLine();
            while (string.IsNullOrEmpty(_details._reqUserToChatWith))
            {
                Console.WriteLine("Incorrect user name, please enter user name again:");
                _details._reqUserToChatWith = Console.ReadLine();
            }

            _details._ipAddress = null;
            _details._port = 0;
            _details._socket = null;
        }
    }
}
