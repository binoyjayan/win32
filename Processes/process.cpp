
#include <afxwin.h>
#include <Psapi.h>


char str[102400];
char tempStr[512];
char szProcessName[MAX_PATH] = "UnKnown";

void PrintProcessName(DWORD processID)
{
	// Get a handle to the passed-in process ID
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE, processID );
	
	// Get the process name
	if(hProcess)
	{
		HMODULE hMod;
		DWORD cbNeeded;
		if(EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
		{
			GetModuleBaseName(hProcess, hMod, szProcessName,sizeof(szProcessName));
			//GetModuleFileName(hMod,szProcessFileName,MAX_PATH);	
		}
	}
	// Print the process name and ID
	sprintf(tempStr,"%s:%u#",szProcessName,processID);
	strcat(str,tempStr);
	strcat(str,"\n");
	CloseHandle( hProcess );
}
void EnumerateProcesses()
{
	DWORD aProcesses[1024];		// Array of process IDs
	DWORD cbNeeded;			// Byte count returned...
	DWORD cProcesses;		// The number of 'em obtained

	unsigned int i;
	// Get a list of all current PIDs running
	if(!EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded))
		return;
	// Get the count of PIDs in the array
	cProcesses = cbNeeded / sizeof(DWORD);
	// Print the name and process identifier for each process
	for(i = 0; i < cProcesses; i++)
	{
		PrintProcessName(aProcesses[i]);
	}
}
void main()
{
	memset(str,0,102400);
	EnumerateProcesses();
	printf(str);
}