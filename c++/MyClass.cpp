#include "MyClass.h"
#include <arpa/inet.h>
#include <iostream>
#include <iomanip> // Include this header for std::setw and std::setfill

// Implement the constructor
MyClass::MyClass(uint16_t initialId, uint16_t initialNumberOfQuestions,
                 uint16_t initialAnswerRecords, uint16_t initialAuthorityRecords,
                 const uint8_t* initialQuestion, size_t questionLength,
                 uint16_t initialAdditionalRecords, uint16_t initialQueryType,
                 uint16_t initialQueryClass)
    : id(initialId),
      flags(0x0100), // Assuming flags is fixed to 0100
      numberOfQuestions(initialNumberOfQuestions),
      answerResourceRecords(initialAnswerRecords),
      authorityResourceRecords(initialAuthorityRecords),
      additionalResourceRecords(initialAdditionalRecords),
      queryType(initialQueryType),
      queryClass(initialQueryClass) {
    // Initialize the question field
    setQuestion(initialQuestion, questionLength);
}
// Implement the getter methods...

// Implement other getter methods...

// Implement the setter methods...
void MyClass::setQuestion(const uint8_t* newQuestion, size_t questionLength) {
    if (questionLength <= sizeof(question)) {
        std::memcpy(question, newQuestion, questionLength);
        questionLength_ = questionLength;
    } else {
        // Handle error or truncation if the input is too long
        // You can choose to throw an exception or handle it as needed
        // For simplicity, we don't handle truncation here
        std::cerr << "Error: Input question is too long." << std::endl;
    }
}

// Encode the fields into a byte array and return the size
int MyClass::encode(uint8_t* byteArray) const {

    // Copy each field into the byte array with htons
    int offset = 0;
    uint16_t idBE = htons(id);
    uint16_t flagsBE = htons(flags);
    uint16_t numberOfQuestionsBE = htons(numberOfQuestions);
    uint16_t answerResourceRecordsBE = htons(answerResourceRecords);
    uint16_t authorityResourceRecordsBE = htons(authorityResourceRecords);
    uint16_t additionalResourceRecordsBE = htons(additionalResourceRecords);
    uint16_t queryTypeBE = htons(queryType);
    uint16_t queryClassBE = htons(queryClass);

    std::memcpy(byteArray + offset, &idBE, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    std::memcpy(byteArray + offset, &flagsBE, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    std::memcpy(byteArray + offset, &numberOfQuestionsBE, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    std::memcpy(byteArray + offset, &answerResourceRecordsBE, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    std::memcpy(byteArray + offset, &authorityResourceRecordsBE, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    std::memcpy(byteArray + offset, &additionalResourceRecordsBE, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    std::memcpy(byteArray + offset, question, questionLength_);
    offset += questionLength_;
    std::memcpy(byteArray + offset, &queryTypeBE, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    std::memcpy(byteArray + offset, &queryClassBE, sizeof(uint16_t));
    offset += sizeof(uint16_t);

    // Calculate and return the size
    return offset;
}



// Implement the printEncodedHex function with size parameter
void MyClass::printEncodedHex(uint8_t* byteArray, int size) const {
    std::cout << "Encoded message in hexadecimal format:" << std::endl;

    // Print the encoded data up to the provided size
    for (int i = 0; i < size; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byteArray[i]);
    }
    std::cout << std::dec << std::endl;
}

bool MyClass::decode(const uint8_t* byteArray, size_t byteArraySize) {
    if (byteArraySize < sizeof(*this)) {
        std::cerr << "Error: Insufficient data for decoding." << std::endl;
        return false;
    }

    int offset = 0;

    // Copy each field from the byte array and convert to host byte order
    std::memcpy(&id, byteArray + offset, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    std::memcpy(&flags, byteArray + offset, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    std::memcpy(&numberOfQuestions, byteArray + offset, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    std::memcpy(&answerResourceRecords, byteArray + offset, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    std::memcpy(&authorityResourceRecords, byteArray + offset, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    std::memcpy(&additionalResourceRecords, byteArray + offset, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    // Copy the question field as-is, assuming it's the remaining data
    if (offset + questionLength_ > (byteArraySize - 16 * 2)) {
        std::cerr << "Error: Insufficient data for question field." << std::endl;
        return false;
    }
    std::memcpy(question, byteArray + offset, questionLength_);
    offset += questionLength_;
    std::memcpy(&queryType, byteArray + offset, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    std::memcpy(&queryClass, byteArray + offset, sizeof(uint16_t));

    return true;
}

// Implement the printFields function
void MyClass::printFields() const {
    std::cout << "id: " << id << std::endl;
    std::cout << "flags: " << flags << std::endl;
    std::cout << "numberOfQuestions: " << numberOfQuestions << std::endl;
    std::cout << "answerResourceRecords: " << answerResourceRecords << std::endl;
    std::cout << "authorityResourceRecords: " << authorityResourceRecords << std::endl;

    std::cout << "question: ";
    for (size_t i = 0; i < questionLength_; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(question[i]);
    }
    std::cout << std::dec << std::endl;

    std::cout << "additionalResourceRecords: " << additionalResourceRecords << std::endl;
    std::cout << "queryType: " << queryType << std::endl;
    std::cout << "queryClass: " << queryClass << std::endl;
}





