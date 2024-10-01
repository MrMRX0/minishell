import re
import os
import glob

# Directory path
source_dir = '.'  # Directory containing .c files
h_file = 'test.h'  # Header file to update

def extract_functions(c_file):
    """
    Extract function signatures from the C file.
    """
    with open(c_file, 'r') as file:
        content = file.read()

    # Regular expression to match function declarations
    function_pattern = r'^\w[\w\s\*]*\s+(\w+)\s*\([^)]*\)\s*{'
    functions = re.findall(function_pattern, content, re.MULTILINE)

    return functions

def generate_function_prototypes(functions, c_file):
    """
    Generate function prototypes from the extracted functions.
    """
    with open(c_file, 'r') as file:
        content = file.read()

    prototypes = []
    for function in functions:
        # Extract full function signature
        pattern = rf'^\w[\w\s\*]*\s+({function})\s*\([^)]*\)'
        match = re.search(pattern, content, re.MULTILINE)
        if match:
            prototypes.append(match.group(0) + ';')

    return prototypes

def update_header_file(h_file, prototypes, file_name):
    """
    Update the header file with function prototypes wrapped in a block with file name comments.
    """
    with open(h_file, 'a') as file:
        # Add the file name as a comment block
        file.write(f"\n/*{file_name}*/\n")
        file.write(f"//--------------------{file_name}--------------------\n")

        # Add each function prototype (no individual comments)
        for proto in prototypes:
            file.write(f"{proto}\n")

        # End of block
        file.write(f"//--------------------{file_name}--------------------\n")

def process_c_files_in_directory(source_dir, h_file):
    """
    Process all .c files in the given directory and update the header file.
    """
    # Get all .c files in the directory
    c_files = glob.glob(os.path.join(source_dir, '*.c'))

    # Step 1: Loop through each .c file
    for c_file in c_files:
        file_name = os.path.basename(c_file).replace('.c', '')  # Get the file name without the extension
        print(f"Processing file: {c_file}")

        # Step 2: Extract functions from the C file
        functions = extract_functions(c_file)

        # Step 3: Generate function prototypes
        prototypes = generate_function_prototypes(functions, c_file)

        # Step 4: Update the header file with file name comments and function prototypes
        update_header_file(h_file, prototypes, file_name)

if __name__ == '__main__':
    # Step 1: Process all .c files in the directory
    process_c_files_in_directory(source_dir, h_file)

    print(f"Header file '{h_file}' updated successfully.")
