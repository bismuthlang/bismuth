; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"(Unit + str)" = type { i32, [8 x i8] }

@0 = private unnamed_addr constant [13 x i8] c"Bounds Error\00", align 1
@1 = private unnamed_addr constant [15 x i8] c"H\09\0A\0D\0A\0B\22'\0Aokay\\\00", align 1
@2 = private unnamed_addr constant [17 x i8] c"Why hello there!\00", align 1
@3 = private unnamed_addr constant [28 x i8] c"This is a different string!\00", align 1
@4 = private unnamed_addr constant [25 x i8] c"Still a different string\00", align 1
@5 = private unnamed_addr constant [17 x i8] c"Why hello there!\00", align 1
@6 = private unnamed_addr constant [14 x i8] c"%d, %d, = %d\0A\00", align 1

define ptr @"programs::test7::accessor"([4 x ptr] %0, i32 %1) {
entry:
  %s = alloca ptr, align 8
  %u = alloca %Unit, align 8
  %2 = alloca %"(Unit + str)", align 8
  %3 = alloca %"(Unit + str)", align 8
  %4 = alloca %"(Unit + str)", align 8
  %idx = alloca i32, align 4
  %array = alloca [4 x ptr], align 8
  store [4 x ptr] %0, ptr %array, align 8
  store i32 %1, ptr %idx, align 4
  %idx1 = load i32, ptr %idx, align 4
  %5 = icmp slt i32 %idx1, 4
  br i1 %5, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %entry
  %6 = icmp sge i32 %idx1, 0
  br i1 %6, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %7 = getelementptr [4 x ptr], ptr %array, i32 0, i32 %idx1
  %8 = load ptr, ptr %7, align 8
  %9 = getelementptr i32, ptr %4, i32 0, i32 0
  store i32 2, ptr %9, align 4
  %10 = getelementptr %"(Unit + str)", ptr %4, i32 0, i32 1
  store ptr %8, ptr %10, align 8
  %11 = load %"(Unit + str)", ptr %4, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %entry
  %12 = getelementptr i32, ptr %3, i32 0, i32 0
  store i32 1, ptr %12, align 4
  %13 = getelementptr %"(Unit + str)", ptr %3, i32 0, i32 1
  store %Unit zeroinitializer, ptr %13, align 1
  %14 = load %"(Unit + str)", ptr %3, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + str)" [ %11, %accessGTZ ], [ %14, %accessBad ]
  store %"(Unit + str)" %arrayAccess, ptr %2, align 4
  %15 = getelementptr %"(Unit + str)", ptr %2, i32 0, i32 0
  %16 = load %"(Unit + str)", ptr %15, align 4
  switch %"(Unit + str)" %16, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %accessAfter
  %17 = getelementptr %"(Unit + str)", ptr %2, i32 0, i32 1
  %18 = load %Unit, ptr %17, align 1
  store %Unit %18, ptr %u, align 1
  ret ptr @0

tagBranch2:                                       ; preds = %accessAfter
  %19 = getelementptr %"(Unit + str)", ptr %2, i32 0, i32 1
  %20 = load ptr, ptr %19, align 8
  store ptr %20, ptr %s, align 8
  %s2 = load ptr, ptr %s, align 8
  ret ptr %s2

match-cont:                                       ; preds = %accessAfter
  unreachable
}

define %Unit @program(ptr %0) {
entry:
  %j = alloca ptr, align 8
  %i = alloca ptr, align 8
  %y = alloca i32, align 4
  %x = alloca i32, align 4
  %array = alloca [4 x ptr], align 8
  %d = alloca ptr, align 8
  %c = alloca ptr, align 8
  %b = alloca ptr, align 8
  %a = alloca ptr, align 8
  %io = alloca ptr, align 8
  store ptr %0, ptr %io, align 8
  %1 = call i32 (...) @printf(ptr @1)
  store ptr @2, ptr %a, align 8
  store ptr @3, ptr %b, align 8
  store ptr @4, ptr %c, align 8
  store ptr @5, ptr %d, align 8
  %2 = getelementptr [4 x ptr], ptr %array, i32 0, i32 0
  %a1 = load ptr, ptr %a, align 8
  store ptr %a1, ptr %2, align 8
  %3 = getelementptr [4 x ptr], ptr %array, i32 0, i32 1
  %b2 = load ptr, ptr %b, align 8
  store ptr %b2, ptr %3, align 8
  %4 = getelementptr [4 x ptr], ptr %array, i32 0, i32 2
  %c3 = load ptr, ptr %c, align 8
  store ptr %c3, ptr %4, align 8
  %5 = getelementptr [4 x ptr], ptr %array, i32 0, i32 3
  %d4 = load ptr, ptr %d, align 8
  store ptr %d4, ptr %5, align 8
  store i32 0, ptr %x, align 4
  store i32 0, ptr %y, align 4
  %x5 = load i32, ptr %x, align 4
  %6 = icmp slt i32 %x5, 4
  br i1 %6, label %loop, label %rest20

loop:                                             ; preds = %rest, %entry
  store i32 0, ptr %y, align 4
  %y6 = load i32, ptr %y, align 4
  %7 = icmp slt i32 %y6, 4
  br i1 %7, label %loop7, label %rest

loop7:                                            ; preds = %loop7, %loop
  %array8 = load [4 x ptr], ptr %array, align 8
  %x9 = load i32, ptr %x, align 4
  %8 = call ptr @"programs::test7::accessor"([4 x ptr] %array8, i32 %x9)
  store ptr %8, ptr %i, align 8
  %array10 = load [4 x ptr], ptr %array, align 8
  %y11 = load i32, ptr %y, align 4
  %9 = call ptr @"programs::test7::accessor"([4 x ptr] %array10, i32 %y11)
  store ptr %9, ptr %j, align 8
  %x12 = load i32, ptr %x, align 4
  %y13 = load i32, ptr %y, align 4
  %i14 = load ptr, ptr %i, align 8
  %j15 = load ptr, ptr %j, align 8
  %10 = icmp eq ptr %i14, %j15
  %11 = call i32 (...) @printf(ptr @6, i32 %x12, i32 %y13, i1 %10)
  %y16 = load i32, ptr %y, align 4
  %12 = add nsw i32 %y16, 1
  store i32 %12, ptr %y, align 4
  %y17 = load i32, ptr %y, align 4
  %13 = icmp slt i32 %y17, 4
  br i1 %13, label %loop7, label %rest

rest:                                             ; preds = %loop7, %loop
  %x18 = load i32, ptr %x, align 4
  %14 = add nsw i32 %x18, 1
  store i32 %14, ptr %x, align 4
  %x19 = load i32, ptr %x, align 4
  %15 = icmp slt i32 %x19, 4
  br i1 %15, label %loop, label %rest20

rest20:                                           ; preds = %rest, %entry
  %16 = sub nsw i32 0, 1
  %17 = call ptr @malloc(i32 4)
  store i32 %16, ptr %17, align 4
  %18 = load ptr, ptr %io, align 8
  %19 = call %Unit @_WriteChannel(ptr %18, ptr %17)
  ret %Unit zeroinitializer
}

declare i32 @printf(...)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
