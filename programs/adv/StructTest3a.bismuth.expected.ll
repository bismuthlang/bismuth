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
  %c3 = load %Color, ptr %c, align 8
  %36 = call i32 @lamePrint(%Color %c3)
  %rgbDat4 = load %RGBData, ptr %rgbDat, align 4
  %37 = getelementptr %RGBColor, ptr %3, i32 0, i32 0
  store %RGBData %rgbDat4, ptr %37, align 4
  %38 = getelementptr %RGBColor, ptr %3, i32 0, i32 1
  store ptr @"getRGBColor::#lambda.3", ptr %38, align 8
  %39 = getelementptr %RGBColor, ptr %3, i32 0, i32 2
  store ptr @"getRGBColor::#lambda.4", ptr %39, align 8
  %40 = getelementptr %RGBColor, ptr %3, i32 0, i32 3
  store ptr @"getRGBColor::#lambda.5", ptr %40, align 8
  %41 = load %RGBColor, ptr %3, align 8
  %42 = getelementptr %ColorType, ptr %1, i32 0, i32 0
  store i32 2, ptr %42, align 4
  %43 = getelementptr %ColorType, ptr %1, i32 0, i32 1
  store %RGBColor %41, ptr %43, align 8
  %44 = load %ColorType, ptr %1, align 4
  %45 = getelementptr %Color, ptr %2, i32 0, i32 0
  store %ColorType %44, ptr %45, align 4
  %46 = getelementptr %Color, ptr %2, i32 0, i32 1
  store ptr @"getRGBColor::#lambda.6", ptr %46, align 8
  %47 = load %Color, ptr %2, align 8
  %48 = call ptr @malloc(i32 56)
  store %Color %47, ptr %48, align 8
  %49 = load ptr, ptr %io, align 8
  %50 = call %Unit @_WriteChannel(ptr %49, ptr %48)
  ret %Unit zeroinitializer
}

define i32 @lamePrint(%Color %0) {
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
  store %Color %0, ptr %c, align 8
  %2 = getelementptr %Color, ptr %c, i32 0, i32 1
  %3 = load ptr, ptr %2, align 8
  store ptr %3, ptr %lam, align 8
  %4 = getelementptr %Color, ptr %c, i32 0, i32 0
  %5 = load %ColorType, ptr %4, align 4
  %lam1 = load ptr, ptr %lam, align 8
  %6 = call ptr %lam1(%ColorType %5)
  %7 = call i32 (ptr, ...) @printf(ptr @2, ptr %6)
  %8 = call i32 (ptr, ...) @printf(ptr @3)
  %9 = getelementptr %Color, ptr %c, i32 0, i32 0
  %10 = load %ColorType, ptr %9, align 4
  store %ColorType %10, ptr %1, align 4
  %11 = getelementptr %ColorType, ptr %1, i32 0, i32 0
  %12 = load i32, ptr %11, align 4
  switch i32 %12, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %entry
  %13 = getelementptr %ColorType, ptr %1, i32 0, i32 1
  %14 = load %RGBColor, ptr %13, align 8
  store %RGBColor %14, ptr %rgb, align 8
  %15 = getelementptr %RGBColor, ptr %rgb, i32 0, i32 1
  %16 = load ptr, ptr %15, align 8
  store ptr %16, ptr %getRed, align 8
  %17 = getelementptr %RGBColor, ptr %rgb, i32 0, i32 2
  %18 = load ptr, ptr %17, align 8
  store ptr %18, ptr %getGreen, align 8
  %19 = getelementptr %RGBColor, ptr %rgb, i32 0, i32 3
  %20 = load ptr, ptr %19, align 8
  store ptr %20, ptr %getBlue, align 8
  %21 = getelementptr %RGBColor, ptr %rgb, i32 0, i32 0
  %22 = load %RGBData, ptr %21, align 4
  %getRed2 = load ptr, ptr %getRed, align 8
  %23 = call i32 %getRed2(%RGBData %22)
  %24 = getelementptr %RGBColor, ptr %rgb, i32 0, i32 0
  %25 = load %RGBData, ptr %24, align 4
  %getBlue3 = load ptr, ptr %getBlue, align 8
  %26 = call i32 %getBlue3(%RGBData %25)
  %27 = getelementptr %RGBColor, ptr %rgb, i32 0, i32 0
  %28 = load %RGBData, ptr %27, align 4
  %getGreen4 = load ptr, ptr %getGreen, align 8
  %29 = call i32 %getGreen4(%RGBData %28)
  %30 = call i32 (ptr, ...) @printf(ptr @4, i32 %23, i32 %26, i32 %29)
  br label %match-cont

tagBranch1:                                       ; preds = %entry
  %31 = getelementptr %ColorType, ptr %1, i32 0, i32 1
  %32 = load %HSVColor, ptr %31, align 8
  store %HSVColor %32, ptr %hsv, align 8
  %33 = getelementptr %HSVColor, ptr %hsv, i32 0, i32 1
  %34 = load ptr, ptr %33, align 8
  store ptr %34, ptr %getHue, align 8
  %35 = getelementptr %HSVColor, ptr %hsv, i32 0, i32 2
  %36 = load ptr, ptr %35, align 8
  store ptr %36, ptr %getSat, align 8
  %37 = getelementptr %HSVColor, ptr %hsv, i32 0, i32 3
  %38 = load ptr, ptr %37, align 8
  store ptr %38, ptr %getVal, align 8
  %39 = getelementptr %HSVColor, ptr %hsv, i32 0, i32 0
  %40 = load %HSVData, ptr %39, align 4
  %getHue5 = load ptr, ptr %getHue, align 8
  %41 = call i32 %getHue5(%HSVData %40)
  %42 = getelementptr %HSVColor, ptr %hsv, i32 0, i32 0
  %43 = load %HSVData, ptr %42, align 4
  %getSat6 = load ptr, ptr %getSat, align 8
  %44 = call i32 %getSat6(%HSVData %43)
  %45 = getelementptr %HSVColor, ptr %hsv, i32 0, i32 0
  %46 = load %HSVData, ptr %45, align 4
  %getVal7 = load ptr, ptr %getVal, align 8
  %47 = call i32 %getVal7(%HSVData %46)
  %48 = call i32 (ptr, ...) @printf(ptr @5, i32 %41, i32 %44, i32 %47)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch1, %tagBranch2, %entry
  %49 = call i32 (ptr, ...) @printf(ptr @6)
  ret i32 0
}

