// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include <winsock.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <direct.h>

#include "Server.h"
#include "ChildView.h"
#include "MainFrm.h"

#define STATUS_EXIT				0
#define STATUS_COMMAND			1
#define STATUS_MSG				2
#define STATUS_GET_OK			3
#define STATUS_GET_SEND			4
#define STATUS_GET_END			5
#define STATUS_GET_ERROR		6
#define STATUS_GET_START		7
#define STATUS_PUT_OK			8
#define STATUS_PUT_SEND			9
#define STATUS_PUT_END			10
#define STATUS_LS_OK			11
#define STATUS_LS_SEND			12
#define STATUS_LS_END			13

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_FILE_STARTSERVER, OnFileStartserver)	
	ON_COMMAND(ID_FILE_SHUTDOWNSERVER, OnFileShutdownServer)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);		

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); //device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}


int PORTNO = 3000;
CUIntArray arr;

#pragma pack(1)
typedef struct tagDATAPACKET
{
	int status;
	int nBytes;
	char s[120];
}DATAPACKET;
#pragma

typedef struct tagCLIENT
{
	SOCKET clientsock;
	char peer[50];
}CLIENT;

char *getnexttoken(char *s, char *p)
{
	//Get to first white space or NULL character
	while(*s != '\0' && *s != ' ' && *s != '\t')
		s++;

	if(*s == '\0')
	{
		*p = 0;
		return NULL;
	}

	while(*s == ' ' || *s == '\t')
		s++;

	char *t = p;
	if(*s == '\"')
	{
		s++;	//skip "
		while(*s!= '\0' && *s != '\"')
		{
			*t = *s;
			s++;
			t++;
		}
	}
	else
	{
		while(*s!= '\0' && *s != ' ' && *s != '\t')
		{
			*t = *s;
			s++;
			t++;
		}
	}
	
	*t = '\0';
	return s;
}
int ProcessCmd(SOCKET cs, DATAPACKET *pkt, char *currentdirectory)
{	
	char *p;
	int n, m;
	CFileFind ff;	
	char curdir[MAX_PATH];
	char t1[100], t2[100];

	CMainFrame *w = (CMainFrame*)((CServerApp*) AfxGetApp())->m_pMainWnd;
	::SetCurrentDirectory(currentdirectory);

	if(strnicmp(pkt->s, "get ", 4) == 0)
	{
		getnexttoken(pkt->s, t1);
		int handle;		
		handle = _open(t1, _O_RDONLY|O_BINARY);
		if(handle == -1)
		{
			pkt->status = STATUS_MSG;//send couldn't open file msg
			strcpy(pkt->s, "Failed to get file.");
			pkt->nBytes = strlen(pkt->s);
			if(send(cs, (char *)pkt, sizeof(DATAPACKET),0) == SOCKET_ERROR)
				return -1;
			return 1;//processed command
		}
		pkt->status = STATUS_GET_OK;
		if(send(cs, (char *)pkt, sizeof(DATAPACKET),0) == SOCKET_ERROR)
		{
			close(handle);
			return -1;
		}
		//Get status if file created at client.
		if(recv(cs, (char*)pkt, sizeof (DATAPACKET), 0) == SOCKET_ERROR)
			return -1;

		if(pkt->status == STATUS_GET_ERROR)
		{
			return 1;	//abort file send.processed cmd
		}

		while(true)
		{
			n = _read(handle, pkt->s, 120);
			if(n <= 0)
				break;//on end of file, break

			pkt->status = STATUS_GET_SEND;
			pkt->nBytes = n;	//no. of bytes
			if(send(cs, (char *)pkt, sizeof(DATAPACKET),0) == SOCKET_ERROR)
			{
				close(handle);
				return -1;
			}
		}
		pkt->status = STATUS_GET_END;
		pkt->s[0] = 0;
		pkt->nBytes = 0;
		if(send(cs, (char *)pkt, sizeof(DATAPACKET),0) == SOCKET_ERROR)
		{
			close(handle);
			return -1;
		}
		return 1;//processed get cmd
	}
	else if(strnicmp(pkt->s, "put ", 4) == 0)
	{
		int handle;
		getnexttoken(pkt->s, t1);
		handle = _open(t1,  _O_CREAT|_O_TRUNC|_O_BINARY|_O_WRONLY, _S_IWRITE);
		if(handle == -1)
		{
			pkt->status = STATUS_MSG;		//send couldn't open file msg
			strcpy(pkt->s, "Failed to put file on Server");
			pkt->nBytes = strlen(pkt->s);
			if(send(cs, (char *)pkt, sizeof(DATAPACKET),0) == SOCKET_ERROR)
				return -1;
			return 1;		//processed put command
		}		

		pkt->status = STATUS_PUT_OK;
		if(send(cs, (char *)pkt, sizeof(DATAPACKET),0) == SOCKET_ERROR)
		{
			close(handle);
			return -1;
		}
		//Start receiving file from client...
		while(true)
		{
			if(recv(cs, (char*)pkt, sizeof (DATAPACKET), 0) == SOCKET_ERROR)
			{
				close(handle);
				return -1;
			}
			if(pkt->status == STATUS_PUT_SEND)
			{
				_write(handle, pkt->s, pkt->nBytes);
			}
			else	//if STATUS_PUT_END
			{
				break;
			}
		}
		close(handle);
		return 1;		//processed put command
	}
	else if(stricmp(pkt->s, "pwd") == 0)
	{
		pkt->status = STATUS_MSG;
		//::GetCurrentDirectory(MAX_PATH, curdir);
		sprintf(pkt->s, "The Current Directory is \'%s\'\n", currentdirectory);
		pkt->nBytes = strlen(pkt->s);
		if(send(cs, (char *)pkt, sizeof(DATAPACKET),0) == SOCKET_ERROR)
			return -1;
		return 1;		//processed cd command
	}
	
	else if(stricmp(pkt->s, "cd") == 0)
	{
		strcpy(curdir, w->m_RootDir);
		SetCurrentDirectory(curdir);
		pkt->status = STATUS_MSG;
		sprintf(pkt->s, "Now the Current Directory is \'%s\'\n", curdir);
		strcpy(currentdirectory, curdir);
		pkt->nBytes = strlen(pkt->s);
		if(send(cs, (char *)pkt, sizeof(DATAPACKET),0) == SOCKET_ERROR)
			return -1;
		return 1;		//processed cd command
	}
	else if(strnicmp(pkt->s, "cd ", 3) == 0)
	{
		pkt->status = STATUS_MSG;
		getnexttoken(pkt->s, t1);		

		if(t1[0] == '\\')
		{
			strcpy(curdir, w->m_RootDir);
			strcat(curdir, t1);
			if(SetCurrentDirectory(curdir))
			{
				::GetCurrentDirectory(MAX_PATH, curdir);
				sprintf(pkt->s, "Now the current directory is \'%s\'\n", curdir);
				strcpy(currentdirectory, curdir);
			}
			else
				strcpy(pkt->s, "Could not find directory.\n");
		}
		else if(t1[1] == ':')
		{
			if(SetCurrentDirectory(t1))
			{
				::GetCurrentDirectory(MAX_PATH, curdir);
				sprintf(pkt->s, "Now the current directory is \'%s\'\n", curdir);
				strcpy(currentdirectory, curdir);
			}
			else
				strcpy(pkt->s, "Could not find directory.\n");
		}		
		else
		{
			GetCurrentDirectory(MAX_PATH, curdir);
			strcat(curdir, "\\");
			strcat(curdir, t1);
			if(SetCurrentDirectory(curdir))
			{
				::GetCurrentDirectory(MAX_PATH, curdir);
				sprintf(pkt->s, "Now the current directory is \'%s\'\n", curdir);
				strcpy(currentdirectory, curdir);
			}
			else
				strcpy(pkt->s, "Could not find directory.\n");
		}

		pkt->nBytes = strlen(pkt->s);
		if(send(cs, (char *)pkt, sizeof(DATAPACKET),0) == SOCKET_ERROR)
			return -1;
		return 1;		//processed cd command
	}
	else if(strnicmp(pkt->s, "del ", 4) == 0)
	{		
		pkt->status = STATUS_MSG;
		getnexttoken(pkt->s, t1);
		if(remove(t1) == 0)//success
			strcpy(pkt->s, "File deleted successfully.\n");
		else
			strcpy(pkt->s, "Error in deleting file.\n");

		pkt->nBytes = strlen(pkt->s);
		if(send(cs, (char *)pkt, sizeof(DATAPACKET),0) == SOCKET_ERROR)
			return -1;
		return 1;		//processed cd command
	}

	else if(strnicmp(pkt->s, "ren ", 4) == 0)
	{		
		pkt->status = STATUS_MSG;
		p = getnexttoken(pkt->s, t1);		
		p = getnexttoken(p, t2);
		if(p == NULL)
		{
			strcpy(pkt->s, "The syntax of the command is incorrect.");
		}
		else
		{
			if(rename(t1, t2) == 0)//success
				strcpy(pkt->s, "File renamed successfully.\n");
			else
				strcpy(pkt->s, "Error in renaming file.\n");
		}
		pkt->nBytes = strlen(pkt->s);		
		if(send(cs, (char *)pkt, sizeof(DATAPACKET),0) == SOCKET_ERROR)
			return -1;
		return 1;		//processed cd command
	}

	else if(stricmp(pkt->s, "ls") == 0)
	{
		GetCurrentDirectory(MAX_PATH, curdir);
		int r;
		r = ff.FindFile("*.*");
		if(r)
		{
			pkt->status = STATUS_LS_OK;
			sprintf(pkt->s, "\nListing Directory \'%s\'\n\n", curdir);
		}
		else
		{
			pkt->status = STATUS_MSG;	//error msg
			strcpy(pkt->s, "Error in listing Directory. Set Current directory using cd command.");
		}
		pkt->nBytes = strlen(pkt->s);		
		if(send(cs, (char *)pkt, sizeof(DATAPACKET),0) == SOCKET_ERROR)
		{
			ff.Close();
			return -1;
		}

		if(r == 0)
			return 1;//if cudnt list directory

		CString s;
		char *p;
		n = m = 0;
		r = 1;
		while(r)
		{
			r = ff.FindNextFile();
			
			s = ff.GetFileName();
			pkt->status = STATUS_LS_SEND;
			pkt->nBytes = s.GetLength();
			p = s.GetBuffer(MAX_PATH);
						
			if(ff.IsDirectory())
			{
				sprintf(pkt->s, "%-5s%s\n", "d", p);
				m++;
			}
			else
			{
				sprintf(pkt->s, "%-5s%s\n", "-", p);
				n++;
			}
			if(send(cs, (char *)pkt, sizeof(DATAPACKET),0) == SOCKET_ERROR)
			{
				ff.Close();
				return -1;
			}
			s.ReleaseBuffer();
		}
		ff.Close();
		pkt->status = STATUS_LS_END;
		pkt->nBytes = sprintf(pkt->s, "%d Directory(s), %d File(s).", m, n);
		if(send(cs, (char *)pkt, sizeof(DATAPACKET),0) == SOCKET_ERROR)
			return -1;

		return 1;
	}
	else if(strnicmp(pkt->s, "mk ", 3) == 0)
	{		
		pkt->status = STATUS_MSG;
		p = getnexttoken(pkt->s, t1);
		
		if(_mkdir(t1) == 0)			//success
			strcpy(pkt->s, "Directory created successfully.\n");
		else
			strcpy(pkt->s, "Error in creating directory.\n");

		pkt->nBytes = strlen(pkt->s);
		if(send(cs, (char *)pkt, sizeof(DATAPACKET),0) == SOCKET_ERROR)
			return -1;
		return 1;		//processed cd command
	}

	else if(strnicmp(pkt->s, "rm ", 3) == 0)
	{		
		pkt->status = STATUS_MSG;
		p = getnexttoken(pkt->s, t1);
		
		if(_rmdir(t1) == 0)			//success
			strcpy(pkt->s, "Directory removed successfully.\n");
		else
			strcpy(pkt->s, "Error in removing directory.\n");

		pkt->nBytes = strlen(pkt->s);
		if(send(cs, (char *)pkt, sizeof(DATAPACKET),0) == SOCKET_ERROR)
			return -1;
		return 1;		//processed cd command
	}
	else if(strnicmp(pkt->s, "server ", 7) == 0)
	{
		pkt->status = STATUS_MSG;
		p = getnexttoken(pkt->s, t1);
		if(stricmp(t1, "restore") == 0)
		{
			strcpy(pkt->s, "Window Restored.\n");
			w->ShowWindow(SW_NORMAL);
		}
		else if(stricmp(t1, "minimize") == 0)
		{
			strcpy(pkt->s, "Window Minimized.\n");
			w->ShowWindow(SW_SHOWMINIMIZED);
		}

		else if(stricmp(t1, "maximize") == 0)
		{
			strcpy(pkt->s, "Window Maximized.\n");
			w->ShowWindow(SW_SHOWMAXIMIZED);
		}
		else if(stricmp(t1, "hide") == 0)
		{
			strcpy(pkt->s, "Window Hidden.\n");
			w->ShowWindow(SW_HIDE);
		}
		else if(stricmp(t1, "load") == 0)
		{
			sprintf(pkt->s, "%d User(s) Connected.\n", arr.GetSize());
		}
		else if(stricmp(t1, "exit") == 0)
		{			
			pkt->status = STATUS_EXIT;
			strcpy(pkt->s, "Server Closed.\n");
			pkt->nBytes = strlen(pkt->s);
			send(cs, (char *)pkt, sizeof(DATAPACKET),0);
			w->SetRegistry();
			exit(0);
		}
		else
			strcpy(pkt->s, "Unsupported Server option.\n");

		pkt->nBytes = strlen(pkt->s);
		if(send(cs, (char *)pkt, sizeof(DATAPACKET),0) == SOCKET_ERROR)
			return -1;
		return 1;
	}

	return 0;//unknown command
}

