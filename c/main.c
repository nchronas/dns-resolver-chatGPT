#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAX_QUESTION_LENGTH 255
#define SERVER_IP "8.8.8.8"  // Replace with the server IP address
#define SERVER_PORT 53      // Replace with the server port number


struct MyClass {
    uint16_t id;
    uint16_t flags; // Assuming flags is fixed to 0100
    uint16_t numberOfQuestions;
    char question[MAX_QUESTION_LENGTH];
    uint16_t answerResourceRecords;
    uint16_t authorityResourceRecords;
    uint16_t additionalResourceRecords;
    uint16_t queryType;
    uint16_t queryClass;
};

// Initialize a MyClass instance
void initializeMyClass(struct MyClass* obj, uint16_t initialId,
                       uint16_t initialNumberOfQuestions,
                       uint16_t initialAnswerRecords,
                       uint16_t initialAuthorityRecords,
                       const char* initialQuestion,
                       uint16_t initialAdditionalRecords,
                       uint16_t initialQueryType,
                       uint16_t initialQueryClass) {
    obj->id = initialId;
    obj->flags = 0x0100; // Assuming flags is fixed to 0100
    obj->numberOfQuestions = initialNumberOfQuestions;
    strncpy(obj->question, initialQuestion, MAX_QUESTION_LENGTH);
    obj->answerResourceRecords = initialAnswerRecords;
    obj->authorityResourceRecords = initialAuthorityRecords;
    obj->additionalResourceRecords = initialAdditionalRecords;
    obj->queryType = initialQueryType;
    obj->queryClass = initialQueryClass;
}

// Encode a MyClass instance into a byte array
int encodeMyClass(const struct MyClass* obj, uint8_t* byteArray) {
    int offset = 0;
    uint16_t idBE = htons(obj->id);
    uint16_t flagsBE = htons(obj->flags);
    uint16_t numberOfQuestionsBE = htons(obj->numberOfQuestions);
    uint16_t answerResourceRecordsBE = htons(obj->answerResourceRecords);
    uint16_t authorityResourceRecordsBE = htons(obj->authorityResourceRecords);
    uint16_t additionalResourceRecordsBE = htons(obj->additionalResourceRecords);
    uint16_t queryTypeBE = htons(obj->queryType);
    uint16_t queryClassBE = htons(obj->queryClass);

    memcpy(byteArray + offset, &idBE, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    memcpy(byteArray + offset, &flagsBE, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    memcpy(byteArray + offset, &numberOfQuestionsBE, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    memcpy(byteArray + offset, &answerResourceRecordsBE, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    memcpy(byteArray + offset, &authorityResourceRecordsBE, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    memcpy(byteArray + offset, &additionalResourceRecordsBE, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    memcpy(byteArray + offset, obj->question, strlen(obj->question) + 1);
    offset += strlen(obj->question) + 1; // Include the null terminator
 
    memcpy(byteArray + offset, &queryTypeBE, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    memcpy(byteArray + offset, &queryClassBE, sizeof(uint16_t));
    offset += sizeof(uint16_t);

    return offset;
}

// Decode a byte array into a MyClass instance
void decodeMyClass(const uint8_t* byteArray, struct MyClass* obj) {
    int offset = 0;
    uint16_t idBE, flagsBE, numberOfQuestionsBE, answerResourceRecordsBE, 
             authorityResourceRecordsBE, additionalResourceRecordsBE, 
             queryTypeBE, queryClassBE;

    memcpy(&idBE, byteArray + offset, sizeof(uint16_t));
    obj->id = ntohs(idBE);
    offset += sizeof(uint16_t);
    memcpy(&flagsBE, byteArray + offset, sizeof(uint16_t));
    obj->flags = ntohs(flagsBE);
    offset += sizeof(uint16_t);
    memcpy(&numberOfQuestionsBE, byteArray + offset, sizeof(uint16_t));
    obj->numberOfQuestions = ntohs(numberOfQuestionsBE);
    offset += sizeof(uint16_t);

    memcpy(&answerResourceRecordsBE, byteArray + offset, sizeof(uint16_t));
    obj->answerResourceRecords = ntohs(answerResourceRecordsBE);
    offset += sizeof(uint16_t);
    memcpy(&authorityResourceRecordsBE, byteArray + offset, sizeof(uint16_t));
    obj->authorityResourceRecords = ntohs(authorityResourceRecordsBE);
    offset += sizeof(uint16_t);
    memcpy(&additionalResourceRecordsBE, byteArray + offset, sizeof(uint16_t));
    obj->additionalResourceRecords = ntohs(additionalResourceRecordsBE);
    offset += sizeof(uint16_t);

 // Copy the question field as-is
    strcpy(obj->question, (const char*)(byteArray + offset));
    offset += strlen(obj->question) + 1; // Include the null terminator


    memcpy(&queryTypeBE, byteArray + offset, sizeof(uint16_t));
    obj->queryType = ntohs(queryTypeBE);
    offset += sizeof(uint16_t);
    memcpy(&queryClassBE, byteArray + offset, sizeof(uint16_t));
    obj->queryClass = ntohs(queryClassBE);
}

// Print the values of a MyClass instance
void printMyClassFields(const struct MyClass* obj) {
    printf("id: %u\n", obj->id);
    printf("flags: %u\n", obj->flags);
    printf("numberOfQuestions: %u\n", obj->numberOfQuestions);
    printf("answerResourceRecords: %u\n", obj->answerResourceRecords);
    printf("authorityResourceRecords: %u\n", obj->authorityResourceRecords);
    printf("question: %s\n", obj->question);
    printf("additionalResourceRecords: %u\n", obj->additionalResourceRecords);
    printf("queryType: %u\n", obj->queryType);
    printf("queryClass: %u\n", obj->queryClass);
}

int main() {
    // Example usage:    
    const char initial_question[] = { 3, 'd', 'n', 's', 6, 'g', 'o', 'o', 'g', 'l', 'e', 3, 'c', 'o', 'm', 0};

    struct MyClass my_object;

    initializeMyClass(&my_object, 23, 1, 0, 0, initial_question, 0, 1, 1);

    // Encoding
    uint8_t encoded_data[sizeof(my_object)];
    int size = encodeMyClass(&my_object, encoded_data);
    printf("Encoded data (hex): ");
    for (int i = 0; i < size; i++) {
        printf("%02X", encoded_data[i]);
    }
    printf("\n");

    // Create a UDP socket
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_socket == -1) {
        perror("Socket creation error");
        return 1;
    }

    // Set up the server address
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr);

    // Send the encoded data to the server
    if (sendto(udp_socket, encoded_data, size, 0,
               (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Sendto error");
        close(udp_socket);
        return 1;
    }

    // Receive response from the server
    uint8_t received_data[sizeof(my_object)];
    socklen_t server_address_len = sizeof(server_address);
    ssize_t bytes_received = recvfrom(udp_socket, received_data, sizeof(received_data), 0,
                                      (struct sockaddr*)&server_address, &server_address_len);
    if (bytes_received == -1) {
        perror("Recvfrom error");
        close(udp_socket);
        return 1;
    }

    printf("Received data (hex): ");
    for (int i = 0; i < bytes_received; i++) {
        printf("%02X", received_data[i]);
    }
    printf("\n");

    // Decoding the received data
    struct MyClass received_object;
    decodeMyClass(received_data, &received_object);
    printf("Received object:\n");
    printMyClassFields(&received_object);

    close(udp_socket);

    return 0;
}
