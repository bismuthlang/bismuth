; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%RGBData = type { [3 x i32] }
%Unit = type {}
%"(Unit + int)" = type { i32, [4 x i8] }
%ColorType = type { i32, [40 x i8] }
%Color = type { %ColorType, ptr }
%RGBColor = type { %RGBData, ptr, ptr, ptr }
%HSVColor = type { %HSVData, ptr, ptr, ptr }
%HSVData = type { [3 x i32] }

@0 = private unnamed_addr constant [4 x i8] c"rgb\00", align 1
@1 = private unnamed_addr constant [16 x i8] c"Color[type=%s, \00", align 1
@2 = private unnamed_addr constant [19 x i8] c"r=%u, g=%u, b=%u]\0A\00", align 1
@3 = private unnamed_addr constant [19 x i8] c"r=%u, g=%u, b=%u]\0A\00", align 1

define i32 @getChannel(%RGBData %0, i32 %1) {
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

define %Unit @getRGBColor(ptr %0) {
entry:
  %1 = alloca %ColorType, align 8
  %2 = alloca %Color, align 8
  %3 = alloca %RGBColor, align 8
  %rgbDat = alloca %RGBData, align 8
  %4 = alloca %RGBData, align 8
  %data = alloca [3 x i32], align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %5 = getelementptr [3 x i32], ptr %data, i32 0, i32 0
  %6 = load ptr, ptr %c, align 8
  %7 = call ptr @_ReadLinearChannel(ptr %6)
  %8 = load i32, ptr %7, align 4
  %9 = call %Unit @free(ptr %7)
  store i32 %8, ptr %5, align 4
  %10 = getelementptr [3 x i32], ptr %data, i32 0, i32 1
  %11 = load ptr, ptr %c, align 8
  %12 = call ptr @_ReadLinearChannel(ptr %11)
  %13 = load i32, ptr %12, align 4
  %14 = call %Unit @free(ptr %12)
  store i32 %13, ptr %10, align 4
  %15 = getelementptr [3 x i32], ptr %data, i32 0, i32 2
  %16 = load ptr, ptr %c, align 8
  %17 = call ptr @_ReadLinearChannel(ptr %16)
  %18 = load i32, ptr %17, align 4
  %19 = call %Unit @free(ptr %17)
  store i32 %18, ptr %15, align 4
  %data1 = load [3 x i32], ptr %data, align 4
  %20 = getelementptr %RGBData, ptr %4, i32 0, i32 0
  store [3 x i32] %data1, ptr %20, align 4
  %21 = load %RGBData, ptr %4, align 4
  store %RGBData %21, ptr %rgbDat, align 4
  %rgbDat2 = load %RGBData, ptr %rgbDat, align 4
  %22 = getelementptr %RGBColor, ptr %3, i32 0, i32 0
  store %RGBData %rgbDat2, ptr %22, align 4
  %23 = getelementptr %RGBColor, ptr %3, i32 0, i32 1
  store ptr @"getRGBColor::#lambda", ptr %23, align 8
  %24 = getelementptr %RGBColor, ptr %3, i32 0, i32 2
  store ptr @"getRGBColor::#lambda.0", ptr %24, align 8
  %25 = getelementptr %RGBColor, ptr %3, i32 0, i32 3
  store ptr @"getRGBColor::#lambda.1", ptr %25, align 8
  %26 = load %RGBColor, ptr %3, align 8
  %27 = getelementptr %ColorType, ptr %1, i32 0, i32 0
  store i32 2, ptr %27, align 4
  %28 = getelementptr %ColorType, ptr %1, i32 0, i32 1
  store %RGBColor %26, ptr %28, align 8
  %29 = load %ColorType, ptr %1, align 4
  %30 = getelementptr %Color, ptr %2, i32 0, i32 0
  store %ColorType %29, ptr %30, align 4
  %31 = getelementptr %Color, ptr %2, i32 0, i32 1
  store ptr @"getRGBColor::#lambda.2", ptr %31, align 8
  %32 = load %Color, ptr %2, align 8
  %33 = call ptr @malloc(i32 56)
  store %Color %32, ptr %33, align 8
  %34 = load ptr, ptr %c, align 8
  %35 = call %Unit @_WriteChannel(ptr %34, ptr %33)
  ret %Unit zeroinitializer
}

define %Unit @fancyPrint(%Color %0) {
entry:
  %hsv = alloca %HSVColor, align 8
  %rgbcolor = alloca %RGBColor, align 8
  %1 = alloca %ColorType, align 8
  %s = alloca ptr, align 8
  %c = alloca %Color, align 8
  store %Color %0, ptr %c, align 8
  %2 = getelementptr %Color, ptr %c, i32 0, i32 0
  %3 = load %ColorType, ptr %2, align 4
  %4 = getelementptr %Color, ptr %c, i32 0, i32 1
  %5 = load ptr, ptr %4, align 8
  %6 = call ptr %5(%ColorType %3)
  store ptr %6, ptr %s, align 8
  %7 = getelementptr %Color, ptr %c, i32 0, i32 0
  %8 = load %ColorType, ptr %7, align 4
  %9 = getelementptr %Color, ptr %c, i32 0, i32 1
  %10 = load ptr, ptr %9, align 8
  %11 = call ptr %10(%ColorType %8)
  %12 = call i32 (ptr, ...) @printf(ptr @1, ptr %11)
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
  store %RGBColor %18, ptr %rgbcolor, align 8
  %19 = getelementptr %RGBColor, ptr %rgbcolor, i32 0, i32 0
  %20 = load %RGBData, ptr %19, align 4
  %21 = getelementptr %RGBColor, ptr %rgbcolor, i32 0, i32 1
  %22 = load ptr, ptr %21, align 8
  %23 = call i32 %22(%RGBData %20)
  %24 = getelementptr %RGBColor, ptr %rgbcolor, i32 0, i32 0
  %25 = load %RGBData, ptr %24, align 4
  %26 = getelementptr %RGBColor, ptr %rgbcolor, i32 0, i32 3
  %27 = load ptr, ptr %26, align 8
  %28 = call i32 %27(%RGBData %25)
  %29 = getelementptr %RGBColor, ptr %rgbcolor, i32 0, i32 0
  %30 = load %RGBData, ptr %29, align 4
  %31 = getelementptr %RGBColor, ptr %rgbcolor, i32 0, i32 2
  %32 = load ptr, ptr %31, align 8
  %33 = call i32 %32(%RGBData %30)
  %34 = call i32 (ptr, ...) @printf(ptr @2, i32 %23, i32 %28, i32 %33)
  br label %match-cont

tagBranch1:                                       ; preds = %entry
  %35 = getelementptr %ColorType, ptr %1, i32 0, i32 1
  %36 = load %HSVColor, ptr %35, align 8
  store %HSVColor %36, ptr %hsv, align 8
  %37 = getelementptr %HSVColor, ptr %hsv, i32 0, i32 0
  %38 = load %HSVData, ptr %37, align 4
  %39 = getelementptr %HSVColor, ptr %hsv, i32 0, i32 1
  %40 = load ptr, ptr %39, align 8
  %41 = call i32 %40(%HSVData %38)
  %42 = getelementptr %HSVColor, ptr %hsv, i32 0, i32 0
  %43 = load %HSVData, ptr %42, align 4
  %44 = getelementptr %HSVColor, ptr %hsv, i32 0, i32 2
  %45 = load ptr, ptr %44, align 8
  %46 = call i32 %45(%HSVData %43)
  %47 = getelementptr %HSVColor, ptr %hsv, i32 0, i32 0
  %48 = load %HSVData, ptr %47, align 4
  %49 = getelementptr %HSVColor, ptr %hsv, i32 0, i32 3
  %50 = load ptr, ptr %49, align 8
  %51 = call i32 %50(%HSVData %48)
  %52 = call i32 (ptr, ...) @printf(ptr @3, i32 %41, i32 %46, i32 %51)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch1, %tagBranch2, %entry
  ret %Unit zeroinitializer
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
  %15 = call %Unit @fancyPrint(%Color %col1)
  %16 = call ptr @malloc(i32 4)
  store i32 0, ptr %16, align 4
  %17 = load ptr, ptr %c, align 8
  %18 = call %Unit @_WriteChannel(ptr %17, ptr %16)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

define private i32 @"getRGBColor::#lambda"(%RGBData %0) {
entry:
  %d = alloca %RGBData, align 8
  store %RGBData %0, ptr %d, align 4
  %d1 = load %RGBData, ptr %d, align 4
  %1 = call i32 @getChannel(%RGBData %d1, i32 0)
  ret i32 %1
}

define private i32 @"getRGBColor::#lambda.0"(%RGBData %0) {
entry:
  %d = alloca %RGBData, align 8
  store %RGBData %0, ptr %d, align 4
  %d1 = load %RGBData, ptr %d, align 4
  %1 = call i32 @getChannel(%RGBData %d1, i32 1)
  ret i32 %1
}

define private i32 @"getRGBColor::#lambda.1"(%RGBData %0) {
entry:
  %d = alloca %RGBData, align 8
  store %RGBData %0, ptr %d, align 4
  %d1 = load %RGBData, ptr %d, align 4
  %1 = call i32 @getChannel(%RGBData %d1, i32 2)
  ret i32 %1
}

define private ptr @"getRGBColor::#lambda.2"(%ColorType %0) {
entry:
  %c = alloca %ColorType, align 8
  store %ColorType %0, ptr %c, align 4
  ret ptr @0
}

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_Execute(ptr)
