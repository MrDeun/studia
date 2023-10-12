import * as THREE from 'three';

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera( 90, window.innerWidth / window.innerHeight, 0.1, 100 );

const renderer = new THREE.WebGLRenderer();
renderer.setSize( window.innerWidth, window.innerHeight );
document.body.appendChild( renderer.domElement );

const geometry = new THREE.BoxGeometry( 1.0, 1.0, 1.0 );
const material = new THREE.MeshBasicMaterial( { color: 0xff0000 } );
const cube = new THREE.Mesh( geometry, material );
scene.add( cube );



//scene.add(spheremesh);

camera.position.z = 3;

function animate() {
	requestAnimationFrame( animate );

	cube.rotation.x = 0.5;
	cube.rotation.y += 0.01;
	cube.rotation.z += 0;

	renderer.render( scene, camera );
}


animate();