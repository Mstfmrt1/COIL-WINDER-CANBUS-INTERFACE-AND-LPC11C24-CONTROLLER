using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using PCANDevice;
using System.Threading;
using System.Diagnostics;
using System.Runtime;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using System.Reflection.Emit;

namespace Coil_Winder
{
    public partial class Form1 : Form
    {

        public static int count = 0;
        public static string[] data = { "", "", "", "", "", "", "", "" };

        private Thread readThread;
        List<ushort> interfaces = PCANDevice.PCANManager.GetAllAvailable();
        PCANDevice.PCANManager pcan = new PCANDevice.PCANManager();


        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            textBox1.Enabled = false;
            textBox2.Enabled = false;
            button1.Enabled = false;
            button2.Enabled = false;
        }

        private void button4_Click_1(object sender, EventArgs e)
        {
            MessageBoxButtons buttons = MessageBoxButtons.OK;
            try
            {
                pcan.Connect(interfaces[0], PCANDevice.TPCANBaudrate.PCAN_BAUD_250K);
                textBox1.Enabled = true;
                textBox2.Enabled = true;
                button1.Enabled = true;

                progressBar1.Value = 100;
                Statuslabel.Text = "ON";
            }
            catch (Exception ex)
            {
                DialogResult result = MessageBox.Show("PCAN NOT AVAILABLE !", "ERROR", buttons, MessageBoxIcon.Warning);
                if (result == DialogResult.OK || result == DialogResult.Cancel)
                {

                    System.Environment.Exit(1);
                }


            }


            //pcan.AddReceiveCallback(callback);

            readThread = new Thread(new ThreadStart(startCallback));
            readThread.Start();
            //pcan.SendFrame(1, 8, new byte[] { 0, 1, 2, 3, 4, 5, 6, 7 });
            //pcan.SendFrameExt(0x7ff1, 8, new byte[] { 0, 1, 2, 3, 4, 5, 6, 7 });
            pcan.ActivateAutoReceive();
        }
        public void startCallback()
        {
            pcan.AddReceiveCallback(callback);
        }
        public void startReceive()
        {
            pcan.ActivateAutoReceive();
        }
        public static int callback(object[] args)
        {
            TPCANMsg msg = (TPCANMsg)args[0];
            string msgID = Convert.ToString(msg.ID.ToString("X"));
            //Debug.WriteLine(Convert.ToString(msg.ID.ToString("X")).PadLeft(8, '0'));
            //Debug.WriteLine(BitConverter.ToString(msg.DATA));

            if (msgID == "500")
            {

                string msgdata0 = Convert.ToString(msg.DATA[0].ToString("X")); //decimal to hex
                string msgdata1 = Convert.ToString(msg.DATA[1].ToString("X"));
                string msgdata2 = Convert.ToString(msg.DATA[2].ToString("X"));
                string msgdata3 = Convert.ToString(msg.DATA[3].ToString("X"));

                int byte0 = Convert.ToInt32(msgdata0, 16);//hex to decimal
                int byte1 = Convert.ToInt32(msgdata1, 16);
                int byte2 = Convert.ToInt32(msgdata2, 16);
                int byte3 = Convert.ToInt32(msgdata3, 16);

                count = byte0 + byte1 + byte2 + byte3;

                //Debug.WriteLine(Convert.ToInt32(count));

            }
            else if (msgID == "545")
            {
                string msgdata0 = Convert.ToString(msg.DATA[0].ToString("X")); //decimal to hex
                string msgdata1 = Convert.ToString(msg.DATA[1].ToString("X"));
                string msgdata2 = Convert.ToString(msg.DATA[2].ToString("X"));
                string msgdata3 = Convert.ToString(msg.DATA[3].ToString("X"));
                string msgdata4 = Convert.ToString(msg.DATA[4].ToString("X")); //decimal to hex
                string msgdata5 = Convert.ToString(msg.DATA[5].ToString("X"));
                string msgdata6 = Convert.ToString(msg.DATA[6].ToString("X"));
                string msgdata7 = Convert.ToString(msg.DATA[7].ToString("X"));

                int byte0 = Convert.ToInt32(msgdata0, 16);
                int byte1 = Convert.ToInt32(msgdata1, 16);
                int byte2 = Convert.ToInt32(msgdata2, 16);
                int byte3 = Convert.ToInt32(msgdata3, 16);
                int byte4 = Convert.ToInt32(msgdata4, 16);
                int byte5 = Convert.ToInt32(msgdata5, 16);
                int byte6 = Convert.ToInt32(msgdata6, 16);
                int byte7 = Convert.ToInt32(msgdata7, 16);

                char a = Convert.ToChar(byte0);
                char b = Convert.ToChar(byte1);
                char c = Convert.ToChar(byte2);
                char d = Convert.ToChar(byte3);
                char e = Convert.ToChar(byte4);
                char f = Convert.ToChar(byte5);
                char g = Convert.ToChar(byte6);
                char k = Convert.ToChar(byte7);

                data[0] = a.ToString();
                data[1] = b.ToString();
                data[2] = c.ToString();
                data[3] = d.ToString();
                data[4] = e.ToString();
                data[5] = f.ToString();
                data[6] = g.ToString();
                data[7] = k.ToString();

            }

            return 0;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            this.Close();
        }



