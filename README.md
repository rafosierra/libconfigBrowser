# libconfig Browser

GUI Browser for config files using the [libconfig++](http://www.hyperrealm.com/libconfig/) library.

This is a very simple C++ program that displays all settings within a configuration file.
Besides displaying each setting, its type, value, and path are also shown.

Here is a screenshot of the main window:
<img src= "docs/main-screenshot_jp.png"/>

I personally use it to verify the structure and contents of my configuration files.

Built using Qt5 under Ubuntu Linux (20.04)

## Requeriments

- libconfig++ (tested with version 1.5)
- Qt5 (tested with version 5.12.8)
 
## Building
QtCreator is not necessary to build.
Just run the `devtools/configure` script from the project's root directory. A `build` directory will be created with a `Makefile`
```
devtools/configure
cd build
make
```

Alternatively, you can import it into QtCreator.

## I18n

This program includes a basic support for UI internationalization. Japanese translation is included.

To update the translations, edit the .ts files and run the `devtools/translate.sh` script.
```
devtools/translate.sh
```

## License
GPLv3
