using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Extensions.Configuration;

namespace ChatClient
{
    public class Client
    {
        private IConfiguration _configuration;
        private Socket _clientSocket;
        public Client(IConfiguration configuration) 
        {
            _configuration = configuration;
            _clientSocket = null;
        }

        public bool Init()
        {
            var section = _configuration.GetSection("serverConfig");

            IPAddress ipAdress = section.GetValue<IPAddress>("ipAddress");
            Socket client = new Socket(_con, SocketType.Stream, ProtocolType.Tcp);

        }
    }
}
