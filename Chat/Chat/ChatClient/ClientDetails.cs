using System.Net;
using System.Net.Sockets;

namespace ChatClient
{
	public class ClientDetails
	{
		public IPAddress _ipAddress;
		public int _port;
		public string _username;
		public string _reqUserToChatWith;
		public Socket _socket;

		//public ClientDetails(IPAddress ipAddress, int port, string username,
		//							string reqUserToChatWith, Socket socket)
		//{
		//	_ipAddress = ipAddress;
		//	_port = port;
		//	_username = username;
		//	_reqUserToChatWith = reqUserToChatWith;
		//	_socket = socket;
		//}
	}
}
