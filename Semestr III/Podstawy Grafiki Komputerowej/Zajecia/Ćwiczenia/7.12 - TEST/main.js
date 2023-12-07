import * as THREE from 'three'
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';
import { GLTFLoader } from 'three/addons/loaders/GLTFLoader.js';

const camera =  new THREE.PerspectiveCamera(60,window.innerWidth/window.innerHeight)
const scene = new THREE.Scene();
const renderer = new THREE.WebGLRenderer();
const controls = new OrbitControls( camera, renderer.domElement );
controls.update();
const loader = new GLTFLoader();


renderer.setSize( window.innerWidth, window.innerHeight );
renderer.setClearColor( new THREE.Color( 0x000033 ) );
renderer.setSize(window.innerWidth,window.innerHeight);
renderer.shadowMap.enabled = true;
document.body.appendChild(renderer.domElement);

scene.add(camera);

camera.position.z += 10.0;
camera.position.y += 20.0;


//SNOW PLANE
const snowPlaneGeometry = new THREE.PlaneGeometry(50.0,50.0,1,1);
const snowPlaneMaterial = new THREE.MeshStandardMaterial({color:0xffffff,metalness:0.1});

const snowPlaneMesh = new THREE.Mesh(snowPlaneGeometry,snowPlaneMaterial);
snowPlaneMesh.rotation.x -= Math.PI/2;

scene.add(snowPlaneMesh);

//LIGHTS

const light = new THREE.DirectionalLight(0xaaaaaa,1.5);
light.position.y += 30.0;
light.position.z += 10.0;
light.position.x += 10.0; 
light.castShadow = true;
scene.add(light);

//TREE
///STUMP
const PineStumpGeometry = new THREE.CylinderGeometry(1.0,1.0,2.0,32,1,false,0,Math.PI*2);
const PineStumpMaterial = new THREE.MeshStandardMaterial({color:0x916411,wireframe:false});
const PineStumpMesh = new THREE.Mesh(PineStumpGeometry,PineStumpMaterial);

PineStumpMesh.position.y += 1.0;
//scene.add(PineStumpMesh);
///CONES
const PineLeavesGeometry = new THREE.ConeGeometry(3.0,5.0,32,1,false,0,Math.PI*2);
const PineLeavesMaterial = new THREE.MeshStandardMaterial({color:0x00aa00,wireframe:false});
const allCones = [];
for(let i=0;i<3;i++)
{
    allCones[i] = new THREE.Mesh(PineLeavesGeometry,PineLeavesMaterial);
    allCones[i].position.y += 4.0 + ( i * 3.0 );
    //scene.add(allCones[i]);
}
///BULBS
const BulbGeometry = new THREE.SphereGeometry(0.5,32,16,0,Math.PI*2,0,Math.PI);
const BulbMaterials = 
[
    new THREE.MeshStandardMaterial({color:0xff0000,metalness:1.0,roughness:0.0}),
    new THREE.MeshStandardMaterial({color:0xffff00,metalness:1.0,roughness:0.0})
]

const allBulbs = []

for(let i=0;i<2;i++)
{
    allBulbs[i] = new THREE.Mesh(BulbGeometry,BulbMaterials[i]);
    allBulbs[i].position.y += ( i+1 ) * 3.0;
    allBulbs[i].position.z += ( i * -1 ) * 1.0;
    //scene.add(allBulbs[i]);
}

allBulbs[0].position.x += 1.66;
allBulbs[0].position.z += 1.66;

console.log(allBulbs[1].position.z);

allBulbs[1].position.z -= 0.66;
allBulbs[1].position.x -= 1.66;

///GROUPING
const christmasTree = new THREE.Group();

christmasTree.add(PineStumpMesh);
christmasTree.add(allCones[0]);christmasTree.add(allCones[1]);christmasTree.add(allCones[2]);
christmasTree.add(allBulbs[0]);christmasTree.add(allBulbs[1]);

christmasTree.castShadow = true;
christmasTree.receiveShadow = true;

scene.add(christmasTree);

//
const animate = function () {
	requestAnimationFrame( animate );

	controls.update();
	renderer.render( scene, camera );
};

animate();

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