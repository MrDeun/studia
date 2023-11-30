import * as THREE from 'three';

console.log("Javascript loaded!")

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera( 75, window.innerWidth / window.innerHeight, 0.1, 5000 );

const renderer = new THREE.WebGLRenderer();
renderer.setSize( window.innerWidth, window.innerHeight );
document.body.appendChild( renderer.domElement );

camera.position.z = 700;

//The sun is deadly laser!
const sunRadius = 200.0;
const sunRotationStep = Math.PI/4096;

const sunGeometry = new THREE.SphereGeometry(sunRadius,32,16,0,Math.PI*2,0,Math.PI);
const sunMaterial = new THREE.MeshBasicMaterial({color:0xaaaa00,wireframe:true});

const sunMesh = new THREE.Mesh(sunGeometry,sunMaterial);

function sunSelfRotation()
{
    sunMesh.rotation.y -= sunRotationStep;
}

scene.add(sunMesh);

//Floating rock in space - Earth

const earthRadius = 20.0;
const earthRotationStep = Math.PI/1024;

const earthGeometry = new THREE.SphereGeometry(earthRadius,32,16,0,Math.PI*2,0,Math.PI);
const earthMaterial = new THREE.MeshBasicMaterial({color:0x9e6847,wireframe:true})

const earthMesh = new THREE.Mesh(earthGeometry,earthMaterial);

function earthSelfRotation()
{
    if(earthMesh.rotation.y > Math.PI*2)
        earthMesh.rotation.y = 0;
    earthMesh.rotation.x += earthRotationStep;
}


//We just got hit by another pile of rocks which is now a moon

const moonRadius = 5.0;
const moonRotationStep = Math.PI/256;
const moonDistanceX = 50.0;
const moonDistanceY = 50.0;
let moonAngle = 0;

const moonGeometry = new THREE.SphereGeometry(moonRadius,32,16,0,Math.PI*2,0,Math.PI);
const moonMaterial = new THREE.MeshBasicMaterial({color:0x666666,wireframe:true});

const moonMesh = new THREE.Mesh(moonGeometry,moonMaterial);

moonMesh.position.x = moonDistanceX;
moonMesh.position.z = moonDistanceY;

function moonSelfRotation()
{
    if(moonMesh.rotation.z > Math.PI*2);
        moonMesh.rotation.z = 0;
    moonMesh.rotation.z += moonRotationStep;

    moonMesh.position.x = moonDistanceX * Math.cos(moonAngle);
    moonMesh.position.z = moonDistanceX * Math.sin(moonAngle);

    moonAngle+=Math.PI/32;
}



//Earth and Moon are one group;

const earthGroupDistanceX = 500.0;
const earthGroupDistanceY = 500.0;
let earthGroupAngle = 0.0;

const earthGroup = new THREE.Group();
earthGroup.add(earthMesh);
earthGroup.add(moonMesh);

earthGroup.position.x = earthGroupDistanceX;
earthGroup.position.z = earthGroupDistanceY;

function earthGroupPosition()
{
    if(earthGroupAngle > Math.PI*2)
        earthGroupAngle = 0;
    earthGroup.position.x = earthGroupDistanceX*Math.cos(earthGroupAngle);
    earthGroup.position.z = earthGroupDistanceX*Math.sin(earthGroupAngle);

    earthGroupAngle += Math.PI/128;
}

scene.add(earthGroup);

function animate() {
    sunSelfRotation();
    earthSelfRotation();
    moonSelfRotation();
    earthGroupPosition();

	requestAnimationFrame( animate );
	renderer.render( scene, camera );
}

animate();


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