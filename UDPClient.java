import java.io.*;
import java.net.*;
import java.lang.*;
import java.util.*;

class UDPClient
{
    private DatagramSocket clientSocket;
    private InetAddress IPAddress;
    private int port;

    public UDPClient(String ip, int port) throws SocketException, UnknownHostException{
        this.clientSocket = new DatagramSocket(8000);
        this.IPAddress = InetAddress.getByName(ip);
        this.port = port;
    }

    public void send(char i) throws IOException, InterruptedException{
        byte[] header = new byte[]{(byte)i};
        DatagramPacket headerPacket = new DatagramPacket(header, header.length, this.IPAddress, this.port);
        this.clientSocket.send(headerPacket);
    }

    public static void main(String args[]){
        if(args.length < 2){
            System.out.println("Usage: UDPClient <IP ADDRESS> <PORT>");
            return;
        }
        try{
            UDPClient udpClient = new UDPClient(args[0],Integer.parseInt(args[1]));
            for(char i=0;i<20;i++){
                udpClient.send(i);
            }
        }
        catch(IOException e){}
        catch(InterruptedException e){}
    }
}
