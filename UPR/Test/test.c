#include <stdio.h>

int main() {
    char buffer[51]; // 50 characters + 1 for the null terminator
    printf("Enter up to 50 characters: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Process the input
        printf("You entered: %s", buffer);
    } else {
        // Handle input error
        printf("Error reading input.\n");
    }
    
    return 0;
}