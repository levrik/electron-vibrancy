var app = require('electron').app
var BrowserWindow = require('electron').BrowserWindow
var path = require('path')

var mainWindow = null

app.on('ready', function () {
  mainWindow = new BrowserWindow({
    center: true,
    width: 1400,
    height: 900,
    minHeight: 100,
    minWidth: 100,
    transparent: true,
    frame: false,
    show: false
  })
  mainWindow.loadURL('file://' + __dirname + '/index.html')
  mainWindow.on('closed', function () { mainWindow = null })
  mainWindow.on('ready-to-show',function() {
    var nativeHandleBuffer = mainWindow.getNativeWindowHandle();
    var electronVibrancy = require(path.join(__dirname,'..','..'));

    // Whole window vibrancy with Material 0 and auto resize
    electronVibrancy.enableVibrancy(mainWindow);

    mainWindow.show();
  })
})
