; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"(Color + Unit + boolean + int + str)" = type { i32, [16 x i8] }
%Color = type { i32, [12 x i8] }
%"(Color + Unit)" = type { i32, [16 x i8] }
%ColorHelper = type { ptr, ptr, ptr }
%"(boolean + int + str)" = type { i32, [8 x i8] }
%HexColor = type { ptr }
%HSVColor = type { i32, i32, i32 }
%RGBColor = type { i32, i32, i32 }

@0 = private unnamed_addr constant [7 x i8] c"FFFFFF\00", align 1
@1 = private unnamed_addr constant [8 x i8] c"int: %u\00", align 1
@2 = private unnamed_addr constant [11 x i8] c"string: %s\00", align 1
@3 = private unnamed_addr constant [12 x i8] c"boolean: %s\00", align 1
@4 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@5 = private unnamed_addr constant [6 x i8] c"false\00", align 1
@6 = private unnamed_addr constant [4 x i8] c"()\0A\00", align 1
@7 = private unnamed_addr constant [22 x i8] c"[Color type=RGB, red=\00", align 1
@8 = private unnamed_addr constant [9 x i8] c", green=\00", align 1
@9 = private unnamed_addr constant [8 x i8] c", blue=\00", align 1
@10 = private unnamed_addr constant [3 x i8] c"]\0A\00", align 1
@11 = private unnamed_addr constant [22 x i8] c"[Color type=HSV, hue=\00", align 1
@12 = private unnamed_addr constant [7 x i8] c", sat=\00", align 1
@13 = private unnamed_addr constant [9 x i8] c", value=\00", align 1
@14 = private unnamed_addr constant [3 x i8] c"]\0A\00", align 1
@15 = private unnamed_addr constant [24 x i8] c"[Color type=HEX, value=\00", align 1
@16 = private unnamed_addr constant [3 x i8] c"]\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %1 = alloca %"(Color + Unit + boolean + int + str)", align 8
  %u = alloca %Unit, align 8
  %2 = alloca %"(Color + Unit + boolean + int + str)", align 8
  %c.0 = alloca %Color, align 8
  %3 = alloca %"(Color + Unit)", align 8
  %4 = alloca %"(Color + Unit)", align 8
  %5 = alloca %"(Color + Unit)", align 8
  %io = alloca ptr, align 8
  %i = alloca i32, align 4
  %samples = alloca [3 x %Color], align 8
  %sampleChannel = alloca ptr, align 8
  %helper = alloca %ColorHelper, align 8
  %6 = alloca %ColorHelper, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %7 = getelementptr %ColorHelper, ptr %6, i32 0, i32 0
  store ptr @"program::getRGBColor", ptr %7, align 8
  %8 = getelementptr %ColorHelper, ptr %6, i32 0, i32 1
  store ptr @"program::getHSVColor", ptr %8, align 8
  %9 = getelementptr %ColorHelper, ptr %6, i32 0, i32 2
  store ptr @"program::getHexColor", ptr %9, align 8
  %10 = load %ColorHelper, ptr %6, align 8
  store %ColorHelper %10, ptr %helper, align 8
  %11 = call ptr @_Execute(ptr @getSampleColors)
  store ptr %11, ptr %sampleChannel, align 8
  %helper1 = load %ColorHelper, ptr %helper, align 8
  %12 = call ptr @malloc(i32 24)
  store %ColorHelper %helper1, ptr %12, align 8
  %13 = load ptr, ptr %sampleChannel, align 8
  %14 = call %Unit @_WriteChannel(ptr %13, ptr %12)
  %15 = load ptr, ptr %sampleChannel, align 8
  %16 = call ptr @_ReadLinearChannel(ptr %15)
  %17 = load [3 x %Color], ptr %16, align 4
  %18 = call %Unit @free(ptr %16)
  store [3 x %Color] %17, ptr %samples, align 4
  store i32 0, ptr %i, align 4
  %i2 = load i32, ptr %i, align 4
  %19 = icmp slt i32 %i2, 3
  br i1 %19, label %loop, label %rest

