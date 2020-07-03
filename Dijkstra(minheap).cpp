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
	class BinMinHeap
	{
	private:
		GraphNode* *arr;
		int heapsize;
	public:
		BinMinHeap(int s)
		{
			arr = new GraphNode*[s];
			heapsize = 0;
		}
		void insert(GraphNode &v)
		{
			arr[heapsize++] = &v;
			pushupward(heapsize - 1);
		}
		void remove(int i)
		{
			arr[i] = arr[--heapsize];
			pushdownward(i);
		}
		void extractmin()
		{
			remove(0);
		}
		GraphNode* getmin()
		{
			return arr[0];
		}
		int parent(int i)
		{
			return (i - 1) / 2;
		}
		int left(int i)
		{
			return 2 * i + 1;
		}
		int right(int i)
		{
			return 2 * i + 2;
		}
		void pushupward(int i)
		{
			if (i > 0)
			{
				int p = parent(i);
				if (arr[i]->dist < arr[p]->dist)
				{
					swap(arr[i], arr[p]);
					pushupward(p);
				}
			}
		}
		void pushdownward(int i)
		{
			if (i < heapsize)
			{
				int l = left(i);
				int r = right(i);
				if (l < heapsize)
				{
					int t = arr[l]->dist < arr[r]->dist ? l : r;
					swap(arr[t], arr[i]);
					pushdownward(t);
				}
			}
		}
		bool isEmpty()
		{
			return heapsize == 0;
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
		BinMinHeap mh(gr.size());
		gr[0].dist = 0;
		for (vector<GraphNode>::iterator it = gr.begin(); it != gr.end(); it++)
			mh.insert(*it);
		while (!mh.isEmpty())
		{
			GraphNode* tmp = mh.getmin();
			mh.extractmin();
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