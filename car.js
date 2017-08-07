var gpio = require('pigpio').Gpio
var Gpio = require('onoff').Gpio
var app = require('express')();
var server = require('http').Server(app);
var io = require('socket.io')(server);

server.listen(8080);

app.get('/', function(req, res) {
  res.send("Socket.io server for car \n Built by Shaunak Kale");
});

io.on('connection', function(socket) {
  console.log('A user connected');

  socket.on('joystickData', function(data) {
    console.log(Math.atan(parseFloat(data[0]) / parseFloat(data[1])) * 180 / Math.pi);
  });
  socket.on('disconnect', function() {
    console.log('A user disconnected');
  });

});


motor = new gpio(25, {
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
pow1 = new Gpio(7, 'out')
pow2 = new Gpio(8, 'out')
pow4 = new Gpio(25, 'out')
pow8 = new Gpio(24, 'out')
pow16 = new Gpio(23, 'out')
pow32 = new Gpio(18, 'out')
leftf = new Gpio(20, 'out')
rightf = new Gpio(21, 'out')
leftb = new Gpio(26, 'out')
rightb = new Gpio(19, 'out')
num = 1

function done() {}
setInterval(
  function() {
    if (num % 2 == 0) {
      pow16.write(1, done())
      pow32.write(1, done())
      leftf.write(0, done())
      rightf.write(0, done())
      leftb.write(0, done())
      rightb.write(1, done())
    } else {
      pow16.write(0, done())
      leftf.write(1, done())
      rightf.write(1, done())
      leftb.write(0, done())
      rightb.write(0, done())
      pow32.write(0, done())
    }
    num++
  }, 500
)
