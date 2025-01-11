using Microsoft.Extensions.Configuration;

namespace ChatClient
{
    internal class Program
    {
        static void Main(string[] args)
        {
            var configuration = new ConfigurationBuilder()
               .SetBasePath(AppDomain.CurrentDomain.BaseDirectory) 
               .AddJsonFile("appsettings.json", optional: false, reloadOnChange: true)  
               .Build();


        }
    }
}