define %Unit @program(ptr %0) {
entry:
  %col = alloca %Color, align 8
  %t = alloca ptr, align 8
  %rgb = alloca %RGBColor, align 8
  %hsv = alloca %HSVColor, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @_Execute(ptr @getRGBColor)
  store ptr %1, ptr %t, align 8
  %2 = call ptr @malloc(i32 4)
  store i32 58, ptr %2, align 4
  %3 = load ptr, ptr %t, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  %5 = call ptr @malloc(i32 4)
  store i32 166, ptr %5, align 4
  %6 = load ptr, ptr %t, align 8
  %7 = call %Unit @_WriteChannel(ptr %6, ptr %5)
  %8 = call ptr @malloc(i32 4)
  store i32 63, ptr %8, align 4
  %9 = load ptr, ptr %t, align 8
  %10 = call %Unit @_WriteChannel(ptr %9, ptr %8)
  %11 = load ptr, ptr %t, align 8
  %12 = call ptr @_ReadLinearChannel(ptr %11)
  %13 = load %Color, ptr %12, align 8
  %14 = call %Unit @free(ptr %12)
  store %Color %13, ptr %col, align 8
  %col1 = load %Color, ptr %col, align 8
  %15 = call i32 @lamePrint(%Color %col1)
  %16 = call ptr @malloc(i32 4)
  store i32 0, ptr %16, align 4
  %17 = load ptr, ptr %c, align 8
  %18 = call %Unit @_WriteChannel(ptr %17, ptr %16)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

define private i32 @"getRGBColor::getChannel"(%RGBData %0, i32 %1) {
entry:
  %i = alloca i32, align 4
  %u = alloca %Unit, align 8
  %2 = alloca %"(Unit + int)", align 8
  %3 = alloca %"(Unit + int)", align 8
  %4 = alloca %"(Unit + int)", align 8
  %channels = alloca [3 x i32], align 4
  %c = alloca i32, align 4
  %d = alloca %RGBData, align 8
  store %RGBData %0, ptr %d, align 4
  store i32 %1, ptr %c, align 4
  %5 = getelementptr %RGBData, ptr %d, i32 0, i32 0
  %6 = load [3 x i32], ptr %5, align 4
  store [3 x i32] %6, ptr %channels, align 4
  %c1 = load i32, ptr %c, align 4
  %7 = icmp slt i32 %c1, 3
  br i1 %7, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %entry
  %8 = icmp sge i32 %c1, 0
  br i1 %8, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %9 = getelementptr [3 x i32], ptr %channels, i32 0, i32 %c1
  %10 = load i32, ptr %9, align 4
  %11 = getelementptr %"(Unit + int)", ptr %4, i32 0, i32 0
  store i32 2, ptr %11, align 4
  %12 = getelementptr %"(Unit + int)", ptr %4, i32 0, i32 1
  store i32 %10, ptr %12, align 4
  %13 = load %"(Unit + int)", ptr %4, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %entry
  %14 = getelementptr %"(Unit + int)", ptr %3, i32 0, i32 0
  store i32 1, ptr %14, align 4
  %15 = getelementptr %"(Unit + int)", ptr %3, i32 0, i32 1
  store %Unit zeroinitializer, ptr %15, align 1
  %16 = load %"(Unit + int)", ptr %3, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + int)" [ %13, %accessGTZ ], [ %16, %accessBad ]
  store %"(Unit + int)" %arrayAccess, ptr %2, align 4
  %17 = getelementptr %"(Unit + int)", ptr %2, i32 0, i32 0
  %18 = load i32, ptr %17, align 4
  switch i32 %18, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %accessAfter
  %19 = getelementptr %"(Unit + int)", ptr %2, i32 0, i32 1
  %20 = load %Unit, ptr %19, align 1
  store %Unit %20, ptr %u, align 1
  %21 = sub nsw i32 0, 1
  ret i32 %21

tagBranch2:                                       ; preds = %accessAfter
  %22 = getelementptr %"(Unit + int)", ptr %2, i32 0, i32 1
  %23 = load i32, ptr %22, align 4
  store i32 %23, ptr %i, align 4
  %i2 = load i32, ptr %i, align 4
  ret i32 %i2

match-cont:                                       ; preds = %accessAfter
  unreachable
}

