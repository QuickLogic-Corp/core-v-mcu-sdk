# core-v-mcu-sdk
Eclipse+FreeRTOS SDK for core-v-mcu

## Background
The purpose of this repo is to hold the common files that are shared among many applications.  THe idea is that a developer will load this repo into their workspace, and then create (or load) other projects that contain the application specific code.  Those projects will use the library files that is the output of this project to access the common functions.

A example workspace after loading both the SDK and the core-v-mcu-cli-test application is:
![FileStructure](./images/FileStructure.png)

The cli-test project has the following items:

| Folder/File       | Purpose |
| ----------        | ------- |
| Includes          | application specific include files |
| app               | application specific source files  |
| kernel            | the FreeRTOS kernel                   |
| appconfig.h       | global defines that configure the app |
| FreeRTOSConfig.h  | defines that configure FreeRTOS for this application |