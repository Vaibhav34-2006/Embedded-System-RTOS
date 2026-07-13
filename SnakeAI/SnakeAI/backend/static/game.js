const canvas = document.getElementById("game");
const ctx = canvas.getContext("2d");

const socket = io();

const box = 20;

let direction = "RIGHT";

let score = 0;

let highScore = localStorage.getItem("highScore") || 0;

document.getElementById("highScore").innerHTML =
"High Score : " + highScore;

let snake = [

    {x:200,y:200}

];

let food = randomFood();

socket.on("direction", function(data){

    if(data==="LEFT" && direction!=="RIGHT")
        direction="LEFT";

    if(data==="RIGHT" && direction!=="LEFT")
        direction="RIGHT";

    // Swap UP and DOWN
    if(data==="UP" && direction!=="UP")
        direction="DOWN";

    if(data==="DOWN" && direction!=="DOWN")
        direction="UP";

});

function randomFood(){

    return{

        x:Math.floor(Math.random()*20)*box,

        y:Math.floor(Math.random()*20)*box

    };

}

function gameOver(){

    clearInterval(gameLoop);

    if(score>highScore){

        localStorage.setItem("highScore",score);

    }

    document.getElementById("finalScore").innerHTML="Score : "+score;

    document.getElementById("gameOver").style.display="block";

}

function draw(){

    ctx.fillStyle="#111";

    ctx.fillRect(0,0,canvas.width,canvas.height);

    ctx.fillStyle="red";

    ctx.fillRect(food.x,food.y,box,box);

    ctx.fillStyle="#00ff99";

    snake.forEach(part=>{

        ctx.fillRect(part.x,part.y,box,box);

    });

    let headX=snake[0].x;

    let headY=snake[0].y;

    switch(direction){

        case "LEFT":
            headX-=box;
            break;

        case "RIGHT":
            headX+=box;
            break;

        case "UP":
            headY-=box;
            break;

        case "DOWN":
            headY+=box;
            break;

    }

    if(headX===food.x && headY===food.y){

        score++;

        document.getElementById("score").innerHTML="Score : "+score;

        do{

            food=randomFood();

        }

        while(snake.some(p=>p.x===food.x && p.y===food.y));

    }

    else{

        snake.pop();

    }

    if(

        headX<0 ||

        headY<0 ||

        headX>=canvas.width ||

        headY>=canvas.height ||

        snake.some(p=>p.x===headX && p.y===headY)

    ){

        gameOver();

        return;

    }

    snake.unshift({

        x:headX,

        y:headY

    });

}

const gameLoop=setInterval(draw,350);