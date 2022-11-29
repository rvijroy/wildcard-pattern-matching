#include <unordered_set>

#include <gtest/gtest.h>

#include <matcher.h>

TEST(TrieMatcherTest, DefaultConstructor) {
    auto matcher = PatternMatcher::WildcardTrie();
    ASSERT_EQ(matcher.size(), 0);
};

TEST(TrieMatcherTest, ArgsConstructorWithNoDuplicates) {
    auto matcher = PatternMatcher::WildcardTrie({"lorem", "ipsum", "dolor", "fizz", "buzz"});
    ASSERT_EQ(matcher.size(), 5);
};

TEST(TrieMatcherTest, ArgsConstructorWithDuplicates) {
    auto matcher = PatternMatcher::WildcardTrie({"fizz", "lorem", "ipsum", "dolor", "fizz", "buzz"});
    ASSERT_EQ(matcher.size(), 5);
};

TEST(TrieMatcherTest, FindAsInExample) {
    auto matcher = PatternMatcher::WildcardTrie({"suyash", "samarth", "sanchit", "saman", "amish", "ravi"});
    ASSERT_EQ(matcher.size(), 6);
    
    auto res = matcher.find("sa*n");
    ASSERT_EQ(res.size(), 1);
    ASSERT_EQ(res[0], "saman");
};

TEST(TrieMatcherTest, FindWithWildCard) {
    std::vector<std::string> words {{"suyash", "samarth", "sanchit", "saman", "amish", "ravi"}};
    
    auto matcher = PatternMatcher::WildcardTrie(words);
    ASSERT_EQ(matcher.size(), words.size());
   
    auto res = matcher.find("*");
    ASSERT_EQ(res.size(), words.size());
    
    auto result_set = std::unordered_set<std::string>(res.begin(), res.end());
    for (const std::string& word: words) {
        ASSERT_NE(result_set.find(word), result_set.end());
    }
};