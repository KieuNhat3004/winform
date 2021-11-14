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

namespace gameduaxe_arduino_control
{
    public partial class Form1 : Form
    {
        String mStr = "020", str1 = "", xl1 = "02",xl2 = "0";
        int a = 0, carspeed = 2;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
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
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            linemove(carspeed);
            gameover();
            totalscore();
            carspeed = Convert.ToInt16(xl1);
        }
        Random pos = new Random();
        void linemove(int speed)
        {
            if (pictureBox1.Top > 380) pictureBox1.Top = 0;
            else pictureBox1.Top += speed;
            if (pictureBox2.Top > 380) pictureBox2.Top = 0;
            else pictureBox2.Top += speed;
            if (pictureBox3.Top > 380) pictureBox3.Top = 0;
            else pictureBox3.Top += speed;


            if (enemy1.Top > 380)
            {
                score++;
                enemy1.Left = pos.Next(0, 200);
                enemy1.Top = pos.Next(0, 40);
                enemy1.Top = 0;
            }
            else enemy1.Top += speed;
            if (enemy2.Top > 380)
            {
                score++;
                enemy2.Left = pos.Next(0, 200);
                enemy2.Top = pos.Next(0, 40);
                enemy2.Top = 0;
            }
            else enemy2.Top += speed;
            if (enemy3.Top > 380)
            {
                score++;
                enemy3.Left = pos.Next(225, 300);
                enemy3.Top = pos.Next(0, 40);
                enemy3.Top = 0;
            }
            else enemy3.Top += speed;
            if (enemy4.Top > 380)
            {
                score++;
                enemy4.Left = pos.Next(225, 300);
                enemy4.Top = pos.Next(0, 40);
                enemy4.Top = 0;
            }
            else enemy4.Top += speed;

        }

        private void timer_data_Tick(object sender, EventArgs e)
        {
            label1.Text = mStr;
            //str1 = mStr;
            //xl1 = str1.Substring(0, 2);
            //xl2 = str1.Substring(2, 1);
            //if (xl2 == "1" && mycar.Left > 0) mycar.Left -= 2;
            //if (xl2 == "2" && mycar.Left < 265) mycar.Left += 2;
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            mStr = serialPort1.ReadLine();
        }

        int score;
        void totalscore()
        {
            textBox1.Text = score.ToString();
        }

        void gameover()
        {
            if (mycar.Bounds.IntersectsWith(enemy1.Bounds) || mycar.Bounds.IntersectsWith(enemy3.Bounds)
                || mycar.Bounds.IntersectsWith(enemy2.Bounds) || mycar.Bounds.IntersectsWith(enemy4.Bounds))
            {
                timer1.Stop();
                timer_data.Stop();
                DialogResult go = MessageBox.Show("Do you want play agian?", "GAME OVER", MessageBoxButtons.YesNo, MessageBoxIcon.Asterisk);
                switch (go)
                {
       
                    case System.Windows.Forms.DialogResult.Yes:
                        timer1.Enabled = true;
                        enemy1.Left = pos.Next(0, 200);
                        enemy1.Top = 0;
                        enemy2.Left = pos.Next(0, 200);
                        enemy2.Top = 0;
                        enemy3.Left = pos.Next(225, 300);
                        enemy3.Top = 0;
                        enemy4.Left = pos.Next(225, 300);
                        enemy4.Top = 0;
                        score = 0;
                        timer_data.Start();
                        timer1.Start();
                        break;
                    case System.Windows.Forms.DialogResult.No:
                        serialPort1.Close();
                        timer_data.Stop();
                        timer1.Stop();
                        this.Close();
                        break;
                }
            }
        }
        private void button1_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)
            {
                serialPort1.PortName = comboBox1.Text;
                serialPort1.Open();
                timer_data.Enabled = true;
                timer1.Enabled = true;
            }
        }
    }
}
