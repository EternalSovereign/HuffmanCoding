#include <iostream>
#include <unordered_map>
#include <queue>
using namespace std;

class node
{
public:
    int data;
    char c;
    node *left;
    node *right;

    // Constructor for internal nodes
    node(int data, node *left, node *right)
    {
        this->data = data;
        this->left = left;
        this->right = right;
    }

    // Constructor for leaf nodes
    node(int data, char c)
    {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
        this->c = c;
    }
};

class comp
{
public:
    bool operator()(node *A, node *B) const
    {
        return A->data > B->data;
    }
};

void maketable(node *root, unordered_map<char, string> &m, string s)
{
    if (root->left == NULL && root->right == NULL)
    {
        m[root->c] = s;
        // acout << root->c << " " << s << endl;
        return;
    }
    maketable(root->left, m, s + "0");
    maketable(root->right, m, s + "1");
    return;
}

int main()
{
    string input;
    cin >> input;
    unordered_map<char, int> m;

    // Count the frequency of each character
    for (char ch : input)
    {
        m[ch]++;
    }

    priority_queue<node *, vector<node *>, comp> q;

    // Create leaf nodes for each character and push them into the priority queue
    for (const auto &pair : m)
    {
        node *n = new node(pair.second, pair.first);
        q.push(n);
    }

    // Build the Huffman tree
    while (q.size() > 1)
    {
        node *h1 = q.top();
        q.pop();
        node *h2 = q.top();
        q.pop();
        node *s1 = new node(h1->data + h2->data, h1, h2);
        q.push(s1);
    }

    node *root = q.top();
    q.pop();

    // Perform further operations with the Huffman tree if needed
    unordered_map<char, string> table;
    string code = "";
    maketable(root, table, code);
    for (const auto &i : table)
    {
        cout << i.first << " " << i.second << endl;
    }
    cin >> input;

    return 0;
}

// #include <vector>
// #include <iostream>
// #include <unordered_map>
// #include <queue>
// using namespace std;

// class hnode
// {
// public:
//     int data;
//     char c;
//     hnode(char c, int data)
//     {
//         this->c = c;
//         this->data = data;
//     }
// };

// class node
// {
// public:
//     int data;
//     node *leftsum;
//     node *rightsum;
//     hnode *left;
//     hnode *right;
//     node(int data, hnode *left, hnode *right)
//     {
//         this->data = data;
//         this->left = left;
//         this->right = right;
//     }
// };

// class comp
// {
// public:
//     bool operator()(node *A, node *B) const
//     {
//         return A->data > B->data;
//     }
// };
// class comp1
// {
// public:
//     bool operator()(hnode *A, hnode *B) const
//     {
//         return A->data > B->data;
//     }
// };
// bool compare(pair<char, int> &A, pair<char, int> &B)
// {
//     return A.second < B.second;
// }

// int main()
// {
//     string s;
//     cin >> s;
//     unordered_map<char, int> m;
//     unordered_map<char, int>::iterator it;
//     for (int i = 0; i < s.length(); i++)
//     {
//         m[s[i]]++;
//     }
//     vector<pair<char, int>> vec(m.begin(), m.end());
//     sort(vec.begin(), vec.end(), compare);
//     for (auto i : vec)
//     {
//         cout << i.first << " " << i.second << endl;
//     }
//     node *s1 = new node(INT_MAX, NULL, NULL);
//     for (auto i = vec.begin(); i != vec.end(); i++)
//     {
//         if (s1->data > i->first && s1->data > (i + 1)->first)
//         {
//             hnode *h1 = new hnode(i->first, i->second);
//             i++;
//             hnode *h2 = new hnode(i->first, i->second);
//             node *s1 = new node(h1->data + h2->data, h1, h2);
//         }
//     }
//     return 0;
// }
