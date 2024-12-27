/*Alice has an undirected tree with n nodes labeled from 0 to n - 1. The tree is represented as a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
Alice wants Bob to find the root of the tree. She allows Bob to make several guesses about her tree. In one guess, he does the following:
Chooses two distinct integers u and v such that there exists an edge [u, v] in the tree.
He tells Alice that u is the parent of v in the tree.
Bob's guesses are represented by a 2D integer array guesses where guesses[j] = [uj, vj] indicates Bob guessed uj to be the parent of vj.
Alice being lazy, does not reply to each of Bob's guesses, but just says that at least k of his guesses are true.
Given the 2D integer arrays edges, guesses and the integer k, return the number of possible nodes that can be the root of Alice's tree. If there is no such tree, return 0.
*/

#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

int rootCount(int edges[][2], int n, int guesses[][2], int m, int k) {
    unordered_map<int, unordered_map<int, bool>> graph;

    for (int i = 0; i < n - 1; i++) {
        int u = edges[i][0], v = edges[i][1];
        graph[u][v] = true;
        graph[v][u] = true;
    }

    unordered_map<int, unordered_map<int, bool>> guess_map;
    for (int i = 0; i < m; i++) {
        int u = guesses[i][0], v = guesses[i][1];
        guess_map[u][v] = true;
    }

    int result = 0;

    for (int root = 0; root < n; ++root) {
        bool parent[n];
        for (int i = 0; i < n; ++i) parent[i] = false;
        parent[root] = true;

        queue<int> q;
        q.push(root);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (auto& neighbor : graph[node]) {
                int child = neighbor.first;
                if (!parent[child]) {
                    parent[child] = true;
                    q.push(child);
                }
            }
        }

        int correct_guesses = 0;
        for (int i = 0; i < m; i++) {
            int u = guesses[i][0], v = guesses[i][1];
            if (parent[u] == true && parent[v] == true) correct_guesses++;
        }

        if (correct_guesses >= k) {
            result++;
        }
    }

    return result;
}

int main() {
    int edges[][2] = {{0,1}, {1,2}, {1,3}, {4,2}};
    int guesses[][2] = {{1,3}, {0,1}, {1,0}, {2,4}};
    int k = 3;
    int n = 5;
    int m = 4;

    int result = rootCount(edges, n, guesses, m, k);
    cout << "Number of possible roots: " << result << endl;

    return 0;
}
