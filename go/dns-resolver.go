package main

import (
    "encoding/binary"
    "fmt"
	"net"
)

type MyClass struct {
    ID                        uint16
    Flags                     uint16
    NumberOfQuestions         uint16
    Question                  string
    AnswerResourceRecords     uint16
    AuthorityResourceRecords  uint16
    AdditionalResourceRecords uint16
    QueryType                 uint16
    QueryClass                uint16
}

// Encode encodes the MyClass instance into a byte slice
func (mc *MyClass) Encode() []byte {
    // Calculate the length of the Question string
    questionLength := uint16(len(mc.Question))

    // Create a byte slice to hold the encoded data
    encodedData := make([]byte, 16+questionLength)

    // Encode each field using binary.BigEndian
    binary.BigEndian.PutUint16(encodedData[0:2], mc.ID)
    binary.BigEndian.PutUint16(encodedData[2:4], mc.Flags)
    binary.BigEndian.PutUint16(encodedData[4:6], mc.NumberOfQuestions)
    binary.BigEndian.PutUint16(encodedData[6:8], mc.AnswerResourceRecords)
    binary.BigEndian.PutUint16(encodedData[8:10], mc.AuthorityResourceRecords)
    binary.BigEndian.PutUint16(encodedData[10:12], mc.AdditionalResourceRecords)
	copy(encodedData[12:], []byte(mc.Question))
	binary.BigEndian.PutUint16(encodedData[12+questionLength:14+questionLength], mc.QueryType)
    binary.BigEndian.PutUint16(encodedData[14+questionLength:16+questionLength], mc.QueryClass)

    return encodedData
}

func main() {
    // Example usage:
    myObject := MyClass{
        ID:                        25,
        Flags:                     0x0100,
        NumberOfQuestions:         1,
        Question:                  "\x03dns\x06google\x03com\x00",
        AnswerResourceRecords:     0,
        AuthorityResourceRecords:  0,
        AdditionalResourceRecords: 0,
        QueryType:                 1,
        QueryClass:                1,
    }

    // Encode the MyClass instance
    encodedData := myObject.Encode()

    // Print the encoded data in hexadecimal format
    fmt.Printf("Encoded Data (Hex): %X\n", encodedData)

	// UDP server address
	serverAddr, err := net.ResolveUDPAddr("udp", "8.8.8.8:53")
	if err != nil {
		fmt.Println("Error resolving address:", err)
		return
	}

	// Create a UDP connection
	udpConn, err := net.DialUDP("udp", nil, serverAddr)
	if err != nil {
		fmt.Println("Error creating UDP connection:", err)
		return
	}
	defer udpConn.Close()

	// Send the encoded data
	_, err = udpConn.Write(encodedData)
	if err != nil {
		fmt.Println("Error sending data:", err)
		return
	}

	// Receive response
	buffer := make([]byte, 1024)
	n, _, err := udpConn.ReadFromUDP(buffer)
	if err != nil {
		fmt.Println("Error reading from UDP:", err)
		return
	}

	// Print the received data in hexadecimal format
	receivedData := buffer[:n]
	fmt.Printf("Received Data (Hex): %X\n", receivedData)
}
