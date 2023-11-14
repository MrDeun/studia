import * as THREE from 'three';

const groundGeometry = new THREE.PlaneGeometry(100.0,100.0,1,1);
const groundMaterial = new THREE.MeshBasicMaterial({color:0x005500});

const roadGeometry = new THREE.PlaneGeometry(10.0,100.0,1,1);
const halfRoadGeometry = new THREE.PlaneGeometry(10.0,55,1,1);
const roadMaterial = new THREE.MeshBasicMaterial({color:0x666666});

export function createTurnRoad()
    {
        const groundMesh = new THREE.Mesh(groundGeometry,groundMaterial);
        groundMesh.position.z -= 0.1;

        const verticalRoadMesh = new THREE.Mesh(halfRoadGeometry,roadMaterial);
        verticalRoadMesh.position.y += 22.5

        const horizontalRoadMesh = new THREE.Mesh(halfRoadGeometry,roadMaterial);
        horizontalRoadMesh.rotation.z += Math.PI/2;
        horizontalRoadMesh.position.x += 22.5;

        const TurnRoadGroup = new THREE.Group();
        TurnRoadGroup.add(verticalRoadMesh);
        TurnRoadGroup.add(groundMesh);
        TurnRoadGroup.add(horizontalRoadMesh);

        TurnRoadGroup.rotation.x -= Math.PI/2;

        return TurnRoadGroup;
    }