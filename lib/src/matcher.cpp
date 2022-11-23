#include <matcher.h>

namespace PatternMatcher
{
    void WildcardTrie::_wild_card_search(const std::string &pattern, const std::string &prefix, std::shared_ptr<node_t> root, size_t len, std::vector<std::string> &wildcard_matches) const noexcept
    {
        if (root == nullptr)
            return;

        if (len == pattern.size())
        {
            if (root->is_leaf)
                wildcard_matches.push_back(prefix);
            return;
        }

        if (pattern[len] == WildcardTrie::WILDCARD_CHAR)
        {
            // CASE: When matching 0 instances of a character
            // We consider the wildcard matched and move over to the next character.
            // Therefore we use the same prefix as before, use the same root,
            // and move to the next character in the string by increasing the len vairable.
            _wild_card_search(pattern, prefix, root, len + 1, wildcard_matches);

            std::string new_prefix = prefix;
            // Matching to any character
            for (auto [next_char, next_node] : root->children)
            {
                new_prefix.push_back(next_char);
                _wild_card_search(pattern, new_prefix, next_node, len, wildcard_matches);
                new_prefix.pop_back();
            }
        }

        else
        {
            char next_char = pattern[len];
            std::shared_ptr<node_t> next_node = root->children[next_char];
            std::string new_prefix = prefix;

            new_prefix.push_back(next_char);
            _wild_card_search(pattern, new_prefix, next_node, len + 1, wildcard_matches);
            new_prefix.pop_back();
        }
    }

    WildcardTrie::WildcardTrie(const std::vector<std::string> &words) noexcept
    {
        for (const std::string &word : words)
        {
            add(word);
        }
    }

    void WildcardTrie::add(const std::string &word) noexcept
    {
        std::shared_ptr<node_t> curr = _root;
        for (const char c : word)
        {
            if (curr->children[c] == nullptr)
            {
                curr->children[c] = std::make_shared<node_t>();
            }

            curr = curr->children[c];
        }

        if (!curr->is_leaf)
            _size++;
        curr->is_leaf = true;
    }

    std::vector<std::string> WildcardTrie::find(const std::string &pattern) const noexcept
    {
        std::vector<std::string> wildcard_matches{};
        _wild_card_search(pattern, "", _root, 0, wildcard_matches);
        return wildcard_matches;
    }

    int WildcardTrie::size() const noexcept
    {
        return _size;
    }

};