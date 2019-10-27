using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;

namespace PythonSTGConfig
{
    
    public partial class FormMain : Form
    {
        private Dictionary<string, string> keyCode = new Dictionary<string, string>();
        [System.Runtime.InteropServices.DllImport("user32.dll")]
        private static extern short GetAsyncKeyState(Keys vKey);
        private ConfigHelper configHelper;
        public FormMain()
        {
            InitializeComponent();

            upKeyBox.ReadOnly = true;
            downKeyBox.ReadOnly = true;
            leftKeyBox.ReadOnly = true;
            rightKeyBox.ReadOnly = true;
            specialKeyBox.ReadOnly = true;
            slowKeyBox.ReadOnly = true;
            shootKeyBox.ReadOnly = true;
 
        }


        private void FormMain_Load(object sender, EventArgs e)
        {
            configHelper = new ConfigHelper();
            configHelper.FileLoad();

            
            upKeyBox.Text = configHelper.getValue("up");
            downKeyBox.Text = configHelper.getValue("down");
            leftKeyBox.Text = configHelper.getValue("left");
            rightKeyBox.Text = configHelper.getValue("right");
            specialKeyBox.Text = configHelper.getValue("item");
            slowKeyBox.Text = configHelper.getValue("slow");
            shootKeyBox.Text = configHelper.getValue("shoot");
            resolutionBox.Text = configHelper.getValue("resolution");
            volumeKeyBox.Text = configHelper.getValue("volume");
         
            isFullScreen.Checked = configHelper.getValue("fullScreen") == "1" ? true : false;
            if (resolutionBox.Text.Length == 0) {
                resolutionBox.SelectedText = "1280x720";
            }
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            configHelper.setValue("up", upKeyBox.Text);
            configHelper.setValue("down", downKeyBox.Text);
            configHelper.setValue("left", leftKeyBox.Text);
            configHelper.setValue("right", rightKeyBox.Text);
            configHelper.setValue("item", specialKeyBox.Text);
            configHelper.setValue("slow", slowKeyBox.Text);
            configHelper.setValue("shoot", shootKeyBox.Text);
            configHelper.setValue("resolution", resolutionBox.SelectedItem.ToString());
            configHelper.setValue("volume", volumeKeyBox.Text);

            configHelper.setValue("fullScreen", isFullScreen.Checked ? "1" : "0");
            configHelper.FileSave();
            MessageBox.Show("Successfully saved.","PythonSTG", MessageBoxButtons.OK,MessageBoxIcon.Information);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            configHelper.FileLoad();
        }

        private void keyDownChecker(object sender, KeyEventArgs e)
        {
            try
            {
                TextBox textBox = (TextBox)sender;
                bool haveValue = false;
                if (e.KeyCode == Keys.Up)
                {
                    textBox.Text = "265";
                    haveValue = true;
                }
                else if (e.KeyCode == Keys.Down)
                {
                    textBox.Text = "264";
                    haveValue = true;
                }
                else if (e.KeyCode == Keys.Left)
                {
                    textBox.Text = "263";
                    haveValue = true;
                }
                else if (e.KeyCode == Keys.Right)
                {
                    textBox.Text = "262";
                    haveValue = true;
                }
                else if (e.KeyCode == Keys.ShiftKey)
                {
                    if (Convert.ToBoolean(GetAsyncKeyState(Keys.LShiftKey)))
                        textBox.Text = "340";
                    if (Convert.ToBoolean(GetAsyncKeyState(Keys.RShiftKey)))
                        textBox.Text = "344";
                    haveValue = true;
                }
                if (!haveValue) {
                    textBox.Text = e.KeyValue.ToString();
                }
            }
            catch (InvalidCastException expt) {
                Console.WriteLine(expt.Message);
            }
           
        }
    }
}
