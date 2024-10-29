#include "Server.h"
struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfPath = false;
    Server* cdnEndpoint;
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode(); // Root node
    }

    void insert(const std::string& path, Server* cdnEndpoint) {
        TrieNode* current = root;
        for (char ch : path) {
            if (!current->children.count(ch)) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->isEndOfPath = true;
        current->cdnEndpoint = cdnEndpoint; // Store CDN endpoint
    }

    Server* search(const std::string& path) {
        TrieNode* current = root;
        for (char ch : path) {
            if (!current->children.count(ch)) {
                std::cout << "No CDN found";
                return nullptr;
            }

            current = current->children[ch];

            if (current->isEndOfPath) {
                return current->cdnEndpoint;
            }
        }
        if (!current->isEndOfPath) {
            std::cout << "No CDN found";
            return nullptr;
        }
        return current->cdnEndpoint;
    }
};
