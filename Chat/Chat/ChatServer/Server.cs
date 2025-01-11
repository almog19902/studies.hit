using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace ChatServer
{
    public class Server
    {
        public readonly ConcurrentDictionary<string, Socket> _clientSocketDict;


    }
}
