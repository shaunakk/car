var gpio = require('pigpio').Gpio
var app = require('express')();
var server = require('http').Server(app);
var io = require('socket.io')(server);
var SerialPort = require('serialport');
var port = new SerialPort('/dev/tty-AMA0', {
  baudRate: 9600
});
server.listen(8080);

app.get('/', function(req, res) {
  res.send("Socket.io server for car \n Built by Shaunak Kale");
});
radtodeg = 180 / Math.PI
io.on('connection', function(socket) {
  console.log('A user connected');

  socket.on('joystickData', function(data) {
    arduData = parseInt(((Math.atan2(parseFloat(data[0]), parseFloat(data[1])) * radtodeg) / 180) * 32 + 32).toString()
    console.log(((Math.atan2(parseFloat(data[0]), parseFloat(data[1])) * radtodeg) / 180) * 32 + 32);
    ardusend(arduData)

  });
  socket.on('disconnect', function() {
    console.log('A user disconnected');
  });

});

function done() {}
motor = new gpio(16, {
    mode: gpio.OUTPUT
  }),
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
}, 500);


function ardusend(data) {
  if (typeof data === 'string') {
    port.write(data, function(err) {
      if (err) {
        return console.log('Error on write: ', err.message);
      }
      console.log('message written');
    });
  }

}
