# Asteroids

An asteroids clone built in the Petrichor Engine

## Architecture

### GENERAL MODULES
| Module Name | Description                                                                                                                                    |
|-------------|------------------------------------------------------------------------------------------------------------------------------------------------|
| Common      | This contains all the code for general purpose stuff like memory management, math, time, and colours. More stuff will probably be added later. |
| Core        | This contains all the code for engine specific stuff, see **Core** table for more details on each module.                                      |
| Game        | This contains specifically all game code, so pretty much just the game state struct.                                                           |
| Vendors     | See the **Vendors** table for the third party libraries used.                                                                                  |

### CORE Table
| Module Name | Description                                                                                                                                                           |
|-------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Audio       | Handles the audio                                                                                                                                                     |
| Events      | Event Queue system                                                                                                                                                    |
| Filesystem  | Loading, and Saving - serialisation handle where the data is created (no general serialise functions)                                                                 |
| Graphics    | General interface for interacting with Renderering APIs - currently targeting Vulkan and DX12, possible software renderer support in future and we will see otherwise |
| Input       | Basic HID system, for keyboard and mouse - and controllers                                                                                                            |
| Platform    | Main entry point into the application and general platform specific implementations                                                                                   |


### VENDORS Table
| Module Name | Description                                   |
|-------------|-----------------------------------------------|
| GLM         | Math library                                  |
| MiniAudio   | Audio library                                 |
| STB         | Image Loading / Creation / Processing Library |