#pragma once




class UF {
	vector<Node> v;

	struct Node {
		int parent;

		//
		// per-set data - EDIT HERE
		//int size = 1;
		void on_merge_from(const Node& o) { // called by UF implementation
			//size += o.size;
		}
		//


		//
		// path aggreg - EDIT HERE
		//
		// If at any point you're calling merge(some_non_root, b),
		// path aggregation isn't real path aggregation,
		// but instead can aggregate paths that go back and forth,
		// visiting some vertices several times.
		// This works for e.g. XOR-ing edge weights,
		// or any other involution (OP == OP^-1)
		//
		// It's meant for edge aggregation. For vertices,
		// the code would require some changes.
		//
		// When calling merge(a,b), that is creating a new edge,
		// be sure to aggregate this edge *after* merging, like this:
		//   uf.merge(a,b);
		//   uf[a].path_edges_parity = 1;
		//
		//bool path_edges_parity = 0;
		void on_path_aggreg(const Node& o) { // called by UF implementation
			//path_edges_parity ^= o.path_edges_parity;
		}
		//

	};

public:
	UF(int sz) : v(sz) {
		FOR(i,sz) v[i].parent = i;
	}

	int find(int x) {
		if(v[x].parent == x) return x;

		int parent = v[x].parent;
		int root = find( parent );
		v[x].path_aggreg( v[parent] );
		v[x].parent = root;

		return root;
	}


	void merge(int a, int b) {
		int fa = find(a);
		int fb = find(b);
		if(fa == fb) return;

		v[fa].parent = a;
		v[fa].on_path_aggreg( v[a] );

		v[a].parent = b;

		v[fb].on_merge_from( v[fa] );
	}

	// helpers
	bool same(int a, int b) { return find(a) == find(b); }
	Node& find_node(int x) { return v[ find(x) ]; }
	auto& operator[](int a) { return v[ a ]; }
};



