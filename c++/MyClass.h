#ifndef MYCLASS_H
#define MYCLASS_H

#include <string>
#include <cstdint>
#include <cstring>

class MyClass {
private:
    uint16_t id; // A 2-byte (16-bit) unsigned integer to store the ID
    uint16_t flags; // Another 2-byte (16-bit) unsigned integer to store flags
    uint16_t numberOfQuestions; // A 2-byte (16-bit) field for the number of questions
    uint16_t answerResourceRecords; // A 2-byte (16-bit) field for answer resource records
    uint16_t authorityResourceRecords; // A 2-byte (16-bit) field for authority resource records
    uint8_t question[255]; // Assuming a maximum question length of 255 bytes
    size_t questionLength_;
    uint16_t additionalResourceRecords; // A 2-byte (16-bit) field for additional resource records
    uint16_t queryType; // A 2-byte (16-bit) field for query type
    uint16_t queryClass; // A 2-byte (16-bit) field for query class

public:
// Constructor to initialize all fields directly
    MyClass(uint16_t initialId, uint16_t initialNumberOfQuestions,
            uint16_t initialAnswerRecords, uint16_t initialAuthorityRecords,
            const uint8_t* initialQuestion, size_t questionLength,
            uint16_t initialAdditionalRecords, uint16_t initialQueryType,
            uint16_t initialQueryClass);

    // Setter and getter for the question
    void setQuestion(const uint8_t* newQuestion, size_t questionLength);
    
    // Getter methods...
    uint16_t getId() const;
    uint16_t getFlags() const;
    uint16_t getNumberOfQuestions() const;
    uint16_t getAnswerResourceRecords() const;
    uint16_t getAuthorityResourceRecords() const;
    uint16_t getAdditionalResourceRecords() const;
    uint16_t getQueryType() const;
    uint16_t getQueryClass() const;

    // Setter methods...
    void setId(uint16_t newId);
    void setNumberOfQuestions(uint16_t newNumberOfQuestions);
    void setAnswerResourceRecords(uint16_t newRecords);
    void setAuthorityResourceRecords(uint16_t newRecords);
    void setAdditionalResourceRecords(uint16_t newRecords);
    void setQueryType(uint16_t newQueryType);
    void setQueryClass(uint16_t newQueryClass);

    // Encode all fields into a byte array
    int encode(uint8_t* byteArray) const;
    bool decode(const uint8_t* byteArray, size_t byteArraySize);

    void printEncodedHex(uint8_t* byteArray, int size) const;
    void printFields() const;
};

#endif // MYCLASS_H
