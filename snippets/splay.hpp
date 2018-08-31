#pragma once






// 1-based indices
class Splay {

	struct Node {
		//
		// EDIT HERE:
		// well, nothing yet
		//

		int c[2] = {0,0}; // children
		int p = 0; // parent
	};

	vector<Node> v;


public:
	Splay() : v(1) {}
	Splay(int size) : v(size+1) {}

	int is_ith(int x) const {
		return v[ v[x].p ].c[1] == x;
	}

	void rotate(int x) {
		int ith = is_ith(x);
		int p = v[x].p; // parent
		int g = v[p].p; // grand-parent
		int i = v[x].c[ !ith ]; // inner child

		v[x].p = g;
		if(g) v[g].c[ is_ith(p) ] = x;

		v[x].c[ !ith ] = p;
		v[p].p = x;

		v[p].c[ ith ] = i;
		v[i].p = p;
	}

	void splay_to_root(int x) {
		//cerr << "splay_to_root " << x << endl;
		for(;;) {
			int p = v[x].p; // parent
			if(!p) break;

			int g = v[p].p;
			if(!g) {
				rotate(x);
				break;
			}

			if(is_ith(x) == is_ith(p)) {
				rotate(p);
				rotate(x);
			}
			else {
				rotate(x);
				rotate(x);
			}
		}
	}

	// assumes:
	//   each element in x <= each element in y
	int merge(int x, int y) {
		splay_to_root(x);

		while( v[y].c[0] ) y = v[y].c[0];
		splay_to_root(y);

		v[x].p = y;
		v[y].c[0] = x;

		return y;
	}


	// split tree into 2 trees of elements (_ < x) and (_ >= x)
	pair<int,int> split(int x) {
		splay_to_root(x);
		int c0 = v[x].c[0];
		if(c0) {
			v[x].c[0] = 0;
			v[c0].p = 0;
		}
		return {c0, x};
	}


	// find first element that satisfies `pred(idx)`,
	// assuming `pred` is monotonic: first `false`, then `true`
	template<class PRED>
	int lower_bound(int x, const PRED& pred) {
		splay_to_root(x);
		//cerr << "lower_bound " << x << endl;
		int cand = 0;
		for(;;) {
			auto r = pred(x);
			if(r) {
				//cerr << "  cand " << x << endl;
				cand = x;
			}

			int next = v[x].c[ !r ];
			//cerr << "  next " << next << endl;
			if(!next) {
				splay_to_root(x);
				break;
			}

			x = next;
		}
		return cand;
	}


	// repeat for all x, while fun(x) == true
	template<class FUN>
	void each_descendant(int x, const FUN& fun) {
		if(!x) return;

		each_descendant(v[x].c[0], fun);
		if( !fun(x) ) return;
		each_descendant(v[x].c[1], fun);
	}

	template<class FUN>
	void each(int x, const FUN& fun) {
		splay_to_root(x);
		each_descendant(x, fun);
	}


	// this can't splay, because can be called from within lambdas
	int next(int x, bool forward = true) const {
		if(v[x].c[forward]) {
			x = v[x].c[forward];
			while( v[x].c[!forward] )  x = v[x].c[!forward];
			return x;
		}
		else for(;;) {
			int p = v[x].p;
			if(!p) return 0;

			if(is_ith(x) != forward) return p;
			x = p;
		}
	}

	int prev(int x) const {
		return next(x, false);
	}

	int first(int x) {
		splay_to_root(x);
		while(v[x].c[0]) x = v[x].c[0];
		splay_to_root(x);
		return x;
	}

	int last(int x) {
		splay_to_root(x);
		while(v[x].c[1]) x = v[x].c[1];
		splay_to_root(x);
		return x;
	}

	// helpers
	Node& operator[](int i) { return v[i]; }
};




