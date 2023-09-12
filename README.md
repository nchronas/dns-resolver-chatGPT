# dns-resolver-chatGPT

<strong>TL/DR</strong> Experimenting with code generation for a basic dns resolver using ChatGPT with multiple languages

## introduction

I wanted to explore AI for code for quite some time. Now that I managed to find some time, I selected one of John's Cricket coding challenges. You can find the challenge [here](https://codingchallenges.substack.com/p/coding-challenge-22-dns-resolver
).

[here is the chatGPT chat that I used to generate the code](https://chat.openai.com/share/5d0f89ad-80a9-4e8d-9236-6997315cd842)


My intention was to generate code with as little coding intervention as possible.

It wasn't aimed at generating quality or production-level code, as I said this is more of an exploration of AI's capabilities. For this project I selected ChatGPT.

I wanted to use multiple languanges that I'm familiar to get a sense of how the code generation went. I used <strong>C, C++, Python, Java, Go and rust</strong> (which I Want to learn next).

This repository holds the code generated for the coding challenge. I focused on encoding and sending/receiving the message and not on the decoding of the dns server response.

## During the "development"

It was an interesting and strange way to create code by describing it, and it was in any case interesting to see what the result would be. It felt more like talking to a junior developer, like trying to explain and guide them to do the task. The mistakes that happened, they were a lot of mistakes that happen frequently during the development of this kind of code (encoding an object to a byte array), during repetitive code (forgetting to add an offset etc). Other issues that I had included trying to run the code in Ubuntu Linux, but it was straightforward to resolve.

The code generated was almost working, with the odd bug now and then. That said, at this stage, the AI definitely cannot replace developers, because you need to understand what the code does and have experience in debugging to figure out the bugs that exist.

I started with the C++ program. It definitely took more time to describe the code than to actually code it, but the interesting part came after that. Once the C++ code was (almost) working, I started generating code for other languages: C, Go, Python, Java and Rust, the latter of which I'm not that familiar. Besides some recurring bugs that I wasn't bothered to solve in the original C++, the code generated and ran almost effortlessly in all languages. That was impressive and quite surprising.

It was also interesting to see how it would solve some errors that I encountered. Most of the time, it provided proper guidance to fix the issue. It was also helpful when some headers were missing to identify them (I never seem to remember different headers).

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
| Python   | 0018 | 01000001000000000000 03 646e73 06 676f6f676c65 03 636f6d 00 00010001                        |
| C        | 0017 | 01000001000000000000 03 646E73 06 676F6F676C65 03 636F6D 00 00010001                        |
| C++      | 0016 | 01000001000000000000 03 646e73 06 676f6f676c65 03 636f6d 00 00010001                        |
| Solution | 0016 | 01000001000000000000 03 646e73 06 676f6f676c65 03 636f6d 00 00010001                        |

### Received response from dns server

Here are the responses from each program. All the ID's correspond to the ID's send. The rest of the response is similiar but I didn't want to take time to decode the responses.

| Language | ID   | DNS response Data                                                                                                                     |
|----------|------|--------------------------------------------------------------------------------------------------------------------------------------|
| Rust     | 001B | 8180000100020000000003646E7306676F6F676C6503636F6D0000010001C00C0001000100000384000408080808C00C0001000100000384000408080404 |
| Java     | 001A | 8180000100020000000003646E7306676F6F676C6503636F6D0000010001C00C0001000100000384000408080404C00C0001000100000384000408080808 |
| Go       | 0019 | 8180000100020000000003646E7306676F6F676C6503636F6D0000010001C00C0001000100000384000408080808C00C0001000100000384000408080404 |
| Python   | 0018 | 8180000100020000000003646e7306676f6f676c6503636f6d0000010001c00c0001000100000384000408080808c00c0001000100000384000408080404 |
| C        | 0017 | 8180000100020000000003646E7306676F6F676C6503636F6D0000010001C00C0001000100000384000408080808C00C0001000100000384000408080404 |
| C++      | 0016 | 8180000100020000000003646e7306676f6f676c6503636f6d0000010001c00c0001000100000384000408080404c00c0001000100000384000408080808 |
| Solution | 0016 | 8080000100020000000003646e7306676f6f676c6503636f6d0000010001c00c0001000100000214000408080808c00c0001000100000214000408080404 |

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