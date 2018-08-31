#pragma once

#include "2d.hpp"




template<class T>
class Hull_Tree {
	struct Tree_Node {
		vector<int> hull;
		int idx[2]; // vertex index in children
	};
	vector<Tree_Node> nodes;
	int N;

	struct Point_Node {
		int original_idx;
		Point<T,2> p;
	};
	vector<Point_Node> pts;

	bool lower = false;


public:
	template<class PTS>
	Hull_Tree(const PTS& new_pts, bool want_lower = false) : lower(want_lower) {
		pts.resize( new_pts.size() );
		FOR(i, new_pts.size()) pts[i] = {i, new_pts[i]};
		sort(ALL(pts), [](auto a, auto b){ return a.p[0] < b.p[0]; });

		rebuild_tree();
	}

	auto get_hull() const {
		vector<int> hull( nodes[1].hull.size() );
		FOR(i, hull.size()) hull[i] = pts[ nodes[1].hull[i] ].original_idx;
		return hull;
	}

	void remove_hull() {
		remove_hull_verts(1, 0, nodes[1].hull.size());
	}


private:
	void rebuild_tree() {
		nodes.clear();
		N = 1;
		while(N < (int)pts.size()) N *= 2;
		nodes.resize( N*2 );

		rebuild_tree_rec(1);
	}

	void rebuild_tree_rec(int v) {
		//DBG << "rebuild_tree_rec " << v << endl;

		if(v >= N) {
			if(v-N < (int)pts.size()) nodes[v].hull = { v-N };
			return;
		}

		rebuild_tree_rec(v*2);
		rebuild_tree_rec(v*2+1);

		rebuild_node(v);
	}

	void rebuild_node(int v) {
		auto& hull_0 = nodes[v*2].hull;
		auto& hull_1 = nodes[v*2+1].hull;

		if(hull_0.size() == 0) {
			nodes[v].hull = hull_1;
			return;
		}

		if(hull_1.size() == 0) {
			nodes[v].hull = hull_0;
			return;
		}

		// todo: first lower_bound
		int i0 = hull_0.size()-1;
		int i1 = 0;
		for(;;) {
			bool change = false;

			while(i1 < (int)hull_1.size()-1  &&  (lower?-1:1) * orient(pts[ hull_0[i0] ].p,  pts[ hull_1[i1] ].p,  pts[ hull_1[i1+1] ].p) >= 0) {
				change = true;
				++i1;
			}

			while(i0 > 0  &&  (lower?-1:1) * orient( pts[ hull_0[i0-1] ].p, pts[ hull_0[i0] ].p, pts[ hull_1[i1] ].p ) >= 0) {
				change = true;
				--i0;
			}

			if(!change) break;
		}

		nodes[v].idx[0] = i0;
		nodes[v].idx[1] = i1;

		nodes[v].hull.clear();
		FO(i, 0, i0+1) nodes[v].hull.push_back( hull_0[i] );
		FO(i, i1, hull_1.size()) nodes[v].hull.push_back( hull_1[i] );

		DBG << "rebuild_node " << v << ": ";
		FOR(i, nodes[v].hull.size()) DBG << nodes[v].hull[i] << ", ";
		DBG << endl;
	}

	void remove_hull_verts(int v, int fr, int to) {
		DBG << "  remove_hull_verts " << v << " [" << fr << ", " << to << ")" << endl;
		if(v >= N) {
			assert(nodes[v].hull.size() <= 1);
			if(nodes[v].hull.size() == 1) DBG << "removing " << nodes[v].hull[0] << " from hull" << endl;
			nodes[v].hull.clear();
			return;
		}

		if(!nodes[v*2].hull.empty() && !nodes[v*2+1].hull.empty()) {
			if(fr <= nodes[v].idx[0])   remove_hull_verts(v*2,   fr, MIN(to, nodes[v].idx[0]+1));
			int right_shift = nodes[v].idx[1] - nodes[v].idx[0]-1;
			if(to >  nodes[v].idx[0]+1) remove_hull_verts(v*2+1, MAX(fr + right_shift, nodes[v].idx[1]), to + right_shift);
		}
		else if(!nodes[v*2].hull.empty()) {
			remove_hull_verts(v*2, fr, to);
		}
		else if(!nodes[v*2+1].hull.empty()) {
			remove_hull_verts(v*2+1, fr, to);
		}

		rebuild_node(v);
	}
};








// builds convex hull of `pts` as layer 0,
// then builds convex hull for remaining points as layer 1, etc.
template<class PTS>
vector<vector<int>> get_convex_hulls(const PTS& pts, bool lower) {
	Hull_Tree<int> ht( pts, lower );

	vector<vector<int>> result;

	DBG << "get_convex_hulls: begin loop" << endl;

	for(;;) {
		auto hull = ht.get_hull();
		if(hull.empty()) break;

		DBG << "got hull: ";
		FOR(i,hull.size()) DBG << hull[i] << ", ";
		DBG << endl;

		result.push_back( hull );
		ht.remove_hull();
	}

	return result;
}






