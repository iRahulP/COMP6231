import java.io.*;
import java.net.*;
import java.util.*;
import java.util.concurrent.Executors;
//Server uses dynamic threadpools for handling multiple clients. Port fixed at 8889
public class Server {
    public static List<String> names = new ArrayList<>();
    public static List<PrintWriter> writers = new ArrayList<>();
    public static void main(String[] args) throws Exception{
        var pool = Executors.newCachedThreadPool();
        try (var listener = new ServerSocket(8889)){
            while (true){
            	Socket vs = listener.accept();
                pool.execute(new clientHandler(vs));
            }
        }}
    public static class clientHandler implements Runnable{
    	public Socket socket;
        public String name;
        public Scanner sIn;
        public PrintWriter pOut;
        
        public clientHandler(Socket socket){
            this.socket = socket;
        }
        public void run(){
            try{
                sIn = new Scanner(socket.getInputStream());
                pOut = new PrintWriter(socket.getOutputStream(), true);
                while(true){
                    pOut.println("SUBMITNAME");
                    name = sIn.nextLine();                   
                    synchronized (names){
                        if(!name.isBlank()){
                            names.add(name);
                            break;
                        }
                        else{
                        	return;
                        }
                    }}
                pOut.println("NAMEACCEPTED "+name);
                for (PrintWriter writer : writers){
                    writer.println("MESSAGE "+name+" has joined");
                }
                writers.add(pOut);
                
                while (true){
                    String input = sIn.nextLine();
                    for (PrintWriter writer : writers){
                        writer.println("MESSAGE "+name+": "+input);
                    }}
            }catch(Exception e){
            	e.printStackTrace();
            }finally{
                if (pOut != null){
                    writers.remove(pOut);
                }
                if(name != null){
                    System.out.println(name+" has left");
                    names.remove(name);
                }try{
                    socket.close();
                }catch (IOException e){
                	e.printStackTrace();
                }
            }
        }
    }}