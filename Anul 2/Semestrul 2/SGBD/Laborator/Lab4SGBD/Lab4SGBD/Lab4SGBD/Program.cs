using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Lab4SGBD
{
    class Program
    {
        
        static void Main(string[] args)
        {
            Thread t1 = new Thread(Deadlock1);
            Thread t2 = new Thread(Deadlock2);

            t1.Start();
            t2.Start();
        }


        static void Deadlock1()
        {
            string connectionString = @"Server=ANDREEA\SQLEXPRESS;Database=ClinicaStomatologica;Integrated Security=true;";
            SqlConnection connection = new SqlConnection(connectionString);
            string deadlock1 = @"[dbo].[deadlock1]";
            SqlCommand cmd1 = new SqlCommand(deadlock1, connection);
            cmd1.CommandType = CommandType.StoredProcedure;
            try
            {
                connection.Open();
                cmd1.ExecuteNonQuery();
                //connection.Close();
                Console.WriteLine("Success T1");

            }
            catch (SqlException ex)
            {
                if (ex.Number == 1205)
                    Console.WriteLine("Deadlock1");
                else
                    Console.WriteLine(ex.Message);

                int times = 5;
                while (times > 0)
                {
                    Console.WriteLine("...T1");
                    try
                    {
                        cmd1.ExecuteNonQuery();
                        times--;
                        Console.WriteLine("Success T1");
                        break;
                    }
                    catch (SqlException exx)
                    {
                        Console.WriteLine("aborted T1");
                        Console.WriteLine(exx.Message);
                    }
                }


            }
        }




        static void Deadlock2()
        {
            string connectionString = @"Server=ANDREEA\SQLEXPRESS;Database=ClinicaStomatologica;Integrated Security=true;";
            SqlConnection connection = new SqlConnection(connectionString);
            string deadlock2 = @"[dbo].[deadlock2]";
            SqlCommand cmd2 = new SqlCommand(deadlock2, connection);
            cmd2.CommandType = CommandType.StoredProcedure;
            try
            {
                connection.Open();
                cmd2.ExecuteNonQuery();
                //connection.Close();

            }
            catch (SqlException ex)
            {
                if (ex.Number == 1205)
                    Console.WriteLine("Deadlock2");
                else
                    Console.WriteLine(ex.Message);

                int times = 5;
                while (times > 0)
                {
                    Console.WriteLine("...T2");
                    try
                    {
                        cmd2.ExecuteNonQuery();
                        times--;
                        Console.WriteLine("Success T2");
                        break;
                    }
                    catch (SqlException exx)
                    {
                        Console.WriteLine("aborted T2");
                        Console.WriteLine(exx.Message);
                    }
                }


            }

        }
    }
}
