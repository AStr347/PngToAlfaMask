# PngToAlfaMask

## Для работы программы в Windows так же требуется переместить .dll файлы из SFML_PATH\bin к .exe файлу

## Применение

```sh
 ./PngToAlfaMask.exe {Flag} {Inpath} {OutPath}
```

### Значения по умалчанию

1. Flag = alfa
2. Inpath = путь к PngToAlfaMask.exe
3. OutPath = Inpath

### Flag=`alfa`

```sh
 ./PngToAlfaMask.exe alfa {Inpath} {OutPath}
```

Превратит все `*.png` по `Inpath`(и ниже) в альфамаски и сохранит их в файлах `OutPath/images.c` и `OutPath/images.h`

### Flag=`png`

```sh
 ./PngToAlfaMask.exe png {Inpath} {OutPath}
```

Превратит все найденные маски из Inpath/images.c в .png и сохранит их в OutPath
