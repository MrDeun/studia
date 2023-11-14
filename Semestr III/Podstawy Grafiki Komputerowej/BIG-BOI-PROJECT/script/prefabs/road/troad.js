import * as THREE from 'three';

const groundGeometry = new THREE.PlaneGeometry(100.0,100.0,1,1);
const groundMaterial = new THREE.MeshBasicMaterial({color:0x005500});

const roadGeometry = new THREE.PlaneGeometry(10.0,100.0,1,1);
const halfRoadGeometry = new THREE.PlaneGeometry(10.0,50.0,1,1);
const roadMaterial = new THREE.MeshBasicMaterial({color:0x666666});

export function createtShapeRoad()
    {
        const groundMesh = new THREE.Mesh(groundGeometry,groundMaterial);
        groundMesh.position.z -= 0.1;

        const verticalRoadMesh = new THREE.Mesh(roadGeometry,roadMaterial);

        const smallRoadMesh = new THREE.Mesh(halfRoadGeometry,roadMaterial);
        smallRoadMesh.rotation.z += Math.PI/2;
        smallRoadMesh.position.x += 25.0;

        const tShapeRoadGroup = new THREE.Group();
        tShapeRoadGroup.add(verticalRoadMesh);
        tShapeRoadGroup.add(groundMesh);
        tShapeRoadGroup.add(smallRoadMesh);

        tShapeRoadGroup.rotation.x -= Math.PI/2;

        return tShapeRoadGroup;
    }


