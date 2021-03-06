//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "BsCMeshCollider.h"
#include "BsSceneObject.h"
#include "BsCRigidbody.h"
#include "BsPhysicsMesh.h"
#include "BsCMeshColliderRTTI.h"

namespace BansheeEngine
{
	CMeshCollider::CMeshCollider(const HSceneObject& parent)
		: CCollider(parent)
	{
		setName("MeshCollider");
	}

	void CMeshCollider::setMesh(const HPhysicsMesh& mesh)
	{
		if (mMesh == mesh)
			return;

		if(getIsTrigger() && mesh->getType() == PhysicsMeshType::Triangle)
		{
			LOGWRN("Triangle meshes are not supported on Trigger colliders.");
			return;
		}

		mMesh = mesh;

		if (mInternal != nullptr)
		{
			_getInternal()->setMesh(mesh);

			if (mParent != nullptr)
			{
				// If triangle mesh its possible the parent can no longer use this collider (they're not supported for 
				// non-kinematic rigidbodies)
				if (mMesh.isLoaded() && mMesh->getType() == PhysicsMeshType::Triangle)
					updateParentRigidbody();
				else
					mParent->_updateMassDistribution();
			}
		}
	}

	SPtr<Collider> CMeshCollider::createInternal()
	{
		SPtr<MeshCollider> collider = MeshCollider::create(SO()->getWorldPosition(), SO()->getWorldRotation());
		collider->setMesh(mMesh);
		collider->_setOwner(PhysicsOwnerType::Component, this);

		return collider;
	}

	bool CMeshCollider::isValidParent(const HRigidbody& parent) const
	{
		// Triangle mesh colliders cannot be used for non-kinematic rigidbodies
		return !mMesh.isLoaded() || mMesh->getType() == PhysicsMeshType::Convex || parent->getIsKinematic();
	}

	RTTITypeBase* CMeshCollider::getRTTIStatic()
	{
		return CMeshColliderRTTI::instance();
	}

	RTTITypeBase* CMeshCollider::getRTTI() const
	{
		return CMeshCollider::getRTTIStatic();
	}
}