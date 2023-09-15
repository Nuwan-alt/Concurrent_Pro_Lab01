//
// Created by jayas on 9/15/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <dirent.h>
#include <errno.h>

void calculateStatsForFile(const char *filename) {
    FILE *fp;
    char buffer[1024];
    double sum = 0.0;
    double sum_of_squares = 0.0;
    double data;
    int count = 0;

    // Open the CSV file for reading
    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error opening file %s %s\n",filename,strerror(errno));
        return;
    }

    // Read and process each line in the CSV file
    while (fgets(buffer, sizeof(buffer), fp)) {
        if (sscanf(buffer, "%lf", &data) == 1) {
            // Add the data to the sum
            sum += data;
            // Add the square of the data to the sum_of_squares
            sum_of_squares += data * data;
            count++;
        }
    }

    // Close the file
    fclose(fp);

    // Calculate the average
    double average = sum / count;

    // Calculate the variance (mean of squared differences from the mean)
    double variance = (sum_of_squares / count) - (average * average);

    // Calculate the standard deviation (square root of the variance)
    double std_deviation = sqrt(variance);

    // Print the results for the current file
    printf("File: %s\n", filename);
    printf("Average: %.2lf\n", average);
    printf("Standard Deviation: %.2lf\n", std_deviation);
    printf("\n");
}

int test(){
    struct dirent *entry;
    DIR *dp;

    // Open the current directory
    dp = opendir("../results/serial");


    if (dp == NULL) {
        perror("opendir");
        return 1;
    }

    // Loop through all files in the directory
    while ((entry = readdir(dp))) {
        // Check if the file name ends with ".csv"
        if (strstr(entry->d_name, ".csv") != NULL) {
            // Process the CSV file
            calculateStatsForFile(entry->d_name);
        }
    }

    // Close the directory
    closedir(dp);
}
