#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace PatternMatcher
{

    class WildcardTrie
    {
    private:
        struct node_t
        {
            std::unordered_map<char, std::shared_ptr<node_t>> children;
            bool is_leaf = false;
        };

    public:
        const static char WILDCARD_CHAR = '*';

    private:
        /**
         * Recursively perform pattern matching in the trie
         */
        void _wild_card_search(const std::string &pattern, const std::string &prefix, std::shared_ptr<node_t> root, size_t len, std::vector<std::string> &wildcard_matches) const noexcept;

    public:
        /**
         * The default constructor
         */
        WildcardTrie() = default;

        /**
         * Initialise the trie using the given words
         */
        WildcardTrie(const std::vector<std::string> &words) noexcept;

        /**
         * Default destructor
         */
        ~WildcardTrie() = default;

        /**
         * Add a string to the trie
         */
        void add(const std::string &word) noexcept;

        /**
         * Find all strings in the trie that match the passed pattern
         */
        std::vector<std::string> find(const std::string &pattern) const noexcept;

        /**
         * Get the number of unique words in the trie
         */
        int size() const noexcept;

    private:
        /**
         * the number of unique words in the trie
         */
        size_t _size = 0;

        /**
         * the root node of the trie
         */
        std::shared_ptr<node_t> _root = std::make_shared<node_t>();
    };

};