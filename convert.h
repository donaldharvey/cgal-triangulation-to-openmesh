#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <map>
#include <array>
#include <fstream>

template <class Tri, class Mesh>
void triangulation_to_mesh(const Tri& tri, Mesh& mesh) {
    typedef typename Mesh::VertexHandle MeshVertexHandle;
    typedef typename Tri::Vertex CGALVertex;
    typedef typename Tri::Vertex::Point CGALPoint;
    typedef typename Mesh::Point MeshPoint;
    typedef typename Tri::Geom_traits::FT CGAL_FT;
    typedef std::array<CGAL_FT, 2> PointArray;

    PointArray key;
    std::map<PointArray, MeshVertexHandle> points_map;
    std::vector<MeshVertexHandle> face_vhandles;
    CGALVertex v;
    MeshPoint p;
    MeshVertexHandle p_h;

    // add the faces. keep track of already-added vertices.
    // n.b. - using std::map to keep track of vertices added; better with a hash table.
    for(typename Tri::All_faces_iterator it = tri.all_faces_begin(); it != tri.all_faces_end(); ++it) {
        for(int i=0; i<3; ++i) {
            v = *(it->vertex(i));
            PointArray key = {v.point().x(), v.point().y()};
            if (points_map.count(key) == 0) {
                p = MeshPoint(key[0], key[1], 0);
                p_h = mesh.add_vertex(p);
                points_map[key] = p_h;
            }
            else {
                p_h = points_map[key]; 
            }
            face_vhandles.push_back(p_h);

        }
        mesh.add_face(face_vhandles);
        face_vhandles.clear();
    }
}