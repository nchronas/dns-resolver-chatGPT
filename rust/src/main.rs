use std::io::Write;
use std::net::UdpSocket;

#[derive(Debug)]
struct MyClass {
    id: u16,
    flags: u16,
    number_of_questions: u16,
    question: String,
    answer_resource_records: u16,
    authority_resource_records: u16,
    additional_resource_records: u16,
    query_type: u16,
    query_class: u16,
}

impl MyClass {
    fn encode(&self) -> Vec<u8> {
        let mut encoded_data = Vec::new();

        encoded_data.write_all(&self.id.to_be_bytes()).unwrap();
        encoded_data.write_all(&self.flags.to_be_bytes()).unwrap();
        encoded_data.write_all(&self.number_of_questions.to_be_bytes()).unwrap();        
        encoded_data.write_all(&self.answer_resource_records.to_be_bytes()).unwrap();
        encoded_data.write_all(&self.authority_resource_records.to_be_bytes()).unwrap();
        encoded_data.write_all(&self.additional_resource_records.to_be_bytes()).unwrap();

        encoded_data.write_all(self.question.as_bytes()).unwrap();
    
        encoded_data.write_all(&self.query_type.to_be_bytes()).unwrap();
        encoded_data.write_all(&self.query_class.to_be_bytes()).unwrap();

        encoded_data
    }
}

fn main() {
    let my_object = MyClass {
        id: 27,
        flags: 0x0100,
        number_of_questions: 1,
        // question: String::from("dns.google.com"),
        // question: ['h', 'e', 'l', 'l', 'o'],
        // question: String::from_iter([3, 'd', 'n', 's', 6, 'g', 'o', 'o', 'g', 'l', 'e', 3, 'c', 'o', 'm', 0]),
        question: String::from_utf8(vec![3, b'd', b'n', b's', 6, b'g', b'o', b'o', b'g', b'l', b'e', 3, b'c', b'o', b'm', 0]).unwrap(),
        answer_resource_records: 0,
        authority_resource_records: 0,
        additional_resource_records: 0,
        query_type: 1,
        query_class: 1,
    };

    let encoded_data = my_object.encode();

    print!("Encoded Data (Hex): ");
    for b in &encoded_data {
        print!("{:02X}", b);
    }
    println!(); // Add a newline after printing the hex values

    // UDP server address
    let server_address = "8.8.8.8:53";

    // Create a UDP socket
    let socket = UdpSocket::bind("0.0.0.0:0").expect("Failed to bind socket");

    // Send the encoded data
    socket.send_to(&encoded_data, server_address).expect("Failed to send data");

    // Receive response
    let mut buffer = [0; 1024];
    let (number_of_bytes, _) = socket.recv_from(&mut buffer).expect("Failed to receive data");

    // Print the received data in hexadecimal format
    print!("Received Data (Hex): ");
    for i in 0..number_of_bytes {
        print!("{:02X}", buffer[i]);
    }
    println!();

    drop(socket);
}
