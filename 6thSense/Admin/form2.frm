VERSION 5.00
Begin VB.Form Form2 
   BackColor       =   &H00C0E0FF&
   ClientHeight    =   4560
   ClientLeft      =   5100
   ClientTop       =   3885
   ClientWidth     =   9660
   LinkTopic       =   "Form2"
   ScaleHeight     =   4560
   ScaleWidth      =   9660
   Begin VB.CommandButton Command3 
      Caption         =   "DELETE"
      Height          =   495
      Left            =   840
      TabIndex        =   5
      Top             =   3120
      Width           =   1335
   End
   Begin VB.ListBox List1 
      Height          =   2790
      ItemData        =   "form2.frx":0000
      Left            =   2160
      List            =   "form2.frx":0002
      TabIndex        =   4
      Top             =   1560
      Width           =   7335
   End
   Begin VB.CommandButton Command2 
      Caption         =   "CLOSE"
      Height          =   495
      Left            =   840
      TabIndex        =   2
      Top             =   3840
      Width           =   1335
   End
   Begin VB.CommandButton Command1 
      Caption         =   "EXCLUDE"
      CausesValidation=   0   'False
      Height          =   495
      Left            =   840
      TabIndex        =   1
      Top             =   2400
      Width           =   1335
   End
   Begin VB.Label Label2 
      BackColor       =   &H00C0E0FF&
      Caption         =   "URL EXCLUSION"
      BeginProperty Font 
         Name            =   "Poor Richard"
         Size            =   21.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   3360
      TabIndex        =   3
      Top             =   360
      Width           =   3135
   End
   Begin VB.Label Label1 
      BackColor       =   &H00C0E0FF&
      Caption         =   "SELECT URL"
      BeginProperty Font 
         Name            =   "Niagara Solid"
         Size            =   24
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   840
      TabIndex        =   0
      Top             =   1560
      Width           =   1935
   End
End
Attribute VB_Name = "Form2"
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
    sqlqry = "update html set flag = 3 where url='" + List1.Text + "';"
    mydb.Execute (sqlqry)
    MsgBox "successfully Excluded from Crawling"
    mydb.Close
End Sub

Private Sub Command2_Click()
    Form2.Hide
End Sub

Private Sub Command3_Click()
    Dim mydb As Database
    Dim ws As Workspace
    Set ws = DBEngine.Workspaces(0)
    Set mydb = ws.OpenDatabase("6thSense.mdb")
    Dim sqlqry As String
    sqlqry = "delete from html where url ='" + List1.Text + "';"
    mydb.Execute (sqlqry)
    List1.RemoveItem (List1.ListIndex)
    MsgBox "Successfully Deleted"
    mydb.Close
End Sub

Public Sub Initialise()
    List1.Clear
    Dim mydb As Database
    Dim ws As Workspace
    Set ws = DBEngine.Workspaces(0)
    Set mydb = ws.OpenDatabase("6thSense.mdb")
    
    Dim r As Recordset
    Dim s As String
    
    s = "select * from html;"
    Set r = mydb.OpenRecordset(s)
    Do While Not r.EOF
        List1.AddItem (r.Fields(2))
        r.MoveNext
    Loop
    mydb.Close
End Sub
Private Sub Form_Load()
    Call Initialise
End Sub

