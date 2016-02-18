<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class frmPrincipale
    Inherits System.Windows.Forms.Form

    'Form esegue l'override del metodo Dispose per pulire l'elenco dei componenti.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Richiesto da Progettazione Windows Form
    Private components As System.ComponentModel.IContainer

    'NOTA: la procedura che segue è richiesta da Progettazione Windows Form
    'Può essere modificata in Progettazione Windows Form.  
    'Non modificarla nell'editor del codice.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.txtInvia = New System.Windows.Forms.TextBox()
        Me.btnInvia = New System.Windows.Forms.Button()
        Me.txtRicevi = New System.Windows.Forms.TextBox()
        Me.SuspendLayout()
        '
        'txtInvia
        '
        Me.txtInvia.Location = New System.Drawing.Point(12, 12)
        Me.txtInvia.Name = "txtInvia"
        Me.txtInvia.Size = New System.Drawing.Size(332, 20)
        Me.txtInvia.TabIndex = 0
        '
        'btnInvia
        '
        Me.btnInvia.Location = New System.Drawing.Point(350, 10)
        Me.btnInvia.Name = "btnInvia"
        Me.btnInvia.Size = New System.Drawing.Size(75, 23)
        Me.btnInvia.TabIndex = 1
        Me.btnInvia.Text = "Invia"
        Me.btnInvia.UseVisualStyleBackColor = True
        '
        'txtRicevi
        '
        Me.txtRicevi.Location = New System.Drawing.Point(12, 46)
        Me.txtRicevi.Multiline = True
        Me.txtRicevi.Name = "txtRicevi"
        Me.txtRicevi.Size = New System.Drawing.Size(413, 185)
        Me.txtRicevi.TabIndex = 2
        '
        'frmPrincipale
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(437, 243)
        Me.Controls.Add(Me.txtRicevi)
        Me.Controls.Add(Me.btnInvia)
        Me.Controls.Add(Me.txtInvia)
        Me.Name = "frmPrincipale"
        Me.Text = "Invia/Ricevi"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents txtInvia As System.Windows.Forms.TextBox
    Friend WithEvents btnInvia As System.Windows.Forms.Button
    Friend WithEvents txtRicevi As System.Windows.Forms.TextBox

End Class
