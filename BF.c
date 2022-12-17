
        // Get and print operating system name and version
    struct utsname uname_buf;
    uname(&uname_buf);
   FILE *fptr;
    fptr = fopen("/etc/os-release", "r");
    if (fptr == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the "NAME" and "VERSION" fields from the file
    char name[1024], version[1024];
    while (1) {
        char line[1024];
        if (fgets(line, 1024, fptr) == NULL) {
            break;
        }

        // Check if the line starts with "NAME="
        if (strncmp(line, "NAME=", 5) == 0) {
            // Extract the value of the "NAME" field
            strcpy(name, line + 5);
            name[strlen(name) - 1] = '\0'; // Remove the trailing newline character
        }

        // Check if the line starts with "VERSION="
        if (strncmp(line, "VERSION=", 8) == 0) {
            // Extract the value of the "VERSION" field
            strcpy(version, line + 8);
            version[strlen(version) - 1] = '\0'; // Remove the trailing newline character
        }
    }

    // Close the file
    fclose(fptr);

    // Print the name and version of the Linux distribution
    printf("Linux distribution: %s %s\n", name, version);
