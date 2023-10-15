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
using System.Configuration;

namespace Tema1SGBD
{
    public partial class Form1 : Form
    {

        DataSet dataset = new DataSet();
        SqlDataAdapter parentAdapter = new SqlDataAdapter();
        SqlDataAdapter childAdapter = new SqlDataAdapter();
        string connectionString = @"Server=ANDREEA\SQLEXPRESS;Database=ClinicaStomatologica;Integrated Security=true;";

        string parentTable = ConfigurationManager.AppSettings.Get("parent");
        string childTable = ConfigurationManager.AppSettings.Get("child");
        string pkParent = ConfigurationManager.AppSettings.Get("pkParent");
        string pkChild = ConfigurationManager.AppSettings.Get("pkChild");
        string fkChild = ConfigurationManager.AppSettings.Get("fkChild");

        string childColumns = ConfigurationManager.AppSettings.Get("childColumns");
        string autoincrement = ConfigurationManager.AppSettings.Get("autoincrement");

        object pkChildValue;

        public Form1()
        {
            InitializeComponent();
            this.Text = parentTable + childTable;
            labelParent.Text = parentTable;
            labelChild.Text = childTable;
        }

        

        private void TableRefresh()
        {
            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                childAdapter.SelectCommand.Connection = connection;
                dataset.Tables[childTable].Clear();
                childAdapter.Fill(dataset, childTable);
            }
        }
        

        private void Form1_Load(object sender, EventArgs e)
        { 
            try
            {
                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    connection.Open();
                    parentAdapter.SelectCommand = new SqlCommand("SELECT * FROM " + parentTable, connection);
                    childAdapter.SelectCommand = new SqlCommand("SELECT * FROM " + childTable, connection);

   
                    parentAdapter.Fill(dataset, parentTable);
                    childAdapter.Fill(dataset, childTable);
                    connection.Close();

                    DataColumn pkColumn = dataset.Tables[parentTable].Columns[pkParent];
                    DataColumn fkColumn = dataset.Tables[childTable].Columns[fkChild];
                  
                    DataRelation relation = new DataRelation(parentTable+childTable, pkColumn, fkColumn);
                    dataset.Relations.Add(relation);

                    dataGridViewParent.DataSource = dataset.Tables[parentTable];

                    dataGridViewChild.DataSource = dataset.Tables[parentTable];
                    dataGridViewChild.DataMember = parentTable+childTable;

                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

        }

       
        private void dataGridViewChild_RowHeaderMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            pkChildValue = dataGridViewChild.Rows[e.RowIndex].Cells[0].Value;  
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    connection.Open();
                    childAdapter.DeleteCommand = new SqlCommand("DELETE FROM " + childTable + " WHERE " + childTable + "." + pkChild + "=" + pkChildValue, connection);
               
                    childAdapter.DeleteCommand.ExecuteNonQuery();
                    connection.Close();

                    TableRefresh(); 
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

                    string textColumns = "";
                    string pkColumn = "";
                    string[] columns = childColumns.Split(';');
                    var j = 0;
                    foreach (var col in columns)
                    {
                        if (j == 0)
                        {
                            pkColumn += col;
                            pkColumn += '=';
                            pkColumn += "'";
                            pkColumn += dataGridViewChild.CurrentRow.Cells[col].Value;
                            pkColumn += "'";
                        }

                        if (j != 0 && j!= columns.Length-1)
                        {
                            textColumns += col;
                            textColumns += '=';
                            textColumns += "'";
                            textColumns += dataGridViewChild.CurrentRow.Cells[col].Value;
                            textColumns += "'";
                            textColumns += ',';
                        }
                        j++;
                    }
                    textColumns = textColumns.Remove(textColumns.Length - 1, 1);

                    connection.Open();
                    childAdapter.UpdateCommand = new SqlCommand("UPDATE " + childTable + " SET " + textColumns + " WHERE " + pkColumn, connection);

                    
                    childAdapter.UpdateCommand.ExecuteNonQuery();
                    connection.Close();

                    TableRefresh();
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
                    string textColumns = "";
                    string valueColumns = "";
                    string[] columns = childColumns.Split(';');

                    if (autoincrement.Equals("yes")) { 
                        var j = 0;
                        foreach (var col in columns)
                        {
                            if (j != 0)
                            {
                                textColumns += col;
                                textColumns += ',';
                            }
                            j++;
                        }
                        textColumns = textColumns.Remove(textColumns.Length - 1, 1);

                        var i = 0;
                        foreach (var col in columns)
                        {
                            if (i != 0)
                            {
                                valueColumns += "'";
                                valueColumns += dataGridViewChild.CurrentRow.Cells[col].Value;
                                valueColumns += "'";
                                valueColumns += ',';
                            }
                            i++;
                        }
                        valueColumns = valueColumns.Remove(valueColumns.Length - 1, 1);

                    }
                    else if (autoincrement.Equals("no"))
                    {
                        
                        foreach (var col in columns)
                        {
                            textColumns += col;
                            textColumns += ',';
                        }
                        textColumns = textColumns.Remove(textColumns.Length - 1, 1);

                        
                        foreach (var col in columns)
                        {
                            valueColumns += "'";
                            valueColumns += dataGridViewChild.CurrentRow.Cells[col].Value;
                            valueColumns += "'";
                            valueColumns += ',';
                        }
                        valueColumns = valueColumns.Remove(valueColumns.Length - 1, 1);
                    }
                    
                    connection.Open();

                    childAdapter.InsertCommand = new SqlCommand("INSERT INTO " + childTable + "(" + textColumns + ")" + " VALUES(" + valueColumns  + ")", connection);
                    childAdapter.InsertCommand.ExecuteNonQuery();
                    connection.Close();

                    TableRefresh();
                  
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            
        }
    }
}

