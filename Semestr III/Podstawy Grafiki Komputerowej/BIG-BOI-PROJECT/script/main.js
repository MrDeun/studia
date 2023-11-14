//REMEMBER: Rotate tiles with rotation.z

import * as THREE from 'three';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';
import { GLTFLoader } from 'three/addons/loaders/GLTFLoader.js';
import { AxesHelper } from 'three';

import { createCrossroad } from './prefabs/road/crossroad';
import { createStraightRoad } from './prefabs/road/plainroad';
import { createtShapeRoad } from './prefabs/road/troad';
import { createTurnRoad } from './prefabs/road/turnroad';

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(90,window.innerWidth/window.innerHeight,0.1,1000);
const renderer = new THREE.WebGLRenderer();
const controls = new OrbitControls( camera, renderer.domElement );
controls.update();
const loader = new GLTFLoader();
const axisHelper = new THREE.AxesHelper(2000);
//Ustawienia Kamery

camera.position.z = 20;
//camera.rotation.y = Math.PI/4;
camera.lookAt(scene.position)

//Ustawienia Renderera
renderer.setSize( window.innerWidth, window.innerHeight );
renderer.setClearColor( new THREE.Color( 0x5588ff ) );
renderer.setSize(window.innerWidth,window.innerHeight);
document.body.appendChild(renderer.domElement);

const center = createCrossroad();
const TTurns = [];
const LTurns = [];

for(let i=0;i<4;i++)
{
	TTurns[i] = createtShapeRoad();
	TTurns[i].rotation.z += (Math.PI/2)*(i);
}

TTurns[0].position.x -= 100.0;
TTurns[1].position.z += 100.0;
TTurns[2].position.x += 100.0;
TTurns[3].position.z -= 100.0;


for(let i=0;i<4;i++)
{
	LTurns[i]=createTurnRoad();
	LTurns[i].rotation.z += (Math.PI/2)*(i);
}

LTurns[0].position.x -= 100.0;LTurns[0].position.z += 100.0;
LTurns[1].position.x += 100.0;LTurns[1].position.z += 100.0;
LTurns[2].position.x += 100.0;LTurns[2].position.z -= 100.0;
LTurns[3].position.x -= 100.0;LTurns[3].position.z -= 100.0;



for(let objectT in TTurns)
	scene.add(TTurns[objectT]);

for(let objectL in LTurns)
	scene.add(LTurns[objectL])

scene.add(axisHelper);
scene.add(center);
const animate = function () {
	requestAnimationFrame( animate );

	//scene.rotation.y += Math.PI/2048;

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