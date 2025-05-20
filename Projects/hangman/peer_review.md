# Peer Review by Arjun KC

## Overview

This project repository contains the Hangman game along with a set of unit tests created using Google Test. The purpose of this repository is to provide a peer review for the project1-tests branch, covering the following aspects:

- **Code Structure and CMake Configuration:** Project files are organized into separate directories for source code, headers, and tests. The build system is configured via CMake.
- **Modularity & Readability:** Functions are clearly separated by functionality. Some opportunities for further modularization and documentation have been identified.
- **Test Coverage:** While the existing tests validate basic functionality, additional edge cases, duplicate handling, and error-checking scenarios were lacking.
- **Architecture & Design:** The review addresses opportunities to further decouple input/output from game logic and suggests potential improvements for enhanced extensibility.

## Peer Review Details
- Observations on code structure, readability, and modularity.
- Identification of gaps in test coverage and logic issues.
- Suggestions for improvements in error handling and documentation.
- Overall feedback on the project's architecture and design decisions.

## New Test Cases

Five new Test cases have been added to address specific gaps and edge cases:

1. **All Unique Letters Guessed:** Verifies that the function handling letter guesses recognizes when all unique letters of the word have been guessed.
2. **No Letters Guessed:** Checks that the function correctly counts the unguessed letters when no guesses have been entered.
3. **Sorting with Duplicates:** Validates that the vector sorting function handles duplicate characters appropriately.
4. **Partial Word Display:** Ensures that the word display function reveals correctly guessed letters while masking unguessed letters.
5. **Non-Empty ASCII Art Output:** Confirms that the ASCII art rendering function returns a non-empty result for valid input conditions.

These tests can be found in [Projects/hangman/test/new_hangman_tests.cpp](Projects/hangman/test/new_hangman_tests.cpp).

## How to Build and Run Tests

1. **Clone the Repository:**
   ```sh
   git clone <repository_url>
   ```

2. **Navigate to the Project Directory:**
   ```sh
   cd hangman
   ```

3. **Create and Change to the Build Directory:**
   ```sh
   mkdir build && cd build
   ```

4. **Run CMake:**
   ```sh
   cmake ..
   ```

5. **Build the Project:**
   ```sh
   cmake --build .
   ```

6. **Run the Tests:**
   ```sh
   ctest
   ```


---
