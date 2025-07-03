// Patil Programming Language 49 (PPL49) - Extended Interpreter Core with Map & Set
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <queue>
#include <random>
#include <ctime>
#include <chrono>
#include <cctype>
#include <memory>
#include <limits>
#include <algorithm>
#include <cmath>
using namespace std;

void print_banner() {
    static bool shown = false;
    if (!shown) {
        cout << "OM" << endl;
        shown = true;
    }
}

// Global Data Structures
unordered_map<string, int> variables;
unordered_map<string, double> doubleVars;
unordered_map<string, float> floatVars;
unordered_map<string, long long> longVars;
unordered_map<string, string> stringVars;
unordered_map<string, string> remembered;
unordered_map<string, vector<int>> arrays;
unordered_map<string, stack<int>> stacks;
unordered_map<string, queue<int>> queues;
unordered_map<string, priority_queue<int>> priorityQueues;
unordered_map<string, priority_queue<int, vector<int>, greater<int>>> minPriorityQueues;
unordered_map<string, unordered_map<int, vector<int>>> graphs;
unordered_map<string, unordered_map<int, vector<pair<int, int>>>> weightedGraphs;
unordered_map<string, unordered_map<string, int>> maps;
unordered_map<string, unordered_set<int>> sets;
unordered_map<string, unordered_map<string, string>> classObjects;
unordered_map<string, unordered_map<string, vector<string>>> stringGraphs;
// Linked List
struct Node {
    int data;
    shared_ptr<Node> next;
    Node(int val) : data(val), next(nullptr) {}
};
unordered_map<string, shared_ptr<Node>> linkedLists;

