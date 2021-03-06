//
// Created by rthier on 2016.06.17..
//

#ifndef NFTSIMPLEPROJ_MATERIALIZEDOBJMESHOBJECT_H
#define NFTSIMPLEPROJ_MATERIALIZEDOBJMESHOBJECT_H

#include "TextureDataHoldingMaterial.h"
#include "ObjMeshObject.h"
#include <string>

namespace ObjMaster {
    /**
     * A special ObjMeshObject that has a material associated with it. The mesh can be rendered with
     * that material. The class can be used to group together parts of the obj model that share the
     * same mesh. The template parameter is used to set the library to use for manipulating various
     * texture memories. For the template parameter see TextureDataHoldingMaterial doc-comments!
     */
    class MaterializedObjMeshObject : public ObjMeshObject {
    public:
	/** The name of the materialized obj mesh object. This usually contains the objFaceMatGroup key when built from an Obj object. */
	std::string name;
        /** The corresponding material and possibly the texture data in it */
        TextureDataHoldingMaterial material;

	// Rem.: As you can try this out yourself too, the defaults here mean that user-defined copies and moves are called in the parent class!!!
	//       That is necessary as the ObjMeshObject is using user-defined stuff
	// Copies are defeaulted
	MaterializedObjMeshObject(const MaterializedObjMeshObject &other) = default;
	MaterializedObjMeshObject& operator=(const MaterializedObjMeshObject &other) = default;
	// Moves are defaulted
	MaterializedObjMeshObject(MaterializedObjMeshObject &&other) = default;
	MaterializedObjMeshObject& operator=(MaterializedObjMeshObject &&other) = default;

        /** Create an obj mesh-object that is having an associated material */
        MaterializedObjMeshObject(const Obj& obj, const FaceElement *meshFaces, int meshFaceCount, TextureDataHoldingMaterial textureDataHoldingMaterial, std::string name);
    };
}


#endif //NFTSIMPLEPROJ_MATERIALIZEDOBJMESHOBJECT_H
