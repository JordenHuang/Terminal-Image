#include <stdio.h>
#include <windows.h>  // For SetConsoleOutputCP()

int main() {
    // Set the console output to UTF-8
    SetConsoleOutputCP(CP_UTF8);

    printf("My name is: ¶ÀÒR¯§\n");
    printf("My name is: 黃淯祐\n");
    printf("The upper half block: \xE2\x96\x80");

    return 0;
}
