var express = require('express');
var path = require('path');
var favicon = require('serve-favicon');
var logger = require('morgan');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');

var index = require('./routes/index');
var users = require('./routes/users');

var app = express();
var gpio = require('pigpio').Gpio
var Gpio = require('onoff').Gpio
var server = require('http').Server(app);
var io = require('socket.io')(app);

app.get('/', function(req, res) {
  res.sendfile(__dirname + '/index.html');
});

io.on('connection', function(socket) {
  socket.emit('news', {
    hello: 'world'
  });
  socket.on('my other event', function(data) {
    console.log(data);
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

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

// uncomment after placing your favicon in /public
//app.use(favicon(path.join(__dirname, 'public', 'favicon.ico')));
app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
  extended: false
}));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));
app.use(express.static(path.join(__dirname, 'node_modules')));

app.use('/', index);
app.use('/users', users);

// catch 404 and forward to error handler
app.use(function(req, res, next) {
  var err = new Error('Not Found');
  err.status = 404;
  next(err);
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});

module.exports = app;
