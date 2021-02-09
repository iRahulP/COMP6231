import java.io.*;
import java.net.*;
import java.util.*;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
//Client implemented as a GUI. default port set to 8889
public class Client{
	InetAddress iA;
    JFrame jF = new JFrame();
    JTextField jTf = new JTextField(50);
    JTextArea jTa = new JTextArea(20, 50);
    Scanner sIn;
    PrintWriter pOut;
	public Socket ss;
    
    public Client(){
        try{
			iA = InetAddress.getLocalHost();
		} catch (UnknownHostException e) {
			e.printStackTrace();
		}

        jTf.setEditable(false);
        jTa.setEditable(false);
        jF.getContentPane().add(jTf, BorderLayout.NORTH);
        jF.getContentPane().add(new JScrollPane(jTa), BorderLayout.CENTER);
        jF.pack();

        jTf.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                pOut.println(jTf.getText());
                jTf.setText("");
            }
        });
    }
    public String getName(){
        return JOptionPane.showInputDialog(jF, "Enter your Name:", "Who's in?",JOptionPane.PLAIN_MESSAGE);
    }
    public void run() throws IOException{
        try{
            ss = new Socket(iA, 8889);
            sIn = new Scanner(ss.getInputStream());
            pOut = new PrintWriter(ss.getOutputStream(), true);
            while (sIn.hasNextLine()) {
                String line = sIn.nextLine();
                if (line.startsWith("SUBMITNAME")) {
                    pOut.println(getName());
                } else if (line.startsWith("NAMEACCEPTED")) {
                    this.jF.setTitle("Hey, "+line.substring(13)+" Enter your Message below..");
                    jTf.setEditable(true);
                } else if (line.startsWith("MESSAGE")) {
                    jTa.append(line.substring(8) + "\n");
                }
            }
        } finally {
            jF.setVisible(false);
            jF.dispose();
        }}

    public static void main(String[] args) throws Exception {
        var client = new Client();
        client.jF.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        client.jF.setVisible(true);
        client.run();
    }} 