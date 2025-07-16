/*
 *  lab2exe_E.cpp
 *  ENSF 694 Lab 2 Exercise E
 *  Completed by: Jack Shenfield
 *  Development Date: July 16th, 2025
 */

#include "compare_sorts.h"
#include <ctype.h>
void to_lower(char *str)
{
    while (*str) {
        *str = std::tolower(*str);
        ++str;
    }
}

void strip_punctuation(char *word)
{
// Students should complete the implementation of this function
    if(word == NULL){
        return;
    }

    char * initial = word; // create new pointers to track comparisons through word
    char * final = word;

    while(*initial != '\0'){ // go through the entire C-string
        if(isalnum(*initial) || *initial == '-'){ // if the initial char is alphanumeric or a hyphen, keep it
            *final = *initial;
            final++; // increment final address
        }
        initial++; // increment initial address
    }

    *final = '\0';
}

bool is_unique(char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int num_words, const char *word)
{
    // Students should complete the implementation of this function
    bool flag = true; // assume unique

    for(int i = 0; i < num_words - 1; i++){ // run through all except the last word, which is compared by 2nd loop every time
        for(int j = i + 1; j < num_words; j++){ // skip i word, compare all others
            if(strcmp(words[i], words[j]) == 0){ // string compare
                flag = false;
                return flag;
            }
        }
    }

    return flag;
}

void quicksort(int *indices, char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int left, int right)
{
    // Students should complete the implementation of this function
    if (left >= right) return;

    int pivot = indices[(left + right)/2]; // initial pivot location
    int i = left;
    int j = right;

    while (i <= j) { // while left is less than or equal to right

        while (strcmp(words[indices[i]], words[pivot]) < 0){
            i++; // move towards middle
        }
        while (strcmp(words[indices[j]], words[pivot]) > 0){
            j--; // move towards middle
        }

        if (i <= j) { // swap
            int temp = indices[i];
            indices[i] = indices[j];
            indices[j] = temp;
            i++;
            j--;
        }
    }

    quicksort(indices, words, left, j);
    quicksort(indices, words, i, right);
}

void shellsort(int *indices, char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int size) 
{
    // Students should complete the implementation of this function
    for (int gap = size / 2; gap > 0; gap /= 2) { // initialize gap at half of the size of array
        for (int i = gap; i < size; i++) {
            int temp = indices[i]; // store current value
            int j = i;

            while (j >= gap && strcmp(words[indices[j - gap]], words[temp]) > 0) { // if higher value is to the right
                indices[j] = indices[j - gap]; // save new value
                j -= gap; 
            }

            indices[j] = temp; // save value for next loop
            }
        }
}

void bubblesort(int *indices, char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int size)
{
    // Students should complete the implementation of this function
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (strcmp(words[indices[j]], words[indices[j + 1]]) > 0) { // check if the next value is less than

                int temp = indices[j]; // swap indices
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }
}

void read_words(const char *input_file, char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int &num_words)
{
    std::ifstream infile(input_file);
    if (!infile) {
        std::cerr << "Error opening input file.\n";
        exit(1);
    }

    char word[MAX_WORD_SIZE + 1];
    num_words = 0;

    while (infile >> word) {
        strip_punctuation(word);
        to_lower(word);
        if (word[0] != '\0' && num_words < MAX_UNIQUE_WORDS && is_unique(words, num_words, word)) {
            std::strncpy(words[num_words++], word, MAX_WORD_SIZE);
        }
    }

    infile.close();
}

void write_words(const char *output_file, char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int *indices, int num_words) 
{
    std::ofstream outfile(output_file);
    if (!outfile) {
        std::cerr << "Error opening output file.\n";
        exit(1);
    }

    for (int i = 0; i < num_words; ++i) {
        outfile << words[indices[i]] << '\n';
    }

    outfile.close();
}

void sort_and_measure_quicksort(char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int* indices, int num_words, void (*sort_func)(int *, char [MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int, int), const char *sort_name)
{
    // Students should complete the implementation of this function


    auto start = std::chrono::high_resolution_clock::now(); // start the clock

    sort_func(indices, words, 0, num_words - 1); // Call the function

    auto end = std::chrono::high_resolution_clock::now(); // end clock

    std::chrono::duration<double> duration = end - start; // calculate the duration and store in double

       std::cout << "\nSorting with Quick Sort completed in " << duration.count() << " seconds.\n"; // print the time
}

void sort_and_measure_shell_bubble(char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int* indices, int num_words, void (*sort_func)(int *, char [MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int), const char *sort_name) 
{
    // Students should complete the implementation of this function


    auto start = std::chrono::high_resolution_clock::now(); // start the clock

    sort_func(indices, words, num_words); // Call the function

    auto end = std::chrono::high_resolution_clock::now(); // end clock

    std::chrono::duration<double> duration = end - start; // calculate the duration and store in double
    if(sort_func == bubblesort){
        std::cout << "\nSorting with Bubble Sort completed in " << duration.count() << " seconds.\n"; // print the time
    }
    else{
        std::cout << "\nSorting with Shell Sort completed in " << duration.count() << " seconds.\n"; // print the time
    }

}

int main() {
    const char *input_file = "input.txt"; // Change this to your input file
    char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE];
    int num_words;
    
    read_words(input_file, words, num_words);
    
    int indices[num_words];
    for (int i = 0; i < num_words; ++i) {
        indices[i] = i;
    }

    sort_and_measure_quicksort(words,indices, num_words, quicksort, "Quick Sort");
    write_words("/Users/jbs/Desktop/ENSF694/Lab_Assignments/ENSF694_LabAssignment2/output_quicksort.txt", words, indices, num_words);
    sort_and_measure_shell_bubble(words,indices, num_words, shellsort, "Shell Sort");
    write_words("/Users/jbs/Desktop/ENSF694/Lab_Assignments/ENSF694_LabAssignment2/output_shellsort.txt", words, indices, num_words);
    sort_and_measure_shell_bubble(words, indices, num_words, bubblesort, "Bubble Sort");
    write_words("/Users/jbs/Desktop/ENSF694/Lab_Assignments/ENSF694_LabAssignment2/output_bubblesort.txt", words, indices, num_words);
    return 0;
}

