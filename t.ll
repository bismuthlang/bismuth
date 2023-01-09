
%RGBData = type { [3 x i32] }

declare void @WriteChannel(i32 %0, i8* %1)

declare i8* @ReadChannel(i32 %0)

declare i32 @Execute(void (i32)* %0)

declare i8* @malloc(i32 %0)

declare i1 @ShouldLoop(i32 %0)

declare void @ContractChannel(i32 %0)

declare void @WeakenChannel(i32 %0)

define void @getRGBColor(i32 %0) {
entry:
  %io = alloca i32, align 4
  store i32 %0, i32* %io, align 4
  %data = alloca [3 x i32], align 4
  %1 = load i32, i32* %io, align 4
  %2 = call i8* @ReadChannel(i32 %1)
  %3 = bitcast i8* %2 to i32*
  %4 = load i32, i32* %3, align 4
  %5 = getelementptr [3 x i32], [3 x i32]* %data, i32 0, i32 0
  store i32 %4, i32* %5, align 4
  %6 = load i32, i32* %io, align 4
  %7 = call i8* @ReadChannel(i32 %6)
  %8 = bitcast i8* %7 to i32*
  %9 = load i32, i32* %8, align 4
  %10 = getelementptr [3 x i32], [3 x i32]* %data, i32 0, i32 1
  store i32 %9, i32* %10, align 4
  %11 = load i32, i32* %io, align 4
  %12 = call i8* @ReadChannel(i32 %11)
  %13 = bitcast i8* %12 to i32*
  %14 = load i32, i32* %13, align 4
  %15 = getelementptr [3 x i32], [3 x i32]* %data, i32 0, i32 2
  store i32 %14, i32* %15, align 4
  %data1 = load [3 x i32], [3 x i32]* %data, align 4
  %16 = alloca %RGBData, align 8
  %17 = getelementptr %RGBData, %RGBData* %16, i32 0, i32 0
  store [3 x i32] %data1, [3 x i32]* %17, align 4
  %18 = load %RGBData, %RGBData* %16, align 4
  %rgbDat = alloca %RGBData, align 8
  store %RGBData %18, %RGBData* %rgbDat, align 4
  %BRK = alloca i32, align 4
  store i32 0, i32* %BRK, align 4
  %rgbDat2 = load %RGBData, %RGBData* %rgbDat, align 4
  %19 = alloca %RGBData, align 8
  store %RGBData %rgbDat2, %RGBData* %19, align 4
  %20 = getelementptr %RGBData, %RGBData* %19, i32 0, i32 0
  %21 = load [3 x i32], [3 x i32]* %20, align 4
  %aAAAAAAAAAAAA = alloca [3 x i32], align 4
  store [3 x i32] %21, [3 x i32]* %aAAAAAAAAAAAA, align 4
  %22 = alloca %RGBData*, align 8
}

declare void @program(i32 %0)

declare i32 @printf(i8* %0, ...)
; ModuleID = 'WPLC.ll'
source_filename = "WPLC.ll"

%RGBData = type { [3 x i32] }

declare void @WriteChannel(i32 %0, i8* %1)

declare i8* @ReadChannel(i32 %0)

declare i32 @Execute(void (i32)* %0)

declare i8* @malloc(i32 %0)

declare i1 @ShouldLoop(i32 %0)

declare void @ContractChannel(i32 %0)

declare void @WeakenChannel(i32 %0)

define void @getRGBColor(i32 %0) {
entry:
  %io = alloca i32, align 4
  store i32 %0, i32* %io, align 4
  %data = alloca [3 x i32], align 4
  %1 = load i32, i32* %io, align 4
  %2 = call i8* @ReadChannel(i32 %1)
  %3 = bitcast i8* %2 to i32*
  %4 = load i32, i32* %3, align 4
  %5 = getelementptr [3 x i32], [3 x i32]* %data, i32 0, i32 0
  store i32 %4, i32* %5, align 4
  %6 = load i32, i32* %io, align 4
  %7 = call i8* @ReadChannel(i32 %6)
  %8 = bitcast i8* %7 to i32*
  %9 = load i32, i32* %8, align 4
  %10 = getelementptr [3 x i32], [3 x i32]* %data, i32 0, i32 1
  store i32 %9, i32* %10, align 4
  %11 = load i32, i32* %io, align 4
  %12 = call i8* @ReadChannel(i32 %11)
  %13 = bitcast i8* %12 to i32*
  %14 = load i32, i32* %13, align 4
  %15 = getelementptr [3 x i32], [3 x i32]* %data, i32 0, i32 2
  store i32 %14, i32* %15, align 4
  %data1 = load [3 x i32], [3 x i32]* %data, align 4
  %16 = alloca %RGBData, align 8
  %17 = getelementptr %RGBData, %RGBData* %16, i32 0, i32 0
  store [3 x i32] %data1, [3 x i32]* %17, align 4
  %18 = load %RGBData, %RGBData* %16, align 4
  %rgbDat = alloca %RGBData, align 8
  store %RGBData %18, %RGBData* %rgbDat, align 4


  %BRK = alloca i32, align 4
  store i32 0, i32* %BRK, align 4


  %rgbDat2 = load %RGBData, %RGBData* %rgbDat, align 4
  %19 = alloca %RGBData, align 8
  store %RGBData %rgbDat2, %RGBData* %19, align 4
  %20 = getelementptr %RGBData, %RGBData* %19, i32 0, i32 0
  %21 = load [3 x i32], [3 x i32]* %20, align 4
  %aAAAAAAAAAAAA = alloca [3 x i32], align 4
  store [3 x i32] %21, [3 x i32]* %aAAAAAAAAAAAA, align 4

  
  %22 = alloca %RGBData*, align 8
  store %RGBData* %rgbDat, %RGBData** %22, align 8
}