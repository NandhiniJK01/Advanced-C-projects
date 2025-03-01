#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void xor_encrypt_decrypt(const char *input_filename, const char *output_filename, char key) {
    FILE *input_file = fopen(input_filename, "rb");
    FILE *output_file = fopen(output_filename, "wb");
    if (!input_file || !output_file) {
        perror("Error opening file");
        return;
    }
    
    char buffer;
    while (fread(&buffer, 1, 1, input_file)) {
        buffer ^= key;
        fwrite(&buffer, 1, 1, output_file);
    }
    
    fclose(input_file);
    fclose(output_file);
    printf("Operation completed successfully.\n");
}

int main() {
    char input_filename[256], output_filename[256], key;
    int choice;
    
    printf("File Encryption & Decryption Tool\n");
    printf("1. Encrypt File\n2. Decrypt File\nEnter choice: ");
    scanf("%d", &choice);
    getchar();
    
    printf("Enter input filename: ");
    fgets(input_filename, 256, stdin);
    strtok(input_filename, "\n");
    
    printf("Enter output filename: ");
    fgets(output_filename, 256, stdin);
    strtok(output_filename, "\n");
    
    printf("Enter a single-character key: ");
    scanf("%c", &key);
    
    xor_encrypt_decrypt(input_filename, output_filename, key);
    return 0;
}
