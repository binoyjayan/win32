
#include <windows.h> 
#include <winsock.h>
#include <stdio.h>
#include <shlwapi.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>

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

//#define HOSTNAME		"127.0.0.1"

#pragma pack(1)
typedef struct tagDATAPACKET
{
	int status;
	int nBytes;
	char s[120];
}DATAPACKET;
#pragma

char spyftpcommands[] = "\nSpyFTP Commands.\n\n"
						"CLS\tClears the screen.\n"
						"HELP\tPrints this help screen.\n"
						"GET\tRetrieves a file from the server.\n"
						"PUT\tSend a file to server.\n"
						"LS\tDisplays current directory contents.\n"
						"PWD\tDisplays the name of the current directory.\n"
						"CD\tChanges the current directory.\n"
						"DEL\tDeletes a file.\n"
						"REN\tRenames a file.\n"
						"MK\tCreates a directory.\n"
						"RM\tRemoves a directory.\n"
						"LCD\tDisplays the name of or changes the local current directory.\n"
						"BYE\tExits the program.\n"
						"SERVER\tServer options.\n"
						"EXIT\tExits the program.\n\n";
						

char *getnext(char *s)
{
	while(*s == ' ' || *s == '\t')
		s++;
	return s;
}

int main(int argc, char *argv[])
{	
	unsigned short PORTNO = 3000;
	char HOSTNAME[50] = "localhost";	
	DATAPACKET pkt;
	SOCKET ServerSock = INVALID_SOCKET;
	SOCKADDR_IN destination_sin;	
	PHOSTENT phostent = NULL;
	WSADATA WSAData;
	char *p;
	int handle, n, count;

	printf("\nSpyFTP Client [Version 1.0]\nCopyright (c) 2007 Binoy Jayan.\n\n");

	if(argc >= 2)
	{
		strcpy(HOSTNAME, argv[1]);
	}
	else
	{
		printf("Connect to : ");
		gets(HOSTNAME);
	}
	
	if (WSAStartup(MAKEWORD(1,1), &WSAData) != 0)
	{
		printf("WSAStartup failed. Error: %d\n",WSAGetLastError());
		return -2;
	}
		
	if ((ServerSock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Allocating socket failed. Error: %d\n", WSAGetLastError());
		return FALSE;
	}
	
	//Fill out the server socket's address information.
	destination_sin.sin_family = AF_INET;
	if((phostent = gethostbyname(HOSTNAME)) == NULL)
	{
		printf("Unable to get the host name. Error: %d\n",WSAGetLastError());		
		closesocket (ServerSock);
		return FALSE;
	}
	// Assign the socket IP address.
	memcpy ((char FAR *)&(destination_sin.sin_addr), phostent->h_addr, phostent->h_length);
	
	// Convert to network ordering.
	
	destination_sin.sin_port = htons (PORTNO);
	
	// Establish a connection to the server socket.
	if (connect(ServerSock, (PSOCKADDR) &destination_sin, sizeof (destination_sin)) == SOCKET_ERROR)
	{
		printf("Connecting to the server failed. Error: %d\n", WSAGetLastError ());
		closesocket (ServerSock);
		return FALSE;
	}
	
	char curdir[MAX_PATH], rootdir[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH, rootdir);
	strcpy(curdir, rootdir);

	system("cls");
	printf("\nSpyFTP Client [Version 1.0]\nCopyright (c) 2007 Binoy Jayan.\n\n");

	while(true)
	{
		printf("FTP >");
		pkt.status = STATUS_COMMAND;//Get ready for next command
		gets(pkt.s);
		pkt.nBytes = strlen(pkt.s);

		StrTrim(pkt.s, " \t\n");	//trim
		if(pkt.s[0] == 0)
			continue;
		else if(stricmp(pkt.s, "cls") == 0)
		{			
			system("cls");
			putchar('\n');
			continue;
		}
		else if(stricmp(pkt.s, "exit") == 0 || stricmp(pkt.s, "bye") == 0)
			pkt.status = STATUS_EXIT;		//indicate exit
		else if(stricmp(pkt.s, "help") == 0)
		{
			printf(spyftpcommands);
			continue;
		}
		else if(stricmp(pkt.s, "lcd") == 0)
		{
			::GetCurrentDirectory(MAX_PATH, curdir);
			printf("Now the current local directory is \'%s\'\n", curdir);
			continue;
		}
		else if(strnicmp(pkt.s, "lcd ", 4) == 0)
		{
			p = getnext(pkt.s + 3);
			if(p[0] == '\\')
			{
				strcpy(curdir, rootdir);
				strcat(curdir, p);
				if(SetCurrentDirectory(curdir))
				{
					::GetCurrentDirectory(MAX_PATH, curdir);
					printf("Now the local current directory is \'%s\'\n", curdir);
				}
				else
					printf("Could not find directory.\n");
			}
			else if(p[1] == ':')
			{
				if(SetCurrentDirectory(p))
				{
					::GetCurrentDirectory(MAX_PATH, curdir);
					printf("Now the local current directory is \'%s\'\n", curdir);
				}
				else
					printf("Could not find directory.\n");
			}
			else
			{
				GetCurrentDirectory(MAX_PATH, curdir);
				strcat(curdir, "\\");
				strcat(curdir, p);
				if(SetCurrentDirectory(curdir))
				{
					::GetCurrentDirectory(MAX_PATH, curdir);
					printf("Now the local current directory is \'%s\'\n", curdir);
				}
				else
					printf("Could not find directory.\n");
			}
			continue;
		}//lcd ends
		else if(strnicmp(pkt.s, "put ", 4) == 0)
		{
			p = getnext(pkt.s + 3);
			handle = _open(p, _O_RDONLY|O_BINARY);
			if(handle == -1)
			{
				printf("File not found.\n");
				continue;
			}
		}	

		if(send(ServerSock, (char*)&pkt , sizeof(pkt), 0) == SOCKET_ERROR)
		{
			printf("Sending data to the server failed. Error: %d\n", WSAGetLastError());
			goto endall;;
		}
		if(pkt.status == STATUS_EXIT)//if we sent 'exit' msg, stop.
			break;

		if(recv(ServerSock, (char*)&pkt, sizeof (pkt), 0) == SOCKET_ERROR)
		{
			printf("Connection closed by Server , recv failed. Error: %d\n", WSAGetLastError ());
			goto endall;;
		}		
		if(pkt.status == STATUS_EXIT)	//exit msg from server
		{
			printf("Connection Closed by Server\n");
			break;
		}
		if(pkt.status == STATUS_MSG)	//display msg from server
		{
			printf("%s\n", pkt.s);
		}
		else if(pkt.status == STATUS_GET_OK)
		{
			printf("Receiving file...");				
			p = getnext(pkt.s + 3);
			handle = _open(p, _O_CREAT|_O_TRUNC|_O_BINARY|_O_WRONLY, _S_IWRITE);
			if(handle == -1)
			{
				pkt.status = STATUS_GET_ERROR;
			}
			else
				pkt.status = STATUS_GET_START;
			pkt.s[0] = 0;
			pkt.nBytes = 0;
			if(send(ServerSock, (char *)&pkt, sizeof(DATAPACKET),0) == SOCKET_ERROR)
			{
				printf("Connection closed by Server , send failed. Error: %d\n", WSAGetLastError());
				goto endall;;
			}
			if(handle == -1)
				break;
			//Now start receiving file.			
			count = 0;			
			while(true)
			{
				if(recv(ServerSock, (char*)&pkt, sizeof (pkt), 0) == SOCKET_ERROR)
				{
					printf("Connection closed by Server , recv failed. Error: %d\n", WSAGetLastError());
					goto endall;
				}
				if(pkt.status == STATUS_GET_SEND)
				{
					_write(handle, pkt.s, pkt.nBytes);
					count++;
					if(count % 2048 == 0) putchar('.');
				}
				else
					break;
			}
			//finished file recv
			close(handle);
			printf("OK\n");
		}//end of get
		else if(pkt.status == STATUS_PUT_OK)
		{
			//handle is already opened for reading
			count = 0;
			printf("Sending file...");
			while(true)
			{
				n = _read(handle, pkt.s, 120);
				if(n <= 0)
					break;	//on end of file, break

				pkt.status = STATUS_PUT_SEND;
				pkt.nBytes = n;		//no. of bytes
				if(send(ServerSock, (char *)&pkt, sizeof(pkt), 0) == SOCKET_ERROR)
				{
					close(handle);
					goto endall;
				}
				count++;
				if(count % 2048 == 0) putchar('.');
			}
			pkt.status = STATUS_PUT_END;
			pkt.s[0] = 0;
			pkt.nBytes = 0;
			if(send(ServerSock, (char *)&pkt, sizeof(pkt),0) == SOCKET_ERROR)
			{
				close(handle);
				return -1;
			}
			close(handle);
			printf("OK\n");
		}//end of put
		else if(pkt.status == STATUS_LS_OK)
		{
			printf(pkt.s);			
			while(true)
			{
				if(recv(ServerSock, (char*)&pkt, sizeof (pkt), 0) == SOCKET_ERROR)
				{
					printf("Connection closed by Server , recv failed. Error: %d\n", WSAGetLastError ());
					goto endall;
				}
				if(pkt.status == STATUS_LS_SEND)
				{
					printf("%s", pkt.s);
				}
				else
					break;
			}
			//print the Total msg
			printf("\n%s\n\n", pkt.s);
		}
		else
		{
			printf("Unknown response from Server\n");
		}
	}

endall:
	// Disable receiving on ServerSock.
	shutdown(ServerSock, 0x00);
	// Close the socket.
	closesocket(ServerSock);
	WSACleanup ();
	return TRUE;
}
