// Program on Rpi to receive the destination co-ordinates input by the user
// Uses sockets to receive the data
import java.net.*;
import java.io.*;
public class Clientside1
{
    private Socket s = null;
    private DataInputStream  in  = null;
    private DataOutputStream out = null;
 int x,y;
 String num1;
    public Clientside1(String address, int port)
    {
        try
        {
            s = new Socket(address, port);
            System.out.println("Connected");
            InputStream is=s.getInputStream();
			InputStreamReader iss=new InputStreamReader(is);
			BufferedReader receive=new BufferedReader(iss);
		           num1=receive.readLine();
			        x=Integer.parseInt(num1);
			        num1=receive.readLine();
			        y=Integer.parseInt(num1);
			        
              s.close();
  }
        catch(UnknownHostException u)
        {
            System.out.println(u);
        }
       
        catch(IOException i)
        {
            System.out.println(i);
        }
        
    }
 public static void main(String args[])
    {
        Clientside1 c = new Clientside1("192.168.43.230", 5000);
    }
}

