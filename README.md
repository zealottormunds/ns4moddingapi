<p align="center">
  <img src="https://i.imgur.com/NfJf6fi.png">
</p>

# Naruto: Storm 4 - Modding API by Zealot Tormunds

This API for Naruto Shippuden: Ultimate Ninja Storm 4 expands the possibilities of modding, allowing developers to create better and bigger mods.

## Current Features:
#### Adding new characters without replacing:
Thanks to the character limit expander, you will never have to replace a prm for another one anymore. You can add up to 65535 characters.

#### Special conditions in characters:
You can add special hardcoded conditions to your characters, like Guy's air dash, Minato's teleport awakening action, and many others.

#### Partner slots:
The API also includes a way to add partners to your characters, just like how Kiba and Akamaru work in the normal game.

#### Executable patching:
This API lets you patch any indices on NSUNS4.exe without modifying the executable itself. This is useful for big mods that require removing or editing bytes on this file, allowing modders to create simple patch files (.ns4p) to release along with their mods. The API is able to read these files at runtime and modify the executable accordingly.
#### Message management:
By using this API you will be able to replace and add message IDs to the game without modifying the MessageInfo file. This means you aren't limited by the size of MessageInfo, and instead you can add your own messages, no matter how much longer than the original they are.

## Installation:
- Download the latest release
- Extract the release in your root Naruto: Storm 4 folder (This will replace d3dcompiler_47_og if you have it)
- Profit!

## Configuring the API:
### For players:
No need to do anything at all!

### For modders:
By default, the API is configured for players instead of modders. This means that the modding console is disabled. To enable it, you need to edit the "config.ini" file located in "/Root folder of Naruto Storm 4/moddingapi/". Open the file and find the property called "EnableConsole=0". Set it as 1, and you're ready to go.

### How to create mods using the API?
You can find all documentation in the API's wiki: https://github.com/zealottormunds/ns4moddingapi/wiki

## Special thanks:
* Valant96
* Kuroha Saenoki
* Xuan Thai
* TheLeonX
