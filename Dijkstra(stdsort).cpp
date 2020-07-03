#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#define Infinity 99999
using namespace std;
class Graph
{
private:
	class GraphNode
	{
	public:
		string data;
		vector<GraphNode*> next;
		vector<int> weight;
		int dist;
		string pred;
		GraphNode(string d)
		{
			data = d;
			dist = Infinity;
			pred = "";
		}
	};
	vector<GraphNode> gr;
	GraphNode* searchPre(string s)
	{
		for (int i = 0; i < gr.size(); i++)
			if (gr[i].data == s)
				return &gr[i];
	}
	void relax(GraphNode &u, GraphNode &v, int w)
	{
		if (v.dist > u.dist + w)
		{
			v.dist = u.dist + w;
			v.pred = u.data;
		}
	}
public:
	void insert(string d)
	{
		GraphNode tmp(d);
		gr.push_back(tmp);
	}
	void link(string a, string b, int w)
	{
		for (vector<GraphNode>::iterator it = gr.begin(); it != gr.end(); it++)
			if (it->data == a)
			{
				it->next.push_back(searchPre(b));
				it->weight.push_back(w);
				break;
			}
	}
	void Dijkstra()
	{
		for (vector<GraphNode>::iterator it = gr.begin(); it != gr.end(); it++)
		{
			it->dist = Infinity;
			it->pred = "";
		}
		gr[0].dist = 0;
		vector<GraphNode*> mh;
		for (int k = 0; k != gr.size(); k++)
			mh.push_back(&gr[k]);
		while (!mh.empty())
		{
			sort(mh.begin(), mh.end(), [](GraphNode *g1, GraphNode *g2) {return g1->dist > g2->dist;});
			GraphNode* tmp = mh.back();
			mh.pop_back();
			vector<GraphNode *> &n = tmp->next;
			vector<int> &w = tmp->weight;
			for (int k = 0; k != n.size(); k++)
				relax(*tmp, *n[k], w[k]);
		}
	}
	void show()
	{
		for (vector<GraphNode>::iterator it = gr.begin(); it != gr.end(); it++)
			cout << it->data << " " << it->dist << " " << (it->pred != "" ? it->pred : "None") << endl;
	}
};
int main()
{
	Graph g;
	g.insert("s");
	g.insert("t");
	g.insert("y");
	g.insert("x");
	g.insert("z");
	g.link("s", "t", 10);
	g.link("s", "y", 5);
	g.link("t", "y", 2);
	g.link("y", "t", 3);
	g.link("t", "x", 1);
	g.link("y", "x", 9);
	g.link("y", "z", 2);
	g.link("x", "z", 4);
	g.link("z", "x", 6);
	g.link("z", "s", 7);
	g.Dijkstra();
	g.show();
	system("pause");
}