const dgram = require("dgram");
const oscmsg = require("osc-msg");
var prompt = require('prompt');
var SEND_PORT = 7000
var RECV_PORT = 8000;
var url="149.31.142.182"
// var url="149.31.202.230"
// var url="localhost"

var id;
var SerialPort = require('serialport');
const Readline = SerialPort.parsers.Readline;
var port = new SerialPort('/dev/cu.usbserial-A904MH09', {
  baudRate: 9600
});
const parser = new Readline();
port.pipe(parser);

var message = {
  address: "",
  args: [
    // { type: "integer", value: 0 },
    { type: "float", value: 0}
  ]
};

var buffer;
var socket;




// prompt.start();
// input();
// setInterval(function(){ port.write("a"+'\n'); }, 2000);

 socket = dgram.createSocket("udp4");
socket.on("message", (buffer) => {
  const bundle = oscmsg.decode(buffer, { strict: true, strip: true, bundle: true });
 
  if (bundle.error) {
    return;
  }
 
  bundle.elements.forEach((message) => {
    console.log(JSON.stringify(message.args));
    if(message.args==2){
    	console.log("bomb a")
     port.write("a"+'\n');
    }

    if(message.args==3){
    	console.log("bomb")
     port.write("b"+'\n');
    }

    if(message.args==4){
    	console.log("bomb")
     port.write("c"+'\n');
    }
    if(message.args==5){
    	console.log("bomb")
     port.write("d"+'\n');
    }

    if(message.args==6){
    	console.log("bomb")
     port.write("e"+'\n');
    }

  });
});
socket.bind(RECV_PORT);


parser.on('data', function (data) {
   console.log(data);
   var datas=data.split(",")
var shoot = datas[3]
var left = datas[5]
var right = datas[6]
var bomb = datas[4]







var Fshoot = {
  address: "/1",
  args: [
    // { type: "integer", value: 0 },
    { type: "float", value: shoot}
  ]
};

buffer = oscmsg.encode(Fshoot);
 socket.send(buffer, 0, buffer.length, SEND_PORT, url);

var Fleft = {
  address: "/2",
  args: [
    // { type: "integer", value: 0 },
    { type: "float", value: left}
  ]
};
buffer = oscmsg.encode(Fleft);
 // socket = dgram.createSocket("udp4");
 socket.send(buffer, 0, buffer.length, SEND_PORT, url);

 var Fright = {
  address: "/3",
  args: [
    // { type: "integer", value: 0 },
    { type: "float", value: right}
  ]
};
buffer = oscmsg.encode(Fright);
 // socket = dgram.createSocket("udp4");
 socket.send(buffer, 0, buffer.length, SEND_PORT, url);


 var Fbomb = {
  address: "/4",
  args: [
    // { type: "integer", value: 0 },
    { type: "float", value: bomb}
  ]
};
buffer = oscmsg.encode(Fbomb);
 // socket = dgram.createSocket("udp4");
 socket.send(buffer, 0, buffer.length, SEND_PORT, url);


});

function input() {
prompt.get(['player', 'value'], function (err, result) {
    //
    // Log the results.
    //
    console.log('Command-line input received:');
  

    var mapped= map_range(result.value, 0, 100, -.05, .05)

// function map_range(value, low1, high1, low2, high2) {
//     return low2 + (high2 - low2) * (value - low1) / (high1 - low1);
// }

  console.log('  player: ' + result.player);
    console.log('  value: ' + result.value);
    console.log('  mapped: ' + mapped);
id=result.player
 message = {
  address: "/"+id,
  args: [
    // { type: "integer", value: 0 },
    { type: "float", value: mapped}
  ]
};
buffer = oscmsg.encode(message);
 socket = dgram.createSocket("udp4");
 socket.send(buffer, 0, buffer.length, SEND_PORT, url);




// message = {
//   address: "/",
//   args: [
//     // { type: "integer", value: 0 },
//     { type: "float", value: 0}
//   ]
// };

//  buffer = oscmsg.encode(message);
//  socket = dgram.createSocket("udp4");
 
// socket.send(buffer, 0, buffer.length, SEND_PORT, url);
setTimeout(function(){ out(); }, 200);

input();

  });

}

function map_range(value, low1, high1, low2, high2) {
    return low2 + (high2 - low2) * (value - low1) / (high1 - low1);
}

 function out() {
 message = {
  address:"/"+id,
  args: [
    // { type: "integer", value: 0 },
    { type: "float", value: 0}
  ]
};
 buffer = oscmsg.encode(message);
 socket = dgram.createSocket("udp4");

 console.log(message)
 
socket.send(buffer, 0, buffer.length, SEND_PORT, url);
 }


 
