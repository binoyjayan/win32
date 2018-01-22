<!@page import="java.io.*">



<html>
<%@page import="java.sql.*" language="java"%>
<%@ page import="javax.swing.*" %>
<head>
<TITLE>6th sense search</title>
<script language="javascript">
function change(k)
{


   window.open(k);

}
</script>
<STYLE type=text/css>
.btn
{
	FONT-WEIGHT: bold; MARGIN-BOTTOM: -1px; WIDTH: 201px; CURSOR: hand; COLOR: #fff; PADDING-TOP: 1px; BACKGROUND-COLOR: #900
}
.cho {
	FONT-WEIGHT: bold; MARGIN-BOTTOM: -1px; WIDTH: 100px; CURSOR: hand; COLOR: BLUE; PADDING-TOP: 1px; BACKGROUND-COLOR: #93C2d3
}
.btn1
{
	FONT-WEIGHT: bold; MARGIN-BOTTOM: -1px; WIDTH: 201px; CURSOR: hand; COLOR: #900; PADDING-TOP: 1px; BACKGROUND-COLOR: #93C2d3
}
</STYLE>
</head>

<%
	
	int l = Integer.parseInt(request.getParameter("igl"));
        int count=Integer.parseInt(request.getParameter("count"));
        String uquery=request.getParameter("query");
        String type=request.getParameter("searchtype");
         int IMAGECOUNT=Integer.parseInt(request.getParameter("linkcount"));
	
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
<% out.println("<img src='" + LOGO[l] + "' ALIGN=LEFT>"); %>


<BR>
<BR>
<BR>
<BR>
<BR>
<BR>
<BR>
<BR>
<CENTER>


         <%
            out.println("<input type=hidden value="+l+" name=igl>"); 
           %>
<HR COLOR="#93A2A3" SIZE=6>

         
        

<CENTER>
<%




class Indexer
{
	Connection c;
	Statement  s;
	ResultSet r;
	Indexer()
	{
		c  = null;
		s = null;
		r = null;
	}
	public void init()
	{
		try
		{
			Class.forName("sun.jdbc.odbc.JdbcOdbcDriver");
			c=DriverManager.getConnection("jdbc:odbc:SIXTHSENSE","","");
			//c=DriverManager.getConnection("jdbc:odbc:SIXTHSENSE","cb206mc015","amrita");
			s=c.createStatement();
		}
		catch(Exception e)
		{
		}
	}

	public ResultSet execute(String table, String pattern, int flag)
	{
		r = null;
	
		String[] pat = new String[100];
		int n=0, i = 0;
		if(pattern == null)
			return null;		
		pattern = pattern.trim();		

		while(pattern.indexOf("+")!=-1)
		{
			pat[n] = pattern.substring(0,pattern.indexOf("+"));
			pattern=pattern.substring(pattern.indexOf("+")+1, pattern.length());
			n++;
		}
		if(pattern.length()!=0)
		{
			pat[n] = pattern;
			n++;
		}		
		//'pat[]' contains the patterns and n contains no of patterns in array 

			
		try
		{
			String sql=null;
			String temp=null;			
			
			sql = "select * from " + table;
			if(pat[0] != null)
			{
				sql = sql + " where istring like '%" + pat[0] + "%'";
				for(i=1;i<n;i++)
				{
					sql = sql + " and istring like '%" + pat[i] + "%'";				
				}
			}
			
			if(flag == 1)
				sql = sql + " order by pr desc";
			else
				sql = sql + " order by lad desc";
			sql = sql + ";";
			//System.out.println(sql);
			r = s.executeQuery(sql);
			
		}
		catch(Exception e)
		{
			//System.out.println(e);
			return null;
		}
		return r;	
	}
	public void close()
	{
		try
		{
			c.close();
		}
		catch(Exception e)
		{
		}
	}
}
















/*Connection c=null;
     Statement  s=null;
     ResultSet r=null;
     
 Class.forName("sun.jdbc.odbc.JdbcOdbcDriver");
     c=DriverManager.getConnection("jdbc:odbc:SIXTHSENSE","cb206mc015","amrita");
     s=c.createStatement();
  sql="select * from image where istring like'%"+uquery+"%';";
   out.println("<br>"+sql);

   r=s.executeQuery(sql);*/








      %>
<center>
<%     
       int i=0,flag=0,curcount=0,initcount=0,lastcount=0,heading=1;

       initcount=count+1;

       Indexer index=new Indexer();

        ResultSet r=null;

        String sql=null,url=null,istring=null,link=null;

        index.init();


        if(type.equals("pr"))
        r=index.execute("image",uquery,1);
        else
         r=index.execute("image",uquery,0);
          
          
                 

     out.println("<table border=6 bordercolor=blue>");
   
       while(r.next())
         {
              
         
              
             if(i==count)
               flag=1;



              if(flag==1)
                {

                istring=r.getString(1);

                    if(istring.indexOf(",")!=-1)
                      istring=istring.substring(0,istring.indexOf(","));

                url=r.getString(2);


               // out.println(url);

                            if(heading==1)
                            {
                                out.println("<center><font color=blue SIZE=6><b><i>Images for you.........</i></b></font></center>");
                                heading=0;
                            }


               if(count%4==0)
                out.println("<tr>");
               out.println("<td><img    src="+url+"   height=150 width=150 onclick='change(\""+url+"\")'><br><center><a href='"+url+"'>"+istring+"</a></center></td>");
               count++;
               curcount++;
            
                if(count%4==0)
                out.println("</tr>");


             if(count%IMAGECOUNT==0)
               break;


                 
                 
                
                   }
                       

                    
                
              i++;
              

          

           }



  
  if(count==0)
      {

           out.println("<br><br><BR><font color=red size=5><B><I>NO PICTURES MATCHING WITH YOUR QUERY</I></B></FONT><br><br><BR>");

      }


