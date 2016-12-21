using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DHT_Remote_Monitoring
{
    public partial class Form1 : Form
    {
        bool cont_monitor = false;
        int t_plus = 1;
        Timer t;
        string filePath, file_text = "";
        float iHum, iTemp;
        string sHum, sTemp;
        char[] f;

        public Form1()
        {
            
            InitializeComponent();
            time_interval.Text = t_plus.ToString().Trim();
            
        }

        private bool IsValidIP(string addr)
        {
            string pattern = @"^([1-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])(\.([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])){3}$";
            Regex check = new Regex(pattern);
            bool valid = false;
            if (String.IsNullOrEmpty(addr))
            {
                valid = false;
            }
            else
            {
                valid = check.IsMatch(addr, 0);
            }
            return valid;
        }

        private bool IsValidHumidity(string humidity) 
        {
            string pattern = @"^(?:\d{1,2})?(?:\.\d{1,2})?$";
            Regex check = new Regex(pattern);
            bool valid;
            if (String.IsNullOrEmpty(humidity))
            {
                valid = false;
            }
            else 
            { 
                valid = check.IsMatch(humidity, 0); 
            }

            return valid;
        }

        private bool IsValidTemperature(string temperature)
        {
            string pattern = @"^(?:\d{1,2})?(?:\.\d{1,2})?$";
            Regex check = new Regex(pattern);
            bool valid;
            if (String.IsNullOrEmpty(temperature))
            {
                valid = false;
            }
            else
            {
                valid = check.IsMatch(temperature, 0);
            }

            return valid;
        }

        private void monitor_button_Click(object sender, EventArgs e)
        {
            string ip_addr = ip_address_input.Text.ToString().Trim();
            string humidity = humidity_textBox.Text.ToString().Trim();
            string temperature = temperature_textBox.Text.ToString().Trim();
            if (!IsValidIP(ip_addr))
            {

                MessageBox.Show("Please input correct IP Address", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            if (!IsValidHumidity(humidity)) 
            {
                MessageBox.Show("Please input upper limit of humidity", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            if (!IsValidTemperature(temperature))
            {
                MessageBox.Show("Please input upper limit of temperature", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            string date = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
            string response = requestSensorData(ip_addr);
            f = response.ToArray();
            sHum = "";
            sTemp = "";
            for (int i = 0; i < response.Length; i++)
            {
                if (9 <= i && i <= 12)
                {
                    sHum += f[i];
                }

                if (28 <= i && i <= 31)
                {
                    sTemp += f[i];
                }

            }
            
            Debug.WriteLine(sHum);
            Debug.WriteLine(sTemp);
            float.TryParse(sHum, out iHum);
            float.TryParse(sTemp, out iTemp);

            Debug.WriteLine(iHum);
            Debug.WriteLine(iTemp);
           
            if (iHum > float.Parse(humidity) || iTemp > float.Parse(temperature))
            {
                makeBuzzerSound(ip_addr, "1");
                Debug.WriteLine("ok");
            }
            else
            {
                makeBuzzerSound(ip_addr, "0");
                Debug.WriteLine("oj");
            }
            Debug.WriteLine(date);
            Debug.WriteLine(response);
            string text_to_write = response + "  " + date + Environment.NewLine;
            data_box.Text += text_to_write;
            file_text += text_to_write;
            if (checkBox2.Checked && !String.IsNullOrEmpty(filePath)) 
            {
                File.WriteAllText(filePath, file_text);
            }
        }

        private string requestSensorData(string ip_addr) 
        {
            var request = (HttpWebRequest)WebRequest.Create("http://"+ip_addr+"/invent_one?action=monitor_sensor&sensor=DHT11");
            var response = (HttpWebResponse)request.GetResponse();
            var responseString = new StreamReader(response.GetResponseStream()).ReadToEnd();
            return responseString.ToString().Trim();
        }

        private string makeBuzzerSound(string ip_addr, string data) 
        {
            var request = (HttpWebRequest)WebRequest.Create("http://" + ip_addr + "/invent_one?action=control_pin_digital&pin=8&state="+data);
            var response = (HttpWebResponse)request.GetResponse();
            var responseString = new StreamReader(response.GetResponseStream()).ReadToEnd();
            return responseString.ToString().Trim();
        }

        private void continuously_monitor_CheckedChanged(object sender, EventArgs e)
        {
            if (continuously_monitor.Checked)
            {
                cont_monitor = true;
                t = new Timer();
                t.Interval += Int32.Parse(time_interval.Text.ToString().Trim()) * 1000;
                t.Tick += new EventHandler(DoThisWhileContinuousChecked);
                t.Start();
            }
            else 
            { 
                cont_monitor = false;
                t.Stop();
                Debug.WriteLine("ok");
            }
        }

        private void DoThisWhileContinuousChecked(object sender, EventArgs e) 
        {
            monitor_button.PerformClick();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            t_plus += 1;
            time_interval.Text = t_plus.ToString().Trim();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (t_plus != 1) 
            {
                t_plus -= 1;
                time_interval.Text = t_plus.ToString().Trim();
            }
        }

        private void data_box_TextChanged(object sender, EventArgs e)
        {
            data_box.SelectionStart = data_box.Text.Length;
            data_box.ScrollToCaret();
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox2.Checked) 
            {
                OpenFileDialog openFileDialog1 = new OpenFileDialog();
                openFileDialog1.InitialDirectory = @"C:\";
                openFileDialog1.Title = "Browse Text File";
                openFileDialog1.CheckFileExists = true;
                openFileDialog1.CheckPathExists = true;
                openFileDialog1.DefaultExt = "txt";
                openFileDialog1.Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
                openFileDialog1.FilterIndex = 2;
                openFileDialog1.RestoreDirectory = true;
                openFileDialog1.ReadOnlyChecked = false;
                openFileDialog1.ShowReadOnly = true;
                if (openFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    filePath = openFileDialog1.FileName;
                }
            }
            
        }

    }
}
