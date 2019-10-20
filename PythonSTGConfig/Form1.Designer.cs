namespace PythonSTGConfig
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormMain));
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.upKeyBox = new System.Windows.Forms.TextBox();
            this.leftKeyBox = new System.Windows.Forms.TextBox();
            this.specialKeyBox = new System.Windows.Forms.TextBox();
            this.downKeyBox = new System.Windows.Forms.TextBox();
            this.rightKeyBox = new System.Windows.Forms.TextBox();
            this.slowKeyBox = new System.Windows.Forms.TextBox();
            this.isFullScreen = new System.Windows.Forms.CheckBox();
            this.isScaleAuto = new System.Windows.Forms.CheckBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.volumeKeyBox = new System.Windows.Forms.TextBox();
            this.shootKeyBox = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(28, 36);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(23, 15);
            this.label1.TabIndex = 0;
            this.label1.Text = "Up";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(223, 36);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(39, 15);
            this.label2.TabIndex = 1;
            this.label2.Text = "Down";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(28, 92);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(39, 15);
            this.label3.TabIndex = 2;
            this.label3.Text = "Left";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(223, 92);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(47, 15);
            this.label4.TabIndex = 3;
            this.label4.Text = "Right";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(28, 149);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(63, 15);
            this.label5.TabIndex = 4;
            this.label5.Text = "Special";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(223, 149);
            this.label6.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(39, 15);
            this.label6.TabIndex = 5;
            this.label6.Text = "Slow";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(28, 211);
            this.label7.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(0, 15);
            this.label7.TabIndex = 6;
            // 
            // upKeyBox
            // 
            this.upKeyBox.Location = new System.Drawing.Point(96, 32);
            this.upKeyBox.Margin = new System.Windows.Forms.Padding(4);
            this.upKeyBox.Name = "upKeyBox";
            this.upKeyBox.Size = new System.Drawing.Size(105, 25);
            this.upKeyBox.TabIndex = 7;
            this.upKeyBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.keyDownChecker);
            // 
            // leftKeyBox
            // 
            this.leftKeyBox.Location = new System.Drawing.Point(96, 92);
            this.leftKeyBox.Margin = new System.Windows.Forms.Padding(4);
            this.leftKeyBox.Name = "leftKeyBox";
            this.leftKeyBox.Size = new System.Drawing.Size(105, 25);
            this.leftKeyBox.TabIndex = 8;
            this.leftKeyBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.keyDownChecker);
            // 
            // specialKeyBox
            // 
            this.specialKeyBox.Location = new System.Drawing.Point(96, 145);
            this.specialKeyBox.Margin = new System.Windows.Forms.Padding(4);
            this.specialKeyBox.Name = "specialKeyBox";
            this.specialKeyBox.Size = new System.Drawing.Size(105, 25);
            this.specialKeyBox.TabIndex = 9;
            this.specialKeyBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.keyDownChecker);
            // 
            // downKeyBox
            // 
            this.downKeyBox.Location = new System.Drawing.Point(293, 32);
            this.downKeyBox.Margin = new System.Windows.Forms.Padding(4);
            this.downKeyBox.Name = "downKeyBox";
            this.downKeyBox.Size = new System.Drawing.Size(105, 25);
            this.downKeyBox.TabIndex = 10;
            this.downKeyBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.keyDownChecker);
            // 
            // rightKeyBox
            // 
            this.rightKeyBox.Location = new System.Drawing.Point(293, 89);
            this.rightKeyBox.Margin = new System.Windows.Forms.Padding(4);
            this.rightKeyBox.Name = "rightKeyBox";
            this.rightKeyBox.Size = new System.Drawing.Size(105, 25);
            this.rightKeyBox.TabIndex = 11;
            this.rightKeyBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.keyDownChecker);
            // 
            // slowKeyBox
            // 
            this.slowKeyBox.Location = new System.Drawing.Point(293, 146);
            this.slowKeyBox.Margin = new System.Windows.Forms.Padding(4);
            this.slowKeyBox.Name = "slowKeyBox";
            this.slowKeyBox.Size = new System.Drawing.Size(105, 25);
            this.slowKeyBox.TabIndex = 12;
            this.slowKeyBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.keyDownChecker);
            // 
            // isFullScreen
            // 
            this.isFullScreen.AutoSize = true;
            this.isFullScreen.Location = new System.Drawing.Point(31, 248);
            this.isFullScreen.Margin = new System.Windows.Forms.Padding(4);
            this.isFullScreen.Name = "isFullScreen";
            this.isFullScreen.Size = new System.Drawing.Size(109, 19);
            this.isFullScreen.TabIndex = 13;
            this.isFullScreen.Text = "FullScreen";
            this.isFullScreen.UseVisualStyleBackColor = true;
            // 
            // isScaleAuto
            // 
            this.isScaleAuto.AutoSize = true;
            this.isScaleAuto.Location = new System.Drawing.Point(226, 248);
            this.isScaleAuto.Margin = new System.Windows.Forms.Padding(4);
            this.isScaleAuto.Name = "isScaleAuto";
            this.isScaleAuto.Size = new System.Drawing.Size(93, 19);
            this.isScaleAuto.TabIndex = 14;
            this.isScaleAuto.Text = "AutoSize";
            this.isScaleAuto.UseVisualStyleBackColor = true;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(132, 289);
            this.button1.Margin = new System.Windows.Forms.Padding(4);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(129, 39);
            this.button1.TabIndex = 15;
            this.button1.Text = "Save";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(269, 289);
            this.button2.Margin = new System.Windows.Forms.Padding(4);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(129, 39);
            this.button2.TabIndex = 16;
            this.button2.Text = "Reset";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // volumeKeyBox
            // 
            this.volumeKeyBox.Location = new System.Drawing.Point(294, 201);
            this.volumeKeyBox.Margin = new System.Windows.Forms.Padding(4);
            this.volumeKeyBox.Name = "volumeKeyBox";
            this.volumeKeyBox.Size = new System.Drawing.Size(105, 25);
            this.volumeKeyBox.TabIndex = 20;
            // 
            // shootKeyBox
            // 
            this.shootKeyBox.Location = new System.Drawing.Point(96, 201);
            this.shootKeyBox.Margin = new System.Windows.Forms.Padding(4);
            this.shootKeyBox.Name = "shootKeyBox";
            this.shootKeyBox.Size = new System.Drawing.Size(105, 25);
            this.shootKeyBox.TabIndex = 19;
            this.shootKeyBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.keyDownChecker);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(223, 204);
            this.label8.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(55, 15);
            this.label8.TabIndex = 18;
            this.label8.Text = "Volume";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(28, 204);
            this.label9.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(47, 15);
            this.label9.TabIndex = 17;
            this.label9.Text = "Shoot";
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(441, 357);
            this.Controls.Add(this.volumeKeyBox);
            this.Controls.Add(this.shootKeyBox);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.isScaleAuto);
            this.Controls.Add(this.isFullScreen);
            this.Controls.Add(this.slowKeyBox);
            this.Controls.Add(this.rightKeyBox);
            this.Controls.Add(this.downKeyBox);
            this.Controls.Add(this.specialKeyBox);
            this.Controls.Add(this.leftKeyBox);
            this.Controls.Add(this.upKeyBox);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.MaximizeBox = false;
            this.Name = "FormMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "PythonSTG Configurator";
            this.Load += new System.EventHandler(this.FormMain_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox upKeyBox;
        private System.Windows.Forms.TextBox leftKeyBox;
        private System.Windows.Forms.TextBox specialKeyBox;
        private System.Windows.Forms.TextBox downKeyBox;
        private System.Windows.Forms.TextBox rightKeyBox;
        private System.Windows.Forms.TextBox slowKeyBox;
        private System.Windows.Forms.CheckBox isFullScreen;
        private System.Windows.Forms.CheckBox isScaleAuto;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.TextBox volumeKeyBox;
        private System.Windows.Forms.TextBox shootKeyBox;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
    }
}

