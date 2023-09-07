#include <iostream>
#include <cstring>
#include <cstdlib>
#include <arpa/inet.h>
#include <iomanip> // Include this header for std::setw and std::setfill
#include <unistd.h>
#include "MyClass.h" // Include your header file here

int main() {

    std::cout << "Hello"  << std::endl;

    const uint8_t question[] = { 3, 'd', 'n', 's', 6, 'g', 'o', 'o', 'g', 'l', 'e', 3, 'c', 'o', 'm', 0};

    // Initialize MyClass instance with sample data
    MyClass myObject(
        22,        // ID
        1,          // Number of questions
        0,          // Answer resource records
        0,          // Authority resource records
        question,          // byte array for the question
        sizeof(question),  // question length
        0,          // Additional resource records
        1,          // Query type
        1           // Query class
    );

    // Create a UDP socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return 1;
    }

    std::cout << "Hello2"  << std::endl;
    

    // Define server information
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(53); // Replace with your desired port
    serverAddr.sin_addr.s_addr = inet_addr("8.8.8.8"); // Replace with your server's IP

    // Encode the MyClass instance into a byte array
    uint8_t encodedData[1024]; // Adjust the size as needed
    int size = myObject.encode(encodedData);

    // Print the encoded message in hexadecimal format
    myObject.printEncodedHex(encodedData, size);

    std::cout << "Hello3"  << std::endl;

    // Send the encoded data to the server
    int bytesSent = sendto(sockfd, encodedData, size, 0,
                        (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (bytesSent == -1) {
        perror("sendto");
        close(sockfd);
        return 1;
    }

    std::cout << "Hello4"  << std::endl;

    // Receive a response from the server
    uint8_t receivedData[1024]; // Adjust the size as needed
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int bytesReceived = recvfrom(sockfd, receivedData, sizeof(receivedData), 0,
                                (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (bytesReceived == -1) {
        perror("recvfrom");
        close(sockfd);
        return 1;
    }

    std::cout << "Hello5"  << std::endl;

    // Process the received data as needed

    // Display the received data in hexadecimal format
    std::cout << "Received data in hexadecimal: ";
    for (int i = 0; i < bytesReceived; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(receivedData[i]);
    }
    std::cout << std::dec << std::endl;

    myObject.decode(receivedData, bytesReceived);
    myObject.printFields();

    // Close the socket
    close(sockfd);

    return 0;
}                      
