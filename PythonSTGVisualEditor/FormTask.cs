using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.VisualBasic;

namespace PythonSTGVisualEditor
{
    public partial class FormTask : Form
    {
        private Task currentTask;
        public FormTask()
        {
            InitializeComponent();

            currentTask = new Task();
        }

        private void TaskAttributeTree_DoubleClick(object sender, EventArgs e)
        {
            TreeView treeView = (TreeView)sender;
            TreeNode node = treeView.SelectedNode;
            if (node.Parent != null)
            {
                string currentValue = node.Text;
                string value = Interaction.InputBox("输入值:","Input value", currentValue);
                if (value.Length > 0) {
                    node.Text = value;
                }
            }
        }

        public Task GetTask() {
            return currentTask;
        }
    }
}
