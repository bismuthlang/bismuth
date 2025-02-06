; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%ColorType = type { i32, [40 x i8] }
%Color = type { %ColorType, ptr }
%RGBColor = type { %RGBData, ptr, ptr, ptr }
%RGBData = type { [3 x i32] }
%HSVColor = type { %HSVData, ptr, ptr, ptr }
%HSVData = type { [3 x i32] }
%"(Unit + int)" = type { i32, [4 x i8] }

@0 = private unnamed_addr constant [4 x i8] c"rgb\00", align 1
@1 = private unnamed_addr constant [4 x i8] c"rgb\00", align 1
@2 = private unnamed_addr constant [16 x i8] c"Color[type=%s, \00", align 1
@3 = private unnamed_addr constant [5 x i8] c"112\0A\00", align 1
@4 = private unnamed_addr constant [19 x i8] c"r=%u, g=%u, b=%u]\0A\00", align 1
@5 = private unnamed_addr constant [19 x i8] c"r=%u, g=%u, b=%u]\0A\00", align 1
@6 = private unnamed_addr constant [5 x i8] c"133\0A\00", align 1

define %Unit @getRGBColor(ptr %0) {
entry:
  %1 = alloca %ColorType, align 8
  %2 = alloca %Color, align 8
  %3 = alloca %RGBColor, align 8
  %io.0 = alloca ptr, align 8
  %c = alloca %Color, align 8
  %4 = alloca %ColorType, align 8
  %5 = alloca %Color, align 8
  %6 = alloca %RGBColor, align 8
  %rgbDat = alloca %RGBData, align 8
  %7 = alloca %RGBData, align 8
  %data = alloca [3 x i32], align 4
  %io = alloca ptr, align 8
  store ptr %0, ptr %io, align 8
  %8 = getelementptr [3 x i32], ptr %data, i32 0, i32 0
  %9 = load ptr, ptr %io, align 8
  %10 = call ptr @_ReadLinearChannel(ptr %9)
  %11 = load i32, ptr %10, align 4
  %12 = call %Unit @free(ptr %10)
  store i32 %11, ptr %8, align 4
  %13 = getelementptr [3 x i32], ptr %data, i32 0, i32 1
  %14 = load ptr, ptr %io, align 8
  %15 = call ptr @_ReadLinearChannel(ptr %14)
  %16 = load i32, ptr %15, align 4
  %17 = call %Unit @free(ptr %15)
  store i32 %16, ptr %13, align 4
  %18 = getelementptr [3 x i32], ptr %data, i32 0, i32 2
  %19 = load ptr, ptr %io, align 8
  %20 = call ptr @_ReadLinearChannel(ptr %19)
  %21 = load i32, ptr %20, align 4
  %22 = call %Unit @free(ptr %20)
  store i32 %21, ptr %18, align 4
  %data1 = load [3 x i32], ptr %data, align 4
  %23 = getelementptr %RGBData, ptr %7, i32 0, i32 0
  store [3 x i32] %data1, ptr %23, align 4
  %24 = load %RGBData, ptr %7, align 4
  store %RGBData %24, ptr %rgbDat, align 4
  %rgbDat2 = load %RGBData, ptr %rgbDat, align 4
  %25 = getelementptr %RGBColor, ptr %6, i32 0, i32 0
  store %RGBData %rgbDat2, ptr %25, align 4
  %26 = getelementptr %RGBColor, ptr %6, i32 0, i32 1
  store ptr @"getRGBColor::#lambda", ptr %26, align 8
  %27 = getelementptr %RGBColor, ptr %6, i32 0, i32 2
  store ptr @"getRGBColor::#lambda.0", ptr %27, align 8
  %28 = getelementptr %RGBColor, ptr %6, i32 0, i32 3
  store ptr @"getRGBColor::#lambda.1", ptr %28, align 8
  %29 = load %RGBColor, ptr %6, align 8
  %30 = getelementptr %ColorType, ptr %4, i32 0, i32 0
  store i32 2, ptr %30, align 4
  %31 = getelementptr %ColorType, ptr %4, i32 0, i32 1
  store %RGBColor %29, ptr %31, align 8
  %32 = load %ColorType, ptr %4, align 4
  %33 = getelementptr %Color, ptr %5, i32 0, i32 0
  store %ColorType %32, ptr %33, align 4
  %34 = getelementptr %Color, ptr %5, i32 0, i32 1
  store ptr @"getRGBColor::#lambda.2", ptr %34, align 8
  %35 = load %Color, ptr %5, align 8
  store %Color %35, ptr %c, align 8
  %36 = call ptr @_Execute(ptr @lamePrint)
  store ptr %36, ptr %io.0, align 8
  %c3 = load %Color, ptr %c, align 8
  %37 = call ptr @malloc(i32 56)
  store %Color %c3, ptr %37, align 8
  %38 = load ptr, ptr %io.0, align 8
  %39 = call %Unit @_WriteChannel(ptr %38, ptr %37)
  %rgbDat4 = load %RGBData, ptr %rgbDat, align 4
  %40 = getelementptr %RGBColor, ptr %3, i32 0, i32 0
  store %RGBData %rgbDat4, ptr %40, align 4
  %41 = getelementptr %RGBColor, ptr %3, i32 0, i32 1
  store ptr @"getRGBColor::#lambda.3", ptr %41, align 8
  %42 = getelementptr %RGBColor, ptr %3, i32 0, i32 2
  store ptr @"getRGBColor::#lambda.4", ptr %42, align 8
  %43 = getelementptr %RGBColor, ptr %3, i32 0, i32 3
  store ptr @"getRGBColor::#lambda.5", ptr %43, align 8
  %44 = load %RGBColor, ptr %3, align 8
  %45 = getelementptr %ColorType, ptr %1, i32 0, i32 0
  store i32 2, ptr %45, align 4
  %46 = getelementptr %ColorType, ptr %1, i32 0, i32 1
  store %RGBColor %44, ptr %46, align 8
  %47 = load %ColorType, ptr %1, align 4
  %48 = getelementptr %Color, ptr %2, i32 0, i32 0
  store %ColorType %47, ptr %48, align 4
  %49 = getelementptr %Color, ptr %2, i32 0, i32 1
  store ptr @"getRGBColor::#lambda.6", ptr %49, align 8
  %50 = load %Color, ptr %2, align 8
  %51 = call ptr @malloc(i32 56)
  store %Color %50, ptr %51, align 8
  %52 = load ptr, ptr %io, align 8
  %53 = call %Unit @_WriteChannel(ptr %52, ptr %51)
  ret %Unit zeroinitializer
}

