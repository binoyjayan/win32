VERSION 5.00
Begin VB.Form Form6 
   BackColor       =   &H00C0E0FF&
   Caption         =   "Login"
   ClientHeight    =   3435
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   4755
   LinkTopic       =   "Form6"
   ScaleHeight     =   3435
   ScaleWidth      =   4755
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame1 
      BackColor       =   &H00C0E0FF&
      Caption         =   "LOGIN"
      Height          =   3135
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   5055
      Begin VB.CommandButton Command2 
         Caption         =   "Cancel"
         Height          =   495
         Left            =   2280
         TabIndex        =   6
         Top             =   2280
         Width           =   2055
      End
      Begin VB.CommandButton Command1 
         Caption         =   "OK"
         Height          =   495
         Left            =   360
         TabIndex        =   5
         Top             =   2280
         Width           =   1215
      End
      Begin VB.TextBox pass 
         Height          =   495
         IMEMode         =   3  'DISABLE
         Left            =   2280
         PasswordChar    =   "*"
         TabIndex        =   4
         Text            =   "a"
         Top             =   1200
         Width           =   2055
      End
      Begin VB.TextBox uname 
         Height          =   495
         Left            =   2280
         TabIndex        =   3
         Text            =   "a"
         Top             =   240
         Width           =   2055
      End
      Begin VB.Label Label2 
         BackColor       =   &H00C0E0FF&
         Caption         =   "PASSWORD"
         Height          =   495
         Left            =   360
         TabIndex        =   2
         Top             =   1320
         Width           =   1215
      End
      Begin VB.Label Label1 
         BackColor       =   &H00C0E0FF&
         Caption         =   "USER NAME"
         Height          =   495
         Left            =   360
         TabIndex        =   1
         Top             =   240
         Width           =   1215
      End
   End
End
Attribute VB_Name = "Form6"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Command1_Click()
    Dim mydb As Database
    Dim ws As Workspace
    Set ws = DBEngine.Workspaces(0)
    Set mydb = ws.OpenDatabase("6thSense.mdb")
    
    Dim r3 As Recordset
    Set r3 = mydb.OpenRecordset("select pass from USERS where uname='" + uname.Text + "';")
    If (r3.Fields(0) = pass.Text) Then
        Form1.Show
        Form1.cur_user = uname.Text
        Form6.Hide
    Else
        MsgBox "INCORRECT PASSWORD"
    End If
    r3.Close
    mydb.Close
End Sub

Private Sub Command2_Click()
    Form6.Hide
End Sub
