
import * as THREE from 'three';

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera( 75, window.innerWidth / window.innerHeight, 0.1, 1000 );

const renderer = new THREE.WebGLRenderer();
renderer.setSize( window.innerWidth, window.innerHeight );
document.body.appendChild( renderer.domElement );

const topScrewGeometry = new THREE.CylinderGeometry(12,12,6,6,1,false,0,Math.PI*2)
const material = new THREE.MeshBasicMaterial( { color: 0xaaaaaa} );
const topScrewMesh = new THREE.Mesh( topScrewGeometry, material );
scene.add( topScrewMesh );

camera.position.z = 20;

renderer.render(scene,camera)


const rotation_step = 0.1;
document.addEventListener(
	'keydown',
	function( e ) {
		switch ( e.key ) {
			case 'ArrowUp': // up
				topScrewMesh.rotation.x -= rotation_step;
				break;
			case 'ArrowDown': // down
				topScrewMesh.rotation.x += rotation_step;
				break;
			case 'ArrowLeft': // left
				topScrewMesh.rotation.y -= rotation_step;
				break;
			case 'ArrowRight': // right
				topScrewMesh.rotation.y += rotation_step;
				break;
			case 'PageUp': // page up
				topScrewMesh.rotation.z -= rotation_step;
				break;
			case 'PageDown': // page down
				topScrewMesh.rotation.z += rotation_step
				break;
			default:
				;
		}
		camera.lookAt( scene.position );
		controls.update();
		renderer.render(scene,camera)
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