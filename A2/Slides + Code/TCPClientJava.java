import java.io.OutputStream;
import java.net.InetAddress;
import java.net.Socket;

public class TCPClientJava {

  public static final void main(final String[] args) {
    InetAddress   ia;

    try {
      ia = InetAddress.getByName("localhost");
      
      try(Socket client = new Socket(ia, 9999)){  
      
       try(OutputStream os = client.getOutputStream()) {
           os.write(1);  
         } 
      }  
    } catch (Throwable t) {
      t.printStackTrace();
    }
  }
}