loop:                                             ; preds = %match-cont, %entry
  %20 = call ptr @_Execute(ptr @toString)
  store ptr %20, ptr %io, align 8
  %i3 = load i32, ptr %i, align 4
  %21 = icmp slt i32 %i3, 3
  br i1 %21, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %loop
  %22 = icmp sge i32 %i3, 0
  br i1 %22, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %23 = getelementptr [3 x %Color], ptr %samples, i32 0, i32 %i3
  %24 = load %Color, ptr %23, align 4
  %25 = getelementptr %"(Color + Unit)", ptr %5, i32 0, i32 0
  store i32 1, ptr %25, align 4
  %26 = getelementptr %"(Color + Unit)", ptr %5, i32 0, i32 1
  store %Color %24, ptr %26, align 4
  %27 = load %"(Color + Unit)", ptr %5, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %loop
  %28 = getelementptr %"(Color + Unit)", ptr %4, i32 0, i32 0
  store i32 2, ptr %28, align 4
  %29 = getelementptr %"(Color + Unit)", ptr %4, i32 0, i32 1
  store %Unit zeroinitializer, ptr %29, align 1
  %30 = load %"(Color + Unit)", ptr %4, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Color + Unit)" [ %27, %accessGTZ ], [ %30, %accessBad ]
  store %"(Color + Unit)" %arrayAccess, ptr %3, align 4
  %31 = getelementptr %"(Color + Unit)", ptr %3, i32 0, i32 0
  %32 = load i32, ptr %31, align 4
  switch i32 %32, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %accessAfter
  %33 = getelementptr %"(Color + Unit)", ptr %3, i32 0, i32 1
  %34 = load %Color, ptr %33, align 4
  store %Color %34, ptr %c.0, align 4
  %c.04 = load %Color, ptr %c.0, align 4
  %35 = getelementptr %"(Color + Unit + boolean + int + str)", ptr %2, i32 0, i32 0
  store i32 1, ptr %35, align 4
  %36 = getelementptr %"(Color + Unit + boolean + int + str)", ptr %2, i32 0, i32 1
  store %Color %c.04, ptr %36, align 4
  %37 = load %"(Color + Unit + boolean + int + str)", ptr %2, align 4
  %38 = call ptr @malloc(i32 20)
  store %"(Color + Unit + boolean + int + str)" %37, ptr %38, align 4
  %39 = load ptr, ptr %io, align 8
  %40 = call %Unit @_WriteChannel(ptr %39, ptr %38)
  br label %match-cont

tagBranch2:                                       ; preds = %accessAfter
  %41 = getelementptr %"(Color + Unit)", ptr %3, i32 0, i32 1
  %42 = load %Unit, ptr %41, align 1
  store %Unit %42, ptr %u, align 1
  %u5 = load %Unit, ptr %u, align 1
  %43 = getelementptr %"(Color + Unit + boolean + int + str)", ptr %1, i32 0, i32 0
  store i32 2, ptr %43, align 4
  %44 = getelementptr %"(Color + Unit + boolean + int + str)", ptr %1, i32 0, i32 1
  store %Unit %u5, ptr %44, align 1
  %45 = load %"(Color + Unit + boolean + int + str)", ptr %1, align 4
  %46 = call ptr @malloc(i32 20)
  store %"(Color + Unit + boolean + int + str)" %45, ptr %46, align 4
  %47 = load ptr, ptr %io, align 8
  %48 = call %Unit @_WriteChannel(ptr %47, ptr %46)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %accessAfter
  %i6 = load i32, ptr %i, align 4
  %49 = add nsw i32 %i6, 1
  store i32 %49, ptr %i, align 4
  %i7 = load i32, ptr %i, align 4
  %50 = icmp slt i32 %i7, 3
  br i1 %50, label %loop, label %rest

rest:                                             ; preds = %match-cont, %entry
  %51 = call ptr @malloc(i32 4)
  store i32 0, ptr %51, align 4
  %52 = load ptr, ptr %c, align 8
  %53 = call %Unit @_WriteChannel(ptr %52, ptr %51)
  ret %Unit zeroinitializer
}

