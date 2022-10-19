#ifndef MODEL
#define MODEL

#include <Mesh.h>

#include <stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model{

    public:
        // model data 
        std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        std::vector<Mesh> meshes;
        bool gammaCorrection;

        Model(std::string const &path, bool gamma = false);
        Model(std::string const &obj_path, std::vector<std::string> texture_paths, bool gamma = false);
        void draw(Shader &shader);	

    private:
        // model data
        std::string directory;

        void loadModel(std::string const& path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string const& typeName);

};

#endif