lastcount=count;

   if(count%IMAGECOUNT!=0)
    out.println("</tr>");
    

out.println("</table>");








  
 // out.println("SPACE TO DISPLAY IMAGES<BR>");   
//out.println("START COUNT="+count+"<br>");
//out.println("search query='"+uquery+"'<BR>");      




  if((count-curcount)==0)
    {
 curcount=0;
   
     }

   else
     {
         curcount=count-(curcount+IMAGECOUNT);
       
 
         }




 if(count%IMAGECOUNT!=0||!r.next())
        {
           count=-1;

          }


index.close();


  %>
</center>
</CENTER>
<HR COLOR="#93A2A3" SIZE=6>


<center>

<br>

<form>
<table  width=100>

<tr>
         
	
<td bgcolor='#93C2d3'>
    
<%
    out.println("<INPUT TYPE=hidden  NAME=query value='"+uquery+"'>");
        out.println("<input type=hidden value="+l+"  NAME=igl>");
 out.println("<input type=hidden value="+IMAGECOUNT+"  NAME=linkcount>");
          
          out.println("<input type=hidden value="+curcount+" name=count>");
         out.println("<input type=hidden value='"+type+"' name=searchtype>");

  %>


<input class=btn type=submit name=k value="&lt;-PREVIOUS">
	</td>
          


</form>















<%
out.println("<td><font color=blue size=5>|"+initcount+"....."+lastcount+"|</font>");


if(count==-1)
  {


out.println("");
         
	
	out.println("<td bgcolor='#93C2d3'>");



	out.println("<input class=btn1 type=button name=k value=\"NO MORE PICTURES\">");
	out.println("</td>");
          
out.println("</TR>");

out.println("</table>");

}
else
  {

out.println("<form>");


out.println("");
         
	
	out.println("<td bgcolor='#93C2d3'>");
    

     out.println("<INPUT TYPE=hidden  NAME=query value='"+uquery+"'>");
        out.println("<input type=hidden value="+l+"  NAME=igl>");
          out.println("<input type=hidden value="+count+" name=count>");
          out.println("<input type=hidden value="+IMAGECOUNT+"  NAME=linkcount>");

          out.println("<input type=hidden value='"+type+"' name=searchtype>");

	out.println("<input class=btn type=submit name=k value=\" NEXT-&gt;\">");
	out.println("</td>");
          
out.println("</TR>");

out.println("</table>");
out.println("</form>");






   }
%>

<br>

<table  BORDER=0 height=25 width=370>
<tr background=pink>
            <td BGCOLOR=#93C2d3 cellspacing="10" cellpadding="10">
	<form action="index.jsp" >
         <%
            out.println("<input type=hidden value="+l+" name=igl>"); 
           %>
         
        <br><center><input class=cho type=submit value=WEB name=ig></center></form>
	</td>

         
	<td BGCOLOR=#93C2d3 BORDER=0>
	<form action="IMAGES.jsp" ><BR>
<%
            out.println("<input type=hidden value="+l+" name=igl>"); 
           %>
         
<input class=cho type=submit value=IMAGES name=ig></center></form>
	</td>


	<td BGCOLOR=#93C2d3 cellspacing="10" cellpadding="10">
	<form action="AUDIOS.jsp">
         <%
            out.println("<input type=hidden value="+l+" name=igl>"); 
           %>
         
        <br><center><input class=cho type=submit value=AUDIOS name=ig></center></form>
	</td>

	
	<td BGCOLOR=#93C2d3 cellspacing="10" cellpadding="10">
	<form action="VIDEOS.jsp" >
         <%
            out.println("<input type=hidden value="+l+" name=igl>"); 
           %>
         
        <br><center><input class=cho type=submit value=VIDEOS name=ig></center></form>
	</td>


	<td BGCOLOR=#93C2d3 cellspacing="10" cellpadding="10">
	<form action="DOCUMENTS.jsp" >
         <%
            out.println("<input type=hidden value="+l+" name=igl>"); 
           %>
         
        <br><center><input class=cho type=submit value=DOCUMENTS name=ig></center></form>
	</td>
      
</tr>
</table>








</center>


<FORM ACTION="imagesearch.jsp">
<table  width=370>
<TR>
	<TD bgcolor="#93C2d3">
	<INPUT TYPE=TEXT size=50 NAME=query value='Image Query'>
	</TD>
	<td bgcolor="#93C2d3">
         <%
            out.println("<input type=hidden value="+l+"  NAME=igl>"); 
              out.println("<input type=hidden value="+type+"  NAME=searchtype>"); 
              out.println("<input type=hidden value="+IMAGECOUNT+"  NAME=linkcount>");
          
          
           %>
           <input type=hidden value=0 name=count>
         
	<input class=cho type=submit>
	</td>
</TR>
</table>
</FORM>



<HR COLOR="#93A2A3" SIZE=7>





</body>
</html>