define %Unit @lamePrint(ptr %0) {
entry:
  %getVal = alloca ptr, align 8
  %getSat = alloca ptr, align 8
  %getHue = alloca ptr, align 8
  %hsv = alloca %HSVColor, align 8
  %getBlue = alloca ptr, align 8
  %getGreen = alloca ptr, align 8
  %getRed = alloca ptr, align 8
  %rgb = alloca %RGBColor, align 8
  %1 = alloca %ColorType, align 8
  %lam = alloca ptr, align 8
  %c = alloca %Color, align 8
  %io = alloca ptr, align 8
  store ptr %0, ptr %io, align 8
  %2 = load ptr, ptr %io, align 8
  %3 = call ptr @_ReadLinearChannel(ptr %2)
  %4 = load %Color, ptr %3, align 8
  %5 = call %Unit @free(ptr %3)
  store %Color %4, ptr %c, align 8
  %6 = getelementptr %Color, ptr %c, i32 0, i32 1
  %7 = load ptr, ptr %6, align 8
  store ptr %7, ptr %lam, align 8
  %8 = getelementptr %Color, ptr %c, i32 0, i32 0
  %9 = load %ColorType, ptr %8, align 4
  %lam1 = load ptr, ptr %lam, align 8
  %10 = call ptr %lam1(%ColorType %9)
  %11 = call i32 (ptr, ...) @printf(ptr @2, ptr %10)
  %12 = call i32 (ptr, ...) @printf(ptr @3)
  %13 = getelementptr %Color, ptr %c, i32 0, i32 0
  %14 = load %ColorType, ptr %13, align 4
  store %ColorType %14, ptr %1, align 4
  %15 = getelementptr %ColorType, ptr %1, i32 0, i32 0
  %16 = load i32, ptr %15, align 4
  switch i32 %16, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %entry
  %17 = getelementptr %ColorType, ptr %1, i32 0, i32 1
  %18 = load %RGBColor, ptr %17, align 8
  store %RGBColor %18, ptr %rgb, align 8
  %19 = getelementptr %RGBColor, ptr %rgb, i32 0, i32 1
  %20 = load ptr, ptr %19, align 8
  store ptr %20, ptr %getRed, align 8
  %21 = getelementptr %RGBColor, ptr %rgb, i32 0, i32 2
  %22 = load ptr, ptr %21, align 8
  store ptr %22, ptr %getGreen, align 8
  %23 = getelementptr %RGBColor, ptr %rgb, i32 0, i32 3
  %24 = load ptr, ptr %23, align 8
  store ptr %24, ptr %getBlue, align 8
  %25 = getelementptr %RGBColor, ptr %rgb, i32 0, i32 0
  %26 = load %RGBData, ptr %25, align 4
  %getRed2 = load ptr, ptr %getRed, align 8
  %27 = call i32 %getRed2(%RGBData %26)
  %28 = getelementptr %RGBColor, ptr %rgb, i32 0, i32 0
  %29 = load %RGBData, ptr %28, align 4
  %getBlue3 = load ptr, ptr %getBlue, align 8
  %30 = call i32 %getBlue3(%RGBData %29)
  %31 = getelementptr %RGBColor, ptr %rgb, i32 0, i32 0
  %32 = load %RGBData, ptr %31, align 4
  %getGreen4 = load ptr, ptr %getGreen, align 8
  %33 = call i32 %getGreen4(%RGBData %32)
  %34 = call i32 (ptr, ...) @printf(ptr @4, i32 %27, i32 %30, i32 %33)
  br label %match-cont

tagBranch1:                                       ; preds = %entry
  %35 = getelementptr %ColorType, ptr %1, i32 0, i32 1
  %36 = load %HSVColor, ptr %35, align 8
  store %HSVColor %36, ptr %hsv, align 8
  %37 = getelementptr %HSVColor, ptr %hsv, i32 0, i32 1
  %38 = load ptr, ptr %37, align 8
  store ptr %38, ptr %getHue, align 8
  %39 = getelementptr %HSVColor, ptr %hsv, i32 0, i32 2
  %40 = load ptr, ptr %39, align 8
  store ptr %40, ptr %getSat, align 8
  %41 = getelementptr %HSVColor, ptr %hsv, i32 0, i32 3
  %42 = load ptr, ptr %41, align 8
  store ptr %42, ptr %getVal, align 8
  %43 = getelementptr %HSVColor, ptr %hsv, i32 0, i32 0
  %44 = load %HSVData, ptr %43, align 4
  %getHue5 = load ptr, ptr %getHue, align 8
  %45 = call i32 %getHue5(%HSVData %44)
  %46 = getelementptr %HSVColor, ptr %hsv, i32 0, i32 0
  %47 = load %HSVData, ptr %46, align 4
  %getSat6 = load ptr, ptr %getSat, align 8
  %48 = call i32 %getSat6(%HSVData %47)
  %49 = getelementptr %HSVColor, ptr %hsv, i32 0, i32 0
  %50 = load %HSVData, ptr %49, align 4
  %getVal7 = load ptr, ptr %getVal, align 8
  %51 = call i32 %getVal7(%HSVData %50)
  %52 = call i32 (ptr, ...) @printf(ptr @5, i32 %45, i32 %48, i32 %51)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch1, %tagBranch2, %entry
  %53 = call i32 (ptr, ...) @printf(ptr @6)
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %io2 = alloca ptr, align 8
  %col = alloca %Color, align 8
  %io = alloca ptr, align 8
  %rgb = alloca %RGBColor, align 8
  %hsv = alloca %HSVColor, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @_Execute(ptr @getRGBColor)
  store ptr %1, ptr %io, align 8
  %2 = call ptr @malloc(i32 4)
  store i32 58, ptr %2, align 4
  %3 = load ptr, ptr %io, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  %5 = call ptr @malloc(i32 4)
  store i32 166, ptr %5, align 4
  %6 = load ptr, ptr %io, align 8
  %7 = call %Unit @_WriteChannel(ptr %6, ptr %5)
  %8 = call ptr @malloc(i32 4)
  store i32 63, ptr %8, align 4
  %9 = load ptr, ptr %io, align 8
  %10 = call %Unit @_WriteChannel(ptr %9, ptr %8)
  %11 = load ptr, ptr %io, align 8
  %12 = call ptr @_ReadLinearChannel(ptr %11)
  %13 = load %Color, ptr %12, align 8
  %14 = call %Unit @free(ptr %12)
  store %Color %13, ptr %col, align 8
  %15 = call ptr @_Execute(ptr @lamePrint)
  store ptr %15, ptr %io2, align 8
  %col1 = load %Color, ptr %col, align 8
  %16 = call ptr @malloc(i32 56)
  store %Color %col1, ptr %16, align 8
  %17 = load ptr, ptr %io2, align 8
  %18 = call %Unit @_WriteChannel(ptr %17, ptr %16)
  %19 = call ptr @malloc(i32 4)
  store i32 0, ptr %19, align 4
  %20 = load ptr, ptr %c, align 8
  %21 = call %Unit @_WriteChannel(ptr %20, ptr %19)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

define private %Unit @"getRGBColor::getChannel"(ptr %0) {
entry:
  %i = alloca i32, align 4
  %u = alloca %Unit, align 8
  %1 = alloca %"(Unit + int)", align 8
  %2 = alloca %"(Unit + int)", align 8
  %3 = alloca %"(Unit + int)", align 8
  %channels = alloca [3 x i32], align 4
  %d = alloca %RGBData, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %4 = load ptr, ptr %c, align 8
  %5 = call ptr @_ReadLinearChannel(ptr %4)
  %6 = load %RGBData, ptr %5, align 4
  %7 = call %Unit @free(ptr %5)
  store %RGBData %6, ptr %d, align 4
  %8 = getelementptr %RGBData, ptr %d, i32 0, i32 0
  %9 = load [3 x i32], ptr %8, align 4
  store [3 x i32] %9, ptr %channels, align 4
  %10 = load ptr, ptr %c, align 8
  %11 = call ptr @_ReadLinearChannel(ptr %10)
  %12 = load i32, ptr %11, align 4
  %13 = call %Unit @free(ptr %11)
  %14 = icmp slt i32 %12, 3
  br i1 %14, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %entry
  %15 = icmp sge i32 %12, 0
  br i1 %15, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %16 = getelementptr [3 x i32], ptr %channels, i32 0, i32 %12
  %17 = load i32, ptr %16, align 4
  %18 = getelementptr %"(Unit + int)", ptr %3, i32 0, i32 0
  store i32 2, ptr %18, align 4
  %19 = getelementptr %"(Unit + int)", ptr %3, i32 0, i32 1
  store i32 %17, ptr %19, align 4
  %20 = load %"(Unit + int)", ptr %3, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %entry
  %21 = getelementptr %"(Unit + int)", ptr %2, i32 0, i32 0
  store i32 1, ptr %21, align 4
  %22 = getelementptr %"(Unit + int)", ptr %2, i32 0, i32 1
  store %Unit zeroinitializer, ptr %22, align 1
  %23 = load %"(Unit + int)", ptr %2, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + int)" [ %20, %accessGTZ ], [ %23, %accessBad ]
  store %"(Unit + int)" %arrayAccess, ptr %1, align 4
  %24 = getelementptr %"(Unit + int)", ptr %1, i32 0, i32 0
  %25 = load i32, ptr %24, align 4
  switch i32 %25, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %accessAfter
  %26 = getelementptr %"(Unit + int)", ptr %1, i32 0, i32 1
  %27 = load %Unit, ptr %26, align 1
  store %Unit %27, ptr %u, align 1
  %28 = sub nsw i32 0, 1
  %29 = call ptr @malloc(i32 4)
  store i32 %28, ptr %29, align 4
  %30 = load ptr, ptr %c, align 8
  %31 = call %Unit @_WriteChannel(ptr %30, ptr %29)
  br label %match-cont

tagBranch2:                                       ; preds = %accessAfter
  %32 = getelementptr %"(Unit + int)", ptr %1, i32 0, i32 1
  %33 = load i32, ptr %32, align 4
  store i32 %33, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %34 = call ptr @malloc(i32 4)
  store i32 %i1, ptr %34, align 4
  %35 = load ptr, ptr %c, align 8
  %36 = call %Unit @_WriteChannel(ptr %35, ptr %34)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %accessAfter
  ret %Unit zeroinitializer
}

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

