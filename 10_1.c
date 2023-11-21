// Reader :- 
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd;
    char *myfifo = "/tmp/myfifo";

    // Create the named pipe (FIFO)
    mkfifo(myfifo, 0666);

    while (1)
    {
        // Open FIFO for reading
        fd = open(myfifo, O_RDONLY);

        // Read the sentence from the FIFO
        char sentence[80];
        read(fd, sentence, sizeof(sentence));
        
        read(fd, sentence, 80);
        // Print the read string and close
        printf("User1: %s\n", sentence);
        close(fd);

        // Process the data (count characters, words, and lines)
        int char_count = 0, word_count = 0, line_count = 0;
        for (int i = 0; sentence[i] != '\0'; i++)
        {
            if(sentence[i] == '\n')
            {
                line_count++;
            }
            else if(sentence[i] == ' ')
            {
                word_count++;
            }
            else
            {
            	char_count++;
            }
            	
        }
        word_count++; // Count the last word

        // Create a string with the counting results
        char counting_result[256];
        snprintf(counting_result, sizeof(counting_result), "Characters: %d, Words: %d, Lines: %d", char_count, word_count, line_count);

        // Write the counting results to a file
        FILE *output_file = fopen("output.txt", "w");
        if (output_file)
        {
            fprintf(output_file, "%s\n", counting_result);
            fclose(output_file);
        }

        // Open FIFO for writing
        fd = open(myfifo, O_WRONLY);

        // Send the counting results back to Process 1
        write(fd, counting_result, strlen(counting_result) + 1);
        close(fd);
    }

    return 0;
}
