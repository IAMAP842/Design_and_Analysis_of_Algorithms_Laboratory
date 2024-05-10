import os

def get_file_size(file_path):
    return os.path.getsize(file_path)

def compare_encoded_files(file1, file2):
    size_file1 = get_file_size(file1)
    size_file2 = get_file_size(file2)

    print(f"Size of {file1}: {size_file1} bytes")
    print(f"Size of {file2}: {size_file2} bytes")

    if size_file1 < size_file2:
        print(f"{file1} has a smaller size, Huffman encoding may be more efficient.")
    elif size_file1 > size_file2:
        print(f"{file2} has a smaller size, Shannon encoding may be more efficient.")
    else:
        print("Both files have the same size. The efficiency of Huffman and Shannon encoding is the same.")

# Paths to the encoded files
huffman_encoded_file = "1stencode.txt"
shannon_encoded_file = "2ndencode.txt"

# Compare the encoded files
compare_encoded_files(huffman_encoded_file, shannon_encoded_file)