define private i32 @"getRGBColor::#lambda"(%RGBData %0) {
entry:
  %io = alloca ptr, align 8
  %d = alloca %RGBData, align 8
  store %RGBData %0, ptr %d, align 4
  %1 = call ptr @_Execute(ptr @"getRGBColor::getChannel")
  store ptr %1, ptr %io, align 8
  %d1 = load %RGBData, ptr %d, align 4
  %2 = call ptr @malloc(i32 12)
  store %RGBData %d1, ptr %2, align 4
  %3 = load ptr, ptr %io, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  %5 = call ptr @malloc(i32 4)
  store i32 0, ptr %5, align 4
  %6 = load ptr, ptr %io, align 8
  %7 = call %Unit @_WriteChannel(ptr %6, ptr %5)
  %8 = load ptr, ptr %io, align 8
  %9 = call ptr @_ReadLinearChannel(ptr %8)
  %10 = load i32, ptr %9, align 4
  %11 = call %Unit @free(ptr %9)
  ret i32 %10
}

declare ptr @_Execute(ptr)

define private i32 @"getRGBColor::#lambda.0"(%RGBData %0) {
entry:
  %io = alloca ptr, align 8
  %d = alloca %RGBData, align 8
  store %RGBData %0, ptr %d, align 4
  %1 = call ptr @_Execute(ptr @"getRGBColor::getChannel")
  store ptr %1, ptr %io, align 8
  %d1 = load %RGBData, ptr %d, align 4
  %2 = call ptr @malloc(i32 12)
  store %RGBData %d1, ptr %2, align 4
  %3 = load ptr, ptr %io, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  %5 = call ptr @malloc(i32 4)
  store i32 1, ptr %5, align 4
  %6 = load ptr, ptr %io, align 8
  %7 = call %Unit @_WriteChannel(ptr %6, ptr %5)
  %8 = load ptr, ptr %io, align 8
  %9 = call ptr @_ReadLinearChannel(ptr %8)
  %10 = load i32, ptr %9, align 4
  %11 = call %Unit @free(ptr %9)
  ret i32 %10
}

