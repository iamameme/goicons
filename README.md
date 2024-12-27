# [Google Symbols](https://fonts.google.com/icons) Icons for Unreal

This is a plugin to make it easier to work with Google Symbols icons in Unreal. 

It includes two classes:

- IconTextBlock: A child of TextBlock, this is for 2D / UMG. Drag and drop this into a Widget and you'll get all the icons!
- IconText3DActor: A child of Text3DActor, this is an actor that can be placed in a Level which renders an Icon in 3D!

## The Font Files

Google Symbols is a dynamic font, which is not supported by Unreal. As a result, fourteen different static fonts were generated from the dynamic font to give support in Unreal. These are located in Source/ThirdParty. 

## How to use these icons without this plugin

If you don't want the ease of having dropdowns for each icon, or maybe you only want one icon in one style, you can follow this method:

- Import the desired .ttf file into Unreal
- Create a TextBlock or another component/actor that supports fonts
- Set the Font Family to the font you imported
- Go to the Google Symbols website and locate the font you desire [here](https://fonts.google.com/icons)
- Find the `Code Point` for the icon (ie. `e8b6`)
- Now, this differs if in Blueprints or C++
    - If in Blueprints: 
        - Enter that unicode character into the text
    - If in C++:
        - Set the Text to the unicode character, for example, `\ue8b6`