package gui;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Image;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.SwingUtilities;
public class mouseclick {
	public static void main(String[] args) {
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
			new mouseclick();
				}
		});
}
	mouseclick(){
		JFrame j=new JFrame("NAVIGATION");
		j.setSize(200,200);
		j.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		BufferedImage back = null;
		try {
			 back=ImageIO.read(new File("C:\\Users\\Lenovo\\Desktop\\m.jpg"));
		} catch (IOException e) {
			e.printStackTrace();
		}
		Image img1=back.getScaledInstance(900,900,Image.SCALE_SMOOTH);
		ImageIcon img=new ImageIcon(img1);
		JLabel w = new JLabel(img);
		w.setPreferredSize(new Dimension(900,900));
		w.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				System.out.println(e.getX()+","+e.getY());
			}
		});
		j.add(w);
		j.setLayout(new FlowLayout());
		j.setLocationRelativeTo(null);
		j.setVisible(true);
	}
}
