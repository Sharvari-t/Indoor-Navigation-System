package gui;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;
import javax.swing.*;
import java.net.*;
import java.io.*;
public class dustyfinal {
	public static void main(String[] args) {
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
			new dustyfinal(5000);
				}
		});
}
	private Socket ss= null;
	private ServerSocket s= null;
	int[][] a=new int[15][15];
dustyfinal(int port){
	JFrame n=new JFrame("GRID_GENERATOR");
	n.setSize(200,200);
	n.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	BufferedImage floor=null;
	try {
		 floor=ImageIO.read(new File("C:\\Users\\Lenovo\\Desktop\\s.jpg"));
	} catch (IOException e) {
		e.printStackTrace();
	}
	int w=floor.getWidth();
	int h=floor.getHeight();
	BufferedImage dimg=new BufferedImage(900,910,floor.getType());
	Graphics2D g=dimg.createGraphics(); 
   g.drawImage(floor, 0, 0, 900, 910, 0, 0, w, h, null);  
   g.dispose();
   w=dimg.getWidth();
   h=dimg.getHeight();
	int x=0,x1 = 0,y=0,y1=0,q=1,l=0,flag=0,p=0,z=0,o=0;
	for(int i=1;i<=210;i++){
    x=q*60;
     if(((i-1)%15)==0) {
    	 y1=y;
    	y=y+65;
    	  q=1;
    	  x1=0;
    	  x=60;
    	  p++;
    	  z=0;
     }	 
     if(i==1) {
    	 x1=0;
    	 y1=0;
    	 y=65;
     }
    for(int j=x1;j<=x;j++) {
    	 for(int k=y1;k<=y;k++) {
    		 if(k<h&&j<w) {
    		 Color my=new Color(dimg.getRGB(j, k));
    		 if(0<=my.getRed()&&my.getRed()<=10) {
    		a[p][z]=0;
    		flag=1;
    		o++;
    		break;
    		
    	 }
     }	
    	 }
    	if(flag==1)
    		break;
     }
    if(flag==0) {
    	a[p][z]=1;
    	l++;
    }
    z++;
   flag=0;
     x1=x;
     q++;
     
	}
	for(int i=0;i<a[0].length;i++) {
		for(int j=0;j<a.length;j++) {
			System.out.print(a[i][j]);
		}
		System.out.println("");
		}
	
	String num1;
	try
    {   
        s = new ServerSocket(port);
        System.out.println("Server started");
        System.out.println("Waiting for a client .");
        ss = s.accept();
        System.out.println("Client accepted");
        OutputStream os=ss.getOutputStream();
		OutputStreamWriter oss=new OutputStreamWriter(os);
		BufferedWriter send=new BufferedWriter(oss);
        for(int i=0;i<a.length;i++) {
    		for(int j=0;j<a[0].length;j++) {
    			 num1=String.valueOf(a[i][j])+"\n";
    	          send.write(num1);
    	          }
    		}
       send.flush();
       ss.close();
    }
    catch(IOException i)
    {
        System.out.println(i);
    }
}
}
