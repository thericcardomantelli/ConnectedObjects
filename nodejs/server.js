var express = require('express');
var app = express();
var server = app.listen(3000, '192.168.43.2');
app.use(express.static('public'));

console.log("My socket server is running");

var socket = require('socket.io');
var io = socket(server);

io.sockets.on('connection', newConnection );

function newConnection(socket) {
	console.log('new connection: '+socket.id);

	socket.on('mouse', mouseMsg);
	function mouseMsg(data) {
		socket.broadcast.emit('mouse', data);
		console.log(data);
	}
	
	socket.on('key', keyMsg);
	function keyMsg(data) {
		socket.broadcast.emit('key', data);
		console.log(data);

	}
	socket.on('iot', arduinoMsg);
	function arduinoMsg(data) {
		socket.broadcast.emit('iot', data);
		console.log('arduino ');
		console.log(data);
	}

}


