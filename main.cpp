#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

bool is_current_or_parent_directory(char *file_name);

int main()
{
    printf("enter a directory path to read files from (255 char max): ");
    char user_input_path[256];
    fgets(user_input_path, sizeof(user_input_path), stdin);
    int newline_index = strcspn(user_input_path, "\n");
    user_input_path[newline_index] = '\0';

    DIR *directory = opendir(user_input_path);
    if (directory == 0)
    {
        int error = errno;
        char *error_message = strerror(error);
        printf("Failed to read directory\n");
        printf("%s\n", error_message);
        return 1;
    }

    struct dirent *file = 0;
    bool more_files_to_read = true;
    while (more_files_to_read)
    {
        file = readdir(directory);
        if (file == 0)
        {
            more_files_to_read = false;
        }
        else
        {
            if (!is_current_or_parent_directory(file->d_name))
            {
                printf("%s\n", file->d_name);
            }
        }
    }

    int close_dir_result = closedir(directory);
    if (close_dir_result == -1)
    {
        char *error = strerror(errno);
        printf("Failed to close directory\n");
        printf("%s\n", error);
        return 1;
    }

    return 0;
}

bool is_current_or_parent_directory(char *file_name)
{
    return strcmp(file_name, ".") == 0 || strcmp(file_name, "..") == 0;
}