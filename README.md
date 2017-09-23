# electron-vibrancy-windows

This module is intended to give an [Electron](https://github.com/electron/electron) BrowserWindow blur on its behind on Windows. Electron does not support 'blur behind' from a transparent window on Windows and this module uses native API calls to achieve the effect.

![](http://i.imgur.com/0sRPzpn.png)

## Running

Since this is a native addon, you will need your platforms build tools. Visual Studio etc. Also Python for `node-gyp`.

```
git clone https://github.com/levrik/electron-vibrancy-windows
cd electron-vibrancy-windows
yarn install
cd spec/app # Go to sample app
electron . # electron --version should be 1.7.6
```

To rebuild again:

```
yarn conf
yarn rebuild
```

Also available through NPM **(not yet)**.

```
yarn add electron-vibrancy-windows
```

To run tests see [scripts/ci](https://github.com/arkenthera/electron-vibrancy/blob/master/scripts/ci.sh)

## Current Supported Platforms
- Windows 10 (stable)

## Things to note
- `BrowserWindow` must be transparent. (`transparent:true`)
- Requires Windows 10 or higher.
- If you get `A dynamic link library (DLL) initialization routine failed.` error, it means that the module isn't compiled against Electron or compiled against the wrong version. 

## API
There are several methods depending on what you want to do and what platform you are on.

### `enableVibrancy(window)` _win_

Returns `Bool`.

* `window` `BrowserWindow` instance

Enables or disables vibrancy for the **WHOLE** window.

### `disableVibrancy(window)` _win_

Disables Vibrancy completely.

* `window` `BrowserWindow` instance

## How to use

```
// mainWindow with show: false
mainWindow.on('ready-to-show',function() {
  var electronVibrancy = require('..');
  
  electronVibrancy.enableVibrancy(mainWindow);

  electronVibrancy.disableVibrancy(mainWindow);

  mainWindow.show();
});

```

## Platform notice

On **Windows 10** the addon uses ```SetWindowCompositionAttribute```, which is an undocumented API, which means it can be changed by Microsoft any time and break the functionality.

## License

This project is under MIT.
See [LICENSE](https://github.com/levrik/electron-vibrancy-windows/blob/master/LICENSE)
