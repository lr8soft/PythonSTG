using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace PythonSTGVisualEditor
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void fileFToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void toolStripStatusLabel1_Click(object sender, EventArgs e)
        {

        }

        private void splitContainer1_Panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void 退出XToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void ComponentTree_DoubleClick(object sender, EventArgs e)
        {
            TreeView treeView = (TreeView)sender;
            TreeNode node = treeView.SelectedNode;
            if (node.Parent != null) {//No root node
                Console.WriteLine(node.Text);
   
            }
            
        }
    }
}
