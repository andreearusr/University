using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace Tema1SGBD
{
    public partial class Form1 : Form
    {

        DataSet dataset = new DataSet();
        SqlDataAdapter parentAdapter = new SqlDataAdapter();
        SqlDataAdapter childAdapter = new SqlDataAdapter();
        string connectionString = @"Server=ANDREEA\SQLEXPRESS;Database=ClinicaStomatologica;Integrated Security=true;";
        Int64 CNPp = 0;
        int ID = 0;
        

        public Form1()
        {
            InitializeComponent();
        }

        private void ClearFields()
        {
            dateTimePicker1.Value = DateTime.Today;
            textBox_Ora.Text = "";
            ID = 0;
        }

        private void TableRefresh()
        {
            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                childAdapter.SelectCommand.Connection = connection;
                dataset.Tables["Programare"].Clear();
                childAdapter.Fill(dataset, "Programare");
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    connection.Open();

                    parentAdapter.SelectCommand = new SqlCommand("SELECT * FROM Pacient;", connection);
                    childAdapter.SelectCommand = new SqlCommand("SELECT * FROM Programare;", connection);

                    parentAdapter.Fill(dataset, "Pacient");
                    childAdapter.Fill(dataset, "Programare");
                    connection.Close();


                    DataColumn pkColumn = dataset.Tables["Pacient"].Columns["CNPp"];
                    DataColumn fkColumn = dataset.Tables["Programare"].Columns["CNPp"];

                    DataRelation relation = new DataRelation("FK__Programare__CNPp__286302EC", pkColumn, fkColumn);
                    dataset.Relations.Add(relation);

                    dataGridViewParent.DataSource = dataset.Tables["Pacient"];

                    dataGridViewChild.DataSource = dataset.Tables["Pacient"];
                    dataGridViewChild.DataMember = "FK__Programare__CNPp__286302EC";

                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

        }

        private void dataGridViewParent_RowHeaderMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            CNPp = Convert.ToInt64(dataGridViewParent.Rows[e.RowIndex].Cells[0].Value);
        }

       
        private void dataGridViewChild_RowHeaderMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            ID = Convert.ToInt32(dataGridViewChild.Rows[e.RowIndex].Cells[0].Value.ToString());
            dateTimePicker1.Value = Convert.ToDateTime(dataGridViewChild.Rows[e.RowIndex].Cells[1].Value.ToString());
            textBox_Ora.Text = dataGridViewChild.Rows[e.RowIndex].Cells[2].Value.ToString();
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    connection.Open();
                    childAdapter.DeleteCommand = new SqlCommand("DELETE FROM Programare WHERE Programare.ID=@ID;", connection);
                    childAdapter.DeleteCommand.Parameters.AddWithValue("@ID", ID);
                    childAdapter.DeleteCommand.ExecuteNonQuery();
                    connection.Close();

                    TableRefresh();
                    ClearFields();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void buttonUpdate_Click(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    connection.Open();
                    childAdapter.UpdateCommand = new SqlCommand("UPDATE Programare SET Data=@Data, Ora=@Ora where ID=@ID", connection);

                    childAdapter.UpdateCommand.Parameters.AddWithValue("@ID", ID);
                    childAdapter.UpdateCommand.Parameters.AddWithValue("@Data", dateTimePicker1.Value);
                    childAdapter.UpdateCommand.Parameters.AddWithValue("@Ora", Convert.ToDateTime(textBox_Ora.Text));
                    childAdapter.UpdateCommand.ExecuteNonQuery();
                    connection.Close();

                    TableRefresh();
                    ClearFields();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void buttonInsert_Click(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    connection.Open();
                    childAdapter.InsertCommand = new SqlCommand("INSERT INTO Programare(Data,Ora,CNPp) VALUES(@Data,@Ora,@CNPp)", connection);

                    childAdapter.InsertCommand.Parameters.AddWithValue("@Data", dateTimePicker1.Value);
                    childAdapter.InsertCommand.Parameters.AddWithValue("@Ora", Convert.ToDateTime(textBox_Ora.Text));
                    childAdapter.InsertCommand.Parameters.AddWithValue("@CNPp", CNPp);
                    childAdapter.InsertCommand.ExecuteNonQuery();
                    connection.Close();

                    TableRefresh();
                    ClearFields();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}

