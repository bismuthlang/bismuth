; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%HSVColor = type { %HSVData }
%HSVData = type { i32 }
%RGBColor = type { %RGBData }
%RGBData = type { i32 }
%ColorType = type { i32, [4 x i8] }
%Color = type { %ColorType }

@0 = private unnamed_addr constant [10 x i8] c"DEBUG=%u\0A\00", align 1
@1 = private unnamed_addr constant [7 x i8] c"r=%u]\0A\00", align 1
@2 = private unnamed_addr constant [5 x i8] c"hsv\0A\00", align 1

define %Unit @getRGBColor(ptr %0) {
entry:
  %hsv = alloca %HSVColor, align 8
  %rgb = alloca %RGBColor, align 8
  %1 = alloca %ColorType, align 8
  %c = alloca %Color, align 8
  %2 = alloca %ColorType, align 8
  %3 = alloca %Color, align 8
  %4 = alloca %RGBColor, align 8
  %ct = alloca %ColorType, align 8
  %5 = alloca %RGBColor, align 8
  %rgbDat = alloca %RGBData, align 8
  %6 = alloca %RGBData, align 8
  %r = alloca i32, align 4
  %io = alloca ptr, align 8
  store ptr %0, ptr %io, align 8
  %7 = load ptr, ptr %io, align 8
  %8 = call ptr @_ReadLinearChannel(ptr %7)
  %9 = load i32, ptr %8, align 4
  %10 = call %Unit @free(ptr %8)
  store i32 %9, ptr %r, align 4
  %r1 = load i32, ptr %r, align 4
  %11 = getelementptr %RGBData, ptr %6, i32 0, i32 0
  store i32 %r1, ptr %11, align 4
  %12 = load %RGBData, ptr %6, align 4
  store %RGBData %12, ptr %rgbDat, align 4
  %rgbDat2 = load %RGBData, ptr %rgbDat, align 4
  %13 = getelementptr %RGBColor, ptr %5, i32 0, i32 0
  store %RGBData %rgbDat2, ptr %13, align 4
  %14 = load %RGBColor, ptr %5, align 4
  %15 = getelementptr %ColorType, ptr %ct, i32 0, i32 0
  store i32 2, ptr %15, align 4
  %16 = getelementptr %ColorType, ptr %ct, i32 0, i32 1
  store %RGBColor %14, ptr %16, align 4
  %rgbDat3 = load %RGBData, ptr %rgbDat, align 4
  %17 = getelementptr %RGBColor, ptr %4, i32 0, i32 0
  store %RGBData %rgbDat3, ptr %17, align 4
  %18 = load %RGBColor, ptr %4, align 4
  %19 = getelementptr %ColorType, ptr %2, i32 0, i32 0
  store i32 2, ptr %19, align 4
  %20 = getelementptr %ColorType, ptr %2, i32 0, i32 1
  store %RGBColor %18, ptr %20, align 4
  %21 = load %ColorType, ptr %2, align 4
  %22 = getelementptr %Color, ptr %3, i32 0, i32 0
  store %ColorType %21, ptr %22, align 4
  %23 = load %Color, ptr %3, align 4
  store %Color %23, ptr %c, align 4
  %24 = getelementptr %Color, ptr %c, i32 0, i32 0
  %25 = load %ColorType, ptr %24, align 4
  store %ColorType %25, ptr %1, align 4
  %26 = getelementptr %ColorType, ptr %1, i32 0, i32 0
  %27 = load i32, ptr %26, align 4
  switch i32 %27, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %entry
  %28 = getelementptr %ColorType, ptr %1, i32 0, i32 1
  %29 = load %RGBColor, ptr %28, align 4
  store %RGBColor %29, ptr %rgb, align 4
  %30 = call i32 (ptr, ...) @printf(ptr @0, i32 0)
  %31 = getelementptr %RGBColor, ptr %rgb, i32 0, i32 0, i32 0
  %32 = load i32, ptr %31, align 4
  %33 = call i32 (ptr, ...) @printf(ptr @1, i32 %32)
  br label %match-cont

tagBranch1:                                       ; preds = %entry
  %34 = getelementptr %ColorType, ptr %1, i32 0, i32 1
  %35 = load %HSVColor, ptr %34, align 4
  store %HSVColor %35, ptr %hsv, align 4
  %36 = call i32 (ptr, ...) @printf(ptr @2)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch1, %tagBranch2, %entry
  %c4 = load %Color, ptr %c, align 4
  %37 = call ptr @malloc(i32 8)
  store %Color %c4, ptr %37, align 4
  %38 = load ptr, ptr %io, align 8
  %39 = call %Unit @_WriteChannel(ptr %38, ptr %37)
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %t = alloca %Color, align 8
  %chan = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @_Execute(ptr @getRGBColor)
  store ptr %1, ptr %chan, align 8
  %2 = call ptr @malloc(i32 4)
  store i32 128, ptr %2, align 4
  %3 = load ptr, ptr %chan, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  %5 = load ptr, ptr %chan, align 8
  %6 = call ptr @_ReadLinearChannel(ptr %5)
  %7 = load %Color, ptr %6, align 4
  %8 = call %Unit @free(ptr %6)
  store %Color %7, ptr %t, align 4
  %9 = call ptr @malloc(i32 4)
  store i32 0, ptr %9, align 4
  %10 = load ptr, ptr %c, align 8
  %11 = call %Unit @_WriteChannel(ptr %10, ptr %9)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_Execute(ptr)
