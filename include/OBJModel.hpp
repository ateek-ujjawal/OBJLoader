/** @file OBJModel.hpp
 *  @brief Defines a class for a .obj model.
 *  
 *  A class for defining .obj wavefront models
 *
 *  @author Ateek
 *  @bug No known bugs.
 */
#ifndef OBJMODEL_HPP
#define OBJMODEL_HPP

#include "PPM.hpp"
#include "glm/glm.hpp"
#include "glad/glad.h"
#include <vector>
#include <string>

struct Vertex {
    glm::vec3 v;
};

struct VertexNormal {
    glm::vec3 vn;
};

struct VertexTexture {
    glm::vec2 st;
};

struct Triangle {
    int vertIndices[3];
    int normalIndices[3];
    int textureIndices[3];
};

class OBJModel {
    private:
        std::vector<Vertex> vertices;
        std::vector<VertexNormal> normals;
        std::vector<VertexTexture> textures;
        std::vector<Triangle> faces;
        PPM diffusePPM;
    public:
        OBJModel(std::string fileName);
        int getNumFaces();
        Vertex getVert(int index);
        VertexNormal getNormal(int index);
        VertexTexture getTexture(int index);
        PPM getDiffusePPM();
        Triangle getFace(int index);
};

#endif