# dns-resolver-chatGPT

<strong>TL/DR</strong> Experimenting with code generation for a basic dns resolver using ChatGPT with multiple languages

## introduction

I wanted to explore AI for code for quite some time. Now that I managed to find some time, I selected one of John's Cricket coding challenges. You can find the challenge [here](https://codingchallenges.substack.com/p/coding-challenge-22-dns-resolver
).

[here is the chatGPT chat that I used to generate the code](https://chat.openai.com/share/5d0f89ad-80a9-4e8d-9236-6997315cd842)

My intention was to generate code with as little coding intervention as possible.

It wasn't aimed at generating quality or production-level code, as I said this is more of an exploration of AI's capabilities. For this project I selected ChatGPT.

I wanted to use multiple languanges that I'm familiar to get a sense of how the code generation went. I used <strong>C, C++, Python, Java, Go and rust</strong> (which I want to learn next).

This repository holds the code generated for the coding challenge. I focused on encoding and sending/receiving the message and not on the decoding of the dns server response.

## During the "development"

It was an interesting and strange way to create code by describing it, and it was in any case interesting to see what the result would be. It felt more like talking to a junior developer, like trying to explain and guide them to do the task. The mistakes that happened, they were a lot of mistakes that happen frequently during the development of this kind of code (encoding an object to a byte array), during repetitive code (forgetting to add an offset etc). Other issues that I had included trying to run the code in Ubuntu Linux, but it was straightforward to resolve.

The code generated was almost working, with the odd bug now and then. That said, at this stage, the AI definitely cannot replace developers, because you need to understand what the code does and have experience in debugging to figure out the bugs that exist.

It was also interesting to see how it would solve some errors that I encountered. Most of the time, it provided proper guidance to fix the issue. It was also helpful when some headers were missing to identify them (I never seem to remember different headers).

### Class construction

I first started how I would start developing a program, I started with a class and starting adding fields. It would definetely be faster if I described all fields in one go but I wasn't certain about the capabilities of chatGPT.

For example:

> Prompt: 2 bytes fields for the following: answer resource records, authority resource record and additional resource record

Result:

> Certainly, you can add 2-byte fields for the "answer resource records," "authority resource records," and "additional resource records" to the class. Here's the updated class definition:

```cpp
class MyClass {
private:
    uint16_t id;        // A 2-byte (16-bit) unsigned integer to store the ID
    uint16_t flags;     // Another 2-byte (16-bit) unsigned integer to store flags
    uint16_t question;  // A 2-byte (16-bit) field called question
    uint16_t answerResourceRecords; // A 2-byte (16-bit) field for answer resource records
    uint16_t authorityResourceRecords; // A 2-byte (16-bit) field for authority resource records
    uint16_t additionalResourceRecords; // A 2-byte (16-bit) field for additional resource records

public:
    // Constructor to initialize all fields
    MyClass(uint16_t initialId, uint16_t initialFlags, uint16_t initialQuestion,
            uint16_t initialAnswerRecords, uint16_t initialAuthorityRecords,
            uint16_t initialAdditionalRecords)
        : id(initialId), flags(initialFlags), question(initialQuestion),
          answerResourceRecords(initialAnswerRecords),
          authorityResourceRecords(initialAuthorityRecords),
          additionalResourceRecords(initialAdditionalRecords) {}

   // Getter, setter functions omitted
};
```

> Now the `MyClass` class includes private member variables for all the specified fields, and corresponding getter and setter methods have been provided for each field. You can create objects of this class with all these fields and manipulate their values as needed.

### Adding an encoding/decoding function

The generated encode/decode functions were impressive and definetely time saving. While it needed some adjusting, it was good enough for now.

> Prompt: add a function in the class that encodes all the fields with their specific order in a byte array 

> Result: Certainly, you can add a member function to the class that encodes all the fields in their specific order into a byte array. Here's the updated class with an `encode` function:

```cpp
#include <string>
#include <cstdint>
#include <arpa/inet.h> // for htons()

class MyClass {
private:
    uint16_t id; // A 2-byte (16-bit) unsigned integer to store the ID
    uint16_t flags; // Another 2-byte (16-bit) unsigned integer to store flags
    uint16_t numberOfQuestions; // A 2-byte (16-bit) field for the number of questions
    uint16_t answerResourceRecords; // A 2-byte (16-bit) field for answer resource records
    uint16_t authorityResourceRecords; // A 2-byte (16-bit) field for authority resource records
    std::string question; // A field of type std::string called question
    uint16_t additionalResourceRecords; // A 2-byte (16-bit) field for additional resource records
    uint16_t queryType; // A 2-byte (16-bit) field for query type
    uint16_t queryClass; // A 2-byte (16-bit) field for query class

public:
    // Constructor to initialize all fields
    MyClass(uint16_t initialId, uint16_t initialNumberOfQuestions,
            uint16_t initialAnswerRecords, uint16_t initialAuthorityRecords,
            const std::string &initialQuestion, uint16_t initialAdditionalRecords,
            uint16_t initialQueryType, uint16_t initialQueryClass)
        : id(htons(initialId)), flags(htons(0x0100)), // Set flags to 0100 (binary) or 256 (decimal) in big-endian
          numberOfQuestions(htons(initialNumberOfQuestions)),
          answerResourceRecords(htons(initialAnswerRecords)),
          authorityResourceRecords(htons(initialAuthorityRecords)),
          question(initialQuestion),
          additionalResourceRecords(htons(initialAdditionalRecords)),
          queryType(htons(initialQueryType)), queryClass(htons(initialQueryClass)) {}

    // Getter methods...

    // Setter methods...

    // Encode all fields into a byte array
    void encode(uint8_t* byteArray) const {
        // Use htons to convert fields to network byte order (big-endian)
        uint16_t idBE = id;
        uint16_t flagsBE = flags;
        uint16_t numberOfQuestionsBE = numberOfQuestions;
        uint16_t answerResourceRecordsBE = answerResourceRecords;
        uint16_t authorityResourceRecordsBE = authorityResourceRecords;
        uint16_t additionalResourceRecordsBE = additionalResourceRecords;
        uint16_t queryTypeBE = queryType;
        uint16_t queryClassBE = queryClass;

        // Copy each field into the byte array
        memcpy(byteArray, &idBE, sizeof(uint16_t));
        byteArray += sizeof(uint16_t);
        memcpy(byteArray, &flagsBE, sizeof(uint16_t));
        byteArray += sizeof(uint16_t);
        memcpy(byteArray, &numberOfQuestionsBE, sizeof(uint16_t));
        byteArray += sizeof(uint16_t);
        // Encode the string question as-is into the byte array
        memcpy(byteArray, question.c_str(), question.size());
        byteArray += question.size();
        memcpy(byteArray, &answerResourceRecordsBE, sizeof(uint16_t));
        byteArray += sizeof(uint16_t);
        memcpy(byteArray, &authorityResourceRecordsBE, sizeof(uint16_t));
        byteArray += sizeof(uint16_t);
        memcpy(byteArray, &additionalResourceRecordsBE, sizeof(uint16_t));
        byteArray += sizeof(uint16_t);
        memcpy(byteArray, &queryTypeBE, sizeof(uint16_t));
        byteArray += sizeof(uint16_t);
        memcpy(byteArray, &queryClassBE, sizeof(uint16_t));
    }
};
```

> In this updated class, the `encode` function takes a pointer to a byte array as an argument and encodes all the fields in their specific order into that byte array. It uses `memcpy` to copy each field into the byte array after converting them to network byte order (big-endian) using `htons`. The string field `question` is copied as-is into the byte array.

### Other

The other major part was the receiving and sending of UDP messages but that was straightforward.

Other operations were creating some debug functions to print the received messages, creating the makefiles and finally for fun to create a dockerfile with the compiled program

### Generating multiple languages

I started with the C++ program. It definitely took more time to describe the code than to actually code it, but the interesting part came after that. Once the C++ code was (almost) working, I started generating code for other languages: C, Go, Python, Java and Rust, the latter of which I'm not that familiar. Besides some recurring bugs that I wasn't bothered to solve in the original C++, the code generated and ran almost effortlessly in all languages. That was impressive and quite surprising.

## Takeaways

I wonder how this will affect how we learn and use new and different languages, especially if you are proficient in one. Because this way of learning is beyond the traditional way of reading a guide book. It is definitely more interactive and more fun than reading how Rust uses if. A lot of times, the AI provided a good explanation of some operations that I wasn't familiar with, in a more natural way for humans. I did occasionally search for some things in Stack Overflow, but it was quite limited.

When AI will be more mature and able to use multiple languages in the same project, it will be interesting if this might also lead to, for example, optimizing each task by using the most suitable programming language.

I'm also very interested to see how AI will affect projects like proto buffers. I see some real potential there.

I will try to continue with my experimentation of code generation for network operations like that using different AI generators, because this is a topic that I have close to my heart.fc

## Results

Here are the results from each program. I used different ID for each language. You can see all byte arrays are identical to the encoding provided in the coding challenge.

### Encoded byte array

| Language | ID | Data                                                                         |
|----------|----------------------------------------|----------------------------------------------------------------------|
| Rust     | 001B | 01000001000000000000 03 646E73 06 676F6F676C65 03 636F6D 00 00010001                        |
| Java     | 001A | 01000001000000000000 03 646E73 06 676F6F676C65 03 636F6D 00 00010001                        |
| Go       | 0019 | 01000001000000000000 03 646E73 06 676F6F676C65 03 636F6D 00 00010001                        |
| Python   | 0018 | 01000001000000000000 03 646e73 06 676f6f676c65 03 636F6D 00 00010001                        |
| C        | 0017 | 01000001000000000000 03 646E73 06 676F6F676C65 03 636F6D 00 00010001                        |
| C++      | 0016 | 01000001000000000000 03 646e73 06 676f6f676c65 03 636F6D 00 00010001                        |
| Solution | 0016 | 01000001000000000000 03 646e73 06 676f6f676c65 03 636F6D 00 00010001                        |

### Received response from dns server

Here are the responses from each program. All the ID's correspond to the ID's send. The rest of the response is similiar but I didn't want to take time to decode the responses.

| Language | ID   | DNS response Data                                                                                                                     |
|----------|------|--------------------------------------------------------------------------------------------------------------------------------------|
| Rust     | 001B | 8180000100020000000003646E7306676F6F676C6503636F6D0000010001C00C0001000100000384000408080808C00C0001000100000384000408080404 |
| Java     | 001A | 8180000100020000000003646E7306676F6F676C6503636F6D0000010001C00C0001000100000384000408080404C00C0001000100000384000408080808 |
| Go       | 0019 | 8180000100020000000003646E7306676F6F676C6503636F6D0000010001C00C0001000100000384000408080808C00C0001000100000384000408080404 |
| Python   | 0018 | 8180000100020000000003646E7306676F6F676C6503636F6d0000010001C00c0001000100000384000408080808C00C0001000100000384000408080404 |
| C        | 0017 | 8180000100020000000003646E7306676F6F676C6503636F6D0000010001C00C0001000100000384000408080808C00C0001000100000384000408080404 |
| C++      | 0016 | 8180000100020000000003646E7306676F6F676C6503636F6D0000010001C00C0001000100000384000408080404C00C0001000100000384000408080808 |
| Solution | 0016 | 8080000100020000000003646E7306676F6F676C6503636F6D0000010001C00C0001000100000214000408080808C00C0001000100000214000408080404 |

## Used versions

| Tool | Version   |
|----------|------|
| Ubuntu | 20.04 LTS |
| AI | ChatGPT 3.5 Aug 3 version |
| Rust | 1.72.0 |
| Go | 1.15.12 |
| Python | 3.8.10 |
| C/C++ | gcc version 9.4.0 (Ubuntu 9.4.0-1ubuntu1~20.04.1) |
| Java | openjdk 17.0.8.1 2023-08-24 |