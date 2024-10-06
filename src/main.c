#include <stdio.h>
#include <stdbool.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_library/stb_image.h"

#if defined(_WIN64) || defined(_WIN32)
    #include <windows.h>  // For SetConsoleOutputCP()
#endif


void cat_image(char *filename, bool show_info, bool show_image)
{
    int img_width, img_height, channel;
    unsigned char *pixels = stbi_load(filename, &img_width, &img_height, &channel, 0);
    if (show_info) {
        printf("Reading image %s\n", filename);
        printf("Image info:\n");
        printf("    width: %d, height: %d, channel: %d\n", img_width, img_height, channel);
    }

    if (show_image) {
        // Print the pixels to the terminal
        int i, j, idx;
        for (i=0; i<img_height; i+=2) {
            // printf("\033[0m%3d: ", i);
            for (j=0; j<img_width*channel; j+=channel) {
                idx = i * img_width * channel + j;
                // foreground color
                printf("\033[38;2;%d;%d;%dm", pixels[idx], pixels[idx+1], pixels[idx+2]);
                // background color
                idx = (i+1) * img_width * channel + j;
                if ((i+1) < img_height) {
                    printf("\033[48;2;%d;%d;%dm", pixels[idx], pixels[idx+1], pixels[idx+2]);
                }
                // Print the upper half block character
                printf("\xE2\x96\x80");
            }
            // reset
            printf("\033[0m\n");
        }
    }
    stbi_image_free(pixels);
}

int main(int argc, char *argv[])
{
#if defined(_WIN64) || defined(_WIN32)
    // Set the console output to UTF-8
    SetConsoleOutputCP(CP_UTF8);
#endif

    if (argc == 1) {
        fprintf(stderr, "[Error] Expected at least one path to the image\n");
        exit(1);
    }

    int i;
    --argc;
    ++argv;
    for (i=0; i<argc; ++i) {
        cat_image(argv[i], false, true);
    }

    return 0;
}

// printf("The upper half block: ▀\n");
// printf("The upper half block: \u2580\n");
// printf("The upper half block: \xE2\x96\x80\n");
