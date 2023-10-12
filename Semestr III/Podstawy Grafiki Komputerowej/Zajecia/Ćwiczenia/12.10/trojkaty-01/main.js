import * as THREE from 'three';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';
import { GLTFLoader } from 'three/addons/loaders/GLTFLoader.js';


const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera( 75, window.innerWidth/window.innerHeight, 0.1, 1000 );
camera.position.z = 5;
camera.lookAt( scene.position );

const renderer = new THREE.WebGLRenderer();
renderer.setSize( window.innerWidth, window.innerHeight );
renderer.setClearColor( new THREE.Color( 0x000000 ) );
document.getElementsByTagName('body')[0].appendChild( renderer.domElement );

const controls = new OrbitControls( camera, renderer.domElement );
controls.update();
const loader = new GLTFLoader();


// Material
const material = new THREE.MeshBasicMaterial( { color: 0xff0000, wireframe: false } );
//material.side = THREE.DoubleSide;

// BufferGeometry
const geometry = new THREE.BufferGeometry();
// create a simple square shape. We duplicate the top left and bottom right
// vertices because each vertex needs to appear once per triangle.
const vertices = new Float32Array( [
	-1.0, -1.0,  1.0,
	1.0, -1.0,  1.0,
	1.0,  1.0,  1.0,

	1.0,  1.0,  1.0,
	-1.0,  1.0,  1.0,
	-1.0, -1.0,  1.0,

	-1.0, -1.0,  -1.0,
	1.0, -1.0,  -1.0,
	1.0,  1.0,  -1.0,

	1.0,  1.0,  -1.0,
	-1.0,  1.0,  -1.0,
	-1.0, -1.0,  -1.0,

	1.0, 1.0, 1.0,
	1.0, -1.0, 1.0,
	1.0, -1.0, -1.0,

	1.0, -1.0, -1.0,
	1.0, 1.0, -1.0,
	1.0, 1.0, 1.0,

	-1.0, 1.0, 1.0,
	-1.0, -1.0, 1.0,
	-1.0, -1.0, -1.0,

	-1.0, -1.0, -1.0,
	-1.0, 1.0, -1.0,
	-1.0, 1.0, 1.0,

	1.0, 1.0, 1.0,
	1.0, 1.0, -1.0,
	-1.0, 1.0, -1.0,

	-1.0,1.0,-1.0,
	-1.0,1.0,1.0,
	1.0,1.0,1.0,

	1.0, -1.0, 1.0,
	1.0, -1.0, -1.0,
	-1.0, -1.0, -1.0,

	-1.0,-1.0,-1.0,
	-1.0,-1.0,1.0,
	1.0,-1.0,1.0,


	//x		y	 z
] );

// itemSize = 3 because there are 3 values (components) per vertex
geometry.setAttribute( 'position', new THREE.BufferAttribute( vertices, 3 ) );
geometry.computeBoundingSphere();

const mesh = new THREE.Mesh( geometry, material );
scene.add( mesh );

// An axis object to visualize the 3 axes in a simple way.
// The X axis is red. The Y axis is green. The Z axis is blue.
const axesHelper = new THREE.AxesHelper( 5 );
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

