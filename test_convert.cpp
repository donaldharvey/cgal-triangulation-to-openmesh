#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/IO/MeshIO.hh>

#include "convert.h"

typedef OpenMesh::PolyMesh_ArrayKernelT<>  Mesh;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation::Point          Point;

int main() {
    Triangulation t;
    Mesh m;
    t.insert(Point(0,1));
    t.insert(Point(1,2));
    t.insert(Point(23,5));
    t.insert(Point(13,2));
    t.insert(Point(-12,5));
    t.insert(Point(8,-10));
    triangulation_to_mesh(t, m);
    Mesh::VertexIter v_it, v_end(m.vertices_end());
     for (v_it=m.vertices_begin(); v_it!=v_end; ++v_it) {
        std::cout << m.point(*v_it);
        std::cout << "\n";
     }
    return 0;
}