define private i32 @"getRGBColor::#lambda.1"(%RGBData %0) {
entry:
  %io = alloca ptr, align 8
  %d = alloca %RGBData, align 8
  store %RGBData %0, ptr %d, align 4
  %1 = call ptr @_Execute(ptr @"getRGBColor::getChannel")
  store ptr %1, ptr %io, align 8
  %d1 = load %RGBData, ptr %d, align 4
  %2 = call ptr @malloc(i32 12)
  store %RGBData %d1, ptr %2, align 4
  %3 = load ptr, ptr %io, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  %5 = call ptr @malloc(i32 4)
  store i32 2, ptr %5, align 4
  %6 = load ptr, ptr %io, align 8
  %7 = call %Unit @_WriteChannel(ptr %6, ptr %5)
  %8 = load ptr, ptr %io, align 8
  %9 = call ptr @_ReadLinearChannel(ptr %8)
  %10 = load i32, ptr %9, align 4
  %11 = call %Unit @free(ptr %9)
  ret i32 %10
}

define private ptr @"getRGBColor::#lambda.2"(%ColorType %0) {
entry:
  %c = alloca %ColorType, align 8
  store %ColorType %0, ptr %c, align 4
  ret ptr @0
}

define private i32 @"getRGBColor::#lambda.3"(%RGBData %0) {
entry:
  %io = alloca ptr, align 8
  %d = alloca %RGBData, align 8
  store %RGBData %0, ptr %d, align 4
  %1 = call ptr @_Execute(ptr @"getRGBColor::getChannel")
  store ptr %1, ptr %io, align 8
  %d1 = load %RGBData, ptr %d, align 4
  %2 = call ptr @malloc(i32 12)
  store %RGBData %d1, ptr %2, align 4
  %3 = load ptr, ptr %io, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  %5 = call ptr @malloc(i32 4)
  store i32 0, ptr %5, align 4
  %6 = load ptr, ptr %io, align 8
  %7 = call %Unit @_WriteChannel(ptr %6, ptr %5)
  %8 = load ptr, ptr %io, align 8
  %9 = call ptr @_ReadLinearChannel(ptr %8)
  %10 = load i32, ptr %9, align 4
  %11 = call %Unit @free(ptr %9)
  ret i32 %10
}