        private void button1_Click(object sender, EventArgs e)
        {
            label1.Text = "";
            if (textBox1.Text != "" && textBox2.Text != "")
            {
                button2.Enabled = true;
                int speed = Convert.ToInt32(textBox1.Text);
                int turn = Convert.ToInt32(textBox2.Text);
                if (turn < 256)
                {
                    pcan.SendFrame(Convert.ToInt32("600", 16), 8, new byte[] { Convert.ToByte(1), Convert.ToByte(speed), Convert.ToByte(turn) });
                }
                else if ((turn > 256) && (turn < 512))
                {
                    pcan.SendFrame(Convert.ToInt32("600", 16), 8, new byte[] { Convert.ToByte(1), Convert.ToByte(speed), Convert.ToByte(255), Convert.ToByte(turn - 255) });
                }
                else if ((turn > 512) && (turn < 768))
                {
                    pcan.SendFrame(Convert.ToInt32("600", 16), 8, new byte[] { Convert.ToByte(1), Convert.ToByte(speed), Convert.ToByte(255), Convert.ToByte(255), Convert.ToByte(turn - 510) });
                }
                else if ((turn > 768) && (turn < 1001))
                {
                    pcan.SendFrame(Convert.ToInt32("600", 16), 8, new byte[] { Convert.ToByte(1), Convert.ToByte(speed), Convert.ToByte(255), Convert.ToByte(255), Convert.ToByte(255), Convert.ToByte(turn - 765) });
                }
            }
            else
            {
                MessageBox.Show("PLEASE ENTER SPEED AND TURN VALUE");
            }



            //pcan.SendFrame(600, 8, new byte[] { 0, 1, 2, 3, 4, 5, 6, 7 });
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            //textBox3.Text = count.ToString();
            label4.Text = Convert.ToString(count);
            Debug.WriteLine(data[0]);
            if (data[0] == "F")
            {
                label1.Text = data[0] + data[1] + data[2] + data[3] + data[4] + data[5] + data[6] + data[7];
            }
            else if (data[0] == "W")
            {
                label1.Text = data[0] + data[1] + data[2] + data[3] + data[4] + data[5] + data[6] + data[7];
            }
        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            e.Handled = !char.IsDigit(e.KeyChar) && !char.IsControl(e.KeyChar);
        }

        private void textBox2_KeyPress(object sender, KeyPressEventArgs e)
        {
            e.Handled = !char.IsDigit(e.KeyChar) && !char.IsControl(e.KeyChar);
        }

        private void textBox1_Leave(object sender, EventArgs e)
        {
            try
            {
                if (Convert.ToInt32(textBox1.Text) < 0 || Convert.ToInt32(textBox1.Text) > 100)
                {
                    MessageBox.Show("PLEASE ENTER NUMBER BETWEEN 0-100");

                }
            }
            catch
            {
                MessageBox.Show("PLEASE ENTER NUMBER BETWEEN 0-100");
                textBox1.Text = "";
                textBox1.Focus();
            }
        }

        private void button2_Click_1(object sender, EventArgs e)
        {
            if (textBox1.Text != "" && textBox2.Text != "")
            {
                pcan.SendFrame(Convert.ToInt32("600", 16), 8, new byte[] { Convert.ToByte(0) });
            }
            else
                MessageBox.Show("PLEASE ENTER SPEED AND TURN VALUE");


        }

    }
}

