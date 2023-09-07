# Use an official Ubuntu as a parent image
FROM ubuntu:latest

# Set environment variables to avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Update package list and install necessary packages
RUN apt-get update && \
    apt-get install -y \
    g++ \
    cmake \
    && rm -rf /var/lib/apt/lists/*

# Create a directory to store your C++ source code
WORKDIR /app

# Copy your C++ source code and CMakeLists.txt to the container
COPY main.cpp /app/
COPY MyClass.h /app/
COPY CMakeLists.txt /app/

# Build your C++ program using CMake
RUN cmake . && make

# Run your compiled C++ program
CMD ["./your_program_name"]  # Replace with the name of your compiled program

# Cleanup unnecessary files and dependencies (optional)
RUN apt-get remove -y cmake g++ && apt-get autoremove -y && apt-get clean

# Set a working directory for the container
WORKDIR /app