define private i32 @"getRGBColor::#lambda"(%RGBData %0) {
entry:
  %d = alloca %RGBData, align 8
  store %RGBData %0, ptr %d, align 4
  %d1 = load %RGBData, ptr %d, align 4
  %1 = call i32 @"getRGBColor::getChannel"(%RGBData %d1, i32 0)
  ret i32 %1
}

define private i32 @"getRGBColor::#lambda.0"(%RGBData %0) {
entry:
  %d = alloca %RGBData, align 8
  store %RGBData %0, ptr %d, align 4
  %d1 = load %RGBData, ptr %d, align 4
  %1 = call i32 @"getRGBColor::getChannel"(%RGBData %d1, i32 1)
  ret i32 %1
}

define private i32 @"getRGBColor::#lambda.1"(%RGBData %0) {
entry:
  %d = alloca %RGBData, align 8
  store %RGBData %0, ptr %d, align 4
  %d1 = load %RGBData, ptr %d, align 4
  %1 = call i32 @"getRGBColor::getChannel"(%RGBData %d1, i32 2)
  ret i32 %1
}

define private ptr @"getRGBColor::#lambda.2"(%ColorType %0) {
entry:
  %c = alloca %ColorType, align 8
  store %ColorType %0, ptr %c, align 4
  ret ptr @0
}

define private i32 @"getRGBColor::#lambda.3"(%RGBData %0) {
entry:
  %d = alloca %RGBData, align 8
  store %RGBData %0, ptr %d, align 4
  %d1 = load %RGBData, ptr %d, align 4
  %1 = call i32 @"getRGBColor::getChannel"(%RGBData %d1, i32 0)
  ret i32 %1
}

define private i32 @"getRGBColor::#lambda.4"(%RGBData %0) {
entry:
  %d = alloca %RGBData, align 8
  store %RGBData %0, ptr %d, align 4
  %d1 = load %RGBData, ptr %d, align 4
  %1 = call i32 @"getRGBColor::getChannel"(%RGBData %d1, i32 1)
  ret i32 %1
}

define private i32 @"getRGBColor::#lambda.5"(%RGBData %0) {
entry:
  %d = alloca %RGBData, align 8
  store %RGBData %0, ptr %d, align 4
  %d1 = load %RGBData, ptr %d, align 4
  %1 = call i32 @"getRGBColor::getChannel"(%RGBData %d1, i32 2)
  ret i32 %1
}

define private ptr @"getRGBColor::#lambda.6"(%ColorType %0) {
entry:
  %c = alloca %ColorType, align 8
  store %ColorType %0, ptr %c, align 4
  ret ptr @1
}

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_Execute(ptr)
