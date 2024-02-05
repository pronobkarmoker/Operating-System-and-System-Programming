#!/bin/bash

# Check if the user provided a directory path
if [ $# -eq 0 ]; then
    echo "Usage: $0 <directory_path>"
    exit 1
fi

directory_path=$1

# Check if the provided path is a directory
if [ ! -d "$directory_path" ]; then
    echo "Error: $directory_path is not a valid directory."
    exit 1
fi

# Find all C and C++ files in the specified directory
files=$(find "$directory_path" -type f \( -name "*.c" -o -name "*.cpp" \))

# Display header
echo "Filename        Size (bytes)   Lines of Code"

# Loop through each file and display filename, size, and line count
for file in $files; do
    filename=$(basename "$file")
    size=$(wc -c < "$file")
    lines=$(wc -l < "$file")
    echo "$filename       $size          $lines"
done
