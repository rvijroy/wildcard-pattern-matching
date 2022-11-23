#include <iostream>

#include <matcher.h>

int main()
{
    auto matcher = PatternMatcher::WildcardTrie({"suyash", "samarth", "sanchit", "saman", "amish", "ravi"});
    std::vector<std::string> matched_words = matcher.find("sa*n");

    if (matched_words.empty())
    {
        std::cout << "No words Found." << std::endl;
    }
    else
    {
        std::cout << "Found the Word(s)!" << std::endl;
        for (const std::string &word : matched_words)
            std::cout << word << " ";
        std::cout << std::endl;
    }
    return 0;
}