import * as THREE from 'three';

const groundGeometry = new THREE.PlaneGeometry(100.0,100.0,1,1);
const groundMaterial = new THREE.MeshBasicMaterial({color:0x005500});

const roadGeometry = new THREE.PlaneGeometry(10.0,100.0,1,1);
const roadMaterial = new THREE.MeshBasicMaterial({color:0x666666});

export function createStraightRoad()
    {
        const groundMesh = new THREE.Mesh(groundGeometry,groundMaterial);
        groundMesh.position.z -= 0.1;

        const verticalRoadMesh = new THREE.Mesh(roadGeometry,roadMaterial);

        const straightRoadGroup = new THREE.Group();
        straightRoadGroup.add(verticalRoadMesh);
        straightRoadGroup.add(groundMesh);

        straightRoadGroup.rotation.x -= Math.PI/2;

        return straightRoadGroup;
    }