define %Unit @getSampleColors(ptr %0) {
entry:
  %rgbChan = alloca ptr, align 8
  %ans = alloca [3 x %Color], align 8
  %helper = alloca %ColorHelper, align 8
  %io = alloca ptr, align 8
  store ptr %0, ptr %io, align 8
  %1 = load ptr, ptr %io, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load %ColorHelper, ptr %2, align 8
  %4 = call %Unit @free(ptr %2)
  store %ColorHelper %3, ptr %helper, align 8
  %5 = getelementptr %ColorHelper, ptr %helper, i32 0, i32 0
  %6 = load ptr, ptr %5, align 8
  %7 = call ptr @_Execute(ptr %6)
  store ptr %7, ptr %rgbChan, align 8
  %8 = call ptr @malloc(i32 4)
  store i32 255, ptr %8, align 4
  %9 = load ptr, ptr %rgbChan, align 8
  %10 = call %Unit @_WriteChannel(ptr %9, ptr %8)
  %11 = call ptr @malloc(i32 4)
  store i32 255, ptr %11, align 4
  %12 = load ptr, ptr %rgbChan, align 8
  %13 = call %Unit @_WriteChannel(ptr %12, ptr %11)
  %14 = call ptr @malloc(i32 4)
  store i32 255, ptr %14, align 4
  %15 = load ptr, ptr %rgbChan, align 8
  %16 = call %Unit @_WriteChannel(ptr %15, ptr %14)
  %17 = getelementptr [3 x %Color], ptr %ans, i32 0, i32 0
  %18 = load ptr, ptr %rgbChan, align 8
  %19 = call ptr @_ReadLinearChannel(ptr %18)
  %20 = load %Color, ptr %19, align 4
  %21 = call %Unit @free(ptr %19)
  store %Color %20, ptr %17, align 4
  %22 = getelementptr [3 x %Color], ptr %ans, i32 0, i32 1
  %23 = getelementptr %ColorHelper, ptr %helper, i32 0, i32 1
  %24 = load ptr, ptr %23, align 8
  %25 = call %Color %24(i32 128, i32 128, i32 128)
  store %Color %25, ptr %22, align 4
  %26 = getelementptr [3 x %Color], ptr %ans, i32 0, i32 2
  %27 = getelementptr %ColorHelper, ptr %helper, i32 0, i32 2
  %28 = load ptr, ptr %27, align 8
  %29 = call %Color %28(ptr @0)
  store %Color %29, ptr %26, align 4
  %ans1 = load [3 x %Color], ptr %ans, align 4
  %30 = call ptr @malloc(i32 48)
  store [3 x %Color] %ans1, ptr %30, align 4
  %31 = load ptr, ptr %io, align 8
  %32 = call %Unit @_WriteChannel(ptr %31, ptr %30)
  ret %Unit zeroinitializer
}

