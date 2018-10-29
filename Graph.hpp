#ifndef AGL_GRAPH_HPP
#define AGL_GRAPH_HPP

class EdgeType; // Ordianaire, 2ec, orienté, ...
class EdgeStorer; // Storemany edges
class Vertex; 
class Edge;

// Data Structure
class BipartiteMatrix_DS;
class Matrix_DS;
template<Storage T> class Adjacency_DS<T>;
class AdjacencyList_DS;


template<class DataStructure>
Graph{
	DataStructure DS;
};


template<typename T>
concept bool EqualityComparable = requires(T a, T b) {
    { a == b } -> bool;
};

// Faire en concept
struct Graph_Range<Graph>
	requires Generable<Graph>
{
	Graph G;
  bool end;
	
  class InputIterator{
		const Graph* ptr;
		
		
	}

};



//Want
auto G = Graph<>::begin();

for (auto& G : Graph<>){
	// Do something
}

#endif
