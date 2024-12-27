---
title: Usage Without Plugin
layout: home
nav_order: 6
---

# Usage without Plugin

* * *

You don't necessarily need this plugin. If you don't want the ease of having dropdowns for each icon, or maybe you only want one icon in one style, you can follow this method:

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