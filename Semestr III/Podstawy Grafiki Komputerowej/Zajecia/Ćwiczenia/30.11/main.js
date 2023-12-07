import * as THREE from 'three';

			import { OrbitControls } from 'three/addons/controls/OrbitControls.js';
			import { RGBELoader } from 'three/addons/loaders/RGBELoader.js';

			import { GUI } from 'three/addons/libs/lil-gui.module.min.js';
			import Stats from 'three/addons/libs/stats.module.js';

			let camera, scene, renderer, stats;
			let cube, sphere, torus, material;

			let cubeCamera, cubeRenderTarget;

			let controls;

			init();

			function init() {

				renderer = new THREE.WebGLRenderer( { antialias: true } );
				renderer.setPixelRatio( window.devicePixelRatio );
				renderer.setSize( window.innerWidth, window.innerHeight );
				renderer.setAnimationLoop( animation );
				renderer.toneMapping = THREE.ACESFilmicToneMapping;
				document.body.appendChild( renderer.domElement );

				window.addEventListener( 'resize', onWindowResized );

				stats = new Stats();
				document.body.appendChild( stats.dom );

				camera = new THREE.PerspectiveCamera( 60, window.innerWidth / window.innerHeight, 1, 1000 );
				camera.position.z = 75;

				scene = new THREE.Scene();
				scene.rotation.y = 0.5; // avoid flying objects occluding the sun

				new RGBELoader()
					.load( './meadow_2_4k.hdr', function ( texture ) {

						texture.mapping = THREE.EquirectangularReflectionMapping;

						scene.background = texture;
						scene.environment = texture;

					} );

				//

				cubeRenderTarget = new THREE.WebGLCubeRenderTarget( 256 );
				cubeRenderTarget.texture.type = THREE.HalfFloatType;

				cubeCamera = new THREE.CubeCamera( 1, 1000, cubeRenderTarget );

				//SCALABILITY

                let figureCount = 10;
                let radius = 24.0;
                let scale = radius/figureCount;

                //MATERIALS

                    const materials = 
                    [
                        new THREE.MeshStandardMaterial({
                            color: 0xffffff,
                            metalness: 0.0,
                            roughness: 0.0,
                            exposure: 1.0
                        }),
                        new THREE.MeshStandardMaterial({
                            color: 0x000000,
                            metalness: 0.0,
                            roughness: 0.0,
                            exposure: 1.0
                        }),
                        new THREE.MeshStandardMaterial({
                            color: 0xff0000,
                            metalness: 0.0,
                            roughness: 0.0,
                            exposure: 1.0
                        }),
                        new THREE.MeshStandardMaterial({
                            color: 0x00ff00,
                            metalness: 0.0,
                            roughness: 0.0,
                            exposure: 1.0
                        }),
                        new THREE.MeshStandardMaterial({
                            color: 0x0000ff,
                            metalness: 0.0,
                            roughness: 0.0,
                            exposure: 1.0
                        }),
                    ]

                //GEOMETRIES

                const geometries =
                [
                    new THREE.BoxGeometry(scale,scale,1,1,1,1),
                    new THREE.SphereGeometry(scale,1,1,0,Math.PI*2,0,Math.PI),
                    new THREE.ConeGeometry(scale,scale,32,1,false,0,Math.PI*2),
                    new THREE.RingGeometry(scale,scale,32,1,0,Math.PI*2),
                ]

				//GROUPING AND POSITIONING

                const figuresGroup = new THREE.Group();
                const figuresArray = [];

                for(let i=0;i<figureCount;i++)
                {
                    figuresArray[i] = new THREE.Mesh(geometries[i%4],materials[i%5]);
                    figuresArray[i].position.x = radius * Math.cos( ( (Math.PI*2)/figureCount) * i);
                    figuresArray[i].position.y = radius * Math.sin( ( (Math.PI*2)/figureCount) * i);
                    figuresGroup.add(figuresArray[i]);x``
                }

                scene.add(figuresGroup);

                //

				controls = new OrbitControls( camera, renderer.domElement );
				controls.autoRotate = false;

			}

			function onWindowResized() {

				renderer.setSize( window.innerWidth, window.innerHeight );

				camera.aspect = window.innerWidth / window.innerHeight;
				camera.updateProjectionMatrix();

			}

			function animation( msTime ) {

				const time = msTime / 1000;

				cubeCamera.update( renderer, scene );
				controls.update();
				renderer.render( scene, camera );


			}
