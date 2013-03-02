var WebSocketServer = require('websocket').server;
var http = require('http');
var gpio = require("pi-gpio");

var PIN_OE   = 5; //= 9;
var PIN_SCLK = 3;  //= 8;
var PIN_LAT  = 23; //= 14;
var PIN_A    = 24; //= 10;
var PIN_B    = 26; //= 11;
var PIN_C    = 19; //= 12;
var PIN_D    = 21; //= 13;
var PIN_R1   = 13; //= 2;
var PIN_G1   = 15; //= 3;
var PIN_B1   = 16; //= 4;
var PIN_R2   = 18; //= 5;
var PIN_G2   = 22; //= 6;
var PIN_B2   = 7;  //= 7;

var opencount = 0;

var errCallback = function(err) {
  if (err) throw err;
}

var openCallback = function(err) {
  if (err) throw err;
  opencount++;
}

function initialize() {
  gpio.open(PIN_OE, 'output', openCallback);
  gpio.open(PIN_SCLK, 'output', openCallback);
  gpio.open(PIN_LAT, 'output', openCallback);
  gpio.open(PIN_A, 'output', openCallback);
  gpio.open(PIN_B, 'output', openCallback);
  gpio.open(PIN_C, 'output', openCallback);
  gpio.open(PIN_D, 'output', openCallback);
  gpio.open(PIN_R1, 'output', openCallback);
  gpio.open(PIN_G1, 'output', openCallback);
  gpio.open(PIN_B1, 'output', openCallback);
  gpio.open(PIN_R2, 'output', openCallback);
  gpio.open(PIN_G2, 'output', openCallback);
  gpio.open(PIN_B2, 'output', openCallback);

  if (opencount != 13) {
    throw new Error("Not all pins were opened");
  }

  gpio.write(PIN_OE, 0, errCallback);
  gpio.write(PIN_SCLK, 0, errCallback);
  gpio.write(PIN_LAT, 0, errCallback);
  gpio.write(PIN_A, 0, errCallback);
  gpio.write(PIN_B, 0, errCallback);
  gpio.write(PIN_C, 0, errCallback);
  gpio.write(PIN_D, 0, errCallback);
  gpio.write(PIN_R1, 0, errCallback);
  gpio.write(PIN_G1, 0, errCallback);
  gpio.write(PIN_B1, 0, errCallback);
  gpio.write(PIN_R2, 0, errCallback);
  gpio.write(PIN_G2, 0, errCallback);
  gpio.write(PIN_B2, 0, errCallback);
}

/**
 * Push one byte of data. Two colors, one in each row.
 */
function clockInData(r1, g1, b1, r2, g2, b2) {
  gpio.write(PIN_R1, r1, errCallback);
  gpio.write(PIN_G1, g1, errCallback);
  gpio.write(PIN_B1, b1, errCallback);
  gpio.write(PIN_R2, r2, errCallback);
  gpio.write(PIN_G2, g2, errCallback);
  gpio.write(PIN_B2, b2, errCallback);

  gpio.write(PIN_SCLK, 0, errCallback);
  gpio.write(PIN_SCLK, 1, errCallback);
}

/** 
 * Select a row. row must be an integer.
 */
function selectRow(row) {
  gpio.write(PIN_A, row & 0x01, errCallback);
  gpio.write(PIN_B, row & 0x02, errCallback);
  gpio.write(PIN_C, row & 0x04, errCallback);
  gpio.write(PIN_D, row & 0x08, errCallback);
}


var server = http.createServer(function(request, response) {
    // process HTTP request. Since we're writing just WebSockets server
    // we don't have to implement anything.
});

server.listen(1337, function() { });

// create the server
wsServer = new WebSocketServer({
    httpServer: server
});

// WebSocket server
wsServer.on('request', function(request) {
    var connection = request.accept(null, request.origin);

    // This is the most important callback for us, we'll handle
    // all messages from users here.
    connection.on('message', function(message) {
        if (message.type === 'utf8') {
          // process WebSocket message
          initialize();

          gpio.write(PIN_LAT, 0, errCallback);

          selectRow(0);

          for (var i = 0; i < 32; i++) {
            clockInData(1,1,0,0,1,0);
          }

          gpio.write(PIN_LAT, 1, errCallback);
        }
    });

    connection.on('close', function(connection) {
        // close user connection
    });
});
