import * as THREE from 'three';

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera( 75, window.innerWidth / window.innerHeight, 0.1, 100 );

const renderer = new THREE.WebGLRenderer();
renderer.setSize( window.innerWidth, window.innerHeight );
document.body.appendChild( renderer.domElement );

const geometry = new THREE.BoxGeometry( 0.25, 1.0, 0.25 );
const material = new THREE.MeshBasicMaterial( { color: 0xff0000 } );
const cube = new THREE.Mesh( geometry, material );
scene.add( cube );

const spheregeo = new THREE.SphereGeometry(1.0,20.0,20.0,3.0,Math.PI*2,0,Math.PI);
const spheremesh = new THREE.Mesh(spheregeo,material);

var cubewire = new THREE.EdgesGeometry(cube.geometry);
var wirematerial = new THREE.LineBasicMaterial({color: 0xffffff});
var spherewire = new THREE.EdgesGeometry(spheremesh.geometry);
var wireframe = new THREE.LineSegments(spherewire,wirematerial);
var cubeWireframe = new THREE.LineSegments(cubewire,wirematerial);

scene.add(wireframe);
scene.add(cubeWireframe);

//scene.add(spheremesh);

camera.position.z = 3;

function animate() {
	requestAnimationFrame( animate );

	cube.rotation.x = 0.5;
	cube.rotation.y += 0.01;
	cube.rotation.z += 0;

	wireframe.rotation.x = 0.5;
	wireframe.rotation.y += 0.01;
	wireframe.rotation.z += 0;
	
	cubeWireframe.rotation.x = 0.5;
	cubeWireframe.rotation.y += 0.01;
	cubeWireframe.rotation.z += 0;

	renderer.render( scene, camera );
}


animate();