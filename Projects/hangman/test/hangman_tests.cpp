#include <gtest/gtest.h>
#include <vector>
#include "../include/hangman_utils.h"

TEST(HangmanChars, sortVecChars) {
    std::vector<char> input = { 'z', 'a', 'm', 'b' };
    sortVecChars(input);
    std::vector<char> output = { 'a', 'b', 'm', 'z' };
    EXPECT_EQ(input, output);
}

TEST(HangmanChars, listVecChars) {
    std::vector<char> input = { 'a', 'b', 'c' };
    EXPECT_EQ(listVecChars(input), "a, b, c");
}

TEST(HangmanChars, charInVec) {
    std::vector<char> vec = { 'a', 'b', 'c' };
    EXPECT_TRUE(charInVec('a', vec));
    EXPECT_FALSE(charInVec('z', vec));
}

TEST(HangmanGameFuncs, lettersLeftToGuess) {
    std::string word = "testy";
    std::vector<char> guessed;
    EXPECT_EQ(lettersLeftToGuess(word, guessed), 4);
    guessed.push_back('t');
    guessed.push_back('e');
    EXPECT_EQ(lettersLeftToGuess(word, guessed), 2); //s and y
    guessed.push_back('s');
    guessed.push_back('y');
    EXPECT_EQ(lettersLeftToGuess(word, guessed), 0);
}

TEST(HangmanGameFuncs, pickFromVec) {
    std::vector<std::string> pool = { "testy" };
    EXPECT_EQ(pickFromVec(pool, 1), "testy"); //1 word
    pool.push_back("toast");
    pool.push_back("tests");
    std::string picked = pickFromVec(pool, 2);
    EXPECT_EQ(picked.length(), 11);
    int spaces = 0;
    for (char c : picked) {
        if (c == ' ') {
            spaces++;
        }
    }
    EXPECT_EQ(spaces, 1); //should only be one space between two words
}