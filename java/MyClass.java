import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.nio.ByteBuffer;
import java.util.ArrayList;

public class MyClass {
    private int id;
    private int flags;
    private int numberOfQuestions;
    private byte[] question;
    private int answerResourceRecords;
    private int authorityResourceRecords;
    private int additionalResourceRecords;
    private int queryType;
    private int queryClass;

    public MyClass(int id, int flags, int numberOfQuestions, byte[] question, int answerResourceRecords,
                   int authorityResourceRecords, int additionalResourceRecords, int queryType, int queryClass) {
        this.id = id;
        this.flags = flags;
        this.numberOfQuestions = numberOfQuestions;
        this.question = question;
        this.answerResourceRecords = answerResourceRecords;
        this.authorityResourceRecords = authorityResourceRecords;
        this.additionalResourceRecords = additionalResourceRecords;
        this.queryType = queryType;
        this.queryClass = queryClass;
    }

    public byte[] encode() {
        int questionLength = question.length;

        byte[] encodedData = new byte[16 + questionLength];

        encodedData[0] = (byte) (id >> 8);
        encodedData[1] = (byte) id;
        encodedData[2] = (byte) (flags >> 8);
        encodedData[3] = (byte) flags;
        encodedData[4] = (byte) (numberOfQuestions >> 8);
        encodedData[5] = (byte) numberOfQuestions;
        encodedData[6] = (byte) (answerResourceRecords >> 8);
        encodedData[7] = (byte) answerResourceRecords;
        encodedData[8] = (byte) (authorityResourceRecords >> 8);
        encodedData[9] = (byte) authorityResourceRecords;
        encodedData[10] = (byte) (additionalResourceRecords >> 8);
        encodedData[11] = (byte) additionalResourceRecords;

        // Encode the question itself
        System.arraycopy(question, 0, encodedData, 12, questionLength);

        encodedData[12 + questionLength] = (byte) (queryType >> 8);
        encodedData[13 + questionLength] = (byte) queryType;
        encodedData[14 + questionLength] = (byte) (queryClass >> 8);
        encodedData[15 + questionLength] = (byte) queryClass;

        return encodedData;
    }

    public static void main(String[] args) {

        byte[] question = ".dns.google.com.".getBytes(); // Convert string to byte array

        question[0] = 3;
        question[4] = 6;
        question[11] = 3;
        question[15] = 0;
    
        MyClass myObject = new MyClass(
                26,
                0x0100,
                1,
                question,
                0,
                0,
                0,
                1,
                1
        );

        byte[] encodedData = myObject.encode();

        System.out.print("Encoded Data (Hex): ");
        for (byte b : encodedData) {
            System.out.printf("%02X", b);
        }
        System.out.printf("\n");

        try {
            // Create a DatagramSocket for sending
            DatagramSocket socket = new DatagramSocket();
            InetAddress serverAddress = InetAddress.getByName("8.8.8.8");
            int serverPort = 53;

            // Send the encoded data
            DatagramPacket sendPacket = new DatagramPacket(encodedData, encodedData.length, serverAddress, serverPort);
            socket.send(sendPacket);


            byte[] receiveData = new byte[1024];
            DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
            socket.receive(receivePacket);

            System.out.print("Received Data (Hex): ");
            for (int i = 0; i < receivePacket.getLength(); i++) {
                System.out.printf("%02X", receiveData[i]);
            }
            System.out.printf("\n");

            
            // Close socket
            socket.close();

        } catch (Exception e) {
            e.printStackTrace();
        }


    }
}
