# dns-resolver-chatGPT

<strong>TL/DR</strong> Experimenting with code generation for a basic dns resolver with multiple languages using ChatGPT

I wanted to explore AI for code for quite some time. Now that I managed to find some time, I selected one of John's Cricket coding challenges. 

My intention was to geneterate code with as less of coding intervention as possible. 

It wasn't aimed to generate quality or production code, as I said this is more of an exploration of the AI's capabilities. For this project I selected ChatGPT. 

This repository holds the generated code for coding challenge. I focused on the encoding and sending/receiving the message and not on the decoding of the dns server response. 

It was an interesting and strange way to create code by describing it and it was always interesting to see what the result would be. It felt more of talking to a junior developer trying to explain and guide over the task. The mistakes that happened, it's a lot of mistakes that happens a lot during development of this kind of code (encoding an object to a byte array), during Crepeatitive code (forgeting to add an offset etc). Other issues that I had is trying to run the code in ubuntu Linux but it was straightforward to resolve.

The code generated was almost working with the odd bug now and then. At this stage it definetely cannot replace developers because you need to understand what the code does and have experience in debugging to figure out the bugs that exist. 

I started with the C++ program. It definetely took more time to describe the code than to actually code it but the interesting part is after that. Once the C++ code was (almost) working, I started generating code for other languages: C, Go, Python, Java and rust which I'm not that familiar. Besides some recurring bugs that I wasn't bothered to solve in the original C++, the code generated and run almost effortless in all languages. That was impressing and quite suprising.

During the "development" 

It was also interesting to see how it would solve some errors that I encountered and most of the times it provided proper guidence to fix the issue. It was also helpfull when some headers were missing to identify them (I never seem to remember different headers).

I wonder how this will affect how we learn new and use different languages, especially if you are proficient in one. Because this way of learning is beyond the traditional way of reading a guide book. It is definetely more interactive and more fun than reading how rust uses if. It's interesting if this might also lead, when AI is more mature to the use of multiple languags in the same projects optimizing each task by using the suitable programming language. A lot of times it provided good explanation of some operations that I wasn't familiar with, in a more natural way for humans. I did occasionally searched some things in stack overflow but it was quite limited.

I'm very interested to see how AI will affect projects like proto buffers. I see some real potential there. 

I will try to continue with my experiementation of code generation for network operations like that using different AI generators, because this is a topic that I have close in heart.

https://codingchallenges.substack.com/p/coding-challenge-22-dns-resolver

https://chat.openai.com/share/5d0f89ad-80a9-4e8d-9236-6997315cd842

## Results

Here are the results from each program. I used different ID for each language. You can see all byte arrays are identical to the encoding provided in the coding challenge.

### Encoded byte array

| Language | ID |                            |                                                       |
|----------|------|----------------------------------|----------------------------------------------------------------------|
| Rust     | 001B | 01000001000000000000             | 03 646E73 06 676F6F676C65 03 636F6D 00 00010001                        |
| Java     | 001A | 01000001000000000000             | 03 646E73 06 676F6F676C65 03 636F6D 00 00010001                        |
| Go       | 0019 | 01000001000000000000             | 03 646E73 06 676F6F676C65 03 636F6D 00 00010001                        |
| Python   | 0018 | 01000001000000000000             | 03 646e73 06 676f6f676c65 03 636f6d 00 00010001                        |
| C        | 0017 | 01000001000000000000             | 03 646E73 06 676F6F676C65 03 636F6D 00 00010001                        |
| C++      | 0016 | 01000001000000000000             | 03 646e73 06 676f6f676c65 03 636f6d 00 00010001                        |
| Solution | 0016 | 01000001000000000000             | 03 646e73 06 676f6f676c65 03 636f6d 00 00010001                        |

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

