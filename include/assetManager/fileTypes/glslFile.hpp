#pragma once
#include "file.hpp"

namespace LTE
{
    struct ShaderProgramSource
    {
        std::string VertexSource;
        std::string FragmentSource;
    };

    class glslFile: public file
    {
        private:
            ShaderProgramSource source;

            void ParseShaders();

        public:
            glslFile(const std::string& filePath);

            virtual ~glslFile();
            virtual asset *genrateAsset();

            virtual void loadFileData();

    };

    class glslFileFactory: public fileFactory
    {
        public:
            glslFileFactory(){}
    
            virtual file* createFile(const std::string& filePath)
            {
                return new glslFile(filePath);
            }
    };

}