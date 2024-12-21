; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"programs::adv::StructTest4::HSVColor" = type { %"programs::adv::StructTest4::HSVData" }
%"programs::adv::StructTest4::HSVData" = type { i32 }
%"programs::adv::StructTest4::RGBColor" = type { %"programs::adv::StructTest4::RGBData" }
%"programs::adv::StructTest4::RGBData" = type { i32 }
%"programs::adv::StructTest4::ColorType" = type { i32, [4 x i8] }
%"programs::adv::StructTest4::Color" = type { %"programs::adv::StructTest4::ColorType" }

@0 = private unnamed_addr constant [10 x i8] c"DEBUG=%u\0A\00", align 1
@1 = private unnamed_addr constant [7 x i8] c"r=%u]\0A\00", align 1
@2 = private unnamed_addr constant [5 x i8] c"hsv\0A\00", align 1

define %Unit @"programs::adv::StructTest4::getRGBColor"(ptr %0) {
entry:
  %hsv = alloca %"programs::adv::StructTest4::HSVColor", align 8
  %rgb = alloca %"programs::adv::StructTest4::RGBColor", align 8
  %1 = alloca %"programs::adv::StructTest4::ColorType", align 8
  %c = alloca %"programs::adv::StructTest4::Color", align 8
  %2 = alloca %"programs::adv::StructTest4::ColorType", align 8
  %3 = alloca %"programs::adv::StructTest4::Color", align 8
  %4 = alloca %"programs::adv::StructTest4::RGBColor", align 8
  %ct = alloca %"programs::adv::StructTest4::ColorType", align 8
  %5 = alloca %"programs::adv::StructTest4::RGBColor", align 8
  %rgbDat = alloca %"programs::adv::StructTest4::RGBData", align 8
  %6 = alloca %"programs::adv::StructTest4::RGBData", align 8
  %r = alloca i32, align 4
  %io = alloca ptr, align 8
  store ptr %0, ptr %io, align 8
  %7 = load ptr, ptr %io, align 8
  %8 = call ptr @_ReadLinearChannel(ptr %7)
  %9 = load i32, ptr %8, align 4
  %10 = call %Unit @free(ptr %8)
  store i32 %9, ptr %r, align 4
  %r1 = load i32, ptr %r, align 4
  %11 = getelementptr %"programs::adv::StructTest4::RGBData", ptr %6, i32 0, i32 0
  store i32 %r1, ptr %11, align 4
  %12 = load %"programs::adv::StructTest4::RGBData", ptr %6, align 4
  store %"programs::adv::StructTest4::RGBData" %12, ptr %rgbDat, align 4
  %rgbDat2 = load %"programs::adv::StructTest4::RGBData", ptr %rgbDat, align 4
  %13 = getelementptr %"programs::adv::StructTest4::RGBColor", ptr %5, i32 0, i32 0
  store %"programs::adv::StructTest4::RGBData" %rgbDat2, ptr %13, align 4
  %14 = load %"programs::adv::StructTest4::RGBColor", ptr %5, align 4
  %15 = getelementptr %"programs::adv::StructTest4::ColorType", ptr %ct, i32 0, i32 0
  store i32 2, ptr %15, align 4
  %16 = getelementptr %"programs::adv::StructTest4::ColorType", ptr %ct, i32 0, i32 1
  store %"programs::adv::StructTest4::RGBColor" %14, ptr %16, align 4
  %rgbDat3 = load %"programs::adv::StructTest4::RGBData", ptr %rgbDat, align 4
  %17 = getelementptr %"programs::adv::StructTest4::RGBColor", ptr %4, i32 0, i32 0
  store %"programs::adv::StructTest4::RGBData" %rgbDat3, ptr %17, align 4
  %18 = load %"programs::adv::StructTest4::RGBColor", ptr %4, align 4
  %19 = getelementptr %"programs::adv::StructTest4::ColorType", ptr %2, i32 0, i32 0
  store i32 2, ptr %19, align 4
  %20 = getelementptr %"programs::adv::StructTest4::ColorType", ptr %2, i32 0, i32 1
  store %"programs::adv::StructTest4::RGBColor" %18, ptr %20, align 4
  %21 = load %"programs::adv::StructTest4::ColorType", ptr %2, align 4
  %22 = getelementptr %"programs::adv::StructTest4::Color", ptr %3, i32 0, i32 0
  store %"programs::adv::StructTest4::ColorType" %21, ptr %22, align 4
  %23 = load %"programs::adv::StructTest4::Color", ptr %3, align 4
  store %"programs::adv::StructTest4::Color" %23, ptr %c, align 4
  %24 = getelementptr %"programs::adv::StructTest4::Color", ptr %c, i32 0, i32 0
  %25 = load %"programs::adv::StructTest4::ColorType", ptr %24, align 4
  store %"programs::adv::StructTest4::ColorType" %25, ptr %1, align 4
  %26 = getelementptr %"programs::adv::StructTest4::ColorType", ptr %1, i32 0, i32 0
  %27 = load i32, ptr %26, align 4
  switch i32 %27, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %entry
  %28 = getelementptr %"programs::adv::StructTest4::ColorType", ptr %1, i32 0, i32 1
  %29 = load %"programs::adv::StructTest4::RGBColor", ptr %28, align 4
  store %"programs::adv::StructTest4::RGBColor" %29, ptr %rgb, align 4
  %30 = call i32 (ptr, ...) @printf(ptr @0, i32 0)
  %31 = getelementptr %"programs::adv::StructTest4::RGBColor", ptr %rgb, i32 0, i32 0, i32 0
  %32 = load i32, ptr %31, align 4
  %33 = call i32 (ptr, ...) @printf(ptr @1, i32 %32)
  br label %match-cont

tagBranch1:                                       ; preds = %entry
  %34 = getelementptr %"programs::adv::StructTest4::ColorType", ptr %1, i32 0, i32 1
  %35 = load %"programs::adv::StructTest4::HSVColor", ptr %34, align 4
  store %"programs::adv::StructTest4::HSVColor" %35, ptr %hsv, align 4
  %36 = call i32 (ptr, ...) @printf(ptr @2)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch1, %tagBranch2, %entry
  %c4 = load %"programs::adv::StructTest4::Color", ptr %c, align 4
  %37 = call ptr @malloc(i32 8)
  store %"programs::adv::StructTest4::Color" %c4, ptr %37, align 4
  %38 = load ptr, ptr %io, align 8
  %39 = call %Unit @_WriteChannel(ptr %38, ptr %37)
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %t = alloca %"programs::adv::StructTest4::Color", align 8
  %chan = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @_Execute(ptr @"programs::adv::StructTest4::getRGBColor")
  store ptr %1, ptr %chan, align 8
  %2 = call ptr @malloc(i32 4)
  store i32 128, ptr %2, align 4
  %3 = load ptr, ptr %chan, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  %5 = load ptr, ptr %chan, align 8
  %6 = call ptr @_ReadLinearChannel(ptr %5)
  %7 = load %"programs::adv::StructTest4::Color", ptr %6, align 4
  %8 = call %Unit @free(ptr %6)
  store %"programs::adv::StructTest4::Color" %7, ptr %t, align 4
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
