import * as THREE from 'three';

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera( 75, window.innerWidth / window.innerHeight, 0.1, 100 );

const renderer = new THREE.WebGLRenderer();
renderer.setSize( window.innerWidth, window.innerHeight );
document.body.appendChild( renderer.domElement );

const geometry = new THREE.BoxGeometry( 0.25, 1.0, 0.25 );
const materialtable = [

	new THREE.MeshBasicMaterial({color:0xff0000}),
	new THREE.MeshBasicMaterial({color:0x00ff00}),
	new THREE.MeshBasicMaterial({color:0x0000ff}),

]
const material = new THREE.MeshBasicMaterial( { color: 0xc100ff } );
const cube = new THREE.Mesh( geometry, material );


const spheregeo = new THREE.SphereGeometry(1.0,5.0,5.0,0,Math.PI*2,0,Math.PI);
const tinysphere = new THREE.SphereGeometry(0.95,24,24,3.0,Math.PI*2,Math.PI);
const spheremesh = new THREE.Mesh(tinysphere,material);

var cubewire = new THREE.EdgesGeometry(cube.geometry);
var wirematerial = new THREE.LineBasicMaterial({color: 0xffffff});
var spherewire = new THREE.EdgesGeometry(spheremesh.geometry);
var wireframe = new THREE.LineSegments(spherewire,wirematerial);
var cubeWireframe = new THREE.LineSegments(cubewire,wirematerial);

scene.add(wireframe);
//scene.add(cubeWireframe);
scene.add( spheremesh );

//scene.add(spheremesh);

camera.position.z = 3;

function animate() {
	requestAnimationFrame( animate );

	spheremesh.rotation.x = 0.5;
	spheremesh.rotation.y += 0.01;
	spheremesh.rotation.z += 0;

	wireframe.rotation.x = 0.5;
	wireframe.rotation.y += 0.01;
	wireframe.rotation.z += 0;
	
	cubeWireframe.rotation.x = 0.5;
	cubeWireframe.rotation.y += 0.01;
	cubeWireframe.rotation.z += 0;

	renderer.render( scene, camera );
}


animate();