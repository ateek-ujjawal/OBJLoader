#include "OBJModel.hpp"
#include "PPM.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

OBJModel::OBJModel(std::string fileName) {
    // Store entire obj file in a result string variable
    std::string result = "";

    std::string line = "";
    std::ifstream myFile(fileName.c_str());

    int found = fileName.find_last_of("/");
    std::string directory = fileName.substr(0, found);
    std::string mtlFilename;

    if(myFile.is_open()){
        while(std::getline(myFile, line)){
            result += line + '\n';
        }
        myFile.close();
    }

    // Read tokens from file to construct obj model
    // using vertices, normals and triangle faces
    std::stringstream fileData(result);
    std::string token;
    bool hasTextureData = false;
    while (fileData >> token) {
        if (token == "mtllib") {
            fileData >> mtlFilename;
        } else if (token[0] == 'v' && token.length() == 1) {
            Vertex vert;
            for (int i = 0; i < 3; i++)
                fileData >> vert.v[i];
            vertices.push_back(vert);
        } else if (token[0] == 'v' && token[1] == 'n' && token.length() == 2) {
            VertexNormal normal;
            for (int i = 0; i < 3; i++)
                fileData >> normal.vn[i];
            normals.push_back(normal);
        } else if (token[0] == 'v' && token[1] == 't' && token.length() == 2) {
            hasTextureData = true;
            VertexTexture texture;
            for (int i = 0; i < 2; i++)
                fileData >> texture.st[i];
            textures.push_back(texture);
        } else if (token[0] == 'f' && token.length() == 1) {
            Triangle t;
            char remove;
            for (int i = 0; i < 3; i++) {
                if (hasTextureData) {
                    fileData >> t.vertIndices[i] >> remove >> t.textureIndices[i] >> remove >> t.normalIndices[i];
                } else {
                    fileData >> t.vertIndices[i] >> remove >> remove >> t.normalIndices[i];
                }
                t.vertIndices[i]--;
                t.normalIndices[i]--;
                t.textureIndices[i]--;
            }
            faces.push_back(t);
        }
    }

    // Get material details
    if (mtlFilename.length() != 0) {
        result = "";
        line = "";
        std::string mtlFile = directory + "/" + mtlFilename;
        std::ifstream mtlFileStream(mtlFile.c_str());

        if(mtlFileStream.is_open()){
            while(std::getline(mtlFileStream, line)){
                result += line + '\n';
            }
            mtlFileStream.close();
        }

        std::stringstream mtlFileData(result);
        std::string diffuseFile;
        while(mtlFileData >> token) {
            if (token == "map_Kd") {
                mtlFileData >> diffuseFile;
            }
        }

        std::string diffuseFilePath = directory + "/" + diffuseFile;
        diffusePPM = PPM(diffuseFilePath);
        diffusePPM.flipPPM();
        diffusePPM.savePPM("./flippedPPM.ppm");
    }
}

int OBJModel::getNumFaces() {
    return faces.size();
}

Vertex OBJModel::getVert(int index) {
    return vertices[index];
}

VertexNormal OBJModel::getNormal(int index) {
    return normals[index];
}

VertexTexture OBJModel::getTexture(int index) {
    return textures[index];
}

PPM OBJModel::getDiffusePPM() {
    return diffusePPM;
}

Triangle OBJModel::getFace(int index) {
    return faces[index];
}