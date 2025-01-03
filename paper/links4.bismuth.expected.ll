; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [16 x i8] c"bool (correct)\0A\00", align 1
@1 = private unnamed_addr constant [17 x i8] c"int (incorrect)\0A\00", align 1
@2 = private unnamed_addr constant [2 x i8] c"5\00", align 1

define %Unit @foo(ptr %0) {
entry:
  %b = alloca ptr, align 8
  %a = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load ptr, ptr %2, align 8
  %4 = call %Unit @free(ptr %2)
  store ptr %3, ptr %a, align 8
  %5 = load ptr, ptr %c, align 8
  %6 = call ptr @_ReadLinearChannel(ptr %5)
  %7 = load ptr, ptr %6, align 8
  %8 = call %Unit @free(ptr %6)
  store ptr %7, ptr %b, align 8
  %9 = load ptr, ptr %a, align 8
  %10 = call i32 @_ReadLinearProjection(ptr %9)
  switch i32 %10, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %entry
  %11 = load ptr, ptr %b, align 8
  %12 = call %Unit @_WriteProjection(ptr %11, i32 1)
  %13 = load ptr, ptr %a, align 8
  %14 = call ptr @_ReadLinearChannel(ptr %13)
  %15 = load i1, ptr %14, align 1
  %16 = call %Unit @free(ptr %14)
  %17 = call ptr @malloc(i32 1)
  store i1 %15, ptr %17, align 1
  %18 = load ptr, ptr %b, align 8
  %19 = call %Unit @_WriteChannel(ptr %18, ptr %17)
  %20 = call i32 (ptr, ...) @printf(ptr @0)
  br label %match-cont

tagBranch2:                                       ; preds = %entry
  %21 = load ptr, ptr %b, align 8
  %22 = call %Unit @_WriteProjection(ptr %21, i32 2)
  %23 = load ptr, ptr %a, align 8
  %24 = call ptr @_ReadLinearChannel(ptr %23)
  %25 = load i32, ptr %24, align 4
  %26 = call %Unit @free(ptr %24)
  %27 = call ptr @malloc(i32 4)
  store i32 %25, ptr %27, align 4
  %28 = load ptr, ptr %b, align 8
  %29 = call %Unit @_WriteChannel(ptr %28, ptr %27)
  %30 = call i32 (ptr, ...) @printf(ptr @1)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %entry
  %31 = call ptr @malloc(i32 8)
  store ptr @2, ptr %31, align 8
  %32 = load ptr, ptr %a, align 8
  %33 = call %Unit @_WriteChannel(ptr %32, ptr %31)
  ret %Unit zeroinitializer
}

define %Unit @bar1(ptr %0) {
entry:
  %xyz = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call %Unit @_WriteProjection(ptr %1, i32 1)
  %3 = call ptr @malloc(i32 1)
  store i1 false, ptr %3, align 1
  %4 = load ptr, ptr %c, align 8
  %5 = call %Unit @_WriteChannel(ptr %4, ptr %3)
  %6 = load ptr, ptr %c, align 8
  %7 = call ptr @_ReadLinearChannel(ptr %6)
  %8 = load ptr, ptr %7, align 8
  %9 = call %Unit @free(ptr %7)
  store ptr %8, ptr %xyz, align 8
  ret %Unit zeroinitializer
}

define %Unit @bar2(ptr %0) {
entry:
  %i = alloca i32, align 4
  %b = alloca i1, align 1
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call i32 @_ReadLinearProjection(ptr %1)
  switch i32 %2, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %entry
  %3 = load ptr, ptr %c, align 8
  %4 = call ptr @_ReadLinearChannel(ptr %3)
  %5 = load i1, ptr %4, align 1
  %6 = call %Unit @free(ptr %4)
  store i1 %5, ptr %b, align 1
  br label %match-cont

tagBranch2:                                       ; preds = %entry
  %7 = load ptr, ptr %c, align 8
  %8 = call ptr @_ReadLinearChannel(ptr %7)
  %9 = load i32, ptr %8, align 4
  %10 = call %Unit @free(ptr %8)
  store i32 %9, ptr %i, align 4
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %entry
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %linker = alloca ptr, align 8
  %l2 = alloca ptr, align 8
  %l1 = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @_Execute(ptr @bar1)
  store ptr %1, ptr %l1, align 8
  %2 = call ptr @_Execute(ptr @bar2)
  store ptr %2, ptr %l2, align 8
  %3 = call ptr @_Execute(ptr @foo)
  store ptr %3, ptr %linker, align 8
  %l11 = load ptr, ptr %l1, align 8
  %4 = call ptr @malloc(i32 8)
  store ptr %l11, ptr %4, align 8
  %5 = load ptr, ptr %linker, align 8
  %6 = call %Unit @_WriteChannel(ptr %5, ptr %4)
  %l22 = load ptr, ptr %l2, align 8
  %7 = call ptr @malloc(i32 8)
  store ptr %l22, ptr %7, align 8
  %8 = load ptr, ptr %linker, align 8
  %9 = call %Unit @_WriteChannel(ptr %8, ptr %7)
  %10 = call ptr @malloc(i32 4)
  store i32 0, ptr %10, align 4
  %11 = load ptr, ptr %c, align 8
  %12 = call %Unit @_WriteChannel(ptr %11, ptr %10)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

declare i32 @_ReadLinearProjection(ptr)

declare %Unit @_WriteProjection(ptr, i32)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_Execute(ptr)
