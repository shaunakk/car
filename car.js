var gpio = require('pigpio').Gpio
var app = require('express')();
var server = require('http').Server(app);
var io = require('socket.io')(server);
var SerialPort = require('serialport');
var left
var max
var right
var dirr
var dirl

var port = new SerialPort('/dev/ttyAMA0', {baudRate: 9600});
port.on('open', () => {
  console.log('port opened');
});
server.listen(8080);

app.get('/', function(req, res) {
  res.send("Socket.io server for car \n Built by Shaunak Kale");
});
io.on('connection', function(socket) {
  console.log('A user connected');

  socket.on('joystickData', function(data) {
    left = parseInt(data[1]) + parseInt(data[0])
    right = parseInt(data[1]) - parseInt(data[0])
    max = Math.max(Math.abs(left), Math.abs(right));
    if (max > 255) {
      left /= max;
      right /= max;
    }
    if (left < 0) {
      left = Math.abs(left)
      dirl = 0
    } else {
      dirl = 1
    }
    if (right < 0) {
      right = Math.abs(right)
      dirr = 0
    } else {
      dirr = 1
    }
    arduData = "L" + parseInt(left) + "R" + parseInt(right) + "A" + dirl + "B" + dirr
    console.log(arduData);
    ardusend(arduData);
  });
  socket.on('disconnect', function() {
    console.log('A user disconnected');
  });

});
motor = new gpio(16, {mode: gpio.OUTPUT}),
pulseWidth = 1500,
increment = 500;

setInterval(function() {
  motor.servoWrite(pulseWidth);

  pulseWidth += increment;
  if (pulseWidth >= 1500) {
    increment = -500;
  } else if (pulseWidth <= 1000) {
    increment = 500;
  }
}, 5000);

function ardusend(data) {
  arddata = data
  port.write(data, function(err) {
    if (err) {
      return console.log('Error on write: ', err.message);
    }
    console.log('message written');
  });

}
