#include "compare_sorts.h"
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
}

bool is_unique(char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int num_words, const char *word)
{
    // Students should complete the implementation of this function
    return true;
}

void quicksort(int *indices, char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int left, int right)
{
    // Students should complete the implementation of this function
}

void shellsort(int *indices, char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int size) 
{
    // Students should complete the implementation of this function
}

void bubblesort(int *indices, char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int size)
{
    // Students should complete the implementation of this function
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
}

void sort_and_measure_shell_bubble(char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int* indices, int num_words, void (*sort_func)(int *, char [MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int), const char *sort_name) 
{
    // Students should complete the implementation of this function
}

int main() {
    const char *input_file = "/Users/mahmoodmoussavi/Dropbox/Data Structue Code/Compare Sort Methods/input.txt"; // Change this to your input file
    char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE];
    int num_words;
    
    read_words(input_file, words, num_words);
    
    int indices[num_words];
    for (int i = 0; i < num_words; ++i) {
        indices[i] = i;
    }

    sort_and_measure_quicksort(words,indices, num_words, quicksort, "Quick Sort");
    write_words("/Users/mahmoodmoussavi/Dropbox/ENSF 694 Labs/Lab2/Compare Sort Methods/output_quicksort.txt", words, indices, num_words);
    sort_and_measure_shell_bubble(words,indices, num_words, shellsort, "Shell Sort");
    write_words("/Users/mahmoodmoussavi/Dropbox/ENSF 694 Labs/Lab2/Compare Sort Methods/output_shellsort.txt", words, indices, num_words);
    sort_and_measure_shell_bubble(words, indices, num_words, bubblesort, "Bubble Sort");
    write_words("/Users/mahmoodmoussavi/Dropbox/ENSF 694 Labs/Lab2/Compare Sort Methods/output_bubblesort.txt", words, indices, num_words);
    return 0;
}

