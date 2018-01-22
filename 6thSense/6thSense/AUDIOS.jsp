<!@page import="java.io.*">

<html>
<head>
<TITLE>6th sense search</title>
<STYLE type=text/css>
.btn
{
	FONT-WEIGHT: bold; MARGIN-BOTTOM: -1px; WIDTH: 100px; CURSOR: hand; COLOR: #fff; PADDING-TOP: 1px; BACKGROUND-COLOR: #900
}
.cho {
	FONT-WEIGHT: bold; MARGIN-BOTTOM: -1px; WIDTH: 100px; CURSOR: hand; COLOR: BLUE; PADDING-TOP: 1px; BACKGROUND-COLOR: #93C2d3
}
.cho1 {
	FONT-WEIGHT: bold; MARGIN-BOTTOM: -1px; WIDTH: 100px; CURSOR: hand; COLOR:  #fff; PADDING-TOP: 1px; BACKGROUND-COLOR:#900
}
</STYLE>
</head>

<%
	
	int l = Integer.parseInt(request.getParameter("igl"));
	
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
<table  BORDER=0 height=25 width=370>
<tr background=pink>
    <td BGCOLOR=#93C2d3 cellspacing="10" cellpadding="10">
	<form action="index.jsp">
         <%
            out.println("<input type=hidden value="+l+" name=igl>"); 
           %>
         
        <br><center><input class=cho type=submit value=WEB name=ig></center></form>
	</td>
	<td BGCOLOR=#93C2d3 cellspacing="10" cellpadding="10" >
	<br><form action="IMAGES.jsp" >
         <%
            out.println("<input type=hidden value="+l+" name=igl>"); 
           %>
	
         
        <center><input class=cho type=submit value=IMAGES name=ig></center></form>
	</td>


	<td BGCOLOR=#93C2d3 cellspacing="10" cellpadding="10">
	
         
        <center><input class=cho1 type=submit value=AUDIOS name=ig></center>
	</td>

	
	<td BGCOLOR=#93C2d3 cellspacing="10" cellpadding="10">
	<form action="VIDEOS.jsp" >
         <%
            out.println("<input type=hidden value="+l+" name=igl>"); 
           %>
         
        <br><center><input class=cho type=submit value=VIDEOS name=ig></center></form>
	</td>


	<td BGCOLOR=#93C2d3 cellspacing="10" cellpadding="10">
	<form action="DOCUMENTS.jsp">
         <%
            out.println("<input type=hidden value="+l+" name=igl>"); 
           %>
         
        <br><center><input class=cho type=submit value=DOCUMENTS name=ig></center></form>
	</td>
       
</tr>
</table>
<br>
<form action="audiosearch.jsp">
<table  width=370>
<tr>
  <td><font color= blue size=4>Search Based On:</font>&nbsp;&nbsp;&nbsp;
   
	<b>Date of Creation</b><input type="radio" name=searchtype value=lad></td>
	<td><b>Popularity</b><input type="radio" name=searchtype value=pr checked></td></font></TR>
<tr>
<td>&nbsp;</td><td>&nbsp;</td>

</tr>



<td><font color= blue size=4>No of Links in a page:</font></td>
<td>
<select name="linkcount">
  <option value="3">
      3
  </option>    
  <option  value="4">
      4
  </option>
    <option  value="5">
      5
  </option>
    <option  value="6">
      6
  </option>
    <option  value="7">
      7
  </option>
    <option  value="8">
      8
  </option>
    <option  value="9" selected>
      9
  </option>
    <option  value="10">
      10
  </option>
    <option  value="11">
      11
  </option>
    <option  value="12">
      12
  </option>
   <option  value="13">
      13
  </option>
   <option  value="14">
      14
  </option>
   <option  value="15">
      15
  </option>
  
</select><td>&nbsp;</td>
</tr>

<tr><td>&nbsp</td></tr>

<TR>
	<TD bgcolor="#93C2d3">
	<INPUT TYPE=TEXT size=50 NAME=query value='Audio Query'>
	</TD>
	<td bgcolor="#93C2d3">
	<input class=btn type=submit name=k> 
      <%
            out.println("<input type=hidden value="+l+"  NAME=igl>"); 
           
          
          
           %>
           <input type=hidden value=0 name=count>
        
	</td>
</TR>
</table>
</form>
<br><br><br>

<HR COLOR="#93A2A3" SIZE=30>
</center>

</body>
</html>