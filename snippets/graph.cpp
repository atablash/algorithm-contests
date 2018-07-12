


struct G {
	struct V {
		struct Out {
			int v = -1; // dest vertex
			int i = -1; // rev-link

			// additional link (edge) data
		};
		vector<Out> outs;

		// additional vertex data
	};

	vector<V> vs;

	void add_edge(int a, int b, int weight) {
		vs[a].outs.push_back( {b, -1, weight} );
		vs[b].outs.push_back( {a, -1, weight} );

		vs[a].outs.back().i = vs[b].outs.size()-1;
		vs[b].outs.back().i = vs[a].outs.size()-1;
	}

	void remove_edge(int v, int i) {
		auto out = vs[v].outs[i];

		replace_edge_with_last(out.v, out.i);
		replace_edge_with_last(v, i);

		vs[v].outs.pop_back();
		vs[out.v].outs.pop_back();
	}

private:
	void replace_edge_with_last(int v, int i) {
		if(i == (int)vs[v].outs.size()-1) return;
		auto& out = vs[v].outs[i] = vs[v].outs.back();
		vs[ out.v ].outs[ out.i ].i = i;
	}
};


