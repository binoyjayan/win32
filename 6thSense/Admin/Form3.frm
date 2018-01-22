VERSION 5.00
Begin VB.Form Form3 
   BackColor       =   &H00C0E0FF&
   Caption         =   "Clear Repositories"
   ClientHeight    =   4335
   ClientLeft      =   4755
   ClientTop       =   3810
   ClientWidth     =   9195
   LinkTopic       =   "Form3"
   ScaleHeight     =   4335
   ScaleWidth      =   9195
   Begin VB.CommandButton Command2 
      Caption         =   "CLOSE"
      Height          =   495
      Left            =   4680
      TabIndex        =   3
      Top             =   2400
      Width           =   2655
   End
   Begin VB.CommandButton Command1 
      Caption         =   "CLEAR"
      Height          =   495
      Left            =   1800
      TabIndex        =   2
      Top             =   2400
      Width           =   2655
   End
   Begin VB.ListBox List1 
      Height          =   1035
      ItemData        =   "Form3.frx":0000
      Left            =   4680
      List            =   "Form3.frx":0013
      TabIndex        =   0
      Top             =   1320
      Width           =   2655
   End
   Begin VB.Label Label1 
      BackColor       =   &H00C0E0FF&
      Caption         =   "SELECT THE TABLE TO CLEAR"
      ForeColor       =   &H000040C0&
      Height          =   375
      Left            =   1800
      TabIndex        =   1
      Top             =   1320
      Width           =   2535
   End
End
Attribute VB_Name = "Form3"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Command1_Click()
    Dim mydb As Database
    Dim ws As Workspace
    
    Set ws = DBEngine.Workspaces(0)
    Set mydb = ws.OpenDatabase("6thSense.mdb")
    
    Dim sqlqry As String
    sqlqry = "delete from " + List1.Text + ";"
    mydb.Execute (sqlqry)
    MsgBox "Table Cleared successfully"
    Form2.List1.Clear
    mydb.Close
    
End Sub

Private Sub Command2_Click()
    Form3.Hide
End Sub

