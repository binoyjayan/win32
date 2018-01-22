VERSION 5.00
Begin VB.Form Form8 
   BackColor       =   &H00C0E0FF&
   Caption         =   "Change Password"
   ClientHeight    =   2415
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   5055
   LinkTopic       =   "Form8"
   ScaleHeight     =   2415
   ScaleWidth      =   5055
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox Text2 
      Height          =   495
      IMEMode         =   3  'DISABLE
      Left            =   1560
      PasswordChar    =   "*"
      TabIndex        =   3
      Top             =   840
      Width           =   3255
   End
   Begin VB.TextBox Text3 
      Height          =   495
      IMEMode         =   3  'DISABLE
      Left            =   1560
      PasswordChar    =   "*"
      TabIndex        =   2
      Top             =   120
      Width           =   3255
   End
   Begin VB.CommandButton Command1 
      Caption         =   "OK"
      Height          =   495
      Left            =   1200
      TabIndex        =   1
      Top             =   1680
      Width           =   1215
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Cancel"
      Height          =   495
      Left            =   3000
      TabIndex        =   0
      Top             =   1680
      Width           =   1215
   End
   Begin VB.Label Label2 
      BackColor       =   &H00C0E0FF&
      Caption         =   "NEW PASSWORD"
      Height          =   495
      Left            =   120
      TabIndex        =   5
      Top             =   240
      Width           =   1215
   End
   Begin VB.Label Label3 
      BackColor       =   &H00C0E0FF&
      Caption         =   "CONFIRM PASSWORD"
      Height          =   495
      Left            =   120
      TabIndex        =   4
      Top             =   840
      Width           =   1215
   End
End
Attribute VB_Name = "Form8"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Command1_Click()
    Dim mydb As Database
    Dim ws As Workspace
    Set ws = DBEngine.Workspaces(0)
    Set mydb = ws.OpenDatabase("6thSense.mdb")
    
    Dim user As String
    If (Text2.Text = Text3.Text) Then
        user = "update USERS set pass='" + Text3.Text + "' where uname='" + Form1.cur_user + "';"
        mydb.Execute (user)
        MsgBox "PASSWORD CHANGED"
        Form8.Hide
    Else
        MsgBox "MISMATCHING PASSWORD ENTRIES"
    End If
    mydb.Close
    
End Sub

Private Sub Command2_Click()
    Form8.Hide
End Sub

