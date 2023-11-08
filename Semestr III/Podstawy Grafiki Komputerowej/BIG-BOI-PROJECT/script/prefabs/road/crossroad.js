import * as THREE from 'three';

//GEOMETRIES
const grassPlaneGeometry = new THREE.PlaneGeometry(50.0,50.0,1,1);
const roadGeometry = new THREE.PlaneGeometry(10.0,50.0,1,1);
//MATERIALS
const grassPlaneMaterial = new THREE.MeshBasicMaterial({color:0x006600});
const roadMaterial = new THREE.MeshBasicMaterial({color:0xaaaaaa});
//MESHES
const verticalRoad = new THREE.Mesh(roadGeometry,roadMaterial);
const horizontalRoad = new THREE.Mesh(roadGeometry,roadMaterial);
const grassMesh = new THREE.Mesh(grassPlaneGeometry,grassPlaneMaterial);
//ROTATION ON MESHES
horizontalRoad.rotation.z += Math.PI/2;
grassMesh.position.z -= 0.1;
//GROUPING
const crossroadTemplate = new THREE.Group();
crossroadTemplate.add(verticalRoad);
crossroadTemplate.add(horizontalRoad);
crossroadTemplate.add(grassMesh);
//ROTATION ON GROUP
crossroadTemplate.rotation.y -= Math.PI/2;
module.exports = 
{

    createCrossroad()
    {
        const crossroadTile = new THREE.Group();
        crossroadTile.copy(crossroadTemplate);
        return crossroadTile;
    }

}


