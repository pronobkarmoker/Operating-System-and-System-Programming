directory_name= /home/shuvo/Desktop/operating\ system
for file in "$directory_name"/* .c "$directory_name"/* .cpp;

do

 if [ -f "$file" ]; then
    filename=$(basename "$file")
    size=$(wc -c < "$file")
    lines=$(wc -l < "$file")
    echo "FileName: $filename, SizeOfFile: $size, Lines of code: $lines"
 fi
 
done
