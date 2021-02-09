import java.io.*;
import java.util.*; 
import java.net.*; 

public class Server{ 
	
    public static Vector<ClientHandler> ar = new Vector<>(); 
    public static int i = 0; 
    public static void main(String[] args) throws Exception{ 
        int portNbr = 8421;
        ServerSocket ss = new ServerSocket(portNbr);   
        Socket s; 
        
        //getting requests and assigning threads respectively
        while (true){ 
            s = ss.accept(); 
            System.out.println("New client request received : " + s); 
            DataInputStream dIS = new DataInputStream(s.getInputStream()); 
            DataOutputStream dOS = new DataOutputStream(s.getOutputStream()); 
             
            System.out.println("Creating a new handler for this client..."); 
  
            ClientHandler cH = new ClientHandler(s,"client " + i, dIS, dOS); 
            
            //Generating thread for each Client request using clientHandler 
            Thread t = new Thread(cH);   
  //          System.out.println("Adding this client to active client list"); 
  
            // add this client to active clients list 
//            ar.add(cH); 
  
            // start the thread. 
            t.start(); 
  
            // increment i for new client. 
            // i is used for naming only, and can be replaced 
            // by any naming scheme 
            i++; 
  
        } 
    } 
} 
  
class ClientHandler implements Runnable{ 
    
	Scanner sc = new Scanner(System.in); 
    
    public String name; 
    public DataInputStream dIS; 
    public DataOutputStream dOS; 
    public Socket s; 
    boolean isloggedin; 
      
    // constructor 
    public ClientHandler(Socket s, String name, DataInputStream dIS, DataOutputStream dOS) { 
        this.dIS = dIS; 
        this.dOS = dOS; 
        this.name = name; 
        this.s = s; 
        this.isloggedin=true; 
    } 
  
    @Override
    public void run() { 
  
        String received; 
        while (true)  
        { 
            try
            { 
                // receive the string 
                received = dIS.readUTF(); 
                  
                // break the string into message and recipient part 
                StringTokenizer st = new StringTokenizer(received, "#"); 
                String MsgToSend = st.nextToken(); 
                String recipient = st.nextToken(); 
  
                // search for the recipient in the connected devices list. 
                // ar is the vector storing client of active users 
                for (ClientHandler mc : Server.ar)  
                { 
                    // if the recipient is found, write on its 
                    // output stream 
                    if (mc.name.equals(recipient) && mc.isloggedin==true)  
                    { 
                        mc.dOS.writeUTF(this.name+" : "+MsgToSend); 
                        break; 
                    } 
                } 
            } catch (IOException e) { 
                  
                e.printStackTrace(); 
            } 
              
        } 
    } 
}