var gpio = require('pigpio').Gpio
var app = require('express')();
var server = require('http').Server(app);
var io = require('socket.io')(server);
var SerialPort = require('serialport');
var port = new SerialPort('/dev/ttyAMA0', {
  baudRate: 115200
});
port.on('open', () => {
  console.log('port opened');
});
server.listen(8080);


app.get('/', function(req, res) {
  res.send("Socket.io server for car \n Built by Shaunak Kale");
});
radtodeg = 180 / Math.PI
io.on('connection', function(socket) {
  console.log('A user connected');

  socket.on('joystickData', function(data) {
    arduData = parseFloat(((Math.atan2(parseFloat(data[0]), parseFloat(data[1])) * radtodeg) / 180) * 32 + 32)
    console.log(arduData);
    ardusend(arduData)

  });
  socket.on('disconnect', function() {
    console.log('A user disconnected');
  });

});
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
  arddata = data
  port.write(data, function(err) {
    if (err) {
      return console.log('Error on write: ', err.message);
    }
    console.log('message written');
  });


}