UINT ProcessClient(LPVOID param)
{
	DATAPACKET pkt;
	int i, r;	
	CLIENT *cl;
	SOCKET clientsock;
	char str[50];
	cl = (CLIENT*)param;
	clientsock = cl->clientsock;
	//strcpy(peer, cl->peer);
	delete cl;//free resource


	CMainFrame *w = (CMainFrame*)((CServerApp*)AfxGetApp())->m_pMainWnd;
	char currentdirectory[MAX_PATH];
	strcpy(currentdirectory, w->m_RootDir);

	while(w->m_ServerStatus)
	{	
		if(recv(clientsock, (char*)&pkt, sizeof (pkt), 0) == SOCKET_ERROR)
		{
			//MessageBox(NULL, "Client Disconnected abrubtly", "Error in connection", MB_OK|MB_ICONSTOP);
			break;
		}	
		if(pkt.status == STATUS_EXIT)		//exit...
			break;

		if(pkt.status == STATUS_COMMAND)	//Command
		{
			r = ProcessCmd(clientsock, &pkt, currentdirectory);
			if(r == -1)						//error in sending
				break;
			else if(r == 0)
			{
				//Send unknown command msg to the client.
				pkt.status = STATUS_MSG;	//message
				strcpy(pkt.s, "Invalid Command. Type \'help\' to view the commands.");
				pkt.nBytes = strlen(pkt.s);
				if(send(clientsock, (char *) &pkt, sizeof(pkt),0) == SOCKET_ERROR)
				{
					break;
				}
			}
		}
	}
	//Finished receive
	shutdown (clientsock, 0x02);
	closesocket (clientsock);

	for(i=0;i<arr.GetSize();i++)
	{
		if(arr.GetAt(i) == clientsock)
		{
			arr.RemoveAt(i);
			break;
		}
	}
	unsigned int n;
	for(i=0;i<w->m_List.GetItemCount();i++)
	{
		w->m_List.GetItemText(i, 0, str,100);
		n = atoi(str);
		if(n == clientsock)
		{
			w->m_List.DeleteItem(i);
			break;
		}
	}
	return true;
}