void insert_end(const string& name, int val) {
    auto& head = linkedLists[name];
    if (!head) head = make_shared<Node>(val);
    else {
        auto cur = head;
        while (cur->next) cur = cur->next;
        cur->next = make_shared<Node>(val);
    }
}
void reverse_linkedlist(const string& name) {
    if (!linkedLists.count(name)) {
        cout << "[Linked List '" << name << "' not found]" << endl;
        return;
    }
    shared_ptr<Node> prev = nullptr, curr = linkedLists[name], next = nullptr;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    linkedLists[name] = prev;
}
// rotate linked list
void rotate_linkedlist(const string& name, int k) {
    if (!linkedLists.count(name)) {
        cout << "[Linked List '" << name << "' not found]" << endl;
        return;
    }

    shared_ptr<Node> head = linkedLists[name];
    if (!head || !head->next || k == 0) return;

    // Find length and tail
    int len = 1;
    shared_ptr<Node> tail = head;
    while (tail->next) {
        tail = tail->next;
        len++;
    }

    k = k % len;
    if (k == 0) return;

    // Connect tail to head (circular)
    tail->next = head;

    // Find new tail (len - k steps)
    shared_ptr<Node> newTail = head;
    for (int i = 0; i < len - k - 1; ++i)
        newTail = newTail->next;

    // Break the circle
    linkedLists[name] = newTail->next;
    newTail->next = nullptr;
}
// search linked list
void search_linkedlist(const string& name, int target) {
    if (!linkedLists.count(name)) {
        cout << "[Linked List '" << name << "' not found]" << endl;
        return;
    }

    auto cur = linkedLists[name];
    int position = 0;
    while (cur) {
        if (cur->data == target) {
            cout << "Found at position " << position << endl;
            return;
        }
        cur = cur->next;
        position++;
    }

    cout << "Not found" << endl;
}
void dijkstra(const string& name, int start) {
    if (!weightedGraphs.count(name)) {
        cout << "[Graph '" << name << "' not found]" << endl;
        return;
    }

    unordered_map<int, int> dist;
    for (auto& [node, _] : weightedGraphs[name]) {
        dist[node] = INT_MAX;
    }

    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;

        for (auto& [v, w] : weightedGraphs[name][u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    // Print result
    for (auto& [node, d] : dist) {
        cout << "Distance to " << node << " = ";
        if (d == INT_MAX) cout << "INF";
        else cout << d;
        cout << endl;
    }
}
void dijkstra_unweighted_str(const string& name, const string& start) {
    if (!stringGraphs.count(name)) {
        cout << "[Graph '" << name << "' not found]" << endl;
        return;
    }

    unordered_map<string, int> dist;
    unordered_set<string> visited;
    queue<string> q;

    // Initialize all distances to "infinity"
    for (auto& [node, _] : stringGraphs[name]) {
        dist[node] = INT_MAX;
    }

    dist[start] = 0;
    visited.insert(start);
    q.push(start);

    while (!q.empty()) {
        string u = q.front(); q.pop();

        for (const string& v : stringGraphs[name][u]) {
            if (!visited.count(v)) {
                visited.insert(v);
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    // Print distances
    for (auto& [node, d] : dist) {
        cout << "Distance to " << node << " = ";
        if (d == INT_MAX) cout << "INF";
        else cout << d;
        cout << endl;
    }
}
void dijkstra_unweighted_str_with_path(const string& name, const string& start) {
    if (!stringGraphs.count(name)) {
        cout << "[Graph '" << name << "' not found]" << endl;
        return;
    }

    unordered_map<string, int> dist;
    unordered_map<string, string> parent;
    unordered_set<string> visited;
    queue<string> q;

    // Initialize
    for (auto& [node, _] : stringGraphs[name]) {
        dist[node] = INT_MAX;
    }

    dist[start] = 0;
    visited.insert(start);
    q.push(start);
    parent[start] = "";

    while (!q.empty()) {
        string u = q.front(); q.pop();

        for (const string& v : stringGraphs[name][u]) {
            if (!visited.count(v)) {
                visited.insert(v);
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    // Output distances and paths
    for (auto& [node, d] : dist) {
        cout << "Distance to " << node << " = ";
        if (d == INT_MAX) {
            cout << "INF" << endl;
        } else {
            cout << d << ", Path: ";
            vector<string> path;
            for (string cur = node; !cur.empty(); cur = parent[cur])
                path.push_back(cur);
            reverse(path.begin(), path.end());
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i];
                if (i != path.size() - 1) cout << " -> ";
            }
            cout << endl;
        }
    }
}
void insert_front(const string& name, int val) {
    auto newNode = make_shared<Node>(val);
    newNode->next = linkedLists[name];
    linkedLists[name] = newNode;
}

void print_list(const string& name) {
    auto cur = linkedLists[name];
    while (cur) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << endl;
}

// Binary Tree
struct TreeNode {
    int data;
    shared_ptr<TreeNode> left, right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};
unordered_map<string, shared_ptr<TreeNode>> trees;

void insert_tree_node(shared_ptr<TreeNode>& root, int val) {
    if (!root) root = make_shared<TreeNode>(val);
    else if (val < root->data) insert_tree_node(root->left, val);
    else insert_tree_node(root->right, val);
}

void print_ascii_tree(shared_ptr<TreeNode> root, int space = 0, int height = 10) {
    if (!root) return;
    space += height;
    print_ascii_tree(root->right, space);
    cout << endl;
    for (int i = height; i < space; i++) cout << ' ';
    cout << root->data << "\n";
    print_ascii_tree(root->left, space);
}

shared_ptr<TreeNode> delete_tree_node(shared_ptr<TreeNode> root, int val) {
    if (!root) return nullptr;
    if (val < root->data) root->left = delete_tree_node(root->left, val);
    else if (val > root->data) root->right = delete_tree_node(root->right, val);
    else {
        if (!root->left) return root->right;
        if (!root->right) return root->left;
        shared_ptr<TreeNode> temp = root->right;
        while (temp->left) temp = temp->left;
        root->data = temp->data;
        root->right = delete_tree_node(root->right, temp->data);
    }
    return root;
}
bool search_tree(shared_ptr<TreeNode> root, int val) {
    if (!root) return false;
    if (root->data == val) return true;
    if (val < root->data)
        return search_tree(root->left, val);
    else
        return search_tree(root->right, val);
}

int tree_height(shared_ptr<TreeNode> root) {
    if (!root) return 0;
    return 1 + max(tree_height(root->left), tree_height(root->right));
}

void inorder(shared_ptr<TreeNode> root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(shared_ptr<TreeNode> root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(shared_ptr<TreeNode> root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}
void dfs_util(const string& name, int node, unordered_set<int>& visited) {
    visited.insert(node);
    cout << node << " ";
    for (int neighbor : graphs[name][node]) {
        if (!visited.count(neighbor))
            dfs_util(name, neighbor, visited);
    }
}

void dfs(const string& name, int start) {
    if (!graphs.count(name)) {
        cout << "[Graph '" << name << "' not found]" << endl;
        return;
    }
    unordered_set<int> visited;
    dfs_util(name, start, visited);
    cout << endl;
}
void bfs(const string& name, int start) {
    if (!graphs.count(name)) {
        cout << "[Graph '" << name << "' not found]" << endl;
        return;
    }
    unordered_set<int> visited;
    queue<int> q;
    visited.insert(start);
    q.push(start);

    while (!q.empty()) {
        int node = q.front(); q.pop();
        cout << node << " ";
        for (int neighbor : graphs[name][node]) {
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }
    cout << endl;
}
void reverse_array(const string& name) {
    if (!arrays.count(name)) {
        cout << "[Array '" << name << "' not found]" << endl;
        return;
    }
    reverse(arrays[name].begin(), arrays[name].end());
}

void rotate_array(const string& name, int k) {
    if (!arrays.count(name)) {
        cout << "[Array '" << name << "' not found]" << endl;
        return;
    }
    vector<int>& arr = arrays[name];
    int n = arr.size();
    if (n == 0) return;
    k = ((k % n) + n) % n;  // handle negative or large k
    rotate(arr.begin(), arr.begin() + (n - k), arr.end());
}
void sort_array(const string& name) {
    if (!arrays.count(name)) {
        cout << "[Array '" << name << "' not found]" << endl;
        return;
    }
    sort(arrays[name].begin(), arrays[name].end());
}
void sort_array_desc(const string& name) {
    if (!arrays.count(name)) {
        cout << "[Array '" << name << "' not found]" << endl;
        return;
    }
    sort(arrays[name].rbegin(), arrays[name].rend());
}
void reverse_string(const string& name) {
    if (!stringVars.count(name)) {
        cout << "[String '" << name << "' not found]" << endl;
        return;
    }
    reverse(stringVars[name].begin(), stringVars[name].end());
}

void rotate_string(const string& name, int k) {
    if (!stringVars.count(name)) {
        cout << "[String '" << name << "' not found]" << endl;
        return;
    }
    string& s = stringVars[name];
    int n = s.length();
    if (n == 0) return;
    k = ((k % n) + n) % n;  // normalize k
    rotate(s.begin(), s.begin() + (n - k), s.end());
}
void interpret(string line) {
    // File redirection check
    size_t pos = line.find('>');
    if (pos != string::npos) {
        string left = line.substr(0, pos);
        string right = line.substr(pos + 1);
        left.erase(left.find_last_not_of(" ") + 1);
        right.erase(0, right.find_first_not_of(" "));
        ofstream out(right);
        streambuf* coutbuf = cout.rdbuf();
        cout.rdbuf(out.rdbuf());
        interpret(left);
        cout.rdbuf(coutbuf);
        return;
    }

    stringstream ss(line);
    string cmd;
    ss >> cmd;

    // Tree commands
    if (cmd == "create_tree") {
        string name; ss >> name;
        trees[name] = nullptr;
    } else if (cmd == "insert_tree") {
        string name; int val; ss >> name >> val;
        insert_tree_node(trees[name], val);
    } else if (cmd == "inorder") {
        string name; ss >> name;
        inorder(trees[name]); cout << endl;
    } else if (cmd == "preorder") {
        string name; ss >> name;
        preorder(trees[name]); cout << endl;
    } else if (cmd == "postorder") {
        string name; ss >> name;
        postorder(trees[name]); cout << endl;
    } else if (cmd == "search_tree") {
        string name; int val; ss >> name >> val;
        if (trees.find(name) == trees.end()) {
            cout << "[Error: Tree '" << name << "' not found]" << endl;
        } else {
            cout << (search_tree(trees[name], val) ? "Found" : "Not Found") << endl;
        }
    } else if (cmd == "delete_tree") {
        string name; int val; ss >> name >> val;
        trees[name] = delete_tree_node(trees[name], val);
    } else if (cmd == "height") {
        string name; ss >> name;
        cout << tree_height(trees[name]) << endl;
    } else if (cmd == "print_tree") {
        string name; ss >> name;
        print_ascii_tree(trees[name]);
    }
    // reverse rotate sort  in an array
    else if (cmd == "reverse_array") {
    string name;
    ss >> name;
    reverse_array(name);
}
else if (cmd == "rotate_array") {
    string name; int k;
    ss >> name >> k;
    rotate_array(name, k);
}
else if (cmd == "sort_array") {
    string name;
    ss >> name;
    sort_array(name);
}
else if (cmd == "sort_array_desc") {
    string name;
    ss >> name;
    sort_array_desc(name);
}
// reverse rotate in string
else if (cmd == "reverse_string") {
    string name;
    ss >> name;
    reverse_string(name);
}
else if (cmd == "rotate_string") {
    string name; int k;
    ss >> name >> k;
    rotate_string(name, k);
}
    // Graphs and Linked List insertions
    else if (cmd == "add_front") {
        string name; int val; ss >> name >> val;
        insert_front(name, val);
    } else if (cmd == "add_end") {
        string name; int val; ss >> name >> val;
        insert_end(name, val);
    } else if (cmd == "add_edge") {
        string name; int u, v; ss >> name >> u >> v;
        graphs[name][u].push_back(v);
        graphs[name][v];
    } else if (cmd == "add_weighted_edge") {
        string name; int u, v, w; ss >> name >> u >> v >> w;
        weightedGraphs[name][u].push_back({v, w});
        weightedGraphs[name][v];
    }
    // reverse rotate linked list
    else if (cmd == "reverse_linkedlist") {
    string name;
    ss >> name;
    reverse_linkedlist(name);
}
else if (cmd == "rotate_linkedlist") {
    string name; int k;
    ss >> name >> k;
    rotate_linkedlist(name, k);
}
    // bfs dfs 
    else if (cmd == "dfs") {
    string name; int start;
    ss >> name >> start;
    dfs(name, start);
}
else if (cmd == "bfs") {
    string name; int start;
    ss >> name >> start;
    bfs(name, start);
}
// search linked list
else if (cmd == "search_linkedlist") {
    string name;
    int val;
    ss >> name >> val;
    search_linkedlist(name, val);
}
// string dijkstra
else if (cmd == "dijkstra_str") {
    string name, start;
    ss >> name >> start;
    dijkstra_unweighted_str(name, start);
}
    // priority queue
    else if (cmd == "push_pq") {
    string name; int val; ss >> name >> val;
    priorityQueues[name].push(val);
}
// else if (cmd == "push_min_pq") {
//     string name; int val; ss >> name >> val;
//     minPriorityQueues[name].push(val);
// }
else if (cmd == "pop_pq") {
    string name; ss >> name;
    if (priorityQueues.count(name) && !priorityQueues[name].empty()) {
        priorityQueues[name].pop();
    } else {
        cout << "[Empty or not found]" << endl;
    }
}
else if (cmd == "peek_pq") {
    string name; ss >> name;
    if (priorityQueues.count(name) && !priorityQueues[name].empty()) {
        cout << priorityQueues[name].top() << endl;
    } else {
        cout << "[Empty or not found]" << endl;
    }
}
else if (cmd == "size_pq") {
    string name; ss >> name;
    if (priorityQueues.count(name)) {
        cout << priorityQueues[name].size() << endl;
    } else {
        cout << "0" << endl;
    }
}
else if (cmd == "empty_pq") {
    string name; ss >> name;
    if (priorityQueues.count(name)) {
        cout << (priorityQueues[name].empty() ? "true" : "false") << endl;
    } else {
        cout << "true" << endl;
    }
}
// min priority queue
else if (cmd == "push_min_pq") {
    string name; int val; ss >> name >> val;
    minPriorityQueues[name].push(val);
}
else if (cmd == "pop_min_pq") {
    string name; ss >> name;
    if (minPriorityQueues.count(name) && !minPriorityQueues[name].empty()) {
        minPriorityQueues[name].pop();
    } else {
        cout << "[Empty or not found]" << endl;
    }
}
else if (cmd == "peek_min_pq") {
    string name; ss >> name;
    if (minPriorityQueues.count(name) && !minPriorityQueues[name].empty()) {
        cout << minPriorityQueues[name].top() << endl;
    } else {
        cout << "[Empty or not found]" << endl;
    }
}
else if (cmd == "size_min_pq") {
    string name; ss >> name;
    if (minPriorityQueues.count(name)) {
        cout << minPriorityQueues[name].size() << endl;
    } else {
        cout << "0" << endl;
    }
}
else if (cmd == "empty_min_pq") {
    string name; ss >> name;
    if (minPriorityQueues.count(name)) {
        cout << (minPriorityQueues[name].empty() ? "true" : "false") << endl;
    } else {
        cout << "true" << endl;
    }
}
// string graph
// Add edge for string graph
else if (cmd == "add_edge_str") {
    string name, u, v;
    ss >> name >> u >> v;
    stringGraphs[name][u].push_back(v);
    stringGraphs[name][v]; // ensure v appears as key
}

// Print string graph
else if (cmd == "print_graph_str") {
    string name;
    ss >> name;
    if (stringGraphs.count(name)) {
        for (auto& [node, adj] : stringGraphs[name]) {
            cout << node << ": ";
            for (const string& neighbor : adj) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    } else {
        cout << "[Graph not found]" << endl;
    }
}
    // Map and Set support
    else if (cmd == "put_map") {
        string name, key; int value; ss >> name >> key >> value;
        maps[name][key] = value;
    } else if (cmd == "get_map") {
        string name, key; ss >> name >> key;
        cout << maps[name][key] << endl;
    } else if (cmd == "print_map") {
        string name; ss >> name;
        for (auto& [k, v] : maps[name]) cout << k << ": " << v << endl;
    } else if (cmd == "add_to_set") {
        string name; int val; ss >> name >> val;
        sets[name].insert(val);
    } else if (cmd == "remove_from_set") {
        string name; int val; ss >> name >> val;
        sets[name].erase(val);
    } else if (cmd == "print_set") {
        string name; ss >> name;
        for (int val : sets[name]) cout << val << " ";
        cout << endl;
    }
    // oops
    else if (cmd == "class") {
    string className;
    ss >> className;
    classObjects[className] = {}; // Initialize object with empty attributes
}
// Set an attribute on the object
else if (cmd == "set_attr") {
    string className, attr;
    ss >> className >> attr;
    string value;
    getline(ss, value);

    // Handle quoted value
    size_t start = value.find('"'), end = value.rfind('"');
    if (start != string::npos && end != string::npos && end > start)
        classObjects[className][attr] = value.substr(start + 1, end - start - 1);
    else
        classObjects[className][attr] = value.substr(value.find_first_not_of(" "));
}

// Print a specific attribute
else if (cmd == "print_attr") {
    string className, attr;
    ss >> className >> attr;
    if (classObjects.count(className) && classObjects[className].count(attr))
        cout << classObjects[className][attr] << endl;
    else
        cout << "[Attribute not found]" << endl;
}

// Print all attributes of the class/object
else if (cmd == "print_class") {
    string className;
    ss >> className;
    if (!classObjects.count(className))
        cout << "[Class not found]" << endl;
    else {
        for (auto& [key, val] : classObjects[className])
            cout << key << ": " << val << endl;
    }
}
// Delete an attribute from an object
else if (cmd == "delete_attr") {
    string obj, attr;
    ss >> obj >> attr;
    if (classObjects.count(obj)) {
        classObjects[obj].erase(attr);
        cout << "Deleted attribute '" << attr << "' from '" << obj << "'\n";
    } else {
        cout << "[Object not found]" << endl;
    }
}
else if (cmd == "clone_class") {
    string newName, oldName;
    ss >> newName >> oldName;
    if (classObjects.count(oldName)) {
        classObjects[newName] = classObjects[oldName];
        cout << "Cloned '" << oldName << "' to '" << newName << "'\n";
    } else {
        cout << "[Class '" << oldName << "' not found]" << endl;
    }
}
else if (cmd == "call_method") {
    string obj, method;
    ss >> obj >> method;
    string key = "method_" + method;
    if (classObjects.count(obj) && classObjects[obj].count(key))
        cout << classObjects[obj][key] << endl;
    else
        cout << "[Method '" << method << "' not found in '" << obj << "']" << endl;
}
else if (cmd == "inherit_class") {
    string child, parent;
    ss >> child >> parent;
    if (!classObjects.count(parent)) {
        cout << "[Parent class not found]" << endl;
    } else {
        for (auto& [key, val] : classObjects[parent]) {
            if (!classObjects[child].count(key)) {
                classObjects[child][key] = val;
            }
        }
        cout << "Class '" << child << "' now inherits from '" << parent << "'\n";
    }
}
// Simulated method call with parameter substitution
else if (cmd == "call_method") {
    string obj, method, param;
    ss >> obj >> method >> param;
    string key = "method_" + method;
    if (classObjects.count(obj) && classObjects[obj].count(key)) {
        string methodBody = classObjects[obj][key];
        size_t pos = methodBody.find("{0}");
        if (pos != string::npos)
            methodBody.replace(pos, 3, param);
        cout << methodBody << endl;
    } else {
        cout << "[Method '" << method << "' not found in '" << obj << "']" << endl;
    }
}
// Simulated method call with parameter substitution
else if (cmd == "call_method") {
    string obj, method, param;
    ss >> obj >> method >> param;
    string key = "method_" + method;
    if (classObjects.count(obj) && classObjects[obj].count(key)) {
        string methodBody = classObjects[obj][key];
        size_t pos = methodBody.find("{0}");
        if (pos != string::npos)
            methodBody.replace(pos, 3, param);
        cout << methodBody << endl;
    } else {
        cout << "[Method '" << method << "' not found in '" << obj << "']" << endl;
    }
}

    // string 
    else if (cmd == "set_str") {
    string name;
    ss >> name;
    string value;
    getline(ss, value);
    size_t start = value.find('"');
    size_t end = value.rfind('"');
    if (start != string::npos && end != string::npos && end > start) {
        stringVars[name] = value.substr(start + 1, end - start - 1);
    } else {
        cout << "[Error: Invalid string]" << endl;
    }
}
else if (cmd == "concat_str") {
    string target;
    ss >> target;

    string part, result;
    while (ss >> part) {
        if (stringVars.count(part))
            result += stringVars[part];
        else
            result += part; // If not a variable, use raw text
    }

    stringVars[target] = result;
}
// dijikstra
else if (cmd == "dijkstra") {
    string name; int start;
    ss >> name >> start;
    dijkstra(name, start);
}
    // Universal print
    else if (cmd == "print") {
        string rest;
        getline(ss, rest);
        rest.erase(0, rest.find_first_not_of(" "));

        vector<string> parts;
        string part;
        stringstream pss(rest);
        while (getline(pss, part, '+')) {
            part.erase(0, part.find_first_not_of(" "));
            part.erase(part.find_last_not_of(" ") + 1);
            parts.push_back(part);
        }

        for (string& p : parts) {
            if (!p.empty() && p.front() == '"' && p.back() == '"') {
                cout << p.substr(1, p.size() - 2);
            } else if (variables.count(p)) cout << variables[p];
            else if (doubleVars.count(p)) cout << doubleVars[p];
            else if (floatVars.count(p)) cout << floatVars[p];
            else if (longVars.count(p)) cout << longVars[p];
            else if (stringVars.count(p)) cout << stringVars[p];
            else if (remembered.count(p)) cout << remembered[p];
            else if (arrays.count(p)) for (int val : arrays[p]) cout << val << " ";
            else if (stacks.count(p)) {
                stack<int> temp = stacks[p]; vector<int> v;
                while (!temp.empty()) { v.push_back(temp.top()); temp.pop(); }
                reverse(v.begin(), v.end());
                for (int val : v) cout << val << " ";
            } else if (queues.count(p)) {
                queue<int> temp = queues[p];
                while (!temp.empty()) { cout << temp.front() << " "; temp.pop(); }
            } else if (priorityQueues.count(p)) {
                priority_queue<int> temp = priorityQueues[p];
                while (!temp.empty()) { cout << temp.top() << " "; temp.pop(); }
            } else if (minPriorityQueues.count(p)) {
                priority_queue<int, vector<int>, greater<int>> temp = minPriorityQueues[p];
                while (!temp.empty()) { cout << temp.top() << " "; temp.pop(); }
            } else if (linkedLists.count(p)) print_list(p);
            else if (graphs.count(p)) {
                for (auto& [u, adj] : graphs[p]) {
                    cout << u << ": ";
                    for (int v : adj) cout << v << " ";
                    cout << endl;
                }
            } else if (weightedGraphs.count(p)) {
                for (auto& [u, adj] : weightedGraphs[p]) {
                    cout << u << ": ";
                    for (auto& [v, w] : adj) cout << "(" << v << "," << w << ") ";
                    cout << endl;
                }
            } else if (maps.count(p)) {
                for (auto& [k, v] : maps[p]) cout << k << ": " << v << endl;
            } else if (sets.count(p)) {
                for (int val : sets[p]) cout << val << " ";
                cout << endl;
            } else {
                stringstream test(p);
                double num;
                if (test >> num && test.eof()) cout << num;
                else cout << "[Undefined: " << p << "]";
            }
        }
        cout << endl;
    } else {
        cout << "Unknown command: " << cmd << endl;
    }
}
int main() {
    print_banner();
    string line;
    cout << "Welcome to Patil Programming Language 49 (PPL49)\n";
    cout << "Type 'exit' to quit.\n";
    while (true) {
        cout << ">>> ";
        getline(cin, line);
        if (line == "exit") break;
        interpret(line);
    }
    return 0;
}
