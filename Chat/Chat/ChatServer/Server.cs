//using ChatClient;
//using System;
//using System.Collections.Concurrent;
//using System.Collections.Generic;
//using System.Linq;
//using System.Net;
//using System.Net.Sockets;
//using System.Text;
//using System.Threading.Tasks;

//namespace ChatServer
//{
//    public class Server
//    {
//        private readonly ConcurrentDictionary<string,ClientDetails> _clients;
//        private readonly Socket _socket;
//        private readonly EndPoint _host;

//        public Server()
//        {
//            _clients = new ConcurrentDictionary<string,ClientDetails>();
//            _host = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 5740); //define
//            _socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
//        }

//        public bool Init()
//        {
//            try
//            {
//                _socket.Bind(_host);
//                serverSocket.Listen(50); //????

//                Console.WriteLine($"server is listening on port {}");
//            }

//            while(true)
//            {

//            }
//        }

//        private Task ListenToServerMessages()
//        {
//            byte[] buffer = new byte[1024];

//            while (true)
//            {
//                _socket.Receive(buffer);
//                Console.WriteLine(Encoding.UTF8.GetString(buffer));
//            }
//        }




//    }
//}
