#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char** argv) {

    // Get and print hostname
    char hostname[128];
    gethostname(hostname, sizeof(hostname));
    printf("\033[1;34mHostname: %s\033[0m\n", hostname);

    
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
    printf("\033[1;31mLinux distribution: %s %s\033[0m\n", name, version);

    // Get and print DE
        char* desktop_env = getenv("DESKTOP_SESSION");
    if (desktop_env) {
        printf("\033[1;31mDE: %s\033[0m\n", desktop_env);
    }

           // Determine package manager based on operating system
    char* package_manager;
    if (strcmp(uname_buf.sysname, "Debian") == 0 || strcmp(uname_buf.sysname, "Ubuntu") == 0 || strcmp(uname_buf.sysname, "LinuxMint") == 0 || strcmp(uname_buf.sysname, "LMDE") == 0) {
        package_manager = "apt";
    } else if (strcmp(uname_buf.sysname, "Fedora") == 0 || strcmp(uname_buf.sysname, "Red Hat") == 0 || strcmp(uname_buf.sysname, "CentOS") == 0) {
        package_manager = "yum";
    } else if (strcmp(uname_buf.sysname, "Arch") == 0) {
        package_manager = "pacman";
    } else if (strcmp(uname_buf.sysname, "Void") == 0) {
        package_manager = "xbps";
    } else {
        package_manager = "unknown";
    }

    printf("\033[1;31mPackage Manager: %s\033[0m\n", package_manager);

    // Get and print kernel version
    printf("\033[1;31mKernel: %s\033[0m\n", uname_buf.release);

    // Get and print uptime
    FILE* uptime_file = fopen("/proc/uptime", "r");
    double uptime;
    fscanf(uptime_file, "%lf", &uptime);
    fclose(uptime_file);
    printf("\033[1;31mUptime: %ld days, %ld hours, %ld minutes\033[0m\n", (long)uptime / 86400, ((long)uptime % 86400) / 3600, ((long)uptime % 3600) / 60);

        // Get and print CPU information
    FILE* cpuinfo_file = fopen("/proc/cpuinfo", "r");
    char line[1024];
    while (fgets(line, sizeof(line), cpuinfo_file)) {
        if (strncmp(line, "model name", 10) == 0) {
            printf("\033[1;31mCPU: %s\033[0m", line + 13);
            break;
        }
    }
    fclose(cpuinfo_file);

    // Get and print GPU information
    char* gpu_info = NULL;
    size_t gpu_info_size = 0;
    FILE* lspci_file = popen("lspci | grep -i 'vga\\|3d\\|2d'", "r");
    if (lspci_file) {
        if (getline(&gpu_info, &gpu_info_size, lspci_file) > 0) {
            printf("\033[1;31mGPU: %s\033[0m", gpu_info);
        }
        pclose(lspci_file);
    }
    free(gpu_info);

    // Get and print RAM information
      // Open the /proc/meminfo file
    FILE* meminfo_file = fopen("/proc/meminfo", "r");
    if (meminfo_file == NULL) {
        perror("Error opening /proc/meminfo");
        return 1;
    }

    // Read the file line by line
    char lines[1024];
    while (fgets(line, sizeof(line), meminfo_file)) {
        // Look for the "MemTotal" line
        if (strncmp(line, "MemTotal", 8) == 0) {
            // Extract the numerical value of the total memory in bytes
            int total_memory_bytes;
            sscanf(line + 10, "%d", &total_memory_bytes);

            // Convert the value to a more human-readable format, such as megabytes or gigabytes
            int total_memory_mb = total_memory_bytes / 1024;
            int total_memory_gb = total_memory_mb / 1024;

            // Print the value with the "RAM:" prefix
            printf("\033[1;31mRAM: %d MB (%d GB)\033[0m\n", total_memory_mb, total_memory_gb);
            break;
        }
    }

    // Close the file
    fclose(meminfo_file);
    
printf("\033[1;32m _ _     \033[0m\n");
printf("\033[1;32m| (_)      \033[0m\n");
printf("\033[1;32m| |_ _ __  _   ___  __\033[0m\n");
printf("\033[1;32m| | | '_ \\| | | \\ \\/ /\033[0m\n");  // remember, \ has a special meaing so if you want to change this art put a double \\ to make a slash      
printf("\033[1;32m| | | | | | |_| |>  < \033[0m\n");
printf("\033[1;32m|_|_|_| |_|\\__,_/_/\\_\\\033[0m\n");              
          




    return 0;
}
