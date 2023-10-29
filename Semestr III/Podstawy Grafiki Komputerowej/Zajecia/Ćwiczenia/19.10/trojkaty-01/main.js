import * as THREE from 'three';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';
import { GLTFLoader } from 'three/addons/loaders/GLTFLoader.js';


const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera( 75, window.innerWidth/window.innerHeight, 0.1, 1000 );
camera.position.z = 20;
camera.lookAt( scene.position );

const renderer = new THREE.WebGLRenderer();
renderer.setSize( window.innerWidth, window.innerHeight );
renderer.setClearColor( new THREE.Color( 0x000000 ) );
document.getElementsByTagName('body')[0].appendChild( renderer.domElement );

const controls = new OrbitControls( camera, renderer.domElement );
controls.update();
const loader = new GLTFLoader();


// Material
const material = new THREE.MeshBasicMaterial( { color: 0xaaaaaa, wireframe: false } );
const topScrewMaterial = new THREE.MeshBasicMaterial({color:0x0000ff})
const rodScrewMaterial = new THREE.MeshBasicMaterial({color:0xff0000})
const pointScrewMaterial = new THREE.MeshBasicMaterial({color:0x00ff00})

const screwMaterials = [topScrewMaterial,rodScrewMaterial,pointScrewMaterial]
//material.side = THREE.DoubleSide;

//Geometry
const topScrewGeometry = new THREE.CylinderGeometry(2.5,2.5,1.0,6.0,1,false,0,Math.PI*2)
const rodScrewGeometry = new THREE.CylinderGeometry(1.0,1.0,10.0,8.0,1.0,false,0,Math.PI*2)
const pointScrewGeometry = new THREE.CylinderGeometry(1.0,0.0,1.0,8,1,false,0,Math.PI*2)



const screwsGeometry = [topScrewGeometry,rodScrewGeometry,pointScrewGeometry]

// BufferGeometry
//const geometry = new THREE.BufferGeometry();
// create a simple square shape. We duplicate the top left and bottom right
// vertices because each vertex needs to appear once per triangle.
// const vertices = new Float32Array( [
// 	-1.0, -1.0,  1.0,
// 	1.0, -1.0,  1.0,
// 	1.0,  1.0,  1.0,

// 	1.0,  1.0,  1.0,
// 	-1.0,  1.0,  1.0,
// 	-1.0, -1.0,  1.0,

// 	-1.0, -1.0,  -1.0,
// 	1.0, -1.0,  -1.0,
// 	1.0,  1.0,  -1.0,

// 	1.0,  1.0,  -1.0,
// 	-1.0,  1.0,  -1.0,
// 	-1.0, -1.0,  -1.0,

// 	1.0, 1.0, 1.0,
// 	1.0, -1.0, 1.0,
// 	1.0, -1.0, -1.0,

// 	1.0, -1.0, -1.0,
// 	1.0, 1.0, -1.0,
// 	1.0, 1.0, 1.0,

// 	-1.0, 1.0, 1.0,
// 	-1.0, -1.0, 1.0,
// 	-1.0, -1.0, -1.0,

// 	-1.0, -1.0, -1.0,
// 	-1.0, 1.0, -1.0,
// 	-1.0, 1.0, 1.0,

// 	1.0, 1.0, 1.0,
// 	1.0, 1.0, -1.0,
// 	-1.0, 1.0, -1.0,

// 	-1.0,1.0,-1.0,
// 	-1.0,1.0,1.0,
// 	1.0,1.0,1.0,

// 	1.0, -1.0, 1.0,
// 	1.0, -1.0, -1.0,
// 	-1.0, -1.0, -1.0,

// 	-1.0,-1.0,-1.0,
// 	-1.0,-1.0,1.0,
// 	1.0,-1.0,1.0,


// 	//x		y	 z
// ] );

// itemSize = 3 because there are 3 values (components) per vertex
//geometry.setAttribute( 'position', new THREE.BufferAttribute( vertices, 3 ) );
//geometry.computeBoundingSphere();

const screwMeshes = []
for(let i = 0;i<3;i++)
	{
		screwMeshes[i]= new THREE.Mesh(screwsGeometry[i],screwMaterials[i]);

	}

screwMeshes[0].position.y = 5.5
screwMeshes[2].position.y = -5.5

// for( let i = 0;i<3;i++)
// {
// 	scene.add(screwMeshes[i]);
// }

const screwGroup1 = new THREE.Group();
const screwGroup2 = new THREE.Group();

for( let i = 0;i<3;i++)
{
	screwGroup1.add(screwMeshes[i])
	screwGroup2.add(screwMeshes[i])
}

scene.add(screwGroup1)
scene.add(screwGroup2)

// screwGroup1.position.x = 5.0
// screwGroup1.rotation.z = Math.PI/6

// screwGroup2.position.y = -10.0
// screwGroup2.rotation.y = Math*PI/2


// An axis object to visualize the 3 axes in a simple way.
// The X axis is red. The Y axis is green. The Z axis is blue.
const axesHelper = new THREE.AxesHelper( 20 );
scene.add( axesHelper );

// render created scene
renderer.render( scene, camera );


const animate = function () {
	requestAnimationFrame( animate );

	controls.update();
	renderer.render( scene, camera );
};

animate();


// keyboard support
const rotation_step = 0.1;
document.addEventListener(
	'keydown',
	function( e ) {
		switch ( e.key ) {
			case 'ArrowUp': // up
				mesh.rotation.x -= rotation_step;
				break;
			case 'ArrowDown': // down
				mesh.rotation.x += rotation_step;
				break;
			case 'ArrowLeft': // left
				mesh.rotation.y -= rotation_step;
				break;
			case 'ArrowRight': // right
				mesh.rotation.y += rotation_step;
				break;
			case 'PageUp': // page up
				mesh.rotation.z -= rotation_step;
				break;
			case 'PageDown': // page down
				mesh.rotation.z += rotation_step
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

