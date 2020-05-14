# PngToAlfaMask
##Что бы собрать нужно
1. Разархивировать SFML-2.5.1.rar в каталог с PngToAlfaMask.slh
2. Разархивировать Release.rar в /x64/Release/ или /x64/Debug/

## Применение
./PngToAlfaMask.exe Flag Inpath OutPath
1. Flag=alfa
превратит все .png по Inpath(и ниже) в альфамаски и сохранит их в файлах OutPath/images.c и OutPath/images.h
2. Flag=png
превратит все найденные маски из Inpath/images.c в .png и сохранит их в OutPath

### Значения по умалчанию:

Flag = alfa
Inpath = путь PngToAlfaMask.exe
OutPath = Inpath
пути должны заканчиваться на '/'