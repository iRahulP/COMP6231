import java.io.InputStream; import java.net.ServerSocket; import java.net.Socket;

public class TCPServerJava {
  public static final void main(final String[] args) {

    try(ServerSocket server = new ServerSocket(9999)){  
      
      for (int j = 5; (--j) >= 0;) { 
        try(Socket client = server.accept()) { 
          System.out.println("New connection from " + client.getRemoteSocketAddress());
      
          try(InputStream is = client.getInputStream()){
            System.out.println(is.read()); 
            } 
          } 
        }
    
    } catch (Throwable t) {
      t.printStackTrace();
    }
  }
}