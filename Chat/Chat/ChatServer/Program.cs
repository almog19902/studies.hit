using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class Server
{
    static void Main()
    {
        const int port = 5740;
        IPEndPoint endPoint = new IPEndPoint(IPAddress.Any, port);

        // Create a socket
        Socket serverSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

        try
        {
            // Bind the socket to the endpoint and start listening
            serverSocket.Bind(endPoint);
            serverSocket.Listen(1); // Only one connection for this chat
            Console.WriteLine($"Server started on port {port}. Waiting for a connection...");

            // Accept an incoming connection
            Socket clientSocket = serverSocket.Accept();
            Console.WriteLine("Client connected. Type 'exit' to end the chat.");

            while (true)
            {
                // Receive a message from the client
                byte[] buffer = new byte[1024];
                int receivedBytes = clientSocket.Receive(buffer);
                string clientMessage = Encoding.UTF8.GetString(buffer, 0, receivedBytes);
                Console.WriteLine($"Client: {clientMessage}");

                if (clientMessage.Equals("exit", StringComparison.OrdinalIgnoreCase))
                {
                    Console.WriteLine("Client disconnected.");
                    break;
                }

                // Send a response to the client
                Console.Write("You: ");
                string response = Console.ReadLine();
                byte[] responseBytes = Encoding.UTF8.GetBytes(response);
                clientSocket.Send(responseBytes);

                if (response.Equals("exit", StringComparison.OrdinalIgnoreCase))
                {
                    Console.WriteLine("You ended the chat.");
                    break;
                }
            }

            // Close the client socket
            clientSocket.Close();
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: {ex.Message}");
        }
        finally
        {
            // Close the server socket
            serverSocket.Close();
            Console.WriteLine("Server stopped.");
        }
    }
}
