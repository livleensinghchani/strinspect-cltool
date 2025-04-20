//  _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ 
// |   __|_   _| __  |     |   | |   __|  _  |   __|     |_   _|
// |__   | | | |    -|-   -| | | |__   |   __|   __|   --| | |  
// |_____| |_| |__|__|_____|_|___|_____|__|  |_____|_____| |_|  
//  ▄▄·  ▄ .▄ ▄▄▄·  ▐ ▄ ▪  
// ▐█ ▌▪██▪▐█▐█ ▀█ •█▌▐███ 
// ██ ▄▄██▀▐█▄█▀▀█ ▐█▐▐▌▐█·
// ▐███▌██▌▐▀▐█ ▪▐▌██▐█▌▐█▌
// ·▀▀▀ ▀▀▀ · ▀  ▀ ▀▀ █▪▀▀▀
// MADE WITH ❤️ :


#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 2048

// Colors
#define COLOR_RESET "\e[0m"
#define BRED "\e[1;31m"
#define BLU "\e[0;34m"
#define BMAG "\e[1;35m"
#define BGRN "\e[1;32m"

// Prototype Functions
int request_input(char* const);
int word_handler(int, char* const);
void print_ascii_range(char* const, int, int);
void print_hex_range(char* const, int, int);
void print_decimal_range(char* const, int, int);
void print_binary_range(char* const, int, int);
void print_binary_char(char);
void copy_string(char* const, char* const);

void print_footer() {
  printf("--------------<");
  puts(BMAG);
  puts("( |-| /\\ |\\| |");
  puts(COLOR_RESET);
}

// Functions
void print_welcome() {
  puts(" _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ ");
  puts("|   __|_   _| __  |     |   | |   __|  _  |   __|     |_   _|");
  puts("|__   | | | |    -|-   -| | | |__   |   __|   __|   --| | |  ");
  puts("|_____| |_| |__|__|_____|_|___|_____|__|  |_____|_____| |_|  ");
  puts("");
}

int request_input(char* const string_buffer) {
  printf("String to Inspect: ");
  if(fgets(string_buffer, BUFFER_SIZE, stdin) == NULL) {
    printf("%sINVALID INPUT%s\n", BRED, COLOR_RESET);
    puts("Exiting...");
    return -1;
  }
  return 0;
}

int word_handler(int index, char* const string_buffer) {
  int start_index = index;
  int end_index = index;
  unsigned char return_back = 0;

  while(1 && index < BUFFER_SIZE) {
    if(string_buffer[index] == 3) {
      return -1;
    }
    if(string_buffer[index] == '\0' || string_buffer[index] == '\n') {
      end_index = index;
      return_back = 1;
      break;
    }
    if(string_buffer[index] == ' ') {
      end_index = index;
      break;
    }
    index++;
  }

  if(start_index == end_index && string_buffer[start_index] == ' ') {
    return end_index+1;
  }

  if(string_buffer[start_index] == '\n') {
    printf("%sEND OF STRING%s\n\n", BRED, COLOR_RESET);
    return -1;
  }

  print_ascii_range(string_buffer, start_index, end_index);
  print_hex_range(string_buffer, start_index, end_index);
  print_decimal_range(string_buffer, start_index, end_index);
  print_binary_range(string_buffer, start_index, end_index);
  puts("");

  if(return_back) {
    return -1;
  } 

  return end_index+1;
}

void print_ascii_range(char* const string_buffer, int start, int end) {
  printf("%sASCII:%s\t", BLU, COLOR_RESET);
  for(int i = start; i < end; i++) {
    printf("%9c", string_buffer[i]);
  }
  puts("");
}

void print_hex_range(char* const string_buffer, int start, int end) {
  printf("%sHEX:%s\t", BLU, COLOR_RESET);
  for(int i = start; i < end; i++) {
    printf("%9X", string_buffer[i]);
  }
  puts("");
}

void print_decimal_range(char* const string_buffer, int start, int end) {
  printf("%sDEC:%s\t", BLU, COLOR_RESET);
  for(int i = start; i < end; i++) {
    printf("%9d", string_buffer[i]);
  }
  puts("");
}

void print_binary_range(char* const string_buffer, int start, int end) {
  printf("%sBIN:%s\t", BLU, COLOR_RESET);
  for(int i = start; i < end; i++) {
    printf(" ");
    print_binary_char(string_buffer[i]);
  }
  puts("");
}

void print_binary_char(char character) {
  for (int i = 0; i < 8; i++) {
    if((character & 0b10000000) == 0b10000000) {
      printf("%d", 1);
    } else {
      printf("%d", 0);
    }
    character = character << 1;
  }
}

void copy_string(char* const source, char* const destination) {
  int index = 0;
  while(source[index] != '\0') {
    destination[index] = source[index];
    index++;
  }
  destination[index] = '\0';
}

void print_stats(char* const string_buffer) {
  unsigned int index = 0;
  unsigned int letter_count = 0;
  unsigned int  word_count = 0;

  while(string_buffer[index] != '\n' && string_buffer[index] != '\0') {
    if(string_buffer[index] == ' ') {
      index++;
      continue;
    }
    
    if(index == 0) {
      word_count++; 
      letter_count++;
      index++;
      continue;
    }

    if(string_buffer[index-1] == ' ' && string_buffer[index] != ' ') {
      word_count++;
    }
    letter_count++;
    index++;
  }

  printf("%sSTR STATS:%s\n", BGRN, COLOR_RESET);
  printf("%sWords%s   : %d\n", BLU, COLOR_RESET, word_count);
  printf("%sLetters%s : %d\n", BLU, COLOR_RESET, letter_count);
  puts("");
}

int main(int argc, char* argv[]) {
  char* const string_buffer = (char*)malloc(BUFFER_SIZE);
  
  if(NULL == string_buffer) {
    fputs("Memory allocation failed!", stderr);
    return EXIT_FAILURE;
  }
  
  print_welcome();
  if(2 != argc) {
    if(request_input(string_buffer) == -1) {
      free(string_buffer);
      exit(1);
    }
  } else {
    copy_string(argv[1], string_buffer);
  }

  int word_index = 0;
  while(word_index != -1) {
    word_index = word_handler(word_index, string_buffer);
  }

  print_stats(string_buffer);

  free(string_buffer);
  print_footer();
  exit(0);
}
