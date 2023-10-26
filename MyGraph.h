#include <iostream>
#include <vector>
//#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>

using namespace std;

//todo: rename lo to v1 and hi to v2?
struct Link {
public:
    int lo = -1, hi = -1; //low, high
    float w = -1;

    Link() = default;
    Link(int low, int high) : lo(low), hi(high) {};
    Link(int low, int high, float weight) : lo(low), hi(high), w(weight) {}
    Link(const Link&) = default;

    bool operator<(const Link& other) const;
    bool operator>(const Link& other) const;
    bool operator==(const Link& other) const;

    bool operator<(const float& other) const;
    bool operator>(const float& other) const;

    friend ostream& operator<<(ostream&, const Link&);
    //friend float& operator<(ostream&, const Link&);

    static bool linkComparator(const Link* l, const float w);
};

class MyGraph {

public:
    MyGraph() = default;
    explicit MyGraph(int n); // n is number of vertices
    MyGraph(const MyGraph&);
    explicit MyGraph(const vector<Link>&);

    ~MyGraph();

    bool addEdge(int a, int b, float w);
    bool addEdge(Link &pipe);
    void output(ostream& os);
    pair<bool, float> weight(int a, int b);

    int numVerts = 0;
    int numEdges = 0;
    vector<Link> edges;
    unordered_map<int, map<int, Link>> graph;

    //Testing
    void printGraph();
};

class MyHelper {

public:
    MyHelper();
    int x;
};

vector<Link> Task1(int n, vector<Link>& pipes, MyHelper& helper);
pair<bool, Link> Task2(int n, vector<Link>& pipes, Link newPipe, MyHelper helper);