define private i32 @"getRGBColor::#lambda.4"(%RGBData %0) {
entry:
  %io = alloca ptr, align 8
  %d = alloca %RGBData, align 8
  store %RGBData %0, ptr %d, align 4
  %1 = call ptr @_Execute(ptr @"getRGBColor::getChannel")
  store ptr %1, ptr %io, align 8
  %d1 = load %RGBData, ptr %d, align 4
  %2 = call ptr @malloc(i32 12)
  store %RGBData %d1, ptr %2, align 4
  %3 = load ptr, ptr %io, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  %5 = call ptr @malloc(i32 4)
  store i32 1, ptr %5, align 4
  %6 = load ptr, ptr %io, align 8
  %7 = call %Unit @_WriteChannel(ptr %6, ptr %5)
  %8 = load ptr, ptr %io, align 8
  %9 = call ptr @_ReadLinearChannel(ptr %8)
  %10 = load i32, ptr %9, align 4
  %11 = call %Unit @free(ptr %9)
  ret i32 %10
}

define private i32 @"getRGBColor::#lambda.5"(%RGBData %0) {
entry:
  %io = alloca ptr, align 8
  %d = alloca %RGBData, align 8
  store %RGBData %0, ptr %d, align 4
  %1 = call ptr @_Execute(ptr @"getRGBColor::getChannel")
  store ptr %1, ptr %io, align 8
  %d1 = load %RGBData, ptr %d, align 4
  %2 = call ptr @malloc(i32 12)
  store %RGBData %d1, ptr %2, align 4
  %3 = load ptr, ptr %io, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  %5 = call ptr @malloc(i32 4)
  store i32 2, ptr %5, align 4
  %6 = load ptr, ptr %io, align 8
  %7 = call %Unit @_WriteChannel(ptr %6, ptr %5)
  %8 = load ptr, ptr %io, align 8
  %9 = call ptr @_ReadLinearChannel(ptr %8)
  %10 = load i32, ptr %9, align 4
  %11 = call %Unit @free(ptr %9)
  ret i32 %10
}

define private ptr @"getRGBColor::#lambda.6"(%ColorType %0) {
entry:
  %c = alloca %ColorType, align 8
  store %ColorType %0, ptr %c, align 4
  ret ptr @1
}
