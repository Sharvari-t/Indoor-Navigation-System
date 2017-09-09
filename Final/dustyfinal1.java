//Program that generates destination co-ordinates when the user clicks on 
// the floorplan image to point the destination where the bot has to arrive.

import java.awt.*;
import java.net.*;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Image;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import java.io.BufferedWriter;
import java.io.File;
import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;

import javax.imageio.ImageIO;
import javax.swing.*;
public class dustyfinal1 {
public static void main(String[] args) {
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
			new dustyfinal1(5000);
				}
		});
}
private Socket ss= null;
private ServerSocket s= null;
	dustyfinal1(int port){
		JFrame j=new JFrame("NAVIGATION");
		j.setSize(200,200);
		j.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		BufferedImage back = null;
		try {
			 back=ImageIO.read(new File("C:\\Users\\Lenovo\\Desktop\\s.jpg"));
		} catch (IOException e) {
			e.printStackTrace();
		}
		Image img1=back.getScaledInstance(900,910,Image.SCALE_SMOOTH);
		ImageIcon img=new ImageIcon(img1);
		JLabel w = new JLabel(img);
		w.setPreferredSize(new Dimension(900,910));
		w.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				System.out.println((e.getY()/65)+","+(e.getX()/60));
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
			    	num1=String.valueOf(e.getX()/60)+"\n";
			        send.write(num1);
			        send.flush();
			        ss.close();
			      }
			    catch(IOException i)
			    {
			        System.out.println(i);
			    }
			}
		});
		j.add(w);
		j.setLayout(new FlowLayout());
		j.setLocationRelativeTo(null);
		j.setVisible(true);
	}
}

