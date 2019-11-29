using PythonSTGVisualEditor.SpecialNode;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.VisualBasic;
using PythonSTGVisualEditor.Sturcture;
using System.IO;
using System.Diagnostics;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Xml.Serialization;

namespace PythonSTGVisualEditor
{
    public partial class FormMain : Form
    {
        private List<string> stageFuncName = new List<string>();

        public static string fileSavePath = null;
        public static string pystgScriptPath = null;
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

        private void ExitProgramme(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void ToolTree_DoubleClickEvent(object sender, EventArgs e)
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
                                string varName = Interaction.InputBox("输入关卡变量名:", "Input value");
                                string displayName = Interaction.InputBox("输入关卡显示名称:", "Input value");
                                StageNode newNode = new StageNode(varName, displayName);
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
                        if (scriptSelectNode != null && scriptSelectNode is StageNode)
                        {
                            Task task = FormTask.Execute();
                            if (task != null)
                            {
                                TaskNode taskNode = new TaskNode(task);
                                scriptSelectNode.Nodes.AddRange(new TreeNode[] {
                                taskNode});
                            }
                        }
                        else {
                            MessageBox.Show("只能在Stage下添加Task节点！", "无法在此处添加节点", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        }
                        break;
                    case "TaskUnit":
                        if (scriptSelectNode != null && scriptSelectNode is TaskNode)
                        {
                            TaskUnit taskunit = FormTaskUnit.Execute();
                            if (taskunit != null)
                            {
                                TaskUnitNode taskNode = new TaskUnitNode(taskunit);
                                scriptSelectNode.Nodes.AddRange(new TreeNode[] {
                                taskNode});
                            }
                        }
                        else
                        {
                            MessageBox.Show("只能在Task下添加TaskUnit节点！", "无法在此处添加节点", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        }
                        break;
                    case "for":
                        if (scriptSelectNode != null &&  scriptSelectNode is TaskUnitNode )
                        {
                            int count = int.Parse(Interaction.InputBox("输入循环次数:", "Input value", "1"));
                            ForNode forNode = new ForNode(count);
                            scriptSelectNode.Nodes.AddRange(new TreeNode[] {
                                 forNode});
                        }
                        else
                        {
                            MessageBox.Show("只能在TaskUnit下添加For节点！", "无法在此处添加节点", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        }
                        break;
                    default:
                        if (toolSelectParent.Text == "BulletType")
                        {
                            if (scriptSelectNode is TaskUnitNode || scriptSelectNode is ForNode)
                            {
                                Bullet bullet = FormBullet.Execute(toolSelectNode.Text);
                                if (bullet != null) {
                                    BulletNode bulletNode = new BulletNode(bullet);
                                    scriptSelectNode.Nodes.AddRange(new TreeNode[] {
                                    bulletNode});
                                }
                            }
                            else {
                                MessageBox.Show("只能在TaskUnit、For下添加Bullet节点！", "无法在此处添加节点", MessageBoxButtons.OK, MessageBoxIcon.Error);
                            }

                        }
                        break;
                }
            }
            
        }

        private void ScriptTree_DoubleClick(object sender, EventArgs e)
        {
            TreeView scriptContext = (TreeView)sender;
            TreeNode currentNode = scriptContext.SelectedNode;
            if (currentNode != null) {
                if (currentNode is StageNode) {
                    StageNode stageNode = (StageNode)currentNode;
                    string varName = Interaction.InputBox("输入关卡变量名:", "Input value", stageNode.getVarName());
                    string displayName = Interaction.InputBox("输入关卡显示名称:", "Input value", stageNode.getDisplayName());
                    if (varName.Length > 0 && displayName.Length > 0) {
                        stageNode.setNodeInfo(varName, displayName);
                    }
                } else if (currentNode is TaskNode) {
                    TaskNode taskNode = (TaskNode)currentNode;
                    Task newTask = FormTask.Execute(taskNode.storageTask);
                    if (newTask != null) {
                        taskNode.storageTask = newTask;
                        taskNode.updateNodeInfo();
                    }
                }
                else if (currentNode is TaskUnitNode)
                {
                    TaskUnitNode unitNode = (TaskUnitNode)currentNode;
                    TaskUnit newUnit = FormTaskUnit.Execute(unitNode.storageUnit);
                    if (newUnit != null)
                    {
                        unitNode.storageUnit = newUnit;
                        unitNode.updateNodeInfo();
                    }
                }
                else if (currentNode is BulletNode)
                {
                    BulletNode bulletNode = (BulletNode)currentNode;
                    Bullet bullet = FormBullet.Execute(bulletNode.currentBullet);
                    if (bullet != null)
                    {
                        bulletNode.currentBullet = bullet;
                        bulletNode.updateNodeInfo();
                    }
                }
                else if (currentNode is ForNode) {
                    ForNode forNode = (ForNode)currentNode;
                    int count = int.Parse(Interaction.InputBox("输入循环次数:", "Input value", forNode.repeatTime.ToString()));
                    forNode.repeatTime = count;
                    forNode.updateNodeInfo();
                }
            }
        }

        private void nodeMoveUp_Click(object sender, EventArgs e)
        {
            TreeView rScriptContext = scriptContext;
            TreeNode currentNode = rScriptContext.SelectedNode;
            if (currentNode != null && currentNode.Parent != null) {
                TreeNode parentNode = currentNode.Parent;
                int index = parentNode.Nodes.IndexOf(currentNode);
                if (index > 0) {
                    parentNode.Nodes.Remove(currentNode);
                    parentNode.Nodes.Insert(--index, currentNode);
                }
            }
        }

        private void nodeMoveDown_Click(object sender, EventArgs e)
        {
            TreeView rScriptContext = scriptContext;
            TreeNode currentNode = rScriptContext.SelectedNode;
            if (currentNode != null && currentNode.Parent != null)
            {
                TreeNode parentNode = currentNode.Parent;
                int index = currentNode.Parent.Nodes.IndexOf(currentNode);
                if (index + 1 < parentNode.GetNodeCount(true))
                {
                    parentNode.Nodes.Remove(currentNode);
                    parentNode.Nodes.Insert(++index, currentNode);
                }
            }
        }

        private void copy(object sender, EventArgs e)
        {

        }

        private string generatePythonScript(int tabCount)
        {
            string pythonScript = "";
            stageFuncName.Clear();

            TreeView ScriptContext = scriptContext;
            TreeNode treeNode = ScriptContext.TopNode;
            if (treeNode!=null) {
                foreach (TreeNode node in treeNode.Nodes) {
                    if (node is StageNode) {
                        StageNode stageNode = (StageNode)node;
                        if (tabCount == 0)
                        {
                            pythonScript += stageNode.getFuncInitScript();
                        }
                        else {
                            pythonScript += FormatHelper.getFormatScript(stageNode.getFuncInitScript(), tabCount - 1);
                        }
                        stageFuncName.Add(stageNode.getSetupFuncName());
                        pythonScript += FormatHelper.getFormatScript(stageNode.getInitScript(), tabCount);

                        foreach (TreeNode taskNodeTemp in stageNode.Nodes)
                        {
                            if (taskNodeTemp is TaskNode)
                            {
                                TaskNode taskNode = (TaskNode)taskNodeTemp;
                                pythonScript += FormatHelper.getFormatScript(taskNode.storageTask.GetInitScript(), tabCount);

                                foreach (TreeNode unitNodeTemp in taskNode.Nodes)
                                {
                                    if (unitNodeTemp is TaskUnitNode) {
                                        TaskUnitNode taskUnitNode = (TaskUnitNode)unitNodeTemp;
                                        pythonScript += FormatHelper.getFormatScript(taskUnitNode.storageUnit.GetInitScript(), tabCount);

                                        foreach (TreeNode bulletNodeTemp in unitNodeTemp.Nodes)
                                        {
                                            if (bulletNodeTemp is BulletNode)
                                            {
                                                BulletNode bulletNode = (BulletNode)bulletNodeTemp;
                                                pythonScript += FormatHelper.getFormatScript(bulletNode.currentBullet.GetInitScript(), tabCount);
                                                pythonScript += FormatHelper.getFormatScript(taskUnitNode.storageUnit.GetAddBulletScript(bulletNode.currentBullet.bulletVarName), tabCount);
                                            }
                                            else if (bulletNodeTemp is ForNode)
                                            {
                                                ForNode forNode = (ForNode)bulletNodeTemp;
                                                pythonScript += FormatHelper.getFormatScript(forNode.getInitScript(), tabCount);
                                                foreach (TreeNode forbulletNodeTemp in forNode.Nodes)
                                                {
                                                    if (forbulletNodeTemp is BulletNode)
                                                    {
                                                        BulletNode forbulletNode = (BulletNode)forbulletNodeTemp;
                                                        pythonScript += FormatHelper.getFormatScript(forbulletNode.currentBullet.GetInitScript(), tabCount + 1);
                                                        pythonScript += FormatHelper.getFormatScript(taskUnitNode.storageUnit.GetAddBulletScript(forbulletNode.currentBullet.bulletVarName), tabCount + 1);
                                                    }
                                                }
                                            }
                                        }
                                        pythonScript += FormatHelper.getFormatScript(taskNode.storageTask.GetAddUnitScript(taskUnitNode.storageUnit.unitVarName), tabCount); ;
                                    } 
                                }
                                pythonScript += FormatHelper.getFormatScript(stageNode.getAddTaskScript(taskNode.storageTask.taskVarName), tabCount);
                            }
                           
                        }
                        pythonScript += FormatHelper.getFormatScript(stageNode.getFuncEndInitScript(), tabCount);
                    }
                }
            }
            return pythonScript;
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Multiselect = false;
            dialog.Title = "选择文件";
            dialog.Filter = "PythonSTG工程文件(*.pstgproj)|*.pstgproj";
            if (dialog.ShowDialog() == DialogResult.OK) {
                if (dialog.FileName != null) {
                    fileSavePath = dialog.FileName;


                    IFormatter formatter = new BinaryFormatter();
                    Stream stream = new FileStream(fileSavePath, FileMode.Open, FileAccess.Read, FileShare.None);

                    TreeView ScriptContext = scriptContext;
                  

                    //scriptContext.Nodes.Add(stageNode);

                    stream.Close();
                }
            }

        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FormAbout formAbout = new FormAbout();
            formAbout.Show();
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (fileSavePath == null)
            {
                SaveFileDialog saveFileDialog = new SaveFileDialog();
                saveFileDialog.Filter = "PythonSTG工程文件(*.pstgproj)|*.pstgproj";
                saveFileDialog.Title = "保存文件";
                if (saveFileDialog.ShowDialog() == DialogResult.OK)
                {
                    fileSavePath = saveFileDialog.FileName;
                    Console.WriteLine(fileSavePath);
                }
            }

            if (fileSavePath != null)
            {
                
                Stream stream = new FileStream(fileSavePath, FileMode.Create, FileAccess.Write, FileShare.None);

                TreeView ScriptContext = scriptContext;
                TreeNode treeNode = ScriptContext.TopNode;
                if (treeNode != null)
                {
                    foreach (TreeNode node in treeNode.Nodes)
                    {
                        if (node is StageNode)
                        {
                            XmlSerializer stageFormatter = new XmlSerializer(typeof(Stage));
                            StageNode stageNode = (StageNode)node;
                            stageFormatter.Serialize(stream, stageNode.storageStage);
                            foreach (TreeNode taskNodeTemp in stageNode.Nodes)
                            {
                                if (taskNodeTemp is TaskNode)
                                {
                                    XmlSerializer taskFormatter = new XmlSerializer(typeof(Task));
                                    TaskNode taskNode = (TaskNode)taskNodeTemp;
                                    taskFormatter.Serialize(stream, taskNode.storageTask);
                                    foreach (TreeNode unitNodeTemp in taskNode.Nodes)
                                    {
                                        if (unitNodeTemp is TaskUnitNode)
                                        {
                                            XmlSerializer unitFormatter = new XmlSerializer(typeof(TaskUnit));
                                            TaskUnitNode taskUnitNode = (TaskUnitNode)unitNodeTemp;
                                            unitFormatter.Serialize(stream, taskUnitNode.storageUnit);
                                            foreach (TreeNode bulletNodeTemp in unitNodeTemp.Nodes)
                                            {
                                                if (bulletNodeTemp is BulletNode)
                                                {
                                                    XmlSerializer bulletFormatter = new XmlSerializer(typeof(Bullet));
                                                    BulletNode bulletNode = (BulletNode)bulletNodeTemp;
                                                    bulletFormatter.Serialize(stream, bulletNode.currentBullet);
                                                }
                                            }
                                        }
                                    }
                                }

                            }
                        }
                    }
                }
                stream.Close();
            }
        }

        private void runToolStripMenuItem_Click(object sender, EventArgs e)
        {
            generatePythonToolStripMenuItem_Click(sender, e);
            if (pystgScriptPath != null)
            {
                Process p = new Process();
                p.StartInfo.FileName = "cmd.exe";
                p.StartInfo.UseShellExecute = false;
                p.StartInfo.RedirectStandardInput = true;
                p.StartInfo.RedirectStandardOutput = true;
                p.StartInfo.RedirectStandardError = true;
                p.StartInfo.CreateNoWindow = true;
                p.Start();

                p.StandardInput.WriteLine("cd /d " + pystgScriptPath.Replace("script", ""));
                p.StandardInput.WriteLine("PythonSTG.exe");
                p.StandardInput.AutoFlush = true;
                p.Close();
            }
        }

        private void generatePythonToolStripMenuItem_Click(object sender, EventArgs e)
        {
            
            if (pystgScriptPath == null)
            {
                FolderBrowserDialog dialog = new FolderBrowserDialog();
                dialog.Description = "选择PythonSTG下的Script文件夹";
                if (dialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    if (!string.IsNullOrEmpty(dialog.SelectedPath) && dialog.SelectedPath.IndexOf("script") != -1)
                    {
                        pystgScriptPath = dialog.SelectedPath;
                        Console.WriteLine(pystgScriptPath);
                    }
                    else
                    {
                        MessageBox.Show("请选择PythonSTG下的Script文件夹！", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
            }

            if (pystgScriptPath != null)
            {
                string pythonScript = generatePythonScript(0);
                try
                {
                    FileStream fileStream = new FileStream(pystgScriptPath + "/CustomStage.py", FileMode.Create);
                    StreamWriter sr = new StreamWriter(fileStream, Encoding.Default);
                    string info = "import random\r\n" +
                    "from .Bullet.Bullet import BulletColor\r\n" +
                    "from .Bullet.CircleBullet import CircleBullet\r\n" +
                    "from .Bullet.HugeBullet import HugeBullet\r\n" +
                    "from .Bullet.RiceBullet import RiceBullet\r\n" +
                    "from .Bullet.OvalBullet import OvalBullet\r\n" +
                    "from .Bullet.CardBullet import CardBullet\r\n" +
                    "from .Stage.Task import Task, TaskUnit\r\n" +
                    "from .Stage.Enemy.FairyEnemy import FairyEnemy, EnemyColor, DropItem\r\n" +
                    "from .Stage.Enemy.DarkButterflyFairy import DarkButterflyFairyEnemy\r\n" +
                    "from .Stage.XCStage import XCStage, StageRank, StageBackGround\r\n" +
                    "from .Stage.Boss import Boss, SpellCard\r\n";

                    sr.WriteLine(info);
                    sr.WriteLine(pythonScript);

                    sr.Close();
                    fileStream.Close();


                  }
                  catch (Exception expt) {
                       MessageBox.Show(expt.ToString(), "无法保存脚本文件CustomStage.py", MessageBoxButtons.OK, MessageBoxIcon.Error);
                  }

                try
                   {
                    StreamReader coreReader = new StreamReader(pystgScriptPath + "/XCCore.py", Encoding.Default);
                    string line, coreinfo = "";

                    
                    while ((line = coreReader.ReadLine()) != null)
                    {
                        coreinfo += line + "\r\n";
                    }
                    
                    coreReader.Close();
                    
                    const string importStart = "# [PySTG-VE IMPORT Start]\r\n";// importEnd = "# [PySTG-VE IMPORT End]\r\n";
                    string insertStr = "import script.CustomStage as CustomStage\r\n";

                    if (coreinfo.IndexOf(insertStr) == -1) {
                        int importStartIndex = coreinfo.IndexOf(importStart);
                        coreinfo = coreinfo.Insert(importStartIndex + importStart.Length, insertStr);
                        Console.WriteLine(coreinfo);
                    }

                    const string initStart = "# [PySTG-VE STAGE Start]\r\n";// initEnd = "# [PySTG-VE STAGE End]\r\n";
                    string insertStageStr = "";
                    bool needInset = false;

                    int stageStartIndex = coreinfo.IndexOf(initStart);
                    for(int i= 0; i < stageFuncName.Count; i++) {
                        string insertStage = string.Format("    {0}=CustomStage.{1}()\r\n    XCInit.addStageItem({0})\r\n", "PYSTGVECustomStage" + i, stageFuncName[i]);
                        if (coreinfo.IndexOf(insertStage) == -1) {
                            insertStageStr += insertStage;
                            needInset = true;
                        }
                    }
                    if (needInset) {
                        coreinfo = coreinfo.Insert(stageStartIndex + initStart.Length, insertStageStr);
                    }

                    FileStream writeStream = new FileStream(pystgScriptPath + "//XCCore.py", FileMode.Create);
                    StreamWriter coreWriter = new StreamWriter(writeStream, Encoding.Default);
                    coreWriter.WriteLine(coreinfo);
                    coreWriter.Close();
                }
                catch (Exception expt) {
                    MessageBox.Show(expt.ToString(), "无法修改脚本文件XCCore.py", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                MessageBox.Show("Python脚本导出完成", "导出完成",MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void scriptContext_Click(object sender, EventArgs e)
        {
            AttributeView.Nodes.Clear();
            TreeView scriptView = (TreeView)sender;
            TreeNode currentNode = scriptView.SelectedNode;
            if (currentNode != null) {
                if (currentNode is StageNode)
                {
                   
                }
                else if (currentNode is TaskNode)
                {
              
                }
                else if (currentNode is TaskUnitNode)
                {
                 
                }
                else if (currentNode is BulletNode)
                {
                 
                }
            }
        }
    }
}
