let x = 0;

function setup() {
  createCanvas(1000, 1000);
}

function draw() {
    background(230);
    strokeWeight(5);
    point(x,sin(x)*x*cos(x)+500)
    x+=0.1;
}