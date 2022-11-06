![](http://www.dalesoft.ru/images/projects/mescalero.jpg)

# Mescalero

The repository contains the Mescalero library and everything you need to use it

## Why Mescalero?

Mescalero is a free library for small graphics projects that simplifies working with ICC and RAW. It hides the unnecessary details of professional libraries and creates an interface that allows you to replace the used professional libraries without changing the code base of your project

1. If you need the essential of graphics only, the library simplifies the connection of third-party libraries. You link only one library<br>
2. You can easily replace any part of Mescalero with another graphical library without changing your codebase
3. The library is licensed under Apache 2.0, which allows you not to "inherit" the rules of copyleft licenses ([L]GPL etc) and not to disclose the source code of your programs

## Why is it named like that?

Mescalero is a main subdivision of the Apache Native American nation.

## What about the License?

Mescalero is licensed under the Apache License, Version 2.0<br>
You may not use it except in compliance with the License. You may obtain a copy of the License at:<br><br>
http://www.apache.org/licenses/LICENSE-2.0<br>

## Project files

mscl_lld.pro - QT 5 project (LittleCMS as ICC, LibRAW as RAW). lcms2.dll and libraw.dll are required<br>
mscl_lls.pro - QT 5 project (LittleCMS as ICC, LibRAW as RAW). No additional dlls are required