define %Unit @printPrimitive(%"(boolean + int + str)" %0) {
entry:
  %b = alloca i1, align 1
  %s = alloca ptr, align 8
  %i = alloca i32, align 4
  %1 = alloca %"(boolean + int + str)", align 8
  %toPrint = alloca %"(boolean + int + str)", align 8
  store %"(boolean + int + str)" %0, ptr %toPrint, align 4
  %toPrint1 = load %"(boolean + int + str)", ptr %toPrint, align 4
  store %"(boolean + int + str)" %toPrint1, ptr %1, align 4
  %2 = getelementptr %"(boolean + int + str)", ptr %1, i32 0, i32 0
  %3 = load i32, ptr %2, align 4
  switch i32 %3, label %match-cont [
    i32 2, label %tagBranch2
    i32 3, label %tagBranch3
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %entry
  %4 = getelementptr %"(boolean + int + str)", ptr %1, i32 0, i32 1
  %5 = load i32, ptr %4, align 4
  store i32 %5, ptr %i, align 4
  %i2 = load i32, ptr %i, align 4
  %6 = call i32 (ptr, ...) @printf(ptr @1, i32 %i2)
  br label %match-cont

tagBranch3:                                       ; preds = %entry
  %7 = getelementptr %"(boolean + int + str)", ptr %1, i32 0, i32 1
  %8 = load ptr, ptr %7, align 8
  store ptr %8, ptr %s, align 8
  %s3 = load ptr, ptr %s, align 8
  %9 = call i32 (ptr, ...) @printf(ptr @2, ptr %s3)
  br label %match-cont

tagBranch1:                                       ; preds = %entry
  %10 = getelementptr %"(boolean + int + str)", ptr %1, i32 0, i32 1
  %11 = load i1, ptr %10, align 1
  store i1 %11, ptr %b, align 1
  %b4 = load i1, ptr %b, align 1
  %12 = call ptr @"printPrimitive::#lambda"(i1 %b4)
  %13 = call i32 (ptr, ...) @printf(ptr @3, ptr %12)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch1, %tagBranch3, %tagBranch2, %entry
  ret %Unit zeroinitializer
}

define %Unit @toString(ptr %0) {
entry:
  %1 = alloca %"(boolean + int + str)", align 8
  %hex = alloca %HexColor, align 8
  %2 = alloca %"(boolean + int + str)", align 8
  %3 = alloca %"(boolean + int + str)", align 8
  %4 = alloca %"(boolean + int + str)", align 8
  %hsv = alloca %HSVColor, align 8
  %5 = alloca %"(boolean + int + str)", align 8
  %6 = alloca %"(boolean + int + str)", align 8
  %7 = alloca %"(boolean + int + str)", align 8
  %rgb = alloca %RGBColor, align 8
  %8 = alloca %Color, align 8
  %c = alloca %Color, align 8
  %9 = alloca %"(boolean + int + str)", align 8
  %s = alloca ptr, align 8
  %10 = alloca %"(boolean + int + str)", align 8
  %b = alloca i1, align 1
  %11 = alloca %"(boolean + int + str)", align 8
  %i = alloca i32, align 4
  %u = alloca %Unit, align 8
  %12 = alloca %"(Color + Unit + boolean + int + str)", align 8
  %obj = alloca %"(Color + Unit + boolean + int + str)", align 8
  %io = alloca ptr, align 8
  store ptr %0, ptr %io, align 8
  %13 = load ptr, ptr %io, align 8
  %14 = call ptr @_ReadLinearChannel(ptr %13)
  %15 = load %"(Color + Unit + boolean + int + str)", ptr %14, align 4
  %16 = call %Unit @free(ptr %14)
  store %"(Color + Unit + boolean + int + str)" %15, ptr %obj, align 4
  %obj1 = load %"(Color + Unit + boolean + int + str)", ptr %obj, align 4
  store %"(Color + Unit + boolean + int + str)" %obj1, ptr %12, align 4
  %17 = getelementptr %"(Color + Unit + boolean + int + str)", ptr %12, i32 0, i32 0
  %18 = load i32, ptr %17, align 4
  switch i32 %18, label %match-cont9 [
    i32 2, label %tagBranch2
    i32 4, label %tagBranch4
    i32 3, label %tagBranch3
    i32 5, label %tagBranch5
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %entry
  %19 = getelementptr %"(Color + Unit + boolean + int + str)", ptr %12, i32 0, i32 1
  %20 = load %Unit, ptr %19, align 1
  store %Unit %20, ptr %u, align 1
  %21 = call i32 (ptr, ...) @printf(ptr @6)
  br label %match-cont9

tagBranch4:                                       ; preds = %entry
  %22 = getelementptr %"(Color + Unit + boolean + int + str)", ptr %12, i32 0, i32 1
  %23 = load i32, ptr %22, align 4
  store i32 %23, ptr %i, align 4
  %i2 = load i32, ptr %i, align 4
  %24 = getelementptr %"(boolean + int + str)", ptr %11, i32 0, i32 0
  store i32 2, ptr %24, align 4
  %25 = getelementptr %"(boolean + int + str)", ptr %11, i32 0, i32 1
  store i32 %i2, ptr %25, align 4
  %26 = load %"(boolean + int + str)", ptr %11, align 4
  %27 = call %Unit @printPrimitive(%"(boolean + int + str)" %26)
  br label %match-cont9

tagBranch3:                                       ; preds = %entry
  %28 = getelementptr %"(Color + Unit + boolean + int + str)", ptr %12, i32 0, i32 1
  %29 = load i1, ptr %28, align 1
  store i1 %29, ptr %b, align 1
  %b3 = load i1, ptr %b, align 1
  %30 = getelementptr %"(boolean + int + str)", ptr %10, i32 0, i32 0
  store i32 1, ptr %30, align 4
  %31 = getelementptr %"(boolean + int + str)", ptr %10, i32 0, i32 1
  store i1 %b3, ptr %31, align 1
  %32 = load %"(boolean + int + str)", ptr %10, align 4
  %33 = call %Unit @printPrimitive(%"(boolean + int + str)" %32)
  br label %match-cont9

tagBranch5:                                       ; preds = %entry
  %34 = getelementptr %"(Color + Unit + boolean + int + str)", ptr %12, i32 0, i32 1
  %35 = load ptr, ptr %34, align 8
  store ptr %35, ptr %s, align 8
  %s4 = load ptr, ptr %s, align 8
  %36 = getelementptr %"(boolean + int + str)", ptr %9, i32 0, i32 0
  store i32 3, ptr %36, align 4
  %37 = getelementptr %"(boolean + int + str)", ptr %9, i32 0, i32 1
  store ptr %s4, ptr %37, align 8
  %38 = load %"(boolean + int + str)", ptr %9, align 4
  %39 = call %Unit @printPrimitive(%"(boolean + int + str)" %38)
  br label %match-cont9

tagBranch1:                                       ; preds = %entry
  %40 = getelementptr %"(Color + Unit + boolean + int + str)", ptr %12, i32 0, i32 1
  %41 = load %Color, ptr %40, align 4
  store %Color %41, ptr %c, align 4
  %c5 = load %Color, ptr %c, align 4
  store %Color %c5, ptr %8, align 4
  %42 = getelementptr %Color, ptr %8, i32 0, i32 0
  %43 = load i32, ptr %42, align 4
  switch i32 %43, label %match-cont [
    i32 3, label %tagBranch36
    i32 1, label %tagBranch17
    i32 2, label %tagBranch28
  ]

tagBranch36:                                      ; preds = %tagBranch1
  %44 = getelementptr %Color, ptr %8, i32 0, i32 1
  %45 = load %RGBColor, ptr %44, align 4
  store %RGBColor %45, ptr %rgb, align 4
  %46 = call i32 (ptr, ...) @printf(ptr @7)
  %47 = getelementptr %RGBColor, ptr %rgb, i32 0, i32 0
  %48 = load i32, ptr %47, align 4
  %49 = getelementptr %"(boolean + int + str)", ptr %7, i32 0, i32 0
  store i32 2, ptr %49, align 4
  %50 = getelementptr %"(boolean + int + str)", ptr %7, i32 0, i32 1
  store i32 %48, ptr %50, align 4
  %51 = load %"(boolean + int + str)", ptr %7, align 4
  %52 = call %Unit @printPrimitive(%"(boolean + int + str)" %51)
  %53 = call i32 (ptr, ...) @printf(ptr @8)
  %54 = getelementptr %RGBColor, ptr %rgb, i32 0, i32 1
  %55 = load i32, ptr %54, align 4
  %56 = getelementptr %"(boolean + int + str)", ptr %6, i32 0, i32 0
  store i32 2, ptr %56, align 4
  %57 = getelementptr %"(boolean + int + str)", ptr %6, i32 0, i32 1
  store i32 %55, ptr %57, align 4
  %58 = load %"(boolean + int + str)", ptr %6, align 4
  %59 = call %Unit @printPrimitive(%"(boolean + int + str)" %58)
  %60 = call i32 (ptr, ...) @printf(ptr @9)
  %61 = getelementptr %RGBColor, ptr %rgb, i32 0, i32 2
  %62 = load i32, ptr %61, align 4
  %63 = getelementptr %"(boolean + int + str)", ptr %5, i32 0, i32 0
  store i32 2, ptr %63, align 4
  %64 = getelementptr %"(boolean + int + str)", ptr %5, i32 0, i32 1
  store i32 %62, ptr %64, align 4
  %65 = load %"(boolean + int + str)", ptr %5, align 4
  %66 = call %Unit @printPrimitive(%"(boolean + int + str)" %65)
  %67 = call i32 (ptr, ...) @printf(ptr @10)
  br label %match-cont

tagBranch17:                                      ; preds = %tagBranch1
  %68 = getelementptr %Color, ptr %8, i32 0, i32 1
  %69 = load %HSVColor, ptr %68, align 4
  store %HSVColor %69, ptr %hsv, align 4
  %70 = call i32 (ptr, ...) @printf(ptr @11)
  %71 = getelementptr %HSVColor, ptr %hsv, i32 0, i32 0
  %72 = load i32, ptr %71, align 4
  %73 = getelementptr %"(boolean + int + str)", ptr %4, i32 0, i32 0
  store i32 2, ptr %73, align 4
  %74 = getelementptr %"(boolean + int + str)", ptr %4, i32 0, i32 1
  store i32 %72, ptr %74, align 4
  %75 = load %"(boolean + int + str)", ptr %4, align 4
  %76 = call %Unit @printPrimitive(%"(boolean + int + str)" %75)
  %77 = call i32 (ptr, ...) @printf(ptr @12)
  %78 = getelementptr %HSVColor, ptr %hsv, i32 0, i32 1
  %79 = load i32, ptr %78, align 4
  %80 = getelementptr %"(boolean + int + str)", ptr %3, i32 0, i32 0
  store i32 2, ptr %80, align 4
  %81 = getelementptr %"(boolean + int + str)", ptr %3, i32 0, i32 1
  store i32 %79, ptr %81, align 4
  %82 = load %"(boolean + int + str)", ptr %3, align 4
  %83 = call %Unit @printPrimitive(%"(boolean + int + str)" %82)
  %84 = call i32 (ptr, ...) @printf(ptr @13)
  %85 = getelementptr %HSVColor, ptr %hsv, i32 0, i32 2
  %86 = load i32, ptr %85, align 4
  %87 = getelementptr %"(boolean + int + str)", ptr %2, i32 0, i32 0
  store i32 2, ptr %87, align 4
  %88 = getelementptr %"(boolean + int + str)", ptr %2, i32 0, i32 1
  store i32 %86, ptr %88, align 4
  %89 = load %"(boolean + int + str)", ptr %2, align 4
  %90 = call %Unit @printPrimitive(%"(boolean + int + str)" %89)
  %91 = call i32 (ptr, ...) @printf(ptr @14)
  br label %match-cont

tagBranch28:                                      ; preds = %tagBranch1
  %92 = getelementptr %Color, ptr %8, i32 0, i32 1
  %93 = load %HexColor, ptr %92, align 8
  store %HexColor %93, ptr %hex, align 8
  %94 = call i32 (ptr, ...) @printf(ptr @15)
  %95 = getelementptr %HexColor, ptr %hex, i32 0, i32 0
  %96 = load ptr, ptr %95, align 8
  %97 = getelementptr %"(boolean + int + str)", ptr %1, i32 0, i32 0
  store i32 3, ptr %97, align 4
  %98 = getelementptr %"(boolean + int + str)", ptr %1, i32 0, i32 1
  store ptr %96, ptr %98, align 8
  %99 = load %"(boolean + int + str)", ptr %1, align 4
  %100 = call %Unit @printPrimitive(%"(boolean + int + str)" %99)
  %101 = call i32 (ptr, ...) @printf(ptr @16)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch28, %tagBranch17, %tagBranch36, %tagBranch1
  br label %match-cont9

match-cont9:                                      ; preds = %match-cont, %tagBranch5, %tagBranch3, %tagBranch4, %tagBranch2, %entry
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

define private %Unit @"program::getRGBColor"(ptr %0) {
entry:
  %1 = alloca %Color, align 8
  %2 = alloca %RGBColor, align 8
  %blue = alloca i32, align 4
  %green = alloca i32, align 4
  %red = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %3 = load ptr, ptr %c, align 8
  %4 = call ptr @_ReadLinearChannel(ptr %3)
  %5 = load i32, ptr %4, align 4
  %6 = call %Unit @free(ptr %4)
  store i32 %5, ptr %red, align 4
  %7 = load ptr, ptr %c, align 8
  %8 = call ptr @_ReadLinearChannel(ptr %7)
  %9 = load i32, ptr %8, align 4
  %10 = call %Unit @free(ptr %8)
  store i32 %9, ptr %green, align 4
  %11 = load ptr, ptr %c, align 8
  %12 = call ptr @_ReadLinearChannel(ptr %11)
  %13 = load i32, ptr %12, align 4
  %14 = call %Unit @free(ptr %12)
  store i32 %13, ptr %blue, align 4
  %red1 = load i32, ptr %red, align 4
  %green2 = load i32, ptr %green, align 4
  %blue3 = load i32, ptr %blue, align 4
  %15 = getelementptr %RGBColor, ptr %2, i32 0, i32 0
  store i32 %red1, ptr %15, align 4
  %16 = getelementptr %RGBColor, ptr %2, i32 0, i32 1
  store i32 %green2, ptr %16, align 4
  %17 = getelementptr %RGBColor, ptr %2, i32 0, i32 2
  store i32 %blue3, ptr %17, align 4
  %18 = load %RGBColor, ptr %2, align 4
  %19 = getelementptr %Color, ptr %1, i32 0, i32 0
  store i32 3, ptr %19, align 4
  %20 = getelementptr %Color, ptr %1, i32 0, i32 1
  store %RGBColor %18, ptr %20, align 4
  %21 = load %Color, ptr %1, align 4
  %22 = call ptr @malloc(i32 16)
  store %Color %21, ptr %22, align 4
  %23 = load ptr, ptr %c, align 8
  %24 = call %Unit @_WriteChannel(ptr %23, ptr %22)
  ret %Unit zeroinitializer
}

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

define private %Color @"program::getHSVColor"(i32 %0, i32 %1, i32 %2) {
entry:
  %3 = alloca %Color, align 8
  %4 = alloca %HSVColor, align 8
  %v = alloca i32, align 4
  %s = alloca i32, align 4
  %h = alloca i32, align 4
  store i32 %0, ptr %h, align 4
  store i32 %1, ptr %s, align 4
  store i32 %2, ptr %v, align 4
  %h1 = load i32, ptr %h, align 4
  %s2 = load i32, ptr %s, align 4
  %v3 = load i32, ptr %v, align 4
  %5 = getelementptr %HSVColor, ptr %4, i32 0, i32 0
  store i32 %h1, ptr %5, align 4
  %6 = getelementptr %HSVColor, ptr %4, i32 0, i32 1
  store i32 %s2, ptr %6, align 4
  %7 = getelementptr %HSVColor, ptr %4, i32 0, i32 2
  store i32 %v3, ptr %7, align 4
  %8 = load %HSVColor, ptr %4, align 4
  %9 = getelementptr %Color, ptr %3, i32 0, i32 0
  store i32 1, ptr %9, align 4
  %10 = getelementptr %Color, ptr %3, i32 0, i32 1
  store %HSVColor %8, ptr %10, align 4
  %11 = load %Color, ptr %3, align 4
  ret %Color %11
}

define private %Color @"program::getHexColor"(ptr %0) {
entry:
  %1 = alloca %Color, align 8
  %2 = alloca %HexColor, align 8
  %s = alloca ptr, align 8
  store ptr %0, ptr %s, align 8
  %s1 = load ptr, ptr %s, align 8
  %3 = getelementptr %HexColor, ptr %2, i32 0, i32 0
  store ptr %s1, ptr %3, align 8
  %4 = load %HexColor, ptr %2, align 8
  %5 = getelementptr %Color, ptr %1, i32 0, i32 0
  store i32 2, ptr %5, align 4
  %6 = getelementptr %Color, ptr %1, i32 0, i32 1
  store %HexColor %4, ptr %6, align 8
  %7 = load %Color, ptr %1, align 4
  ret %Color %7
}

declare ptr @_Execute(ptr)

define private ptr @"printPrimitive::#lambda"(i1 %0) {
entry:
  %bool = alloca i1, align 1
  store i1 %0, ptr %bool, align 1
  %bool1 = load i1, ptr %bool, align 1
  br i1 %bool1, label %then, label %else

then:                                             ; preds = %entry
  ret ptr @4

else:                                             ; preds = %entry
  ret ptr @5
}
