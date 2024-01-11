var mercury_rotation = 0
var earth_rotation = 0
var moon_rotation = 0
function draw_sun()
{
  push();
  translate(0,0,0);
  stroke(128,128,0);
  sphere(50);
  pop();
}

function draw_mercury(mercury_rotation)
{
  push();
  rotateZ(mercury_rotation);
  translate(-100,0,0);
  stroke(128,128,255);
  sphere(10);
  pop();

  return mercury_rotation+Math.PI/360;
}

function draw_moon(moon_rotation)
{
  push();
  translate(-30,0,0);
  rotateZ(moon_rotation);
    stroke(128,128,128);
    sphere(5);
  pop();

  return moon_rotation + Math.Pi/12;
}
  
  function draw_earth_and_moon(earth_rotation,moon_rotation)
{
  push();
  rotateZ(earth_rotation);
  translate(150,0,0);
    stroke(0,255,0);
    sphere(20);  
    moon_rotation = draw_moon(moon_rotation);
  pop();
  return earth_rotation + Math.PI/180;
}

function setup() {
  createCanvas(800, 600, WEBGL);
}

function draw() {
  background(255);
  draw_sun();
  mercury_rotation = draw_mercury(mercury_rotation);
  earth_rotation = draw_earth_and_moon(earth_rotation,moon_rotation);
}
