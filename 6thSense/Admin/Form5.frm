VERSION 5.00
Begin VB.Form Form5 
   BackColor       =   &H00C0E0FF&
   Caption         =   "URL Initialization"
   ClientHeight    =   5490
   ClientLeft      =   5100
   ClientTop       =   3450
   ClientWidth     =   8550
   LinkTopic       =   "Form5"
   ScaleHeight     =   5490
   ScaleWidth      =   8550
   Begin VB.TextBox Text5 
      Height          =   495
      Left            =   1800
      MultiLine       =   -1  'True
      TabIndex        =   12
      Top             =   3960
      Width           =   5655
   End
   Begin VB.TextBox Text4 
      Height          =   495
      Left            =   1800
      MultiLine       =   -1  'True
      TabIndex        =   7
      Top             =   3360
      Width           =   5655
   End
   Begin VB.TextBox Text3 
      Height          =   495
      Left            =   1800
      MultiLine       =   -1  'True
      TabIndex        =   6
      Top             =   2760
      Width           =   5655
   End
   Begin VB.TextBox Text2 
      Height          =   495
      Left            =   1800
      MultiLine       =   -1  'True
      TabIndex        =   5
      Top             =   2160
      Width           =   5655
   End
   Begin VB.CommandButton Command2 
      Caption         =   "CANCEL"
      Height          =   735
      Left            =   5880
      TabIndex        =   3
      Top             =   4680
      Width           =   1575
   End
   Begin VB.CommandButton Command1 
      Caption         =   "SET"
      Height          =   735
      Left            =   1800
      TabIndex        =   2
      Top             =   4680
      Width           =   1575
   End
   Begin VB.TextBox Text1 
      Height          =   495
      Left            =   1800
      MultiLine       =   -1  'True
      TabIndex        =   0
      Top             =   1560
      Width           =   5655
   End
   Begin VB.Label Label7 
      BackColor       =   &H00C0E0FF&
      Caption         =   "PAGE RANK"
      Height          =   375
      Left            =   360
      TabIndex        =   13
      Top             =   4080
      Width           =   1095
   End
   Begin VB.Label Label6 
      BackColor       =   &H00C0E0FF&
      Caption         =   "CONTENT"
      Height          =   495
      Left            =   360
      TabIndex        =   11
      Top             =   3360
      Width           =   1095
   End
   Begin VB.Label Label5 
      BackColor       =   &H00C0E0FF&
      Caption         =   "LAD"
      Height          =   495
      Left            =   360
      TabIndex        =   10
      Top             =   2760
      Width           =   1095
   End
   Begin VB.Label Label4 
      BackColor       =   &H00C0E0FF&
      Caption         =   "URL"
      Height          =   495
      Left            =   360
      TabIndex        =   9
      Top             =   2160
      Width           =   1095
   End
   Begin VB.Label Label3 
      BackColor       =   &H00C0E0FF&
      Caption         =   "ISTRING"
      Height          =   495
      Left            =   360
      TabIndex        =   8
      Top             =   1560
      Width           =   1095
   End
   Begin VB.Label Label2 
      BackColor       =   &H00C0E0FF&
      Caption         =   "URL INITIALIZATION"
      BeginProperty Font 
         Name            =   "Comic Sans MS"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   2228
      TabIndex        =   4
      Top             =   240
      Width           =   4095
   End
   Begin VB.Label Label1 
      BackColor       =   &H00C0E0FF&
      Caption         =   "ENTER THE URLS"
      BeginProperty Font 
         Name            =   "WST_Swed"
         Size            =   18
         Charset         =   2
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   1320
      TabIndex        =   1
      Top             =   1080
      Width           =   2655
   End
End
Attribute VB_Name = "Form5"
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
    sqlqry = "insert into html values(0,'" + Text1.Text + "','" & Text2.Text + "','" & Text3.Text + "','" & Text4.Text & "','" + Text5.Text + "');"
    mydb.Execute (sqlqry)
    MsgBox "inserted successfully"
    mydb.Close
    
End Sub

Private Sub Command2_Click()
    Form5.Hide
End Sub

