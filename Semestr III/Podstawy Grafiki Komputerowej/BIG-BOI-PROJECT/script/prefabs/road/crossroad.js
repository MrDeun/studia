import * as THREE from 'three';

const groundGeometry = new THREE.PlaneGeometry(50.0,50.0,1,1);
const groundMaterial = new THREE.MeshBasicMaterial({color:0x005500});

const roadGeometry = new THREE.PlaneGeometry(10.0,50.0,1,1);
const roadMaterial = new THREE.MeshBasicMaterial({color:0x666666});

export function createCrossroad()
    {
        const groundMesh = new THREE.Mesh(groundGeometry,groundMaterial);
        groundMesh.position.z -= 0.1;

        const verticalRoadMesh = new THREE.Mesh(roadGeometry,roadMaterial);
        const horizontalRoadMesh = new THREE.Mesh(roadGeometry,roadMaterial);
        horizontalRoadMesh.rotation.x += Math.PI/2;

        const crossroadGroup = new THREE.Group();
        crossroadGroup.add(verticalRoadMesh);
        crossroadGroup.add(horizontalRoadMesh);
        crossroadGroup.add(groundMesh);

        return crossroadGroup;
    }


