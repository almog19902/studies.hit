//using System;
//using System.Net;
//using System.Net.Sockets;
//using System.Text;

//class Server
//{
//    static void Main()
//    {
//        const int port = 5740;
//        IPEndPoint endPoint = new IPEndPoint(IPAddress.Any, port);

//        // Create a socket
//        Socket serverSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

//        try
//        {
//            // Bind the socket to the endpoint and start listening
//            serverSocket.Bind(endPoint);
//            serverSocket.Listen(1); // Only one connection for this chat
//            Console.WriteLine($"Server started on port {port}. Waiting for a connection...");

//            // Accept an incoming connection
//            Socket clientSocket = serverSocket.Accept();
//            Console.WriteLine("Client connected. Type 'exit' to end the chat.");

//            while (true)
//            {
//                // Receive a message from the client
//                byte[] buffer = new byte[1024];
//                int receivedBytes = clientSocket.Receive(buffer);
//                string clientMessage = Encoding.UTF8.GetString(buffer, 0, receivedBytes);
//                Console.WriteLine($"Client: {clientMessage}");

//                if (clientMessage.Equals("exit", StringComparison.OrdinalIgnoreCase))
//                {
//                    Console.WriteLine("Client disconnected.");
//                    break;
//                }

//                // Send a response to the client
//                Console.Write("You: ");
//                string response = Console.ReadLine();
//                byte[] responseBytes = Encoding.UTF8.GetBytes(response);
//                clientSocket.Send(responseBytes);

//                if (response.Equals("exit", StringComparison.OrdinalIgnoreCase))
//                {
//                    Console.WriteLine("You ended the chat.");
//                    break;
//                }
//            }

//            // Close the client socket
//            clientSocket.Close();
//        }
//        catch (Exception ex)
//        {
//            Console.WriteLine($"Error: {ex.Message}");
//        }
//        finally
//        {
//            // Close the server socket
//            serverSocket.Close();
//            Console.WriteLine("Server stopped.");
//        }
//    }
//}

using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

class Program
{
    private static Dictionary<string, Socket> clients = new Dictionary<string, Socket>();
    private const int port = 5000;

    static void Main(string[] args)
    {
        Socket serverSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        serverSocket.Bind(new IPEndPoint(IPAddress.Any, port));
        serverSocket.Listen(5);

        Console.WriteLine($"Server started on port {port}. Waiting for connections...");

        while (true)
        {
            Socket clientSocket = serverSocket.Accept();
            Thread clientThread = new Thread(() => HandleClient(clientSocket));
            clientThread.Start();
        }
    }

    private static void HandleClient(Socket clientSocket)
    {
        try
        {
            // Ask for client name
            byte[] buffer = new byte[1024];
            int receivedBytes = clientSocket.Receive(buffer);
            string clientName = Encoding.UTF8.GetString(buffer, 0, receivedBytes).Trim();

            if (clients.ContainsKey(clientName))
            {
                clientSocket.Send(Encoding.UTF8.GetBytes("Name already taken."));
                clientSocket.Close();
                return;
            }

            lock (clients)
            {
                clients.Add(clientName, clientSocket);
            }

            Console.WriteLine($"{clientName} connected.");
            clientSocket.Send(Encoding.UTF8.GetBytes("Welcome to the chat server!"));

            while (true)
            {
                receivedBytes = clientSocket.Receive(buffer);
                string message = Encoding.UTF8.GetString(buffer, 0, receivedBytes).Trim();

                if (message.StartsWith("/to"))
                {
                    string[] parts = message.Split(' ', 3);
                    if (parts.Length < 3)
                    {
                        clientSocket.Send(Encoding.UTF8.GetBytes("Invalid command. Use /to <name> <message>"));
                        continue;
                    }

                    string targetName = parts[1];
                    string msg = parts[2];

                    if (clients.ContainsKey(targetName))
                    {
                        Socket targetSocket = clients[targetName];
                        targetSocket.Send(Encoding.UTF8.GetBytes($"{clientName}: {msg}"));
                    }
                    else
                    {
                        clientSocket.Send(Encoding.UTF8.GetBytes($"User {targetName} not found."));
                    }
                }
                else
                {
                    clientSocket.Send(Encoding.UTF8.GetBytes("Invalid command. Use /to <name> <message>"));
                }
            }
        }
        catch (SocketException)
        {
            Console.WriteLine("A client disconnected.");
        }
        finally
        {
            lock (clients)
            {
                foreach (var pair in clients)
                {
                    if (pair.Value == clientSocket)
                    {
                        clients.Remove(pair.Key);
                        break;
                    }
                }
            }
            clientSocket.Close();
        }
    }
}
