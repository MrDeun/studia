import * as THREE from 'three';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';
import { GLTFLoader } from 'three/addons/loaders/GLTFLoader.js';


const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(90,window.innerWidth/window.innerHeight,0.1,1000);
const renderer = new THREE.WebGLRenderer();
const controls = new OrbitControls( camera, renderer.domElement );
controls.update();
const loader = new GLTFLoader();

//Ustawienia Kamery

camera.position.z = 20;
//camera.rotation.y = Math.PI/4;
camera.lookAt(scene.position)

//Ustawienia Renderera
renderer.setSize( window.innerWidth, window.innerHeight );
renderer.setClearColor( new THREE.Color( 0x5588ff ) );
renderer.setSize(window.innerWidth,window.innerHeight);
document.body.appendChild(renderer.domElement);

//Geometria drogii
const verticalRoadGeometry = new THREE.PlaneGeometry(50.0,5.0,1,1)
const horizontalRoadGeometry = new THREE.PlaneGeometry(5.0,50.0,1,1)
//Material drogi
const roadMaterial = new THREE.MeshBasicMaterial({color:0x777777})
//Meshe drogi
const verticalRoadMesh = new THREE.Mesh(verticalRoadGeometry,roadMaterial);
const horizontalRoadMesh = new THREE.Mesh(horizontalRoadGeometry,roadMaterial);
//Grupa skrzyzowanie
const crossroad = new THREE.Group();
crossroad.add(verticalRoadMesh);
crossroad.add(horizontalRoadMesh);

//Geometria trawnika
const grassPlaneGeometry = new THREE.PlaneGeometry(50.0,50,1,1);
//Material trawnika
const grassPlaneMaterial = new THREE.MeshBasicMaterial({color:0x005500})
//Mesh trawnika
const grassPlaneMesh = new THREE.Mesh(grassPlaneGeometry,grassPlaneMaterial);
//Pozycja Trawnika
grassPlaneMesh.position.z = -0.01;

//Geometria drzewa
const treeCrownGeometry = new THREE.SphereGeometry(3.5,8,8,0,Math.PI*2,0.0,Math.Pi)
const treeStumpGeometry = new THREE.CylinderGeometry(1.0,1.25,4.0,8,2,true,0,Math.PI*2);
//Material drzewa
const treeCrownMaterial = new THREE.MeshBasicMaterial({color:0x00aa00})
const treeStumpMaterial = new THREE.MeshBasicMaterial({color:0x916411})
//Meshe drzewa
const treeCrown = new THREE.Mesh(treeCrownGeometry,treeCrownMaterial);
const treeStump = new THREE.Mesh(treeStumpGeometry,treeStumpMaterial);
//Pozycja drzewa
treeStump.position.y = 2.0;
treeCrown.position.y += treeStump.position.y + 3.0;
//Grupowanie drzewa;
const tree = new THREE.Group();
tree.add(treeCrown);
tree.add(treeStump);

tree.position.x = -15.0
tree.position.z = 7.0


//Geometria Domu
const houseMainBodyGeometry = new THREE.BoxGeometry(3.0,2.0,3.0,1,1,1)
const houseRoofGeometry = new THREE.ConeGeometry(3.0,1.5,4,1,false,0,Math.PI*2);
//Material Domu
const houseMainBodyMaterial = new THREE.MeshBasicMaterial({color:0x8e4738})
const houseRoofMaterial = new THREE.MeshBasicMaterial({color:0x603100})
//Meshes i pozycjonowanie Domu
const houseMainBody = new THREE.Mesh(houseMainBodyGeometry,houseMainBodyMaterial);
const houseRoof = new THREE.Mesh(houseRoofGeometry,houseRoofMaterial);

houseMainBody.position.y = 1.0;
houseRoof.position.y = houseMainBody.position.y + 1.5;
houseRoof.rotation.y = Math.PI/4
//Grupowanie domu
const house = new THREE.Group();
house.add(houseRoof)
house.add(houseMainBody)

house.position.x = 10.0
house.position.z = 10.0

const ground = new THREE.Group();
ground.add(crossroad)
ground.add(grassPlaneMesh)
ground.rotation.x = -Math.PI/2;

const meshScene = new THREE.Group();
meshScene.add(ground);
meshScene.add(tree);
meshScene.add(house)
scene.add(meshScene);

const animate = function () {
	requestAnimationFrame( animate );

	controls.update();
	renderer.render( scene, camera );
};

animate();

const rotation_step = 0.1;
document.addEventListener(
	'keydown',
	function( e ) {
		switch ( e.key ) {
			case 'w': // up
				meshScene.rotation.x -= rotation_step;
				break;
			case 's': // down
				meshScene.rotation.x += rotation_step;
				break;
			case 'a': // left
				meshScene.rotation.y -= rotation_step;
				break;
			case 'd': // right
				meshScene.rotation.y += rotation_step;
				break;
			case 'PageUp': // page up
				meshScene.rotation.z -= rotation_step;
				break;
			case 'PageDown': // page down
				meshScene.rotation.z += rotation_step
				break;
            case 'r': //Reset
                meshScene.rotation.z = 0;
                meshScene.rotation.y = 0;
                meshScene.rotation.x = 0;
                break;
            case 'ArrowUp': //Zoom In
                meshScene.position.z += rotation_step;
                break;
            case 'ArrowDown': //Zoom Out
                meshScene.position.z -= rotation_step;
                break;
			default:
				;
		}
		camera.lookAt( scene.position );
		controls.update();
		renderer.render( scene, camera );
	},
	false
);

// redraw in case of window's size change
window.addEventListener(
	'resize',
	function() {
		camera.aspect = window.innerWidth / window.innerHeight;
		camera.updateProjectionMatrix();
		renderer.setSize( window.innerWidth, window.innerHeight );
		renderer.render( scene, camera );
	},
	false
);