//
// Created by rthier on 2016.06.21..
//

#ifndef NFTSIMPLEPROJ_MTLLIB_H
#define NFTSIMPLEPROJ_MTLLIB_H

#include "TextureDataHoldingMaterial.h"
#include "AssetLibrary.h"
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

namespace ObjMaster {
    class MtlLib {
    public:
        static const std::string KEYWORD;
        /**
         * The names of the material library files that this library builds upon.
         */
        // TODO: In the *.obj file, they can be there as a CSV - currently unused, only one is added
        std::vector <std::string> libraryFiles;

        /** Decides if the given fields can be parsed as an MtlLib element */
        static bool isParsable(const char *fields);

        /**
         * Create a material library from the given obj fields. The constructor also load the mtl
         * file to construct the whole corresponding library thus the asses library is needed.
         * The given asset library is only used for construction and is not stored so the ownership
         * of the referenced object stays at the host code!
         */
        MtlLib(const char *fields, const char *assetPath, const AssetLibrary &assetLibrary);
        /**
         * Create a material library from the given obj fields. The constructor also load the mtl
         * file to construct the whole corresponding library thus the asses library is needed.
         * The given asset library is only used for construction and is not stored so the ownership
         * of the referenced object stays at the host code!
         */
        MtlLib(char *fields, const char *assetPath, const AssetLibrary &assetLibrary);
        /** The default constructor just create a completely empty library */
        MtlLib() {}

	/** The absolute textual reference to the *.mtl as it is references from the *.obj file - this should go into the *.obj output! */
	inline std::string asText(const char *path, const char *fileName) {
		// Rem.: The compiler should be smart-enough to optimize this when inlined...
		std::string fullPath = std::string(path) + fileName;
		return asText(fullPath.c_str());
	}

	/** The relative textual reference to the *.mtl as it is references from the *.obj file - this should go into the *.obj output! */
	inline std::string asText(const char *fileName) {
		return KEYWORD + " " + fileName;
	}

	/** Save this MtlLib as a *.mtl - using the (relative) fileName and the provided asset-out library */
	inline void saveAs(const AssetOutputLibrary &assetOutputLibrary, const char* fileName){
		saveAs(assetOutputLibrary, "", fileName);
	}
	/** Save this MtlLib as a *.mtl - using the path, fileName and the provided asset-out library */
	void saveAs(const AssetOutputLibrary &assetOutputLibrary, const char* path, const char* fileName, bool alwaysGrowLibraryFilesList = false);

        /** Returns a copy of the given material  */
        TextureDataHoldingMaterial getNonLoadedMaterialFor(std::string materialName);

        /** Returns the number of materials in this library */
        int getMaterialCount();

        // Rem.: Currently the mtllib is completely empty if there are no source files
        // - this might change in the future code versions accordingly!
        /** Returns if this mtllib is a completely empty library or not! */
        bool isEmpty() { return libraryFiles.size() == 0; }
    private:

        /** Material name -> material hash for basic material access without loaded texture data */
        std::unordered_map <std::string, TextureDataHoldingMaterial> materials;

        void constructionHelper(char *fields, const char *assetPath, const AssetLibrary &assetLibrary);

        /** !!! Helper function - BEWARE: This might change the argument as a side-effect !!! */
        std::string updateCurrentMaterialName(char *line);
    };
}

#endif //NFTSIMPLEPROJ_MTLLIB_H
