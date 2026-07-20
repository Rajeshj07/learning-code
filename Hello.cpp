#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
private:
    // Define the Trie Node structure
    struct TrieNode {
        unordered_map<char, TrieNode*> children;
        int count;
        
        TrieNode() {
            count = 0;
        }
    };

    // Helper function to insert a word into the Trie and update frequencies
    void insert(TrieNode* root, const string& word) {
        TrieNode* curr = root;
        for (char c : word) {
            // If the character doesn't exist, create a new node
            if (curr->children.find(c) == curr->children.end()) {
                curr->children[c] = new TrieNode();
            }
            curr = curr->children[c];
            curr->count++; // Increment how many words pass through this prefix
        }
    }

    // Helper function to find the shortest unique prefix for a given word
    string getUniquePrefix(TrieNode* root, const string& word) {
        TrieNode* curr = root;
        string prefix = "";
        
        for (char c : word) {
            prefix += c;
            curr = curr->children[c];
            
            // If only 1 word (this word) passes through this node, it's unique!
            if (curr->count == 1) {
                break;
            }
        }
        return prefix;
    }

public:
    vector<string> findPrefixes(vector<string>& arr) {
        TrieNode* root = new TrieNode();
        
        // Step 1: Insert all words into the Trie
        for (const string& word : arr) {
            insert(root, word);
        }
        
        // Step 2: Query the Trie to find the unique prefix for each word
        vector<string> result;
        for (const string& word : arr) {
            result.push_back(getUniquePrefix(root, word));
        }
        
        return result;
    }
};
