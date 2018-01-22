// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Crawler.h"
#include "HTMLParser.h"
#include "DBAccess.h"
#include "MainFrm.h"
#include "CrawlerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_FILE_STARTCRAWLER, OnFileStartcrawler)	
	ON_WM_DESTROY()
	ON_COMMAND(ID_FILE_STOP_CRAWLING, OnFileStopCrawling)
	ON_COMMAND(ID_CRAWLERSTATUS, OnCrawlerstatusDialogShow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_pThread = NULL;
	m_CrawlerStatus = 0;
	m_Dlg = new CCrawlerDlg();
	m_Dlg->Create(IDD_CRAWLING);	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	CRect r;
	GetClientRect(&r);
	m_List.Create(WS_CHILD | WS_VISIBLE | WS_BORDER| WS_VSCROLL | LVS_REPORT , r, &m_wndView, 123);

	m_List.SetImageList(&m_Img, LVSIL_SMALL);

	m_List.InsertColumn(0, "URL", LVCFMT_LEFT, 400);
	m_List.InsertColumn(1, "Date / Time", LVCFMT_LEFT, 150);
	m_List.InsertColumn(2, "Length", LVCFMT_LEFT, 150);
	m_List.InsertColumn(3, "Status", LVCFMT_LEFT, 150);
	m_List.InsertColumn(4, "Page Rank", LVCFMT_LEFT, 150);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the view window
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

UINT CrawlerThread ( LPVOID param ) ;


int GetNextURLFromDB(char *lpszNextURL)
{
	int ret_val;
	try
	{
		CDBAccess db;
		CRecordset * rs;
		db.Open();
		rs = db.ExecuteQuery("select * from HTML where flag = 0");
		
		CString str, sql;
		int count = 0;	
		if(rs -> GetRecordCount() > 0)
		{
			rs->GetFieldValue("url", str);
			strcpy(lpszNextURL, str);		
			ret_val = TRUE;
		}
		else
		{
			ret_val = FALSE;
		}
		rs->Close();
		db.Close();
	}
	catch(...)
	{
		ret_val = 0; 
	}
/*
	//Update table
	db.Open();
	sql.Format("update HTML set flag = 1 where url = '%s'", (LPCTSTR)str);
	db.ExecuteUpdate(sql);
	db.Close();
*/
	return ret_val;
}

void CMainFrame::Stop()
{
	m_CrawlerStatus = 0;
	m_pThread = NULL;
	m_Dlg->ShowWindow(SW_HIDE);
}


void CMainFrame::OnFileStopCrawling() 
{
	Stop();
}


void CMainFrame::OnFileStartcrawler() 
{
	m_pThread = AfxBeginThread(CrawlerThread, NULL);
	m_CrawlerStatus = 1;	
	m_Dlg->ShowWindow(SW_NORMAL);	
}


int FindInTable(const char *table, const char *URL)
{
	try
	{

		CDBAccess db;
		CString sql;
		CRecordset *rs;	
		int flag = 0;

		if(db.Open())
		{
			sql.Format("select * from %s where url = '%s'", table, URL);
			rs = db.ExecuteQuery(sql);
			if(rs->GetRecordCount() > 0)		//if record is present
			{
				flag = 1;
			}		
		}
		else
			return -1;

		rs->Close();
		db.Close();
		if(flag)
			return 1;		
	}
	catch(...)
	{
	}
	return 0;
}

void SetUpdateFlag(const char *URL)
{
	//Update the HTML table
	try
	{
		CDBAccess db;	
		CString sql;	
		int flag;

		flag = FindInTable("HTML", URL);

		if(flag != 1)		//If could not open DB
			return ;

		if(db.Open())		//If could not open DB
		{	
			sql.Format("update HTML set flag = 1 where url = '%s'", URL);
			db.ExecuteUpdate(sql);
			db.Close();
		}
	}
	catch(...)
	{
	}
}

int UpdateHTMLTable(const char *URL, const char *istring, const char *content, const char *lad)
{
	//Update the HTML table

	try
	{
		CDBAccess db;	
		CString sql;	
		int flag;

		flag = FindInTable("HTML", URL);

		if(flag == -1)		//If could not open DB
			return FALSE;

		if(!db.Open())		//If could not open DB
		{
			return FALSE;
		}

		if(flag == 1) //If present URL
		{
			sql.Format("update HTML set istring = '%s' where url = '%s'", istring, URL);
		}
		else //if not present , insert new record into table
		{
			sql.Format("insert into HTML values(0, '%s','%s','%s', '%s', '0.1')", istring, URL, lad, content);
		}
		db.ExecuteUpdate(sql);
		db.Close();	
		return TRUE;
	}
	catch(...)
	{
		return 0;
	}
}

int UpdateOTHERTable(const char *URL, const char *istring, const char *lad, char *table, CString size)
{
	//Update the table: IMAGE/AUDIO....
	try
	{
		CDBAccess db;
		CString sql;
		int flag;
		
		flag = FindInTable(table, URL);
		if(flag == -1)
			return FALSE; //DB error

		if(!db.Open())//If could not open DB
		{
			return FALSE;
		}

		if(flag == 1)	//If record present, then update
		{
			sql.Format("update %s set istring = '%s' where url = '%s', %s", table, istring, URL,  (LPCTSTR)size);
		}
		else	//Update
		{
			sql.Format("insert into %s values('%s','%s','%s', '0.1', %s)", table, istring, URL, lad, (LPCTSTR)size);
		}
		db.ExecuteUpdate(sql);	
		db.Close();
		return TRUE;
	}
	catch(...)
	{
		return 0;
	}
}

int UpdateMetaInfo(const char *URL, const char *meta, const char * content)
{
	//If URL present in HTML table, ADD to its meta content

	try
	{
		CDBAccess db;
		CString sql, str;
		CRecordset *rs;	
		int flag = 0;

		if(!db.Open())
			return FALSE;

		sql.Format("select istring from HTML where url = '%s'", URL);
		rs = db.ExecuteQuery(sql);
		if(rs -> IsEOF() != -1)		//if record is present
		{
			rs->GetFieldValue("istring", str);	//str contains meta data 
			flag = 1;
		}
		rs->Close();
		db.Close();

		if(flag == 0)return FALSE;
		
		//Now Update Meta data

		str.TrimLeft();
		if(!str.IsEmpty())
			str = meta;
		else
			str = str + "," + meta;
		
		if(!db.Open())
			return FALSE;
		
		sql.Format("update HTML set istring = '%s', cnt = '%s' where url = '%s'", (LPCTSTR)str, content, URL);
		db.ExecuteUpdate(sql);
		
		db.Close();

		return TRUE;
	}
	catch(...)
	{
		return 0;
	}
}

int ConstructURL(const char *url, char *URL, char *value)
{
	CString sr, strobj;
	INTERNET_PORT port;
	DWORD svrtype;
	int n;

	::AfxParseURL(value, svrtype, sr, strobj, port);
	if(sr.IsEmpty())
	{
		//Only relative path is specified
		n = strlen(url) - 1;

		while(n > 0 && URL[n] != '/')
			n--;

		URL[n+1] = '\0';
		strcat(URL, value);
	}
	else
	{
		// Absolute URL
		strcpy(URL, value);
	}
	return TRUE;
}

char iext[][5] = {"bmp", "dib", "jpg", "jpeg", "jpe", "jfif", "png", "gif", "tif","tiff", "png"};
char aext[][5] = {"wav", "wma", "mp1", "mp2", "mp3","acc","mid","midi", "rmi", "kar", "apl", "cda", "miz", "nsa"};
char vext[][5] = {"mpg", "mpeg", "m2v", "avi", "asf","wmv", "mp4","m4a","nsv","ogg", "voc","au", "snd", "aif", "aiff", "flv"};

int FindExtensionCheck(char *url)
{	
	int n, i;
	i = 0;
	char temp[5];

	n = strlen(url) - 1;
	while(n > 0 && url[n] != '.')
		n--;
	if(n == 0)
		return 0;	//None 

	strcpy(temp, &url[n+1]);
	
	//Checking for image extension
	for(i = 0; i< sizeof(iext) / 5 ; i++)
	{
		if(stricmp(iext[i], temp) == 0)
			return 1;
	}

	//Checking for audio extension
	for(i = 0; i< sizeof(aext) / 5 ; i++)
	{
		if(stricmp(aext[i], temp) == 0)
			return 2;
	}
	//Checking for video extension
	for(i = 0; i< sizeof(vext) / 5 ; i++)
	{
		if(stricmp(vext[i], temp) == 0)
			return 3;
	}
	//Otherswise it is a document (word/ excel/zip/rar/exe files)
	return 4;
	
}

void GetURLFileName(char *URL, char *filename)
{
	int i, len;
	len = strlen(URL);
	for(i=len;i > 0 && URL[i] != '/' ;i--);

	strcpy(filename, URL + i + 1);

	i = 0;
	while(filename[i] != '\0' && filename[i] != '.')
		i++;
	filename[i] = '\0';
}

int FindURLType(char *url, char *filename, CString &lenstr)
{
	CInternetSession session;
	CHttpConnection *connection;
	CHttpFile *phttpfile;
	CString status, strobj, svr;
	INTERNET_PORT port;
	DWORD svrtype;
	int ret_value;	

	::AfxParseURL(url, svrtype, svr, strobj, port);
	HTMLParser *par = NULL;	

	try
	{
		connection = session.GetHttpConnection(svr, port);		
		phttpfile = connection -> OpenRequest(1, strobj);		
		phttpfile -> SendRequest();		
		phttpfile -> QueryInfo ( HTTP_QUERY_STATUS_TEXT, status);		
		
		if ( phttpfile -> QueryInfo(HTTP_QUERY_CONTENT_LENGTH, lenstr ) == 0 )
			lenstr = "0";

		par = new HTMLParser(phttpfile);

		if(par->FindInBuffer("HTML") || par->FindInBuffer("html"))
		{
			ret_value = 0;		
		}
		else
		{	
			GetURLFileName(url, filename);
			ret_value = FindExtensionCheck(url);
		}
		phttpfile->Close();
	}
	catch (CInternetException *e )
	{	
		//skip URL
		e -> Delete();
		ret_value = -1;
	}
	catch(...)
	{		
		ret_value =  -1;
	}
	if(status != "OK")
		ret_value = -1;

	if(par)
		delete par;

	if (session)
		session.Close();
	if (connection)
		connection ->Close();

	return ret_value;
}


char urltemp[512], url[512];
char tag[12], attr[12], value[250], content[100];
char descript[250];
char desc[250], lpszFileName[200];

UINT CrawlerThread (LPVOID param)
{
	CInternetSession *session;
	CHttpConnection *connection;
	CHttpFile *phttpfile;
	
	CMainFrame *w = (CMainFrame*)((CCrawlerApp*) AfxGetApp())->m_pMainWnd;
	
	CString svr, strobj;
	DWORD svrtype;	
	INTERNET_PORT port;

	CString status, datestr, lenstr;
	
	static index = 0;

	//Start Crawling the Internet/Intranet...

startcrawling:

	if(!w->m_CrawlerStatus)
		return 0;

	if(!GetNextURLFromDB(url))
	{
		//Stop Crawling
		AfxMessageBox("Finished Crawling....");
		w->m_Dlg->ShowWindow(SW_HIDE);
		return TRUE;
	}

	w->m_Dlg->UpdateURL(url);

	::AfxParseURL(url, svrtype, svr, strobj, port);
	try
	{
		session = new CInternetSession();
		connection = session->GetHttpConnection(svr, port);
		phttpfile = connection -> OpenRequest ( 1, strobj);
		phttpfile -> SendRequest();

		w->m_List.InsertItem(index, url);
		
		SYSTEMTIME *ptime = new SYSTEMTIME ;

		if ( phttpfile -> QueryInfo(HTTP_QUERY_LAST_MODIFIED, ptime ) == 0)
			datestr = "0000:00:00 00:00:00" ;
		else
			datestr.Format( "%2d-%2d-%4d %2d:%2d:%2d", ptime->wMonth, ptime->wDay, ptime->wYear, ptime->wHour, ptime->wMinute, ptime->wSecond ) ;

		w->m_List.SetItemText ( index, 1, datestr ) ;

		if ( phttpfile -> QueryInfo(HTTP_QUERY_CONTENT_LENGTH, lenstr ) == 0 )
			lenstr = "0";
		
		w->m_List.SetItemText(index, 2, lenstr);

		phttpfile -> QueryInfo ( HTTP_QUERY_STATUS_TEXT, status) ;
		w->m_List.SetItemText(index, 3, status);
		
		w->m_List.SetItemText(index, 4, "0.1");

		index++ ;
		delete ptime;
	}
	catch ( CInternetException *e )
	{
		e -> Delete();
		SetUpdateFlag(url);		
		goto startcrawling;
	}
	catch(...)
	{		
	}

	if(status != "OK")		//If file could not be downloaded...SKIP it.
	{
		SetUpdateFlag(url);		
		goto startcrawling;
	}
	

	HTMLParser *parser = new HTMLParser(phttpfile);

	if(parser->FindInBuffer("HTML") || parser->FindInBuffer("html"))
	{		
		int desflag = 0;	
		int metacount = 0;
		int urltype;
		while(parser->GetNextTag(tag, attr, value, content, descript, &desflag) && w->m_CrawlerStatus)
		{
			if(descript[0] != '\0')
			{
				if(metacount)
				{
					metacount = parser->GetMetaCount() > metacount ? parser->GetMetaCount() : metacount;
					strcpy(desc, descript);
					//store Description, meta information
					UpdateMetaInfo(url, parser->GetMetaString(), desc);
				}
			}
			strcpy(urltemp, url);
			ConstructURL(url, urltemp, value);	//now urltemp has a valid url
			w->m_Dlg->UpdateLink(urltemp);
			urltype = FindURLType(urltemp, lpszFileName, lenstr);
			switch(urltype)
			{
			case -1:
				//Could not retrieve the file... ('Object Not Found' Error) Skip file
				break;
			case 0: 
				///HTML					
				UpdateHTMLTable(urltemp, content, content, (LPCTSTR)datestr);	//desc is NULL
				break;
			case 1:
				//Image table
				UpdateOTHERTable(urltemp, lpszFileName, (LPCTSTR)datestr,  "IMAGE", lenstr);
				break;
			case 2:
				//Audio table
				UpdateOTHERTable(urltemp, lpszFileName, (LPCTSTR)datestr, "AUDIO", lenstr);
				break;
			case 3:
				//Video table
				UpdateOTHERTable(urltemp, lpszFileName, (LPCTSTR)datestr, "VIDEO", lenstr);
				break;
			case 4:
				//Document table
				UpdateOTHERTable(urltemp, lpszFileName, (LPCTSTR)datestr, "DOCUMENT", lenstr);
				break;
			}			
		}		
	}
	
	phttpfile->Close();
	if ( *session )
		session->Close( ) ;
	if ( connection )
		connection -> Close();

	if(session)delete session;
	if(parser)delete parser;
	SetUpdateFlag(url);

	goto startcrawling;
	
	return TRUE ;
}

void CMainFrame::OnDestroy() 
{
	OnFileStopCrawling();
	CFrameWnd::OnDestroy();
		
}
void CMainFrame::OnCrawlerstatusDialogShow()
{
	if(m_CrawlerStatus)
		m_Dlg->ShowWindow(SW_NORMAL);
}
