VERSION 5.00
Begin VB.Form Form1 
   BackColor       =   &H00C0C0FF&
   BorderStyle     =   0  'None
   Caption         =   "Form1"
   ClientHeight    =   5850
   ClientLeft      =   4950
   ClientTop       =   3180
   ClientWidth     =   9225
   LinkTopic       =   "Form1"
   ScaleHeight     =   5850
   ScaleWidth      =   9225
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton Command5 
      BackColor       =   &H008080FF&
      Caption         =   "EXIT"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   7800
      Style           =   1  'Graphical
      TabIndex        =   7
      Top             =   4680
      Width           =   975
   End
   Begin VB.Frame Frame1 
      BackColor       =   &H00FF8080&
      BorderStyle     =   0  'None
      Height          =   2535
      Left            =   1320
      TabIndex        =   2
      Top             =   2640
      Width           =   6015
      Begin VB.CommandButton Command7 
         Caption         =   "CHANGE PASSWORD"
         BeginProperty Font 
            Name            =   "WST_Germ"
            Size            =   9
            Charset         =   2
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Left            =   3240
         TabIndex        =   9
         Top             =   1800
         Width           =   2415
      End
      Begin VB.CommandButton Command6 
         Caption         =   "ADD USER"
         BeginProperty Font 
            Name            =   "WST_Germ"
            Size            =   9
            Charset         =   2
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Left            =   240
         TabIndex        =   8
         Top             =   1800
         Width           =   2415
      End
      Begin VB.CommandButton Command4 
         Caption         =   "INCLUDE PRIMARY URLS"
         BeginProperty Font 
            Name            =   "WST_Germ"
            Size            =   9
            Charset         =   2
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Left            =   3240
         TabIndex        =   6
         Top             =   1080
         Width           =   2415
      End
      Begin VB.CommandButton Command3 
         Caption         =   "INITIATE CRAWLING"
         BeginProperty Font 
            Name            =   "WST_Germ"
            Size            =   9
            Charset         =   2
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Left            =   240
         TabIndex        =   5
         Top             =   1080
         Width           =   2415
      End
      Begin VB.CommandButton Command2 
         Caption         =   "CLEAR REPOSITORY"
         BeginProperty Font 
            Name            =   "WST_Germ"
            Size            =   9
            Charset         =   2
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Left            =   3240
         TabIndex        =   4
         Top             =   360
         Width           =   2415
      End
      Begin VB.CommandButton Command1 
         Caption         =   "EXCLUDE/DELETE URLS"
         BeginProperty Font 
            Name            =   "WST_Germ"
            Size            =   9
            Charset         =   2
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Left            =   240
         TabIndex        =   3
         Top             =   360
         Width           =   2415
      End
   End
   Begin VB.Line Line1 
      BorderStyle     =   6  'Inside Solid
      BorderWidth     =   5
      X1              =   0
      X2              =   8880
      Y1              =   1440
      Y2              =   1440
   End
   Begin VB.Label Label2 
      BackColor       =   &H00C0C0FF&
      Caption         =   "6TH SENSE"
      BeginProperty Font 
         Name            =   "Niagara Solid"
         Size            =   36
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00404000&
      Height          =   735
      Left            =   2280
      TabIndex        =   1
      Top             =   600
      Width           =   2175
   End
   Begin VB.Label Label1 
      BackColor       =   &H00C0C0FF&
      Caption         =   "ADMINISTRATOR"
      BeginProperty Font 
         Name            =   "Niagara Solid"
         Size            =   27.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00808080&
      Height          =   615
      Left            =   4440
      TabIndex        =   0
      Top             =   720
      Width           =   4335
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Public cur_user As String

Private Sub Command1_Click()
Form2.Show
Form3.Hide
End Sub

Private Sub Command2_Click()
    Form3.Show
    Form2.Hide
    Form2.Initialise
    Form4.Hide
End Sub

Private Sub Command3_Click()
    Form4.Show
    Form3.Hide
    Form2.Hide
End Sub

Private Sub Command4_Click()
    Form5.Show
    Form2.Hide
    Form3.Hide
    Form4.Hide

End Sub

Private Sub Command5_Click()
    End
End Sub

Private Sub Command6_Click()
    Form7.Show
End Sub

Private Sub Command7_Click()
    Form8.Show
End Sub

