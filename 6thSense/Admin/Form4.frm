VERSION 5.00
Begin VB.Form Form4 
   BackColor       =   &H00C0E0FF&
   Caption         =   "Managing Crawler"
   ClientHeight    =   5655
   ClientLeft      =   5100
   ClientTop       =   3180
   ClientWidth     =   8880
   LinkTopic       =   "Form4"
   ScaleHeight     =   5655
   ScaleWidth      =   8880
   Begin VB.CommandButton Command2 
      Caption         =   "CANCEL"
      Height          =   615
      Left            =   3960
      TabIndex        =   6
      Top             =   4200
      Width           =   1215
   End
   Begin VB.ComboBox Combo2 
      Height          =   315
      ItemData        =   "Form4.frx":0000
      Left            =   4560
      List            =   "Form4.frx":0010
      TabIndex        =   5
      Text            =   "1"
      Top             =   3120
      Width           =   855
   End
   Begin VB.ComboBox Combo1 
      Height          =   315
      ItemData        =   "Form4.frx":0020
      Left            =   4560
      List            =   "Form4.frx":0030
      TabIndex        =   3
      Text            =   "1"
      Top             =   2280
      Width           =   855
   End
   Begin VB.CommandButton Command1 
      Caption         =   "SET CRAWLER"
      Height          =   615
      Left            =   2160
      TabIndex        =   1
      Top             =   4200
      Width           =   1215
   End
   Begin VB.Label Label3 
      BackColor       =   &H00C0E0FF&
      Caption         =   "SELECT THE NO OF CRAWLERS"
      Height          =   495
      Left            =   1560
      TabIndex        =   4
      Top             =   3120
      Width           =   2775
   End
   Begin VB.Label Label2 
      BackColor       =   &H00C0E0FF&
      Caption         =   "SELECT THE  NO OF THREADS"
      Height          =   495
      Left            =   1560
      TabIndex        =   2
      Top             =   2280
      Width           =   2775
   End
   Begin VB.Label Label1 
      BackColor       =   &H00C0E0FF&
      Caption         =   "CRAWLER MANAGEMENT"
      BeginProperty Font 
         Name            =   "Niagara Engraved"
         Size            =   36
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1215
      Left            =   2520
      TabIndex        =   0
      Top             =   360
      Width           =   3855
   End
End
Attribute VB_Name = "Form4"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Command1_Click()
    Dim crawler As String
    Dim t As Integer
    Dim i As Integer
    t = Val(Combo2.Text)
    crawler = "Crawler.exe " + Combo1.Text
    
    Do While (i < t)
        Shell crawler, vbNormalFocus
        i = i + 1
    Loop
    
End Sub

Private Sub Command2_Click()
    Form4.Hide
End Sub

