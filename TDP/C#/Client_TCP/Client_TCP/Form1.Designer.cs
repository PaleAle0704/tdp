namespace Client_TCP
{
    partial class Form1
    {
        /// <summary>
        /// Variabile di progettazione necessaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Liberare le risorse in uso.
        /// </summary>
        /// <param name="disposing">ha valore true se le risorse gestite devono essere eliminate, false in caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Codice generato da Progettazione Windows Form

        /// <summary>
        /// Metodo necessario per il supporto della finestra di progettazione. Non modificare
        /// il contenuto del metodo con l'editor di codice.
        /// </summary>
        private void InitializeComponent()
        {
            this.gpbConnessione = new System.Windows.Forms.GroupBox();
            this.btnConnetti = new System.Windows.Forms.Button();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.txtIp = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.txtNome = new System.Windows.Forms.Label();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.gpbMessaggio = new System.Windows.Forms.GroupBox();
            this.btnInvia = new System.Windows.Forms.Button();
            this.txtMessaggio = new System.Windows.Forms.TextBox();
            this.btnEsci = new System.Windows.Forms.Button();
            this.txtPort = new System.Windows.Forms.TextBox();
            this.gpbConnessione.SuspendLayout();
            this.gpbMessaggio.SuspendLayout();
            this.SuspendLayout();
            // 
            // gpbConnessione
            // 
            this.gpbConnessione.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.gpbConnessione.Controls.Add(this.txtPort);
            this.gpbConnessione.Controls.Add(this.btnConnetti);
            this.gpbConnessione.Controls.Add(this.textBox2);
            this.gpbConnessione.Controls.Add(this.txtIp);
            this.gpbConnessione.Controls.Add(this.textBox1);
            this.gpbConnessione.Controls.Add(this.txtNome);
            this.gpbConnessione.Location = new System.Drawing.Point(12, 12);
            this.gpbConnessione.Name = "gpbConnessione";
            this.gpbConnessione.Size = new System.Drawing.Size(326, 91);
            this.gpbConnessione.TabIndex = 0;
            this.gpbConnessione.TabStop = false;
            this.gpbConnessione.Text = "groupBox1";
            // 
            // btnConnetti
            // 
            this.btnConnetti.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.btnConnetti.Location = new System.Drawing.Point(255, 27);
            this.btnConnetti.Name = "btnConnetti";
            this.btnConnetti.Size = new System.Drawing.Size(65, 48);
            this.btnConnetti.TabIndex = 4;
            this.btnConnetti.Text = "Connetti";
            this.btnConnetti.UseVisualStyleBackColor = true;
            this.btnConnetti.Click += new System.EventHandler(this.btnConnetti_Click);
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(121, 55);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(82, 20);
            this.textBox2.TabIndex = 3;
            // 
            // txtIp
            // 
            this.txtIp.AutoSize = true;
            this.txtIp.Location = new System.Drawing.Point(6, 58);
            this.txtIp.Name = "txtIp";
            this.txtIp.Size = new System.Drawing.Size(109, 13);
            this.txtIp.TabIndex = 2;
            this.txtIp.Text = "Indirizzo Ip del server:";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(121, 29);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(128, 20);
            this.textBox1.TabIndex = 1;
            // 
            // txtNome
            // 
            this.txtNome.AutoSize = true;
            this.txtNome.Location = new System.Drawing.Point(6, 32);
            this.txtNome.Name = "txtNome";
            this.txtNome.Size = new System.Drawing.Size(71, 13);
            this.txtNome.TabIndex = 0;
            this.txtNome.Text = "Nome utente:";
            // 
            // textBox3
            // 
            this.textBox3.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.textBox3.Location = new System.Drawing.Point(12, 109);
            this.textBox3.Multiline = true;
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(326, 176);
            this.textBox3.TabIndex = 1;
            // 
            // gpbMessaggio
            // 
            this.gpbMessaggio.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.gpbMessaggio.Controls.Add(this.btnInvia);
            this.gpbMessaggio.Controls.Add(this.txtMessaggio);
            this.gpbMessaggio.Location = new System.Drawing.Point(12, 291);
            this.gpbMessaggio.Name = "gpbMessaggio";
            this.gpbMessaggio.Size = new System.Drawing.Size(326, 91);
            this.gpbMessaggio.TabIndex = 2;
            this.gpbMessaggio.TabStop = false;
            this.gpbMessaggio.Text = "Messaggio";
            // 
            // btnInvia
            // 
            this.btnInvia.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.btnInvia.Location = new System.Drawing.Point(241, 27);
            this.btnInvia.Name = "btnInvia";
            this.btnInvia.Size = new System.Drawing.Size(79, 48);
            this.btnInvia.TabIndex = 4;
            this.btnInvia.Text = "Invia";
            this.btnInvia.UseVisualStyleBackColor = true;
            // 
            // txtMessaggio
            // 
            this.txtMessaggio.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)));
            this.txtMessaggio.Location = new System.Drawing.Point(6, 19);
            this.txtMessaggio.Multiline = true;
            this.txtMessaggio.Name = "txtMessaggio";
            this.txtMessaggio.Size = new System.Drawing.Size(229, 66);
            this.txtMessaggio.TabIndex = 1;
            // 
            // btnEsci
            // 
            this.btnEsci.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnEsci.Location = new System.Drawing.Point(253, 388);
            this.btnEsci.Name = "btnEsci";
            this.btnEsci.Size = new System.Drawing.Size(85, 25);
            this.btnEsci.TabIndex = 5;
            this.btnEsci.Text = "Esci";
            this.btnEsci.UseVisualStyleBackColor = true;
            // 
            // txtPort
            // 
            this.txtPort.Location = new System.Drawing.Point(209, 55);
            this.txtPort.Name = "txtPort";
            this.txtPort.Size = new System.Drawing.Size(40, 20);
            this.txtPort.TabIndex = 5;
            this.txtPort.Text = "30000";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(350, 425);
            this.Controls.Add(this.btnEsci);
            this.Controls.Add(this.gpbMessaggio);
            this.Controls.Add(this.textBox3);
            this.Controls.Add(this.gpbConnessione);
            this.MinimumSize = new System.Drawing.Size(366, 464);
            this.Name = "Form1";
            this.Text = "Form1";
            this.gpbConnessione.ResumeLayout(false);
            this.gpbConnessione.PerformLayout();
            this.gpbMessaggio.ResumeLayout(false);
            this.gpbMessaggio.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox gpbConnessione;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label txtNome;
        private System.Windows.Forms.Button btnConnetti;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Label txtIp;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.GroupBox gpbMessaggio;
        private System.Windows.Forms.Button btnInvia;
        private System.Windows.Forms.TextBox txtMessaggio;
        private System.Windows.Forms.Button btnEsci;
        private System.Windows.Forms.TextBox txtPort;
    }
}

