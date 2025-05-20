#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "hangman_utils.h"
#include "text_utils.h"

// Test 1: All Unique Letters Guessed
TEST(HangmanEdgeCases, AllUniqueLettersGuessed) {
    std::string word = "hello";
    // Unique letters in "hello": h, e, l, o.
    std::vector<char> guessed = { 'h', 'e', 'l', 'o' };
    EXPECT_EQ(lettersLeftToGuess(word, guessed), 0);
}

// Test 2: No Letters Guessed
TEST(HangmanEdgeCases, NoLettersGuessed) {
    std::string word = "world";
    // Unique letters in "world": w, o, r, l, d.
    std::vector<char> guessed;
    EXPECT_EQ(lettersLeftToGuess(word, guessed), 5);
}

// Test 3: Sorting with Duplicates
TEST(TextUtils, SortVecCharsWithDuplicates) {
    std::vector<char> input = { 'z', 'a', 'm', 'a', 'b' };
    sortVecChars(input);
    std::vector<char> expected = { 'a', 'a', 'b', 'm', 'z' };
    EXPECT_EQ(input, expected);
}

// Test 4: Partial Word Display
TEST(HangmanDisplay, PartialWordDisplay) {
    std::string word = "hangman";
    std::vector<char> guessed = { 'h', 'a', 'n' };
    // Expected: "han__an" where unguessed letters are masked by underscores.
    std::string expected = "han__an";
    EXPECT_EQ(displayWords(word, guessed), expected);
}

// Test 5: Non-Empty ASCII Art Output
TEST(HangmanDisplay, NonEmptyAsciiArtOutput) {
    // Using arbitrary valid parameters for petroglyph.
    std::string artOutput = petroglyph(3, 5);
    EXPECT_FALSE(artOutput.empty());
}