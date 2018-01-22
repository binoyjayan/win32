import java.io.*;
import java.sql.*;

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
			c=DriverManager.getConnection("jdbc:odbc:SIXTHSENSE","cb206mc015","amrita");
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

class imgsearch
{
	public static void main(String arg[])
	{
		try
		{
			Indexer ind = new Indexer();
			ind.init();
	
			ResultSet r=null;	
		
			r = ind.execute("image", "mech", 1);
	
			while(r.next())
			{
				System.out.println(r.getString(1)+ ":" + r.getString(2));
			}			
		}
		catch(Exception e)
		{
			System.out.println(e);
		}
	}
}
