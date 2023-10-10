
import * as THREE from 'three' //Importowanie biblioteki three z npm

////////////////////////////
//Tworzenie sceny, kamery, renderera
//
var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera( 5, window.innerWidth/window.innerHeight, 0.01, 1000 );

var renderer = new THREE.WebGLRenderer();
renderer.setSize( window.innerWidth, window.innerHeight );

////////////////////////////
//powiazanie renderera z <body>
//
document.body.appendChild( renderer.domElement );



//1.wytlumacz studentom polozenie punktu vs polozenie kamery
//2.pokaz co robi sizeAttenuation !!!!!

////////////////////////////
//Tworzenie geometrii, materialu, Siatki. Dodanie do sceny
//
var geometry = new THREE.BufferGeometry( );
const vertices = new Float32Array([0.0, 0.0, -1]);
const colors =new Float32Array([0, 1, 0]);

geometry.setAttribute('position', new THREE.BufferAttribute(vertices, 3) );
geometry.setAttribute('color', new THREE.BufferAttribute(colors, 3) );

var material = new THREE.PointsMaterial( 
    { 
        size: 1.0
        //, sizeAttenuation: false	//true jest domyslne
        // , color: 0xff00ff 	//odkomentuj i zakomentuj linie ponizej aby miec kolor materialu (domyslne)
        , vertexColors: true
        //, vertexColors: false	//domyslna
    } );
var dot = new THREE.Points( geometry, material );
scene.add( dot );

camera.position.z = 1;
renderer.render(scene, camera);