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
    printf("Hostname: %s\n", hostname);

    // Get and print DE
        char* desktop_env = getenv("DESKTOP_SESSION");
    if (desktop_env) {
        printf("DE: %s\n", desktop_env);
    }


    // Get and print operating system name and version
    struct utsname uname_buf;
    uname(&uname_buf);
    printf("Operating System: %s %s\n", uname_buf.sysname, uname_buf.release);

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

    printf("Package Manager: %s\n", package_manager);

    // Get and print kernel version
    printf("Kernel: %s\n", uname_buf.release);

    // Get and print uptime
    FILE* uptime_file = fopen("/proc/uptime", "r");
    double uptime;
    fscanf(uptime_file, "%lf", &uptime);
    fclose(uptime_file);
    printf("Uptime: %ld days, %ld hours, %ld minutes\n", (long)uptime / 86400, ((long)uptime % 86400) / 3600, ((long)uptime % 3600) / 60);

        // Get and print CPU information
    FILE* cpuinfo_file = fopen("/proc/cpuinfo", "r");
    char line[1024];
    while (fgets(line, sizeof(line), cpuinfo_file)) {
        if (strncmp(line, "model name", 10) == 0) {
            printf("CPU: %s", line + 13);
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
            printf("GPU: %s", gpu_info);
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
            printf("RAM: %d MB (%d GB)\n", total_memory_mb, total_memory_gb);
            break;
        }
    }

    // Close the file
    fclose(meminfo_file);
    
printf(" _ _     \n");
printf("| (_)      \n");
printf("| |_ _ __  _   ___  __\n");
printf("| | | '_ \\| | | \\ \\/ /\n");  // remember, \ has a special meaing so if you want to change this art put a double \\ to make a slash      
printf("| | | | | | |_| |>  < \n");
printf("|_|_|_| |_|\\__,_/_/\\_\\\n");              




    return 0;
}
