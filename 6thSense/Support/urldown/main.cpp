

#include <urlmon.h>
#include <stdio.h>

char url[256]   = "f:\\main.plg";
char dfile[256] = "download.html";


/*
Note: link the library "urlmon.lib" for the function 'URLDownloadToFile'
*/
main()
{	
	
	URLDownloadToFile(0,url, dfile, 0, 0);
	return 0;
}