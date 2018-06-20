#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <tiny_obj_loader.h>

#include "mesh.hpp"

struct vertex {
    bool operator==(vertex const& other) { return std::vector<float>{other.vx, other.vy, other.vz, other.vnx, other.vny, other.vnz, other.vtx, other.vty} == std::vector<float>{vx, vy, vz, vnx, vny, vnz, vtx, vty}; }
    float vx, vy, vz, vnx, vny, vnz, vtx, vty;
};

ogld::obj_mesh::obj_mesh(std::string const& path) {
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string error_string;
    if (!tinyobj::LoadObj(shapes, materials, error_string, path.c_str())) { 
        throw std::runtime_error(std::string("failed to load '") + path + std::string("'.\n\terror_string: ") + error_string); 
    }

    std::vector<vertex> repeating_vertex_data;

    for (auto const& shape : shapes) {
        for (auto const& index : shape.mesh.indices) {
            repeating_vertex_data.push_back({shape.mesh.positions.at(index * 3),
                                             shape.mesh.positions.at(index * 3 + 1),
                                             shape.mesh.positions.at(index * 3 + 2),
                                             shape.mesh.normals.at(index * 3),
                                             shape.mesh.normals.at(index * 3 + 1),
                                             shape.mesh.normals.at(index * 3 + 2),
                                             shape.mesh.texcoords.at(index * 2),
                                             shape.mesh.texcoords.at(index * 2 + 1)});
        }
    }

    std::vector<vertex> unique_vertices;
    unsigned int index_count = 0;

    for (auto const& vertex_ : repeating_vertex_data) {
        if (std::find(unique_vertices.begin(), unique_vertices.end(), vertex_) == unique_vertices.end()) {
            unique_vertices.push_back(vertex_);
            vertex_data.insert(vertex_data.end(), {vertex_.vx, vertex_.vy, vertex_.vz,
                                                   vertex_.vnx, vertex_.vny, vertex_.vnz,
                                                   vertex_.vtx, vertex_.vty});

            indices.push_back(index_count);
            ++index_count;
        }
        else {
            indices.push_back(std::distance(unique_vertices.begin(), std::find(unique_vertices.begin(), unique_vertices.end(), vertex_)));
        }
    }
}
