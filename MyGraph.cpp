#include <iostream>
#include <cmath>
#include "MyGraph.h"

bool Link::operator<(const Link &other) const {
    return w < other.w;
}

bool Link::operator>(const Link &other) const {
    return w > other.w;
}

bool Link::operator==(const Link &other) const {
    bool low = (lo == other.lo);
    bool high = (hi == other.hi);
    //bool weight = (w == other.w);
    return (low && high);
}

ostream &operator<<(ostream &os, const Link &l) {
    os << l.lo << " " << l.hi << " " << l.w;
    return os;
}

bool Link::operator<(const float &other) const {
    return w < other;
}

bool Link::operator>(const float &other) const {
    return w > other;
}

bool Link::linkComparator(const Link *l, const float w) {
    return l->w < w;
}

//todo: probably unnecessary, move to header file
MyGraph::MyGraph(int n) : numVerts(n) {
//    for (int i = 1; i <= n; i++) {
//        graph[i].insert(Link());
//    }
}

MyGraph::MyGraph(const MyGraph &g) : numVerts(g.numVerts), numEdges(g.numEdges), edges(g.edges), graph(g.graph) {}

MyGraph::MyGraph(const vector<Link>& vl) {
    for (auto link : vl) {
        addEdge(link);
    }
}

MyGraph::~MyGraph() {

}

//todo: remove low high check for optimization or move to link constructor?
bool MyGraph::addEdge(int a, int b, float w) {
    int low, high;

    if (a < b)
        low = a, high = b;
    else
        low = b, high = a;

    //create edge
    bool edgeExists = std::binary_search(edges.begin(), edges.end(), Link(low, high, w));

    //adjacency list stuff, cut if maps arent allowed
    if (!edgeExists) {
        cout << "Attempted to add duplicate edge. Adding aborted." << endl;
        return false;
    }

    graph[low].emplace(high, Link(low, high, w));
    graph[high].emplace(low, Link(low, high, w));
    numEdges++;

    // add edge to vector
    auto it = upper_bound(edges.begin(), edges.end(), Link(low, high, w));
    edges.emplace(it, Link(low, high, w));

    return true;
}

bool MyGraph::addEdge(Link &pipe) {
    if (pipe.lo > pipe.hi) {
        swap (pipe.lo, pipe.hi);
    }

    int low = pipe.lo, high = pipe.hi;
    float w = pipe.w;

    //create edge
    bool edgeExists = std::binary_search(edges.begin(), edges.end(), Link(low, high, w));

    //adjacency list stuff, cut if maps arent allowed
    if (!edgeExists) {
        cout << "Attempted to add duplicate edge. Adding aborted." << endl;
        return false;
    }

    graph[low].emplace(high, Link(low, high, w));
    graph[high].emplace(low, Link(low, high, w));
    numEdges++;

    // add edge to vector
    auto it = upper_bound(edges.begin(), edges.end(), Link(low, high, w));
    edges.emplace(it, Link(low, high, w));

    return true;
}

void MyGraph::output(ostream &os) {
    os << numVerts << endl;
    for (Link edge: edges) {
        os << edge << endl;
    }
}

pair<bool, float> MyGraph::weight(int a, int b) {
    pair<bool, float> res;
    res.first = false;
    res.second = NAN;

    int low, high;

    if (a < b)
        low = a, high = b;
    else
        low = b, high = a;

    //linear search if <algorithm> isnt allowed
    //for (int i = 0; i < numEdges; i++) {
    //    if (edges[i].lo == low && edges[i].hi == high) {
    //        res.first = true;
    //        res.second = edges[i].w;
    //        return res;
    //    }
    //}

    //todo: comment here and rename map iter names to be less confusing
    auto nodeIter = graph.find(low);

    if (nodeIter == graph.end()) return res;

    auto *edgeMap = &(nodeIter->second);
    auto linkIter = graph[nodeIter->first].find(low);

    if (linkIter == edgeMap->end()) return res;

    res.first = true;
    res.second = linkIter->second.w;

    return res;
}

void MyGraph::printGraph() {
    for (const auto& node : graph) {
        cout << node.first << ": " << endl;
        for (auto link : node.second) {
            cout << "(" << link.second << ") ";
        }
    }
}

MyHelper::MyHelper() {

}

vector<Link> Task1(int n, vector<Link> &pipes, MyHelper &helper) {
    vector<Link> res = pipes;
    MyGraph graph = MyGraph(pipes);
    graph.printGraph();
    //for (Link& pipe : pipes) {
    //
    //}

    return res;
}

pair<bool, Link> Task2(int n, vector<Link> &pipes, Link newPipe, MyHelper helper) {
    Link l1;
    pair<bool, Link> sol;
    sol.first = true;
    sol.second = newPipe;
    return sol;
}
