using PythonSTGVisualEditor.SpecialNode;
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
    public partial class FormMain : Form
    {
        public FormMain()
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
            TreeView rScriptContext = scriptContext;
            TreeView treeView = (TreeView)sender;

            TreeNode toolSelectNode = treeView.SelectedNode;
            TreeNode toolSelectParent = treeView.SelectedNode.Parent;
            
            TreeNode scriptSelectNode = rScriptContext.SelectedNode;
            if (toolSelectParent != null) {//No root node
                switch (toolSelectNode.Text) {
                    case "Stage":
                        if (scriptSelectNode != null) {

                            if (scriptSelectNode.Text == scriptContext.Nodes[0].Text)
                            {
                                StageNode newNode = new StageNode();
                                newNode.Name = "Stage";
                                newNode.Text = "Stage 1";
                                scriptSelectNode.Nodes.AddRange(new TreeNode[] {
                                 newNode});
                            }
                            else {
                                MessageBox.Show("只能在Stage Group节点下新建Stage!", "无法在此处添加节点", MessageBoxButtons.OK, MessageBoxIcon.Error);
                            }
                        }
                        else
                        {
                            MessageBox.Show("未选择节点！", "无法在此处添加节点", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        }
                        break;

                    case "Task":
                        FormTask formTask = new FormTask();
                        formTask.Show();
                        break;

                }
   
            }
            
        }
    }
}
