# PngToAlfaMask
[ссылка на самого себя](https://github.com/AStr347/PngToAlfaMask)

## Для работы программы в Windows так же требуется переместить .dll файлы из SFML_PATH\bin к .exe файлу

## Применение
 ./PngToAlfaMask.exe Flag Inpath OutPath
1. Flag=alfa превратит все .png по Inpath(и ниже) в альфамаски и сохранит их в файлах OutPath/images.c и OutPath/images.h

2. Flag=png превратит все найденные маски из Inpath/images.c в .png и сохранит их в OutPath

### Значения по умалчанию
1. Flag = alfa
2. Inpath = путь к PngToAlfaMask.exe
3. OutPath = Inpath
