import struct
import socket

class MyClass:
    def __init__(self, initial_id, initial_number_of_questions,
                 initial_answer_records, initial_authority_records,
                 initial_question, initial_additional_records,
                 initial_query_type, initial_query_class):
        self.id = initial_id
        self.flags = 0x0100  # Assuming flags is fixed to 0100
        self.number_of_questions = initial_number_of_questions
        self.answer_resource_records = initial_answer_records
        self.authority_resource_records = initial_authority_records
        self.question = initial_question
        self.additional_resource_records = initial_additional_records
        self.query_type = initial_query_type
        self.query_class = initial_query_class

    def encode(self):
        # Encode the string
        question_bytes = self.question.encode('utf-8')
        question_length = len(question_bytes)

        # Define the format string for packing
        format_string = f'!HHHHHH{question_length}sHH'
        packed_data = struct.pack(
            format_string,
            self.id,
            self.flags,
            self.number_of_questions,
            self.answer_resource_records,
            self.authority_resource_records,
            self.additional_resource_records,
            question_bytes,
            self.query_type,
            self.query_class
        )

        return packed_data

    @staticmethod
    def decode(encoded_data):
        decoded_fields = struct.unpack(
            ">HHH255sHHHH",
            encoded_data[:struct.calcsize(">HHH255sHHHH")]
        )
        id, flags, number_of_questions, question_bytes, \
        answer_resource_records, authority_resource_records, \
        additional_resource_records, query_type, query_class = decoded_fields

        question = question_bytes.decode('utf-8').rstrip('\x00')

        return MyClass(id, number_of_questions, answer_resource_records,
                        authority_resource_records, question,
                        additional_resource_records, query_type, query_class)

    def print_fields(self):
        print("id:", self.id)
        print("flags:", self.flags)
        print("number_of_questions:", self.number_of_questions)
        print("answer_resource_records:", self.answer_resource_records)
        print("authority_resource_records:", self.authority_resource_records)
        print("question:", self.question)
        print("additional_resource_records:", self.additional_resource_records)
        print("query_type:", self.query_type)
        print("query_class:", self.query_class)




def main():
    # Example usage:
    initial_question = chr(3) + "dns" + chr(6) + "google" + chr(3) + "com" + chr(0)
    my_object = MyClass(24, 1, 0, 0, initial_question, 0, 1, 1)

    # Encoding
    encoded_data = my_object.encode()
    print("Encoded data (hex):", encoded_data.hex())

    # UDP server address and port
    server_ip = "8.8.8.8"  # Replace with the server IP address
    server_port = 53      # Replace with the server port number

    # Create a UDP socket
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # Send the encoded data to the server
    udp_socket.sendto(encoded_data, (server_ip, server_port))

    # Receive response from the server
    received_data, server_address = udp_socket.recvfrom(1024)

    # Decoding the received data
    hex_string = received_data.hex()
    print("Received Data (Hex):", hex_string)

    # Close the socket
    udp_socket.close()

if __name__ == "__main__":
    main()