UINT AcceptIncomingConnections(LPVOID param)
{
	//char *s = (char*)param;
	//MessageBox(NULL, "Server Started", "Hello",MB_OK|MB_ICONINFORMATION);
	int index = 0;
	char str[100];
	SOCKET WinSocket = INVALID_SOCKET;
	SOCKET ClientSock = INVALID_SOCKET;
	SOCKADDR_IN local_sin, accept_sin;
	int accept_sin_len;
	WSADATA WSAData;
	
	// Initialize Winsock.
	if(WSAStartup(MAKEWORD(1,1), &WSAData) != 0)
	{
		printf("WSAStartup failed. Error: %d", WSAGetLastError());
		return FALSE;
	}
	if((WinSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		sprintf(str, "Allocating socket failed. Error: %d", WSAGetLastError());
		//MessageBox(NULL, str, "Error!", MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	// Fill out the local socket's address information.
	local_sin.sin_family = AF_INET;
	local_sin.sin_port = htons (PORTNO);
	local_sin.sin_addr.s_addr = htonl (INADDR_ANY);

	if(bind(WinSocket,(struct sockaddr *) &local_sin, sizeof (local_sin)) == SOCKET_ERROR)
	{
		sprintf(str, "Binding socket failed. Error: %d", WSAGetLastError());
		//MessageBox(NULL, str, "Error!", MB_OK|MB_ICONSTOP);
		closesocket (WinSocket);
		return FALSE;
	}
	
	// Establish a socket to listen for incoming connections.
	if (listen(WinSocket, 4) == SOCKET_ERROR)
	{
		sprintf(str, "Listening to the client failed. Error: %d", WSAGetLastError ());
		//MessageBox(NULL, str, "Error!", MB_OK|MB_ICONSTOP);
		closesocket(WinSocket);
		return FALSE;
	}
	
	//CMainFrame *w = (CMainFrame*)AfxGetMainWnd();
	CMainFrame *w = (CMainFrame*)((CServerApp*)AfxGetApp())->m_pMainWnd;
	w->m_ServerStatus = 1;
	CTime time;
	int hour;	
	while(w->m_ServerStatus) //while server is running
	{
		accept_sin_len = sizeof (accept_sin);	
		ClientSock = accept(WinSocket, (struct sockaddr *) &accept_sin, (int *) &accept_sin_len);		
		if (ClientSock == INVALID_SOCKET)
		{
			sprintf(str, "Accepting connection with client failed Error: %d", WSAGetLastError());
			//MessageBox(NULL, str, "Accept Error!", MB_OK | MB_ICONSTOP);
			break;
		}
		LPHOSTENT lpPeerHost = gethostbyaddr((const char*)&accept_sin.sin_addr, sizeof(struct in_addr), AF_INET);		
		CLIENT *cl = new CLIENT;
		cl->clientsock = ClientSock;
		strcpy(cl->peer, lpPeerHost->h_name);
		arr.Add(ClientSock);
		sprintf(str, "%u", ClientSock);
		w->m_List.InsertItem(arr.GetSize()-1, str, 0);
		w->m_List.SetItemText(arr.GetSize()-1, 1, lpPeerHost->h_name);
		time = CTime::GetCurrentTime();
		hour = time.GetHour();

		if(hour % 12)
			sprintf(str, "%02d:%02d:%02d PM", hour%12,time.GetMinute(),time.GetSecond());
		else
			sprintf(str, "%02d:%02d:%02d AM", hour%12,time.GetMinute(),time.GetSecond());

		w->m_List.SetItemText(arr.GetSize()-1, 2, str);
		
		AfxBeginThread(ProcessClient, (LPVOID) cl);
	}
	// Stop listening for connections from clients.
	closesocket (WinSocket);

	WSACleanup();
	return true;
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	/*
	CRect r;
	GetClientRect(&r);	
	//CBrush b(RGB(253,198, 137));
	//CBrush b(RGB(122,204, 200));
	//CBrush b(RGB(255,0, 255));
	CBrush b(RGB(245,152, 157));
	pDC->FillRect(&r, &b);
	return true;
	*/
	return CWnd ::OnEraseBkgnd(pDC);
}


void CChildView::OnFileStartserver()
{
	CMainFrame *w = (CMainFrame*)((CServerApp*) AfxGetApp())->m_pMainWnd;

	if(w->m_ServerStatus == 0)
	{
		//::MessageBox(NULL, "Server Started","OK", MB_OK);
		AfxBeginThread(AcceptIncomingConnections, (LPVOID) NULL);
	}
}

void CChildView::Start()
{
	OnFileStartserver();
}

void CChildView::OnFileShutdownServer()
{
	CMainFrame *w = (CMainFrame*)((CServerApp*) AfxGetApp())->m_pMainWnd;
	w->m_ServerStatus = 0;//stop server
	//Remove list, array elements
	w->m_List.DeleteAllItems();
	arr.RemoveAll();

}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd ::OnCreate(lpCreateStruct) == -1)
		return -1;
	CMainFrame *w = (CMainFrame*)((CServerApp*) AfxGetApp())->m_pMainWnd;
	w->m_Img.Create(IDB_BITMAP1, 20, 1, CLR_NONE);
	return 0;
}
