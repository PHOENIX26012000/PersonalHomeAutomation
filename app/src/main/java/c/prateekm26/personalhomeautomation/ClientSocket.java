package c.prateekm26.personalhomeautomation;
import java.io.IOException;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
public class ClientSocket {
    private String command;
private String ip_address;
    public ClientSocket(String ip_address, String command){
        this.ip_address=ip_address;
        this.command=command;
    }
Socket s;

    {
        try {
            s = new Socket(ip_address,1088);
PrintStream ps=new PrintStream(s.getOutputStream());
ps.println(command);
s.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
