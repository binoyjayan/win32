<!@page import="java.io.*">

<html>
<head>
<TITLE>6th sense search</title>
<STYLE type=text/css>
.btn
{
	FONT-WEIGHT: bold; MARGIN-BOTTOM: -1px; WIDTH: 100px; CURSOR: hand; COLOR: #fff; PADDING-TOP: 1px; BACKGROUND-COLOR: #900
}
</STYLE>
</head>

<%
	double k=0.0;
	k = java.lang.Math.random();
	int l = 0;
	l = (int) ((k*100)%12);
	String[] LOGO = new String[12];
	LOGO[0] = "images/p0.jpg";
	LOGO[1] = "images/p1.jpg";
	LOGO[2] = "images/p2.jpg";
	LOGO[3] = "images/p3.jpg";
	LOGO[4] = "images/p4.jpg";
	LOGO[5] = "images/p5.jpg";
	LOGO[6] = "images/p6.jpg";
	LOGO[7] = "images/p7.jpg";
	LOGO[8] = "images/p8.jpg";
	LOGO[9] = "images/p9.jpg";
	LOGO[10] = "images/p10.jpg";
	LOGO[11] = "images/p11.jpg";
%>

<body>

<img src='images/rightworld.gif' align=right>

<br><br><br>

<center>

<table border=0>
<tr>
<td>&nbsp;</td>
<td>&nbsp;</td>
<td>&nbsp;</td>
<% out.println("<td><img src='" + LOGO[l] + "'></td>"); %>
<td>&nbsp;</td>
<td>&nbsp;</td>
<td>&nbsp;</td>
</tr>

<tr>
<td><img src="images/searchdog.gif" width=150></td>
<td><img src="images/searchdog.gif" width=150></td>
<td><img src="images/searchdog.gif" width=150></td>
<td>&nbsp;</td>
<td><img src="images/searchdog.gif" width=150></td>
<td><img src="images/searchdog.gif" width=150></td>
<td><img src="images/searchdog.gif" width=150></td>
</tr>
</table>

<br><HR COLOR="#93A2A3" SIZE=30>
<BR>
<BR>
<table  BGCOLOR=#93b2dd BORDER=0 height=30 width=370>
<tr background=pink>
	<td BGCOLOR=#93C2d3>
	<A HREF="a.html"><font color=BLUE size=4><b>IMAGES</b></font></A>
	</td>

	<td BGCOLOR=#93C2d3>
	<A HREF=""><font color=BLUE size=4> <b>VIDEOS</b>  </font></A>
	</td>
	
	<td BGCOLOR=#93C2d3>
	<A HREF=""> <font color=BLUE size=4><b>AUDIOS</b></font></A>
	</td>

	<td BGCOLOR=#93C2d3>
	<A HREF=""><font color=BLUE size=4><b>CODES</b></font></A>
	</td>
</tr>
</table>
<br>

<table  width=370>
<TR>
	<TD bgcolor="#93C2d3">
	<INPUT TYPE=TEXT size=50 NAME=query value=k>
	</TD>
	<td bgcolor="#93C2d3">
	<input class=btn type=submit>
	</td>
</TR>
</table>
<br><br><br>

<HR COLOR="#93A2A3" SIZE=30>
</center>

</body>
</html>