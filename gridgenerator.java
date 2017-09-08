package gui;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.*;
public class gridgenerator {
	public static void main(String[] args) {
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
			new gridgenerator();
				}
		});
}
gridgenerator(){
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
	 int[][] a=new int[27][18];
	for(int i=1;i<=468;i++){
    x=q*50;
     if(((i-1)%18)==0) {
    	 y1=y;
    	y=y+35;
    	  q=1;
    	  x1=0;
    	  x=50;
    	  p++;
    	  z=0;
     }	 
     if(i==1) {
    	 x1=0;
    	 y1=0;
    	 y=35;
     }
    for(int j=x1;j<=x;j++) {
    	 for(int k=y1;k<=y;k++) {
    		 if(k<h&&j<w) {
    		 Color my=new Color(dimg.getRGB(j, k));
    		 if(0<=my.getRed()&&my.getRed()<=20) {
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
   System.out.println(a.length+","+a[0].length);
	for(int i=0;i<a.length;i++) {
		for(int j=0;j<a[0].length;j++) {
			System.out.print(a[i][j]);
		}
		System.out.println("");
		}
	Image floor1=dimg.getScaledInstance(900, 910, Image.SCALE_SMOOTH);
    ImageIcon img=new ImageIcon(floor1);
	JLabel show=new JLabel(img);
	show.setPreferredSize(new Dimension(900,910));
	show.addMouseListener(new MouseAdapter() {
		@Override
		public void mouseClicked(MouseEvent e) {
			System.out.println(e.getX()+","+e.getY());
		}
	});
	n.add(show);
	n.setLayout(new FlowLayout());
	n.setLocationRelativeTo(null);
	n.setVisible(true);
	
}
}
