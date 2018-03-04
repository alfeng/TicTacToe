@REM ** Install dependencies
npm install

@REM ** Install electron-rebuild
@REM npm install --save-dev electron-rebuild

@REM ** Normal build first
@REM node-gyp build

@REM ** Rebuild for same version of V8 as electron
.\node_modules\.bin\electron-rebuild -v "1.7.12"

@REM ** Build for standard Node.js, not electron
node-gyp configure
node-gyp build
node cgdv-test.js
