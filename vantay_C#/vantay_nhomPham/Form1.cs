using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.IO;
using System.IO.Ports;
using System.Xml;

namespace vantay_nhomPham
{
    public partial class Form1 : Form
    {
        String mStr, str1, chuoi1 ="A", chuoi2 = "001", chuoi3 = "C",
            chuoi4 = "E", chuoi5 = "G", chuoi6 = "1111", chuoiAll ="";
        Int16 i = 0;
        public Form1()
        {
            InitializeComponent();
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            mStr = "abc";
            chuoi1 = "A";
            chuoi2 = "001";
            chuoi3 = "C";
            chuoi4 = "E";
            chuoi5 = "G";
            chuoiAll = "*" + chuoi1 + chuoi2 + chuoi3 + chuoi4 + chuoi5 + chuoi6 + "#";
            pictureBox2.BackColor = Color.DimGray;
            String[] strPortname = SerialPort.GetPortNames();
            foreach (string m in strPortname)
            {
                comboBox1.Items.Add(m);
            }
            comboBox1.SelectedIndex = 0;
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            serialPort1.Close();
            timer_data.Stop();
            timer1.Stop();
        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {

             mStr = serialPort1.ReadLine();
        }

        private void timer_data_Tick(object sender, EventArgs e)
        {
            textBox1.Text = mStr;
            str1 = mStr;
            if (str1.IndexOf('.') == 0)
            {
                pictureBox1.BackColor = Color.Lime;
            }
            else pictureBox1.BackColor = Color.DarkRed;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)
            {
                serialPort1.PortName = comboBox1.Text;
                serialPort1.Open();
                timer_data.Enabled = true;
                timer1.Enabled = true;
                pictureBox2.BackColor = Color.Lime;
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            chuoiAll = "*" + chuoi1 + chuoi2 + chuoi3 + chuoi4 + chuoi5 + chuoi6 + "#";
        }
        private void btcreat_Click(object sender, EventArgs e)
        {
            chuoi3 = "D";
            serialPort1.Write(chuoiAll);
            timer_realease.Start();
        }

        private void timer_realease_Tick(object sender, EventArgs e)
        {
            i++;
            if(i == 2)
            { 
                chuoi1 = "A";
                chuoi3 = "C";
                chuoi4 = "E";
                chuoi5 = "G";
                //chuoi6 = "1111";
                chuoiAll = "*" + chuoi1 + chuoi2 + chuoi3 + chuoi4 + chuoi5 + chuoi6 + "#";
                timer_realease.Stop();
                i = 0;
            }
            
            serialPort1.Write(chuoiAll);
        }

        private void btmanu_Click(object sender, EventArgs e)
        {
            chuoi4 = "F";
            serialPort1.Write(chuoiAll);
            timer_realease.Start();
        }

        private void btdele_Click(object sender, EventArgs e)
        {
            chuoi5 = "H";
            serialPort1.Write(chuoiAll);
            timer_realease.Start();
        }
     
    }
}
