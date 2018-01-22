VERSION 5.00
Begin VB.Form Form7 
   BackColor       =   &H00C0E0FF&
   Caption         =   "Add User"
   ClientHeight    =   3825
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   5730
   LinkTopic       =   "Form7"
   ScaleHeight     =   3825
   ScaleWidth      =   5730
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command2 
      Caption         =   "Cancel"
      Height          =   495
      Left            =   3960
      TabIndex        =   7
      Top             =   3000
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "OK"
      Height          =   495
      Left            =   1920
      TabIndex        =   6
      Top             =   3000
      Width           =   1215
   End
   Begin VB.TextBox Text3 
      Height          =   495
      IMEMode         =   3  'DISABLE
      Left            =   1920
      PasswordChar    =   "*"
      TabIndex        =   5
      Top             =   1320
      Width           =   3255
   End
   Begin VB.TextBox Text2 
      Height          =   495
      IMEMode         =   3  'DISABLE
      Left            =   1920
      PasswordChar    =   "*"
      TabIndex        =   2
      Top             =   1920
      Width           =   3255
   End
   Begin VB.TextBox Text1 
      Height          =   495
      Left            =   1920
      TabIndex        =   0
      Top             =   720
      Width           =   3255
   End
   Begin VB.Label Label3 
      BackColor       =   &H00C0E0FF&
      Caption         =   "CONFIRM PASSWORD"
      Height          =   495
      Left            =   600
      TabIndex        =   4
      Top             =   1920
      Width           =   1215
   End
   Begin VB.Label Label2 
      BackColor       =   &H00C0E0FF&
      Caption         =   "PASSWORD"
      Height          =   495
      Left            =   600
      TabIndex        =   3
      Top             =   1320
      Width           =   1215
   End
   Begin VB.Label Label1 
      BackColor       =   &H00C0E0FF&
      Caption         =   "USER NAME"
      Height          =   495
      Left            =   600
      TabIndex        =   1
      Top             =   720
      Width           =   1215
   End
End
Attribute VB_Name = "Form7"
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
    Dim r1 As Recordset
    Set r1 = mydb.OpenRecordset("select uname from USERS where uname='" + Text1.Text + "';")
    If (r1.EOF) Then
        If (Text2.Text = Text3.Text) Then
            user = "insert into USERS values('" + Text1.Text + "','" + Text3.Text + "');"
            mydb.Execute (user)
            MsgBox "NEW USER CREATED"
            Form7.Hide
        Else
            MsgBox "MISMATCHING PASSWORD ENTRIES"
        End If
    Else
        MsgBox "ALREADY EXISTING USER,TRY WITH ANOTHER USERNAME"
    End If
    r1.Close
    mydb.Close
End Sub

Private Sub Command2_Click()
    Form7.Hide
End Sub

