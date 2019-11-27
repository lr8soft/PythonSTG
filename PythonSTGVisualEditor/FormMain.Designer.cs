using System;

namespace PythonSTGVisualEditor
{
    partial class FormMain
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.TreeNode treeNode1 = new System.Windows.Forms.TreeNode("Stage");
            System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("StageType", new System.Windows.Forms.TreeNode[] {
            treeNode1});
            System.Windows.Forms.TreeNode treeNode3 = new System.Windows.Forms.TreeNode("Task");
            System.Windows.Forms.TreeNode treeNode4 = new System.Windows.Forms.TreeNode("TaskUnit");
            System.Windows.Forms.TreeNode treeNode5 = new System.Windows.Forms.TreeNode("TaskType", new System.Windows.Forms.TreeNode[] {
            treeNode3,
            treeNode4});
            System.Windows.Forms.TreeNode treeNode6 = new System.Windows.Forms.TreeNode("CircleBullet");
            System.Windows.Forms.TreeNode treeNode7 = new System.Windows.Forms.TreeNode("OvalBullet");
            System.Windows.Forms.TreeNode treeNode8 = new System.Windows.Forms.TreeNode("RiceBullet");
            System.Windows.Forms.TreeNode treeNode9 = new System.Windows.Forms.TreeNode("CardBullet");
            System.Windows.Forms.TreeNode treeNode10 = new System.Windows.Forms.TreeNode("HugeBullet");
            System.Windows.Forms.TreeNode treeNode11 = new System.Windows.Forms.TreeNode("BulletType", new System.Windows.Forms.TreeNode[] {
            treeNode6,
            treeNode7,
            treeNode8,
            treeNode9,
            treeNode10});
            System.Windows.Forms.TreeNode treeNode12 = new System.Windows.Forms.TreeNode("FairyEnemy");
            System.Windows.Forms.TreeNode treeNode13 = new System.Windows.Forms.TreeNode("ButterflyFairyEnemy");
            System.Windows.Forms.TreeNode treeNode14 = new System.Windows.Forms.TreeNode("EnemyType", new System.Windows.Forms.TreeNode[] {
            treeNode12,
            treeNode13});
            System.Windows.Forms.TreeNode treeNode15 = new System.Windows.Forms.TreeNode("for语句");
            System.Windows.Forms.TreeNode treeNode16 = new System.Windows.Forms.TreeNode("LogicalStruct", new System.Windows.Forms.TreeNode[] {
            treeNode15});
            System.Windows.Forms.TreeNode treeNode17 = new System.Windows.Forms.TreeNode("Stage Group");
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormMain));
            this.menuGroup = new System.Windows.Forms.MenuStrip();
            this.fileToolMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.editToolMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.cancelToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.redoRToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
            this.cutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.copyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pasteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.deleteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.testToolMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.runToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.runConsoleToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.buildToolMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.generatePythonToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.updateToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mainContainer = new System.Windows.Forms.SplitContainer();
            this.toolContainer = new System.Windows.Forms.SplitContainer();
            this.ComponentTree = new System.Windows.Forms.TreeView();
            this.AttributeBox = new System.Windows.Forms.GroupBox();
            this.AttributeList = new System.Windows.Forms.ListView();
            this.scriptContext = new System.Windows.Forms.TreeView();
            this.nodeRightClickMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.nodeMoveUp = new System.Windows.Forms.ToolStripMenuItem();
            this.nodeMoveDown = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripSeparator();
            this.cutRToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.copyRToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.pasteRToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.menuGroup.SuspendLayout();
            this.mainContainer.Panel1.SuspendLayout();
            this.mainContainer.Panel2.SuspendLayout();
            this.mainContainer.SuspendLayout();
            this.toolContainer.Panel1.SuspendLayout();
            this.toolContainer.Panel2.SuspendLayout();
            this.toolContainer.SuspendLayout();
            this.AttributeBox.SuspendLayout();
            this.nodeRightClickMenu.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuGroup
            // 
            this.menuGroup.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.menuGroup.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuGroup.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolMenu,
            this.editToolMenu,
            this.testToolMenu,
            this.buildToolMenu,
            this.helpToolMenu});
            this.menuGroup.Location = new System.Drawing.Point(0, 0);
            this.menuGroup.Name = "menuGroup";
            this.menuGroup.Padding = new System.Windows.Forms.Padding(7, 3, 0, 3);
            this.menuGroup.Size = new System.Drawing.Size(873, 30);
            this.menuGroup.TabIndex = 1;
            this.menuGroup.Text = "menuStrip1";
            // 
            // fileToolMenu
            // 
            this.fileToolMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.saveAsToolStripMenuItem,
            this.toolStripMenuItem1,
            this.exitToolStripMenuItem});
            this.fileToolMenu.Name = "fileToolMenu";
            this.fileToolMenu.Size = new System.Drawing.Size(69, 24);
            this.fileToolMenu.Text = "文件(&F)";
            this.fileToolMenu.Click += new System.EventHandler(this.fileFToolStripMenuItem_Click);
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.openToolStripMenuItem.Text = "打开(&O)";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.saveToolStripMenuItem.Text = "保存(&S)";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // saveAsToolStripMenuItem
            // 
            this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
            this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.saveAsToolStripMenuItem.Text = "另存为(&A)";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(213, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.exitToolStripMenuItem.Text = "退出(&X)";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.ExitProgramme);
            // 
            // editToolMenu
            // 
            this.editToolMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.cancelToolStripMenuItem,
            this.redoRToolStripMenuItem,
            this.toolStripMenuItem2,
            this.cutToolStripMenuItem,
            this.copyToolStripMenuItem,
            this.pasteToolStripMenuItem,
            this.deleteToolStripMenuItem});
            this.editToolMenu.Name = "editToolMenu";
            this.editToolMenu.Size = new System.Drawing.Size(69, 24);
            this.editToolMenu.Text = "编辑(&E)";
            // 
            // cancelToolStripMenuItem
            // 
            this.cancelToolStripMenuItem.Name = "cancelToolStripMenuItem";
            this.cancelToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.cancelToolStripMenuItem.Text = "撤销(&U)";
            // 
            // redoRToolStripMenuItem
            // 
            this.redoRToolStripMenuItem.Name = "redoRToolStripMenuItem";
            this.redoRToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.redoRToolStripMenuItem.Text = "重做(&R)";
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(213, 6);
            // 
            // cutToolStripMenuItem
            // 
            this.cutToolStripMenuItem.Name = "cutToolStripMenuItem";
            this.cutToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.cutToolStripMenuItem.Text = "剪切(&T)";
            // 
            // copyToolStripMenuItem
            // 
            this.copyToolStripMenuItem.Name = "copyToolStripMenuItem";
            this.copyToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.copyToolStripMenuItem.Text = "复制(&C)";
            this.copyToolStripMenuItem.Click += new System.EventHandler(this.copy);
            // 
            // pasteToolStripMenuItem
            // 
            this.pasteToolStripMenuItem.Name = "pasteToolStripMenuItem";
            this.pasteToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.pasteToolStripMenuItem.Text = "粘贴(&P)";
            // 
            // deleteToolStripMenuItem
            // 
            this.deleteToolStripMenuItem.Name = "deleteToolStripMenuItem";
            this.deleteToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.deleteToolStripMenuItem.Text = "删除(&D)";
            // 
            // testToolMenu
            // 
            this.testToolMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.runToolStripMenuItem,
            this.runConsoleToolStripMenuItem});
            this.testToolMenu.Name = "testToolMenu";
            this.testToolMenu.Size = new System.Drawing.Size(70, 24);
            this.testToolMenu.Text = "测试(&S)";
            // 
            // runToolStripMenuItem
            // 
            this.runToolStripMenuItem.Name = "runToolStripMenuItem";
            this.runToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.runToolStripMenuItem.Text = "运行(&R)";
            this.runToolStripMenuItem.Click += new System.EventHandler(this.runToolStripMenuItem_Click);
            // 
            // runConsoleToolStripMenuItem
            // 
            this.runConsoleToolStripMenuItem.Name = "runConsoleToolStripMenuItem";
            this.runConsoleToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.runConsoleToolStripMenuItem.Text = "带控制台运行(&C)";
            // 
            // buildToolMenu
            // 
            this.buildToolMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.generatePythonToolStripMenuItem});
            this.buildToolMenu.Name = "buildToolMenu";
            this.buildToolMenu.Size = new System.Drawing.Size(70, 24);
            this.buildToolMenu.Text = "生成(&B)";
            // 
            // generatePythonToolStripMenuItem
            // 
            this.generatePythonToolStripMenuItem.Name = "generatePythonToolStripMenuItem";
            this.generatePythonToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.generatePythonToolStripMenuItem.Text = "生成Python脚本(&G)";
            this.generatePythonToolStripMenuItem.Click += new System.EventHandler(this.generatePythonToolStripMenuItem_Click);
            // 
            // helpToolMenu
            // 
            this.helpToolMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.updateToolStripMenuItem,
            this.aboutToolStripMenuItem});
            this.helpToolMenu.Name = "helpToolMenu";
            this.helpToolMenu.Size = new System.Drawing.Size(73, 24);
            this.helpToolMenu.Text = "帮助(&H)";
            // 
            // updateToolStripMenuItem
            // 
            this.updateToolStripMenuItem.Name = "updateToolStripMenuItem";
            this.updateToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.updateToolStripMenuItem.Text = "检查更新(&U)";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.aboutToolStripMenuItem.Text = "关于(&A)";
            this.aboutToolStripMenuItem.Click += new System.EventHandler(this.aboutToolStripMenuItem_Click);
            // 
            // mainContainer
            // 
            this.mainContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainContainer.Location = new System.Drawing.Point(0, 30);
            this.mainContainer.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.mainContainer.Name = "mainContainer";
            // 
            // mainContainer.Panel1
            // 
            this.mainContainer.Panel1.Controls.Add(this.toolContainer);
            // 
            // mainContainer.Panel2
            // 
            this.mainContainer.Panel2.Controls.Add(this.scriptContext);
            this.mainContainer.Size = new System.Drawing.Size(873, 532);
            this.mainContainer.SplitterDistance = 209;
            this.mainContainer.TabIndex = 2;
            // 
            // toolContainer
            // 
            this.toolContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.toolContainer.Location = new System.Drawing.Point(0, 0);
            this.toolContainer.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.toolContainer.Name = "toolContainer";
            this.toolContainer.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // toolContainer.Panel1
            // 
            this.toolContainer.Panel1.Controls.Add(this.ComponentTree);
            // 
            // toolContainer.Panel2
            // 
            this.toolContainer.Panel2.Controls.Add(this.AttributeBox);
            this.toolContainer.Size = new System.Drawing.Size(209, 532);
            this.toolContainer.SplitterDistance = 281;
            this.toolContainer.SplitterWidth = 5;
            this.toolContainer.TabIndex = 0;
            // 
            // ComponentTree
            // 
            this.ComponentTree.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ComponentTree.HideSelection = false;
            this.ComponentTree.Location = new System.Drawing.Point(0, 0);
            this.ComponentTree.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.ComponentTree.Name = "ComponentTree";
            treeNode1.Name = "StageNode";
            treeNode1.Text = "Stage";
            treeNode2.Name = "StageRoot";
            treeNode2.Text = "StageType";
            treeNode3.Name = "TaskNode";
            treeNode3.Text = "Task";
            treeNode4.Name = "TaskUnitNode";
            treeNode4.Text = "TaskUnit";
            treeNode5.Name = "TaskRoot";
            treeNode5.Text = "TaskType";
            treeNode6.Name = "CircleBulletNode";
            treeNode6.Text = "CircleBullet";
            treeNode7.Name = "OvalBulletNode";
            treeNode7.Text = "OvalBullet";
            treeNode8.Name = "RiceBulletNode";
            treeNode8.Text = "RiceBullet";
            treeNode9.Name = "CardBulletNode";
            treeNode9.Text = "CardBullet";
            treeNode10.Name = "HugeBulletNode";
            treeNode10.Text = "HugeBullet";
            treeNode11.Name = "BulletNodeRoot";
            treeNode11.Text = "BulletType";
            treeNode12.Name = "FairyEnemyNode";
            treeNode12.Text = "FairyEnemy";
            treeNode13.Name = "ButterflyFairyEnemyNode";
            treeNode13.Text = "ButterflyFairyEnemy";
            treeNode14.Name = "EnemyTypeRoot";
            treeNode14.Text = "EnemyType";
            treeNode15.Name = "forNode";
            treeNode15.Text = "for语句";
            treeNode16.Name = "LogicalStructRoot";
            treeNode16.Text = "LogicalStruct";
            this.ComponentTree.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode2,
            treeNode5,
            treeNode11,
            treeNode14,
            treeNode16});
            this.ComponentTree.Size = new System.Drawing.Size(209, 281);
            this.ComponentTree.TabIndex = 0;
            this.ComponentTree.DoubleClick += new System.EventHandler(this.ToolTree_DoubleClickEvent);
            // 
            // AttributeBox
            // 
            this.AttributeBox.Controls.Add(this.AttributeList);
            this.AttributeBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.AttributeBox.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.AttributeBox.Location = new System.Drawing.Point(0, 0);
            this.AttributeBox.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.AttributeBox.Name = "AttributeBox";
            this.AttributeBox.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.AttributeBox.Size = new System.Drawing.Size(209, 246);
            this.AttributeBox.TabIndex = 0;
            this.AttributeBox.TabStop = false;
            this.AttributeBox.Text = "属性";
            // 
            // AttributeList
            // 
            this.AttributeList.Dock = System.Windows.Forms.DockStyle.Fill;
            this.AttributeList.HideSelection = false;
            this.AttributeList.Location = new System.Drawing.Point(3, 24);
            this.AttributeList.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.AttributeList.Name = "AttributeList";
            this.AttributeList.Size = new System.Drawing.Size(203, 218);
            this.AttributeList.TabIndex = 0;
            this.AttributeList.UseCompatibleStateImageBehavior = false;
            // 
            // scriptContext
            // 
            this.scriptContext.ContextMenuStrip = this.nodeRightClickMenu;
            this.scriptContext.Dock = System.Windows.Forms.DockStyle.Fill;
            this.scriptContext.HideSelection = false;
            this.scriptContext.Location = new System.Drawing.Point(0, 0);
            this.scriptContext.Margin = new System.Windows.Forms.Padding(34, 40, 34, 40);
            this.scriptContext.Name = "scriptContext";
            treeNode17.Name = "StageGroupRoot";
            treeNode17.Text = "Stage Group";
            this.scriptContext.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode17});
            this.scriptContext.Size = new System.Drawing.Size(660, 532);
            this.scriptContext.TabIndex = 0;
            this.scriptContext.DoubleClick += new System.EventHandler(this.ScriptTree_DoubleClick);
            // 
            // nodeRightClickMenu
            // 
            this.nodeRightClickMenu.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.nodeRightClickMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.nodeMoveUp,
            this.nodeMoveDown,
            this.toolStripMenuItem3,
            this.cutRToolStripMenuItem,
            this.copyRToolStripMenuItem1,
            this.pasteRToolStripMenuItem1});
            this.nodeRightClickMenu.Name = "nodeRightClickMenu";
            this.nodeRightClickMenu.Size = new System.Drawing.Size(130, 130);
            // 
            // nodeMoveUp
            // 
            this.nodeMoveUp.Name = "nodeMoveUp";
            this.nodeMoveUp.Size = new System.Drawing.Size(129, 24);
            this.nodeMoveUp.Text = "上移(&U)";
            this.nodeMoveUp.Click += new System.EventHandler(this.nodeMoveUp_Click);
            // 
            // nodeMoveDown
            // 
            this.nodeMoveDown.Name = "nodeMoveDown";
            this.nodeMoveDown.Size = new System.Drawing.Size(129, 24);
            this.nodeMoveDown.Text = "下移(&D)";
            this.nodeMoveDown.Click += new System.EventHandler(this.nodeMoveDown_Click);
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.Size = new System.Drawing.Size(126, 6);
            // 
            // cutRToolStripMenuItem
            // 
            this.cutRToolStripMenuItem.Name = "cutRToolStripMenuItem";
            this.cutRToolStripMenuItem.Size = new System.Drawing.Size(129, 24);
            this.cutRToolStripMenuItem.Text = "剪切(&T)";
            // 
            // copyRToolStripMenuItem1
            // 
            this.copyRToolStripMenuItem1.Name = "copyRToolStripMenuItem1";
            this.copyRToolStripMenuItem1.Size = new System.Drawing.Size(129, 24);
            this.copyRToolStripMenuItem1.Text = "复制(&C)";
            // 
            // pasteRToolStripMenuItem1
            // 
            this.pasteRToolStripMenuItem1.Name = "pasteRToolStripMenuItem1";
            this.pasteRToolStripMenuItem1.Size = new System.Drawing.Size(129, 24);
            this.pasteRToolStripMenuItem1.Text = "粘贴(&P)";
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(873, 562);
            this.Controls.Add(this.mainContainer);
            this.Controls.Add(this.menuGroup);
            this.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuGroup;
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.Name = "FormMain";
            this.Text = "PythonSTG VisualEditor";
            this.menuGroup.ResumeLayout(false);
            this.menuGroup.PerformLayout();
            this.mainContainer.Panel1.ResumeLayout(false);
            this.mainContainer.Panel2.ResumeLayout(false);
            this.mainContainer.ResumeLayout(false);
            this.toolContainer.Panel1.ResumeLayout(false);
            this.toolContainer.Panel2.ResumeLayout(false);
            this.toolContainer.ResumeLayout(false);
            this.AttributeBox.ResumeLayout(false);
            this.nodeRightClickMenu.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.MenuStrip menuGroup;
        private System.Windows.Forms.ToolStripMenuItem fileToolMenu;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem editToolMenu;
        private System.Windows.Forms.ToolStripMenuItem testToolMenu;
        private System.Windows.Forms.ToolStripMenuItem helpToolMenu;
        private System.Windows.Forms.ToolStripMenuItem cancelToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem redoRToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem cutToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem copyToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem pasteToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem deleteToolStripMenuItem;
        private System.Windows.Forms.SplitContainer mainContainer;
        private System.Windows.Forms.TreeView scriptContext;
        private System.Windows.Forms.SplitContainer toolContainer;
        private System.Windows.Forms.GroupBox AttributeBox;
        private System.Windows.Forms.TreeView ComponentTree;
        private System.Windows.Forms.ListView AttributeList;
        private System.Windows.Forms.ToolStripMenuItem runToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem runConsoleToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem updateToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem buildToolMenu;
        private System.Windows.Forms.ToolStripMenuItem generatePythonToolStripMenuItem;
        private System.Windows.Forms.ContextMenuStrip nodeRightClickMenu;
        private System.Windows.Forms.ToolStripMenuItem nodeMoveUp;
        private System.Windows.Forms.ToolStripMenuItem nodeMoveDown;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem3;
        private System.Windows.Forms.ToolStripMenuItem cutRToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem copyRToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem pasteRToolStripMenuItem1;
    }
}

